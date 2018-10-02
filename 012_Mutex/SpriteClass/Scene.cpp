#include "stdafx.h"
#include "Device.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Sprite.h"

#include <thread>
#include <mutex>

Rect* rect;
Sprite* sprite;

bool bSprite = false;
bool bJoin = false;

thread t;
mutex m;

void LoadSprite()
{
	sprite = new Sprite(L"WallPaper.jpg");
	sprite->Position(0, 0);
	sprite->Scale(1280, 720);
	
	m.lock();
	bSprite = true;
	m.unlock();

	// 지연 로딩을 할때 쓰는 함수
	//Device->CreateDeferredContext()
	// Texture 불러오는거
	//D3DX11CreateShaderResourceViewFromFile()
}

thread t2;
mutex m2;
int value = 0;
void Add()
{
	for(int i=0; i<10000; i++) 
	{
		m2.lock();
		value++;
		m2.unlock();

		Sleep(10);
	}
}

void InitScene()
{	
	rect = new Rect();
	rect->Position(0, 200);
	rect->Scale(300, 100);
	rect->Color(0, 1, 0, 1);
	
	t2 = thread(Add);
	// 람다식
	//t2 = thread([&]()
	//{
	//	for (int i = 0; i<10000; i++)
	//	{
	//		m2.lock();
	//		value++;
	//		m2.unlock();

	//		Sleep(10);
	//	}
	//});
}

void DestroyScene()
{
	t2.join();

	SAFE_DELETE(rect);
	SAFE_DELETE(sprite);
}

void Update()
{
	if (Key->Down(VK_SPACE)) {
		//LoadSprite();

		//thread t(LoadSprite);
		//t.join();

		t = thread(LoadSprite);
	}

	if (Key->Down(VK_RETURN)) {
		t2.join();
	}

	rect->Update();

	bool temp;
	m.lock();
	{
		temp = bSprite;
	}
	m.unlock();

	if (temp == true) {
		if (bJoin == false) {
			t.join();

			bJoin = true;
		}

		sprite->Update();
	}
}

void Render()
{
	rect->Render();	

	if (bSprite == true)
		sprite->Render();

	static int i = 0;
	ImGui::Text("Time : %d", i++);

	int temp;

	m2.lock();
	temp = value;
	m2.unlock();

	ImGui::ProgressBar((float)temp / 10000.0f);

	//if(temp >= 10000)
	//	t2.join();
}

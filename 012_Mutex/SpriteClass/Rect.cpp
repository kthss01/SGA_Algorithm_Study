#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{
	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);


	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create ColorBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(ColorBufferDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = Device->CreateBuffer(&desc, NULL, &colorBuffer);
		assert(SUCCEEDED(hr));
	}

	shader = new Shader(L"Rect.hlsl");
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 1);
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);
	
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(colorBuffer);
}

void Rect::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Rect::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Rect::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Rect::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Rect::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Rect::Color(D3DXCOLOR vec)
{
	colorBufferData.Color = vec;
}

void Rect::Update()
{
	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0);

	shader->World(S * T);
}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;	

	shader->SetBuffers();

	DeviceContext->UpdateSubresource(colorBuffer, 0, NULL, &colorBufferData, 0, 0);
	DeviceContext->PSSetConstantBuffers(0, 1, &colorBuffer);

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->Draw(VertexCount, 0);
}

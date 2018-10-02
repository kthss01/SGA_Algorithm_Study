#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(wstring file)
{
	vertices = new Vertex[VertexCount];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(0.0f, 1.0f);
	vertices[1].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[2].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].Uv = D3DXVECTOR2(1.0f, 1.0f);
	vertices[4].Uv = D3DXVECTOR2(0.0f, 0.0f);
	vertices[5].Uv = D3DXVECTOR2(1.0f, 0.0f);


	HRESULT hr;

	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * VertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	shader = new Shader(L"Sprite.hlsl");
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shader->CreateInputLayout(LayoutDesc, 2);

	
	wstring textureFile = L"../_Textures/" + file;
	D3DX11CreateShaderResourceViewFromFile
	(
		Device, textureFile.c_str(), NULL, NULL, &srv, &hr
	);
	assert(SUCCEEDED(hr));
}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_DELETE_ARRAY(vertices);
	
	SAFE_RELEASE(vertexBuffer);
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 vec)
{
	scale = vec;
}

void Sprite::Update()
{
	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0);

	shader->World(S * T);
}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;	

	shader->SetBuffers();

	DeviceContext->PSSetShaderResources(0, 1, &srv);

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->Draw(VertexCount, 0);
}

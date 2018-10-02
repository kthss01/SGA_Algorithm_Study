#pragma once

class Rect
{
public:
	Rect();
	~Rect();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Color(float r, float g, float b, float a = 1.0f);
	void Color(D3DXCOLOR vec);


	void Update();
	void Render();

private:
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	Shader* shader;

private:
	struct Vertex
	{
		Vertex() {}

		Vertex(D3DXVECTOR3 position) : Position(position)
		{

		}

		D3DXVECTOR3 Position;
	};

	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

private:
	struct ColorBufferDesc
	{
		ColorBufferDesc() : Color(0, 0, 0, 1)
		{
			
		}

		ColorBufferDesc(D3DXCOLOR color) : Color(color)
		{

		}

		D3DXCOLOR Color;
	} colorBufferData;

	ID3D11Buffer* colorBuffer;
};
#pragma once

class Sprite
{
public:
	Sprite(wstring file);
	~Sprite();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void Update();
	void Render();

private:
	const UINT VertexCount = 6;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	Shader* shader;
	ID3D11ShaderResourceView* srv;

private:
	struct Vertex
	{
		Vertex() {}

		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;
};
#include "Model.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"

#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

XX::Model::Model(std::string file_name)
{
	MODEL model;
	LoadObj(file_name.c_str(), &model);



	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * model.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = model.VertexArray;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * model.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = model.IndexArray;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	// サブセット設定
	{
		m_SubsetArray = new SUBSET[model.SubsetNum];
		m_SubsetNum = model.SubsetNum;

		for (unsigned int i = 0; i < model.SubsetNum; i++)
		{
			m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
			m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;

			m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;

			m_SubsetArray[i].Material.Texture = NULL;

			D3DX11CreateShaderResourceViewFromFile(
				ExtraX::graphics.device,
				model.SubsetArray[i].Material.TextureName,
				NULL,
				NULL,
				&m_SubsetArray[i].Material.Texture,
				NULL);

			assert(m_SubsetArray[i].Material.Texture);

		}
	}

	delete[] model.VertexArray;
	delete[] model.IndexArray;
	delete[] model.SubsetArray;
}

XX::Model::~Model()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		m_SubsetArray[i].Material.Texture->Release();
	}

	delete[] m_SubsetArray;
}

void XX::Model::Render3D()
{

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, game_object->transform->scale.x, game_object->transform->scale.y, game_object->transform->scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, game_object->transform->rotation.x, game_object->transform->rotation.y, game_object->transform->rotation.z);
	D3DXMatrixTranslation(&trans, game_object->transform->position.x, game_object->transform->position.y, game_object->transform->position.z);
	world = scale * rot * trans;
	ExtraX::graphics.SetWorldMatrix(&world);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	ExtraX::graphics.device_context->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		// マテリアル設定
		ExtraX::graphics.SetMaterial(m_SubsetArray[i].Material.Material);

		// テクスチャ設定
		ExtraX::graphics.device_context->PSSetShaderResources(0, 1, &m_SubsetArray[i].Material.Texture);

		// ポリゴン描画
		ExtraX::graphics.device_context->DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
	}
}

void XX::Model::LoadObj(const char* FileName, MODEL* Model)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);

	D3DXVECTOR3* positionArray;
	D3DXVECTOR3* normalArray;
	D3DXVECTOR2* texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL* materialArray = NULL;
	unsigned int	materialNum = 0;

	char str[256];
	char* s;
	char c;


	FILE* file;
	file = fopen(FileName, "rt");
	assert(file);



	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;

			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new D3DXVECTOR3[positionNum];
	normalArray = new D3DXVECTOR3[normalNum];
	texcoordArray = new D3DXVECTOR2[texcoordNum];


	Model->VertexArray = new VERTEX_3D[vertexNum];
	Model->VertexNum = vertexNum;

	Model->IndexArray = new unsigned int[indexNum];
	Model->IndexNum = indexNum;

	Model->SubsetArray = new SUBSET[subsetNum];
	Model->SubsetNum = subsetNum;




	//要素読込
	D3DXVECTOR3* position = positionArray;
	D3DXVECTOR3* normal = normalArray;
	D3DXVECTOR2* texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//マテリアルファイル
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//オブジェクト名
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//頂点座標
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//法線
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//テクスチャ座標
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//マテリアル
			fscanf(file, "%s", str);

			if (sc != 0)
				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;

			Model->SubsetArray[sc].StartIndex = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].Name) == 0)
				{
					Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//面
			in = 0;

			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				Model->VertexArray[vc].position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok(NULL, "/");
					Model->VertexArray[vc].tex_coord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Model->VertexArray[vc].normal = normalArray[atoi(s) - 1];

				Model->VertexArray[vc].diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

				Model->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if (sc != 0)
		Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;


	fclose(file);


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

void XX::Model::LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum)
{

	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);



	char str[256];

	FILE* file;
	file = fopen(FileName, "rt");
	assert(file);

	MODEL_MATERIAL* materialArray;
	unsigned int materialNum = 0;

	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;


		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	}


	//メモリ確保
	materialArray = new MODEL_MATERIAL[materialNum];


	//要素読込
	int mc = -1;

	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;


		if (strcmp(str, "newmtl") == 0)
		{
			//マテリアル名
			mc++;
			fscanf(file, "%s", materialArray[mc].Name);
			strcpy(materialArray[mc].TextureName, "");

			materialArray[mc].Material.emission.r = 0.0f;
			materialArray[mc].Material.emission.g = 0.0f;
			materialArray[mc].Material.emission.b = 0.0f;
			materialArray[mc].Material.emission.a = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			//アンビエント
			fscanf(file, "%f", &materialArray[mc].Material.ambient.r);
			fscanf(file, "%f", &materialArray[mc].Material.ambient.g);
			fscanf(file, "%f", &materialArray[mc].Material.ambient.b);
			materialArray[mc].Material.ambient.a = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//ディフューズ
			fscanf(file, "%f", &materialArray[mc].Material.diffuse.r);
			fscanf(file, "%f", &materialArray[mc].Material.diffuse.g);
			fscanf(file, "%f", &materialArray[mc].Material.diffuse.b);
			materialArray[mc].Material.diffuse.a = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//スペキュラ
			fscanf(file, "%f", &materialArray[mc].Material.specular.r);
			fscanf(file, "%f", &materialArray[mc].Material.specular.g);
			fscanf(file, "%f", &materialArray[mc].Material.specular.b);
			materialArray[mc].Material.specular.a = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//スペキュラ強度
			fscanf(file, "%f", &materialArray[mc].Material.shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//アルファ
			fscanf(file, "%f", &materialArray[mc].Material.diffuse.a);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//テクスチャ
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			strcat(materialArray[mc].TextureName, path);
		}
	}

	fclose(file);

	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}

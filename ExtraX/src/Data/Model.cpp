#include "Model.h"
#include "../XX.h"
#include "Data.h"

#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")


XX::Model::Model(std::string file_name)
{
	XXModel model;
	_LoadObj(file_name.c_str(), &model);


	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(XXVertex3D) * model.vertex_num;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = model.vertex_array;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _vertex_buffer.GetAddressOf());
	}


	// �C���f�b�N�X�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * model.index_num;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = model.index_array;

		ExtraX::graphics.device->CreateBuffer(&bd, &sd, _index_buffer.GetAddressOf());
	}

	// �T�u�Z�b�g�ݒ�
	{
		_subset_array = new XXSubset[model.subset_num];
		_subset_num = model.subset_num;

		for (unsigned int i = 0; i < model.subset_num; i++)
		{
			_subset_array[i].start_index = model.subset_array[i].start_index;
			_subset_array[i].index_num = model.subset_array[i].index_num;

			_subset_array[i].material.material = model.subset_array[i].material.material;

			_subset_array[i].material.texture = NULL;

			_subset_array[i].material.texture = XX::Texture::Load(model.subset_array[i].material.texture_name);

		}
	}

	delete[] model.vertex_array;
	delete[] model.index_array;
	delete[] model.subset_array;

}

void XX::Model::Apply()
{

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(XXVertex3D);
	UINT offset = 0;

	ExtraX::graphics.device_context->IASetVertexBuffers(0, 1, _vertex_buffer.GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	ExtraX::graphics.device_context->IASetIndexBuffer(_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	ExtraX::graphics.device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	for (unsigned int i = 0; i < _subset_num; i++)
	{
		// �}�e���A���ݒ�
		ExtraX::graphics.SetMaterial(_subset_array[i].material.material);

		// �e�N�X�`���ݒ�
		_subset_array[i].material.texture->Apply();

		// �|���S���`��
		ExtraX::graphics.device_context->DrawIndexed(_subset_array[i].index_num, _subset_array[i].start_index, 0);
	}


}

XX::Model::~Model()
{
	delete[] _subset_array;
}

void XX::Model::_LoadObj(const char* file_name, XXModel* model)
{
	char dir[MAX_PATH];
	strcpy(dir, file_name);
	PathRemoveFileSpec(dir);

	XXVector3* positionArray;
	XXVector3* normalArray;
	XXVector2* texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	XXModelMaterial* materialArray = NULL;
	unsigned int	materialNum = 0;

	char str[256];
	char* s;
	char c;


	FILE* file;
	file = fopen(file_name, "rt");
	assert(file);



	//�v�f���J�E���g
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

			//�l�p�͎O�p�ɕ���
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//�������m��
	positionArray = new XXVector3[positionNum];
	normalArray = new XXVector3[normalNum];
	texcoordArray = new XXVector2[texcoordNum];


	model->vertex_array = new XXVertex3D[vertexNum];
	model->vertex_num = vertexNum;

	model->index_array = new unsigned int[indexNum];
	model->index_num = indexNum;

	model->subset_array = new XXSubset[subsetNum];
	model->subset_num = subsetNum;




	//�v�f�Ǎ�
	XXVector3* position = positionArray;
	XXVector3* normal = normalArray;
	XXVector2* texcoord = texcoordArray;

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
			//�}�e���A���t�@�C��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			_LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//�I�u�W�F�N�g��
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//���_���W
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//�@��
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//�e�N�X�`�����W
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//�}�e���A��
			fscanf(file, "%s", str);

			if (sc != 0)
				model->subset_array[sc - 1].index_num = ic - model->subset_array[sc - 1].start_index;

			model->subset_array[sc].start_index = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].name) == 0)
				{
					model->subset_array[sc].material.material = materialArray[i].material;
					strcpy(model->subset_array[sc].material.texture_name, materialArray[i].texture_name);
					strcpy(model->subset_array[sc].material.name, materialArray[i].name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//��
			in = 0;

			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				model->vertex_array[vc].position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok(NULL, "/");
					model->vertex_array[vc].tex_coord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				model->vertex_array[vc].normal = normalArray[atoi(s) - 1];

				model->vertex_array[vc].diffuse = XXVector4(1.0f, 1.0f, 1.0f, 1.0f);

				model->index_array[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
			{
				model->index_array[ic] = vc - 4;
				ic++;
				model->index_array[ic] = vc - 2;
				ic++;
			}
		}
	}


	if (sc != 0)
		model->subset_array[sc - 1].index_num = ic - model->subset_array[sc - 1].start_index;


	fclose(file);


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

void XX::Model::_LoadMaterial(const char* file_name, XXModelMaterial** material_array, unsigned int* material_num)
{
	char dir[MAX_PATH];
	strcpy(dir, file_name);
	PathRemoveFileSpec(dir);



	char str[256];

	FILE* file;
	file = fopen(file_name, "rt");
	assert(file);

	XXModelMaterial* materialArray;
	unsigned int materialNum = 0;

	//�v�f���J�E���g
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


	//�������m��
	materialArray = new XXModelMaterial[materialNum];


	//�v�f�Ǎ�
	int mc = -1;

	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;


		if (strcmp(str, "newmtl") == 0)
		{
			//�}�e���A����
			mc++;
			fscanf(file, "%s", materialArray[mc].name);
			strcpy(materialArray[mc].texture_name, "");

			materialArray[mc].material.emission.r = 0.0f;
			materialArray[mc].material.emission.g = 0.0f;
			materialArray[mc].material.emission.b = 0.0f;
			materialArray[mc].material.emission.a = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			//�A���r�G���g
			fscanf(file, "%f", &materialArray[mc].material.ambient.r);
			fscanf(file, "%f", &materialArray[mc].material.ambient.g);
			fscanf(file, "%f", &materialArray[mc].material.ambient.b);
			materialArray[mc].material.ambient.a = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//�f�B�t���[�Y
			fscanf(file, "%f", &materialArray[mc].material.diffuse.r);
			fscanf(file, "%f", &materialArray[mc].material.diffuse.g);
			fscanf(file, "%f", &materialArray[mc].material.diffuse.b);
			materialArray[mc].material.diffuse.a = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//�X�y�L����
			fscanf(file, "%f", &materialArray[mc].material.specular.r);
			fscanf(file, "%f", &materialArray[mc].material.specular.g);
			fscanf(file, "%f", &materialArray[mc].material.specular.b);
			materialArray[mc].material.specular.a = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//�X�y�L�������x
			fscanf(file, "%f", &materialArray[mc].material.shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//�A���t�@
			fscanf(file, "%f", &materialArray[mc].material.diffuse.a);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//�e�N�X�`��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			strcat(materialArray[mc].texture_name, path);
		}
	}

	fclose(file);

	*material_array = materialArray;
	*material_num = materialNum;
}

#include "Mesh.h"
#include "../XX.h"
#include "../GameObjects/GameObject.h"
#include "../Components/Transform.h"


#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

XX::Mesh::Mesh(std::string file_name)
{
	_model = Model::Load(file_name);
}

XX::Mesh::~Mesh()
{
	
}

void XX::Mesh::Render3D()
{
	game_object->transform->SetWorldMatrix();


	_model->Apply();
	
}


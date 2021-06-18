#pragma once
#ifndef _EXTRA_X_TYPE_H_
#define _EXTRA_X_TYPE_H_



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx9.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#pragma warning(pop)


#include <functional>

#include "Texture.h"
#include "Shader.h"
#include "Vector.h"



namespace XX
{
	struct VERTEX_3D
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR4 diffuse;
		D3DXVECTOR2 tex_coord;
	};



	struct MATERIAL
	{
		D3DXCOLOR	ambient;
		D3DXCOLOR	diffuse;
		D3DXCOLOR	specular;
		D3DXCOLOR	emission;
		float		shininess;
		float		dummy[3];
	};



	struct LIGHT
	{
		BOOL		enable;
		BOOL		dummy[3];
		D3DXVECTOR4	direction;
		D3DXCOLOR	diffuse;
		D3DXCOLOR	ambient;
	};


	


	class Scene;
	class GameObject;
	class Component;
	class Transform;
}



#endif // !_EXTRA_X_TYPE_H_

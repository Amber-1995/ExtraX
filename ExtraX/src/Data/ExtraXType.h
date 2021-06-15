#pragma once
#ifndef _EXTRA_X_TYPE_H_
#define _EXTRA_X_TYPE_H_

#include <D3D11.h>
#include <D3DX11.h>
#include <d3dx9.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;

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

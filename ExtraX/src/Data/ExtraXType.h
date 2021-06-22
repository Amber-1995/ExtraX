#pragma once
#ifndef _EXTRA_X_TYPE_H_
#define _EXTRA_X_TYPE_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <wrl.h>

#include "Vector.h"
#include "Color.h"


#define DEFAULT_TEXTRUE "Assets\\Textures\\default.png"


namespace XX
{
	struct XXVertex3D
	{
		XXVector3 position;
		XXVector3 normal;
		XXVector4 diffuse;
		XXVector2 tex_coord;
	};

	struct XXMaterial
	{
		XXColor	ambient;
		XXColor	diffuse;
		XXColor	specular;
		XXColor	emission;
		float	shininess;
		float	dummy[3];
	};

	struct XXLight
	{
		int		enable;
		int		dummy[3];
		XXVector4	direction;
		XXColor		diffuse;
		XXColor		ambient;
	};

	class Scene;
	class GameObject;
	class Component;
	class Transform;

	typedef Microsoft::WRL::ComPtr<ID3D11Device> ID3D11DevicePtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> ID3D11DeviceContextPtr;
	typedef Microsoft::WRL::ComPtr<IDXGISwapChain> IDXGISwapChainPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView> ID3D11RenderTargetViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView> ID3D11DepthStencilViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Buffer> ID3D11BufferPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ID3D11DepthStencilStatePtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> ID3D11Texture2DPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11VertexShader> ID3D11VertexShaderPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11InputLayout> ID3D11InputLayoutPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11PixelShader> ID3D11PixelShaderPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ID3D11ShaderResourceViewPtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Resource> ID3D11ResourcePtr;
	typedef Microsoft::WRL::ComPtr<ID3D11Buffer> ID3D11BufferPtr;


	typedef std::shared_ptr<Scene> ScenePtr;
	typedef std::shared_ptr<GameObject> GameObjectPtr;
	typedef std::shared_ptr<Component> ComponentPtr;
	typedef std::shared_ptr<Transform> TransformPtr;
}



#endif // !_EXTRA_X_TYPE_H_

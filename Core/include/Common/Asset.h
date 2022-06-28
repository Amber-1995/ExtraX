#ifndef CORE_ASSET_H
#define CORE_ASSET_H

#include "ExtraX.h"

namespace XX
{
	
	class _Texture
	{
	public:
		virtual void SetToDiffuse(int thread) = 0;
		virtual void SetToNormal(int thread) = 0;
	};

	class _Model
	{
	public:
		virtual void Set(int thread = 0) = 0;
	};

	class _Shader
	{
	public:
		virtual void Set(size_t thread) = 0;
	};

	using Texture = std::shared_ptr<_Texture>;

	using Model = std::shared_ptr<_Model>;

	using Shader = std::shared_ptr<_Shader>;


	XXAPI class AssetImporter
	{
		friend class ExtraX;
	private:
		std::unordered_map<std::string, Texture> _textures;
		std::unordered_map<std::string, Model> _models;
		std::unordered_map<std::string, Shader> _shaders;
		
		AssetImporter() = default;
		virtual ~AssetImporter() = default;

	public:
		Texture ImportTexture(const std::string& file);
		Model ImportModel(const std::string& file);
		Shader ImportShader(const std::string& file);
		
		
	};

}

#endif // !CORE_ASSET_HPP


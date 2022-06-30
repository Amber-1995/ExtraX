#ifndef CORE_EXTRAX_H
#define CORE_EXTRAX_H

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <stdint.h>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <DirectXMath.h>
#include <fstream>


#ifdef XX_DLL_EXPORT
	#define XXAPI __declspec(dllexport)
#else
	#ifdef XX_DLL_IMPORT
		#define XXAPI __declspec(dllimport)
	#else
		#define XXAPI
	#endif // XXCORE_DLL_IMPORT
#endif // XXCORE_DLL_EXPORT


#define THREAD_NUM (6)
#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)


namespace XX
{

	class Graphics;
	class AssetImporter;
	class Input;
	class Window;
	class Timer;

	XXAPI class ExtraX
	{
	private:
		inline static bool _running = true;
		inline static Graphics* _graphics = nullptr;
		inline static AssetImporter* _asset_importer = nullptr;
		inline static Input* _input = nullptr;
		inline static Window* _window = nullptr;
		inline static Timer* _timer = nullptr;

		ExtraX() = delete;
	public:
		inline static const bool& running = _running;
		inline static Graphics* const& graphics = _graphics;
		inline static AssetImporter* const& asset_importer = _asset_importer;
		inline static Input* const& input = _input;
		inline static Window* const& window = _window;
		inline static Timer* const& timer = _timer;

		static void Exit();

		static void Initialize(const std::string& title);

		static void UnInitialize();
	};

	XXAPI class Helper
	{
	private:
		Helper() = delete;
	public:
		static std::string GetDirectoryFromPath(const std::string& filepath);
		static std::string GetFileExtension(const std::string& filename);
		static std::wstring ToWide(const std::string& narrow);
		static std::string ToNarrow(const std::wstring& wide);

		template<class IT>
		static void Next(IT& it, IT end, size_t n);
	};

	namespace Game
	{
		class Scene;
	}
	

	XXAPI class ThreadManager
	{
	private:
		size_t _thread_num;

		std::vector<std::atomic<bool>> _signal;

		std::vector<std::thread*> _thread;

		void _SendCompletionSignal(size_t n);

		void _WaitBeginSignal(size_t n);

		static  void _ProcessPerThread(ThreadManager* thread_manager, Game::Scene* scene, void(Game::Scene::* Process)(size_t thread_num), size_t thread_num);

	public:
		ThreadManager(size_t thread_num);

		virtual ~ThreadManager();

		void Start(Game::Scene* scene, void(Game::Scene::* ProcessPerThread)(size_t thread_num));

		void SendBeginSignal();

		void WaitCompletionSignal();

	};

	template<class IT>
	inline void Helper::Next(IT& it, IT end, size_t n)
	{
		while (it != end && n > 0) {
			--n;
			++it;
		}
	}

	
	
}



#endif // !CORE_EXTRAX_H

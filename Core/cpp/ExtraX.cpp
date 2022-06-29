#include "Common/ExtraX.h"
#include "Common/Graphics.h"
#include "Common/Asset.h"
#include "Common/Input.h"
#include "Common/Window.h"
#include "Common/Timer.h"


namespace XX
{
	void ExtraX::Exit()
	{
		_running = false;
	}
	
	void ExtraX::UnInitialize()
	{
		delete _graphics;
		delete _asset_importer;
		delete _input;
		delete _window;
		delete _timer;
	}

	std::string Helper::GetDirectoryFromPath(const std::string& filepath)
	{
		size_t off1 = filepath.find_last_of('\\');
		size_t off2 = filepath.find_last_of('/');
		if (off1 == std::string::npos && off2 == std::string::npos)
		{
			return "";
		}
		if (off1 == std::string::npos)
		{
			return filepath.substr(0, off2);
		}
		if (off2 == std::string::npos)
		{
			return filepath.substr(0, off1);
		}

		return filepath.substr(0, std::max(off1, off2));
	}

	std::string Helper::GetFileExtension(const std::string& filename)
	{
		size_t off = filename.find_last_of('.');
		if (off == std::string::npos)
		{
			return {};
		}
		return std::string(filename.substr(off + 1));
	}

	std::wstring Helper::ToWide(const std::string& narrow)
	{
		wchar_t wide[512];
		mbstowcs_s(nullptr, wide, narrow.c_str(), _TRUNCATE);
		return wide;
	}

	std::string Helper::ToNarrow(const std::wstring& wide)
	{
		char narrow[512];
		wcstombs_s(nullptr, narrow, wide.c_str(), _TRUNCATE);
		return narrow;
	}


	ThreadManager::ThreadManager(void(*func)(size_t n), size_t thread_num):
		_thread_num(thread_num)
	{
		_signal = new std::atomic<bool>[_thread_num];
		for (int i = 0; i < _thread_num; ++i)
		{
			_signal[i] = false;
		}
		 
		_thread = new std::thread * [_thread_num];
		for (int i = 0; i < _thread_num; ++i)
		{
			_thread[i] = new std::thread(func, i);
		}

	}

	ThreadManager::~ThreadManager()
	{
		delete[] _signal;

		for (int i = 0; i < _thread_num; ++i)
		{
			_thread[i]->join();
			delete _thread[i];
		}
		delete _thread;
	}

	void ThreadManager::SendCompletionSignal(size_t n)
	{
		_signal[n] = false;
	}

	void ThreadManager::SendBeginSignal()
	{
		for (int i = 0; i < _thread_num; ++i)
		{
			_signal[i] = true;
		}
	}

	void ThreadManager::WaitCompletionSignal()
	{
		for (size_t i = 0; i < _thread_num; ++i)
		{
			while (_signal[i])
			{
				std::this_thread::yield();
			}
		}
		
	}

	void ThreadManager::WaitBeginSignal(size_t n)
	{
		while (!_signal[n] && ExtraX::running)
		{            
			std::this_thread::yield();
		}
	}
}
#include "pch.h"
#include "MovieClient.h"
#include "MovieReader.h"

using namespace System::Diagnostics;

namespace ImageUtil {
	MovieClient::MovieClient(String^ path)
	{
		// unmanaged ƒ‚ƒWƒ…[ƒ‹‚Ì‰Šú‰»
		pReader = new MovieReader(msclr::interop::marshal_as<std::string>(path));
		int width = pReader->GetWidth();
		int height = pReader->GetHeight();
		fps = pReader->GetFPS();
		Frame = gcnew ImageData(width, height, 3);
	}
	MovieClient::!MovieClient() {
		Stop();
		if(pReader != nullptr) {
			delete (MovieReader*)pReader;
			pReader = nullptr;
		}
	}
	bool MovieClient::Start() 
	{
		mut->WaitOne();
		if(pReader == nullptr || capTask != nullptr) {
			mut->ReleaseMutex();
			return false;
		}
		StopRequest = false;
		capTask = System::Threading::Tasks::Task::Run(gcnew System::Action(this, &MovieClient::CaptrureLoop));
		return true;
	}
	bool MovieClient::Stop() 
	{
		mut->WaitOne();
		if(pReader == nullptr || capTask == nullptr) {
			mut->ReleaseMutex();
			return false;
		}
		StopRequest = true;
		capTask->Wait();
		mut->ReleaseMutex();
		return true;
	}
	ImageData^ MovieClient::GetFrame() 
	{
		Frame->mutex->WaitOne();
		bool ret = pReader->Retrieve(Frame->pMat);
		Frame->mutex->ReleaseMutex();
		return ret ? Frame : nullptr;
	}
	void MovieClient::CaptrureLoop() {
		std::chrono::system_clock::time_point  start, end;
		const double interval = 1000.0 / fps;
		while (StopRequest == false) {
			start = std::chrono::system_clock::now();
			if (pReader->Grab() == true) {
				OnCapture(this);
			}
			end = std::chrono::system_clock::now();		
			double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			if(elapsed <= interval) {
				int wait = (int)(interval - elapsed);
				System::Diagnostics::Debug::WriteLine("wait(ms) =" + wait.ToString());
				System::Threading::Thread::Sleep(wait);
			}
		}
	};
}

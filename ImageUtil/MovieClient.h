#pragma once
#pragma unmanaged
#include"IMovieReader.h"
#pragma managed
#include"ImageData.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageUtil {
	public ref class MovieClient
	{
	public:
		delegate void OnCaptureDelegate(MovieClient^ hClient);
		OnCaptureDelegate^ _OnCapture;
		event OnCaptureDelegate^ OnCapture {
			void add(OnCaptureDelegate^ handler)
			{
				_OnCapture = static_cast<OnCaptureDelegate^> (Delegate::Combine(_OnCapture, handler));
			}
			void remove(OnCaptureDelegate^ handler)
			{
				_OnCapture = static_cast<OnCaptureDelegate^> (Delegate::Remove(_OnCapture, handler));
			}
			void raise(MovieClient^ hClient)
			{
				if (_OnCapture != nullptr) {
					_OnCapture->Invoke(hClient);
				}
			}
		}
	public:
		MovieClient(String^ path);
		!MovieClient();
		~MovieClient() {
			this->!MovieClient();
		}
		bool Start();
		ImageData^ GetFrame();
		bool Stop();
	private:
		void CaptrureLoop();
	private:
		IMovieReader* pReader = nullptr;
		ImageData^ Frame = nullptr;
		System::Threading::Tasks::Task^ capTask = nullptr;
		System::Threading::Mutex^ mut = gcnew System::Threading::Mutex();
		bool StopRequest = false;
		double fps = 30.0;
	};
}


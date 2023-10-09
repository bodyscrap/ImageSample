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
	private:
		System::EventHandler<ImageData^>^ _OnCapture = nullptr;
	public:
		event System::EventHandler<ImageData^>^ OnCapture {
			void add(System::EventHandler<ImageData^>^ handler)
			{
				_OnCapture = static_cast<System::EventHandler<ImageData^>^> (Delegate::Combine(_OnCapture, handler));
			}
			void remove(System::EventHandler<ImageData^>^ handler)
			{
				_OnCapture = static_cast<System::EventHandler<ImageData^>^> (Delegate::Remove(_OnCapture, handler));
			}
			void raise(Object^ sender, ImageData^ img)
			{
				if (_OnCapture != nullptr) {
					_OnCapture->Invoke(sender, img);
				}
			}
		}
		delegate void OnCaptureDelegate(IMovieReader *pReader);
	public:
		MovieClient(String^ path);
		!MovieClient();
		~MovieClient() {
			this->!MovieClient();
		}
		bool Start();
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


#include "pch.h"
#include "MovieClient.h"
#include "MovieReader.h"

namespace ImageUtil {
	MovieClient::MovieClient(String^ path)
	{
		// unmanaged モジュールの初期化
		reader = new MovieReader(msclr::interop::marshal_as<std::string>(path));
		// unmanaged モジュールにコールバックを登録
		fp = gcnew OnCaptureDelegate(this, &MovieClient::OnCaptureNative);
		gchandle = GCHandle::Alloc(fp);
		IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
		reader->SetCallback(static_cast<IMovieReader::CAPTURE_CALLBACK_TYPE>(ip.ToPointer()));
	}
	MovieClient::!MovieClient() {
		Stop();
		if(reader != nullptr) {
			delete (MovieReader*)reader;
			reader = nullptr;
		}
		gchandle.Free();
	}
	bool MovieClient::Start() 
	{
		if(reader == nullptr) {
			return false;
		}
		return reader->StartCapture();
	}
	void MovieClient::Stop() 
	{
		if(reader == nullptr) {
			return;
		}
		return reader->StopCapture();
	}
	void MovieClient::OnCaptureNative(cv::Mat *pMat) {
		if (pMat != nullptr)
		{
			OnCapture(this, gcnew ImageData(pMat));
		}
	};
}

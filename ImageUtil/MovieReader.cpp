#include "pch.h"
#include "MovieReader.h"

namespace ImageUtil {
	bool MovieReader::StartCapture() {
		if(isRunning == true) {
			return false;
		}
		else {
			isRunning = true;
			th = std::thread(&MovieReader::CaptureLoop, this);
			return true;
		}

	}
	void MovieReader::StopCapture() {
		if(isRunning == true) {
			isRunning = false;
			if (th.joinable() == true) {
				th.join();
			}
		}
	}
	void MovieReader::SetCallback(CAPTURE_CALLBACK_TYPE callback)
	{
		OnCapture = callback;
	}
	void MovieReader::RemoveCallback()
	{
		OnCapture = nullptr;
	}
	void MovieReader::CaptureLoop() {
		while (isRunning) {
			bool ret  = cap.grab();
			if (ret == false) {
				break;
			}
			ret = cap.retrieve(frame);
			if(ret == true) {
				if (OnCapture != nullptr) {
					cv::Mat *pCopy = new cv::Mat(frame.clone());
					OnCapture(pCopy);
				}
			}
		}
	}
}

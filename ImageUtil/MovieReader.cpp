#include "pch.h"
#include "MovieReader.h"

namespace ImageUtil {
	bool MovieReader::StartCapture() {
		std::lock_guard<std::mutex> lock(capMutex);
		if(isRunning == true) {
			return false;
		}
		else {
			isRunning = true;
			std::thread capth = std::thread(&MovieReader::CaptureLoop, this);
			capth.detach();
			return true;
		}

	}
	void MovieReader::StopCapture() {
		std::lock_guard<std::mutex> lock(capMutex);
		if (isRunning == true) {
			isRunning = false;
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
		while (isRunning == true) {
			bool ret = cap.grab();
			if (ret == false) {
				continue;
			}
			ret = cap.retrieve(frame);
			if (ret == true) {
				if (OnCapture != nullptr) {
					cv::Mat* pCopy = new cv::Mat(frame.clone());
					OnCapture(pCopy);
				}
			}
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
}

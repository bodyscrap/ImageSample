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
	cv::Mat* MovieReader::Retrieve() {
		cap.retrieve(frame);
		return new::cv::Mat(frame.clone());
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
			if (ret == true) {
				if (OnCapture != nullptr) {
					OnCapture(this);
				}
			}
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
}

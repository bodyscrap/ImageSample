#include "pch.h"
#include "MovieReader.h"

using namespace System::Diagnostics;

namespace ImageUtil {
	bool MovieReader::Grab() {
		std::lock_guard<std::mutex> lock(capMutex);
		if(cap.isOpened() == true) {
			return cap.grab();
		}
		else {
			return false;
		}

	}
	bool MovieReader::Retrieve(cv::Mat *pDst) {
		std::lock_guard<std::mutex> lock(capMutex);
		if(cap.isOpened() == true) {
			const bool ret = cap.retrieve(*pDst);
			return ret;
		}
		else {
			return false;
		}
		cap.retrieve(frame);
		return new::cv::Mat(frame.clone());
	}
	void MovieReader::Release() {
		std::lock_guard<std::mutex> lock(capMutex);
		cap.release();
		frame.release();
	}
}

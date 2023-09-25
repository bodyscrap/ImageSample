#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <future>
#include "IMovieReader.h"

namespace ImageUtil {
	public class MovieReader : public IMovieReader
	{
	private:
		cv::VideoCapture cap;
		cv::Mat frame;
		bool isRunning = false;
		CAPTURE_CALLBACK_TYPE OnCapture = nullptr;
		bool ret = false;
		std::mutex capMutex;
	public:
		MovieReader(std::string path)
		{
			cap = cv::VideoCapture(path);
			ret = cap.isOpened();
		}
		~MovieReader() {
			StopCapture();
			cap.release();
		}
		bool StartCapture();
		void StopCapture();
		void SetCallback(CAPTURE_CALLBACK_TYPE callback);
		void RemoveCallback();
	private:
		void CaptureLoop();
	};
}

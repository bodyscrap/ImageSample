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
		std::mutex capMutex;
	public:
		MovieReader(std::string path)
		{
			cap = cv::VideoCapture(path, cv::CAP_FFMPEG);
		}
		~MovieReader() {
			Release();
		}
		int GetWidth() {
			return (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
		}
		int GetHeight() {
			return (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		}
		double GetFPS() {
			return cap.get(cv::CAP_PROP_FPS);
		}
		bool Grab();
		bool Retrieve(cv::Mat *pDst);
		void Release();
	};
}

#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

namespace ImageUtil {
	public class IMovieReader
	{
	public:
		IMovieReader() {};
		virtual ~IMovieReader() { };
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual double GetFPS() = 0;
		virtual bool Grab() = 0;
		virtual bool Retrieve(cv::Mat *pDst) = 0;
		virtual void Release() = 0;
	};
}


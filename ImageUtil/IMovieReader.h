#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

namespace ImageUtil {
	public class IMovieReader
	{
	public:
		using CAPTURE_CALLBACK_TYPE = void(__stdcall*)(IMovieReader* pReader);
		IMovieReader() {};
		virtual ~IMovieReader() { };
		virtual bool StartCapture() = 0;
		virtual cv::Mat* Retrieve() = 0;
		virtual void StopCapture() = 0;
		virtual void SetCallback(CAPTURE_CALLBACK_TYPE callback) = 0;
		virtual void RemoveCallback() = 0;
	};
}


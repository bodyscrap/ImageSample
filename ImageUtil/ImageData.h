#pragma once
# pragma unmanaged
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
# pragma managed
#include <msclr/marshal_cppstd.h>
using namespace System;
using namespace System::Windows::Media;
using namespace System::Windows::Media::Imaging;

namespace ImageUtil {
	public ref class ImageData
	{
	public:
		ImageData(int width, int height, int channels) 
		{
			int type;
			switch (channels) {
				case 1:
					type = CV_8UC1;
					break;
				case 3:
				default:
					type = CV_8UC3;
			}
			pMat = new cv::Mat(width, height, type);
			if (pMat->empty() == false) {
				bufSize = pMat->total() * pMat->elemSize();
				stride = pMat->step1();
				GC::AddMemoryPressure(bufSize);
			}
		}
		ImageData(String^ path, int channels) 
		{
			int type;
			switch (channels) {
				case 1:
					type = cv::IMREAD_GRAYSCALE;
					break;
				case 3:
				default:
					type = cv::IMREAD_COLOR;
			}
			cv::Mat img = cv::imread(msclr::interop::marshal_as<std::string>(path), type);
			pMat = new cv::Mat(img);
			if (pMat->data != nullptr) {
				bufSize = pMat->total() * pMat->elemSize();
				stride = pMat->step1();
				GC::AddMemoryPressure(bufSize);
			}
		}
		ImageData(cv::Mat *pSrc) 
		{
			if(pSrc == nullptr)
			{
				throw gcnew ArgumentNullException("pSrc", "Mat is null");
			}
			if(pSrc->data == nullptr)
			{
				throw gcnew ArgumentNullException("pSrc", "data of Mat is null");
			}
			pMat = pSrc;
			if (pMat->data != nullptr) {
				bufSize = pMat->total() * pMat->elemSize();
				stride = pMat->step1();
				GC::AddMemoryPressure(bufSize);
			}
		}
		!ImageData() {
			if (pMat != nullptr) {
				if (pMat->empty() == false) {
					GC::RemoveMemoryPressure(bufSize);
				}
			}
            delete pMat;
            pMat = nullptr;
			bufSize = 0;
        }
		~ImageData() {
			this->!ImageData();
		}
		BitmapSource^ CreateBitmapSoruce();
	internal:
		cv::Mat* pMat = nullptr;
		int bufSize = 0;
		int stride = 0;
	};
}

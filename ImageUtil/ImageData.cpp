#include "pch.h"

#include "ImageData.h"

namespace ImageUtil {
	/// <summary>
	/// C++/CLIからBitmapImageを読み込むサンプル
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	BitmapSource^ ImageData::CreateBitmapSoruce() {
		mutex->WaitOne();
		if(pMat == nullptr)
		{
			mutex->ReleaseMutex();
			throw gcnew System::ArgumentNullException("Mat is null");
		}
		if(pMat->data == nullptr)
		{
			mutex->ReleaseMutex();
			throw gcnew System::ArgumentNullException("data of Mat is null");
		}
		PixelFormat format = (pMat->channels() == 3) ? PixelFormats::Bgr24 : PixelFormats::Gray8;
		BitmapSource^ ret = BitmapSource::Create(
			pMat->cols,
			pMat->rows,
			96,
			96,
			format,
			nullptr,
			IntPtr(pMat->data),
			bufSize,
			stride
		);
		mutex->ReleaseMutex();
		return ret;
	}
}

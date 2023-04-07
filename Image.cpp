#include "Image.h"

namespace Dithering
{
	bool Image::openImage(const std::string& path)
	{
		image_.load(path.c_str());

		if (!image_)
		{
			return false;
		}

		path_ = path;
		pixel_components_step_ = image_.width() * image_.height() * image_.depth();

		return true;
	}

	bool Image::createImage(const std::string& path, int rows, int columns)
	{
		image_ = cimg_library::CImg<unsigned char>(columns, rows, 1, 3, 0);

		if (!image_)
		{
			return false;
		}

		path_ = path;
		pixel_components_step_ = image_.width() * image_.height() * image_.depth();

		return true;
	}

	void Image::saveImage() const
	{
		image_.save(path_.c_str());
	}

	void Image::getSize(int& rows, int& columns) const
	{
		rows = image_.height();
		columns = image_.width();
	}
}
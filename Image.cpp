#include "Image.h"

namespace Dithering
{
	void Image::openImage(const std::string& path)
	{
		image_.load(path.c_str());

		if (!image_)
		{
			std::string message = "Can't open file ";
			message += path;
			throw std::exception(message.c_str());
		}

		path_ = path;
		pixel_components_step_ = image_.width() * image_.height() * image_.depth();
	}

	void Image::createImage(const std::string& path, int rows, int columns)
	{
		image_ = cimg_library::CImg<unsigned char>(columns, rows, 1, 3, 0);

		if (!image_)
		{
			throw std::exception("Can't allocate memory for the new image");
		}

		path_ = path;
		pixel_components_step_ = image_.width() * image_.height() * image_.depth();
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
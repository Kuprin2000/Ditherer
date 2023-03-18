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
	}

	void Image::createImage(const std::string& path, int rows, int columns)
	{
		image_ = cimg_library::CImg<unsigned char>(columns, rows, 1, 3, 0);

		if (!image_)
		{
			throw std::exception("Can't allocate memory for the new image");
		}

		path_ = path;
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

	Color Image::getColor(int row, int column) const
	{
		return
		{
			*image_.data(column, row, 0, 0),
			*image_.data(column, row, 0, 1),
			*image_.data(column, row, 0, 2)
		};
	}

	void Image::setColor(const Color &new_color, int row, int column)
	{
		*image_.data(column, row, 0, 0) = new_color[0];
		*image_.data(column, row, 0, 1) = new_color[1];
		*image_.data(column, row, 0, 2) = new_color[2];
	}
}
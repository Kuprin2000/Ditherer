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
		image_ = cimg_library::CImg<unsigned char>(columns, rows, 1, 4, 1);

		if (!image_)
		{
			throw std::exception("Can't allocate memory for the new image");
		}

		path_ = path;
	}

	Image::Format Image::pathToFormat(const std::string& path)
	{
		const auto format = path.substr(path.find('.'));
		if (!format.compare(".jpeg"))
		{
			return Format::JPEG;
		}

		if (!format.compare(".png"))
		{
			return Format::PNG;
		}

		throw std::exception("Bad saving format");
	}

	void Image::saveImage(Format save_format, int quality) const
	{
		if (save_format == Format::JPEG)
		{
			image_.save_jpeg(path_.c_str(), quality);
		}
		else
		{
			image_.save_png(path_.c_str(), 3);
		}
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
			*image_.data(column, row, 1, 0),
			*image_.data(column, row, 1, 1),
			*image_.data(column, row, 1, 2)
		};
	}

	void Image::setColor(Color new_color, int row, int column)
	{
		*image_.data(column, row, 1, 0) = new_color[0];
		*image_.data(column, row, 1, 1) = new_color[1];
		*image_.data(column, row, 1, 2) = new_color[2];
	}
}
#pragma once
#define cimg_use_jpeg
#define cimg_use_png
// #define cimg_display 0
#include <string>
#include <array>
#include "cimg/CImg.h"

namespace Dithering
{
	using Color = std::array<unsigned char, 3>;

	class Image
	{
	public:
		enum class Format : uint8_t
		{
			JPEG,
			PNG
		};

		Image() = default;

		Image(const Image& image) = delete;

		Image(Image&& image) = delete;

		void operator=(const Image& image) = delete;

		void openImage(const std::string& path);

		void createImage(const std::string& path, int rows, int columns);

		_NODISCARD static Format pathToFormat(const std::string& path);

		void saveImage(Format save_format, int quality) const;

		_NODISCARD void getSize(int& rows, int& columns) const;

		_NODISCARD Color getColor(int row, int column) const;

		void setColor(Color new_color, int row, int column);

	private:
		static const int BAD_COLOR = -1;

		cimg_library::CImg<unsigned char> image_;

		std::string path_ = "";
	};
}
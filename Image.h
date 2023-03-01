#pragma once
#define cimg_use_jpeg
#define cimg_use_png
#define cimg_display 0
#define XMD_H
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

		void operator=(const Image& image) = delete;

		void openImage(const std::string& path);

		void createImage(const std::string& path, int rows, int columns);

		_NODISCARD static Format pathToFormat(const std::string& path);

		void saveImage(Format save_format) const;

		_NODISCARD void getSize(int& rows, int& columns) const;

		_NODISCARD Color getColor(int row, int column) const;

		void setColor(Color new_color, int row, int column);

		_NODISCARD float getBrightness(int row, int column) const;

		void scaleBrightness(float new_brightness, int row, int column);

	private:
		static const int BAD_COLOR = -1;

		// 1.0f / (sqrtf(3.0f)*255.0f)
		const float brightness_coeff_ = 0.0022641187f;

		cimg_library::CImg<unsigned char> image_;

		std::string path_ = "";
	};
}
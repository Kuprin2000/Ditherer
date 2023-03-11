#pragma once
#define cimg_use_jpeg 1
#define cimg_use_png 1
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
		Image() = default;

		Image(const Image& image) = delete;

		void operator=(const Image& image) = delete;

		void openImage(const std::string& path);

		void createImage(const std::string& path, int rows, int columns);

		void saveImage() const;

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
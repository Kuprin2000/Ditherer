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

		_NODISCARD bool openImage(const std::string& path);

		_NODISCARD bool createImage(const std::string& path, int rows, int columns);

		void saveImage() const;

		_NODISCARD void getSize(int& rows, int& columns) const;

		__forceinline _NODISCARD Color getColor(int row, int column) const
		{
			auto ptr = image_.data() + column + image_.width() * row;

			return
			{
				*(ptr),
				*(ptr + pixel_components_step_),
				*(ptr + 2 * pixel_components_step_),
			};
		}

		__forceinline void setColor(const Color& new_color, int row, int column)
		{
			auto ptr = image_.data() + column + image_.width() * row;

			*ptr = new_color[0];
			*(ptr + pixel_components_step_) = new_color[1];
			*(ptr + 2 * pixel_components_step_) = new_color[2];
		}

	private:
		static const int BAD_COLOR = -1;

		// sqrt(255) / sqrt(3)
		const float brightness_coeff_ = 9.2195444f;

		int pixel_components_step_ = 0;

		cimg_library::CImg<unsigned char> image_;

		std::string path_ = "";
	};
}
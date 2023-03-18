#pragma once
#include "Image.h"

namespace Dithering
{
	static const int PALLETES_COUNT = 17;

	enum class Palette : uint8_t
	{
		BLACK_AND_WHITE,
		BLACK_GRAY_AND_WHITE,
		TWO_BIT_GRAYSCALE,
		FOUR_BIT_GRAYSCALE,
		BLACK_RED_GREEN_BLUE,
		BK_0011_PALETTE_1,
		BK_0011_PALETTE_2,
		BK_0011_PALETTE_3,
		BK_0011_PALETTE_6,
		BK_0011_PALETTE_7,
		BK_0011_PALETTE_8,
		BK_0011_PALETTE_9,
		BK_0011_PALETTE_10,
		BK_0011_PALETTE_11,
		BK_0011_PALETTE_12,
		EGA_16_COLORS,
		VGA_256_COLORS
	};

	class Ditherer
	{
	public:
		Ditherer();

		void process(Image& input_image, Image& output_image, Palette pallete, int algorithm_id, int threads_count) const;

	private:
		void processSingleThread(Image& input_image, Image& output_image, Palette palette) const;

		void processMultiThread(Image& input_image, Image& output_image, Palette palette, int threads_count) const;

		void processSingleThreadTwo(Image& input_image, Image& output_image, Palette palette) const;

		void processMultiThreadTwo(Image& input_image, Image& output_image, Palette palette, int threads_count) const;

		void processPixel(Image& input_image, Image& output_image, Palette palette, int row, int column) const;

		void findOptimalColor(const Image& input_image, int row, int column, Palette palette, int& optimal_color, std::array<int, 3>& mistake) const;

	private:
		// 7.0f / 48.0f
		const float coeff_7_48_ = 0.1458333333f;

		// 5.0f / 48.0f
		const float coeff_5_48_ = 0.1041666667f;

		// 3.0f / 48.0f
		const float coeff_3_48_ = 0.0625000000f;

		// 1.0f / 48.0f
		const float coeff_1_48_ = 0.0208333333f;

		std::array<std::vector<Color>, PALLETES_COUNT> palettes_;
	};
}
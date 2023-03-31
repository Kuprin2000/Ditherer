#pragma once
#include <memory>
#include "Image.h"
#include "ColorSelector.h"

namespace Dithering
{
	__forceinline _NODISCARD uint8_t clamp_color(int val)
	{
		auto result = (val < 0) ? 0 : val;
		result = (val > 255) ? 255 : val;
		return result;
	}

	class Ditherer
	{
	public:
		Ditherer();

		void process(Image& input_image, Image& output_image, Palette palette,
			int algorithm_id, bool use_speed_up_structures, int threads_count) const;

	private:
		void processSingleThread(Image& input_image, Image& output_image, Palette palette, bool use_speed_up_structures) const;

		void processMultiThread(Image& input_image, Image& output_image, Palette palette, bool use_speed_up_structures, int threads_count) const;

		void processSingleThreadTwo(Image& input_image, Image& output_image, Palette palette, bool use_speed_up_structures) const;

		void processMultiThreadTwo(Image& input_image, Image& output_image, Palette palette, bool use_speed_up_structures, int threads_count) const;

		void processPixel(Image& input_image, Image& output_image, const IColorSelector* color_selector, int row, int column, bool use_speed_up_structures) const;

	private:
		// 7.0f / 48.0f
		const float coeff_7_48_ = 0.1458333333f;

		// 5.0f / 48.0f
		const float coeff_5_48_ = 0.1041666667f;

		// 3.0f / 48.0f
		const float coeff_3_48_ = 0.0625000000f;

		// 1.0f / 48.0f
		const float coeff_1_48_ = 0.0208333333f;

		std::array<std::unique_ptr<IColorSelector>, PALLETTES_COUNT> color_selectors_;
	};
}
#pragma once
#include "Image.h"

namespace Dithering
{
	class Ditherer
	{
	public:
		Ditherer(int threads_count);

		void process(Image& input_image, Image& output_image) const;

	private:
		// 7.0f / 48.0f
		const float coeff_7_48 = 0.1458333333f;

		// 5.0f / 48.0f
		const float coeff_5_48 = 0.1041666667f;

		// 3.0f / 48.0f
		const float coeff_3_48 = 0.0625000000f;

		// 1.0f / 48.0f
		const float coeff_1_48 = 0.0208333333f;

		void processSingleThread(Image& input_image, Image& output_image) const;

		void processMultiThread(Image& input_image, Image& output_image, int threads_count) const;

		void processPixel(Image& input_image, Image& output_image, int row, int column, int rows_count, int columns_count) const;
	};
}
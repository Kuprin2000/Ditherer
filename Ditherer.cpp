#include <cmath>
#include <omp.h>
#include <vector>
#include "Ditherer.h"

namespace Dithering
{
	void Ditherer::process(Image& input_image, Image& output_image, int algorithm_id, int threads_count) const
	{
		if (!algorithm_id)
		{
			if (threads_count == 1)
			{
				processSingleThread(input_image, output_image);
			}
			else
			{
				processMultiThread(input_image, output_image, threads_count);
			}

			return;
		}

		if (algorithm_id == 1)
		{
			if (threads_count == 1)
			{
				processSingleThreadTwo(input_image, output_image);
			}
			else
			{
				processMultiThreadTwo(input_image, output_image, threads_count);
			}

			return;
		}

		throw std::exception("Wrong algorithm id");
	}

	void Ditherer::processSingleThread(Image& input_image, Image& output_image) const
	{
		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		for (int i = 0; i < rows_count; ++i)
		{
			for (int j = 0; j < columns_count; ++j)
			{
				processPixel(input_image, output_image, i, j, rows_count, columns_count);
			}
		}
	}

	void Ditherer::processMultiThread(Image& input_image, Image& output_image, int threads_count) const
	{
		if (threads_count % 3 && threads_count != 1)
		{
			threads_count -= threads_count % 3;
		}
		omp_set_num_threads(threads_count);

		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		const auto iterations_count = columns_count + threads_count * 3;
		std::vector<int> column_counters(threads_count, 0);

		#pragma omp parallel shared(column_counters)
		{
			const auto thread_id = omp_get_thread_num();

			for (int row = 0; row < rows_count; row += threads_count)
			{
				column_counters[thread_id] = 0;
				for (int iteration = 0; iteration < iterations_count; ++iteration)
				{
					if (row + thread_id < rows_count && column_counters[thread_id] < columns_count)
					{
						if (!thread_id || (thread_id && column_counters[thread_id - 1] > 3))
						{
							processPixel(input_image, output_image, row + thread_id, column_counters[thread_id], rows_count, columns_count);
							++column_counters[thread_id];
						}
					}

					#pragma omp barrier
				}
			}
		}
	}

	void Ditherer::processSingleThreadTwo(Image& input_image, Image& output_image) const
	{
		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		const auto row_coeff = 1.0f / 3.0f;
		const auto iterations_count = (rows_count - 1) * 3 + columns_count;
		for (int i = 0; i < iterations_count; ++i)
		{
			int row = (int)ceilf(std::max(i - columns_count + 1.0f, 0.0f) * row_coeff);
			int column = i - row * 3;
			const auto elements_count = std::min(1 + column / 3, rows_count - row);

			for (int j = 0; j < elements_count; ++j)
			{
				processPixel(input_image, output_image, row, column, rows_count, columns_count);
				++row;
				column -= 3;
			}
		}
	}

	void Ditherer::processMultiThreadTwo(Image& input_image, Image& output_image, int threads_count) const
	{
		omp_set_num_threads(threads_count);

		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		const auto row_coeff = 1.0f / 3.0f;
		const auto iterations_count = (rows_count - 1) * 3 + columns_count;
		for (int i = 0; i < iterations_count; ++i)
		{
			int row = (int)ceilf(std::max(i - columns_count + 1.0f, 0.0f) * row_coeff);
			int column = i - row * 3;

			const auto elements_count = std::min(1 + column / 3, rows_count - row);
			#pragma omp parallel for
			for (int j = 0; j < elements_count; ++j)
			{
				processPixel(input_image, output_image, row + j, column - 3 * j, rows_count, columns_count);
			}
		}
	}

	void Ditherer::processPixel(Image& input_image, Image& output_image, int row, int column, int rows_count, int columns_count) const
	{
		const auto brightness = input_image.getBrightness(row, column);

		if (brightness >= 0.5f)
		{
			output_image.setColor({ 255, 255, 255 }, row, column);
		}
		else
		{
			output_image.setColor({ 0, 0, 0 }, row, column);
		}

		const auto mistake = 0.5f - brightness;
		const auto mistake_7_48 = mistake * coeff_7_48;
		const auto mistake_5_48 = mistake * coeff_5_48;
		const auto mistake_3_48 = mistake * coeff_3_48;
		const auto mistake_1_48 = mistake * coeff_1_48;

		const auto opposite_brightness = 1.0f / brightness;

		const auto brightness_coef_7_48 = 1.0f + mistake_7_48 * opposite_brightness;
		const auto brightness_coef_5_48 = 1.0f + mistake_5_48 * opposite_brightness;
		const auto brightness_coef_3_48 = 1.0f + mistake_3_48 * opposite_brightness;
		const auto brightness_coef_1_48 = 1.0f + mistake_1_48 * opposite_brightness;

		if (column + 1 < columns_count)
		{
			input_image.scaleBrightness(brightness_coef_7_48, row, column + 1);
		}
		if (column + 2 < columns_count)
		{
			input_image.scaleBrightness(brightness_coef_5_48, row, column + 2);
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				input_image.scaleBrightness(brightness_coef_3_48, row, column - 2);
			}
			if (column - 1 > 0)
			{
				input_image.scaleBrightness(brightness_coef_5_48, row, column - 1);
			}

			input_image.scaleBrightness(brightness_coef_7_48, row, column);

			if (column + 1 < columns_count)
			{
				input_image.scaleBrightness(brightness_coef_5_48, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				input_image.scaleBrightness(brightness_coef_3_48, row, column + 2);
			}
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				input_image.scaleBrightness(brightness_coef_1_48, row, column - 2);
			}
			if (column - 1 > 0)
			{
				input_image.scaleBrightness(brightness_coef_3_48, row, column - 1);
			}

			input_image.scaleBrightness(brightness_coef_5_48, row, column);

			if (column + 1 < columns_count)
			{
				input_image.scaleBrightness(brightness_coef_3_48, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				input_image.scaleBrightness(brightness_coef_1_48, row, column + 2);
			}
		}
	}
}
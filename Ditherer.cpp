#include <cmath>
#include <omp.h>
#include <vector>
#include "Ditherer.h"

namespace Dithering
{
	Ditherer::Ditherer()
	{
		color_selectors_[(int)Palette::BLACK_AND_WHITE].reset(new BlackAndWhiteColorSelector());
		color_selectors_[(int)Palette::BLACK_GRAY_AND_WHITE].reset(new BlackGrayAndWhiteColorSelector());
		color_selectors_[(int)Palette::TWO_BIT_GRAYSCALE].reset(new TwoBitGrayscaleColorSelector());
		color_selectors_[(int)Palette::FOUR_BIT_GRAYSCALE].reset(new FourBitGrayscaleColorSelector());
		color_selectors_[(int)Palette::BLACK_RED_GREEN_BLUE].reset(new BlackRedGreenBlueColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_1].reset(new Palette1ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_2].reset(new Palette2ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_3].reset(new Palette3ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_6].reset(new Palette6ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_7].reset(new Palette7ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_8].reset(new Palette8ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_9].reset(new Palette9ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_10].reset(new Palette10ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_11].reset(new Palette11ColorSelector());
		color_selectors_[(int)Palette::BK_0011_PALETTE_12].reset(new Palette12ColorSelector());
		color_selectors_[(int)Palette::EGA_16_COLORS].reset(new Ega16ColorsColorSelector());
		color_selectors_[(int)Palette::VGA_256_COLORS].reset(new Vga256ColorsColorSelector());
	}

	void Ditherer::process(Image& input_image, Image& output_image, Palette palette, int algorithm_id, int threads_count) const
	{
		if (!algorithm_id)
		{
			if (threads_count == 1)
			{
				processSingleThread(input_image, output_image, palette);
			}
			else if (threads_count > 1)
			{
				processMultiThread(input_image, output_image, palette, threads_count);
			}
		}

		else if (algorithm_id == 1)
		{
			if (threads_count == 1)
			{
				processSingleThreadTwo(input_image, output_image, palette);
			}
			else if (threads_count > 1)
			{
				processMultiThreadTwo(input_image, output_image, palette, threads_count);
			}
		}

		else
		{
			throw std::exception("Wrong algorithm id");
		}
	}

	void Ditherer::processSingleThread(Image& input_image, Image& output_image, Palette palette) const
	{
		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		for (int i = 0; i < rows_count; ++i)
		{
			for (int j = 0; j < columns_count; ++j)
			{
				processPixel(input_image, output_image, palette, i, j);
			}
		}
	}

	void Ditherer::processMultiThread(Image& input_image, Image& output_image, Palette palette, int threads_count) const
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
							processPixel(input_image, output_image, palette, row + thread_id, column_counters[thread_id]);
							++column_counters[thread_id];
						}
					}

#pragma omp barrier
				}
			}
		}
	}

	void Ditherer::processSingleThreadTwo(Image& input_image, Image& output_image, Palette palette) const
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
				processPixel(input_image, output_image, palette, row, column);
				++row;
				column -= 3;
			}
		}
	}

	void Ditherer::processMultiThreadTwo(Image& input_image, Image& output_image, Palette palette, int threads_count) const
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
				processPixel(input_image, output_image, palette, row + j, column - 3 * j);
			}
		}
	}

	void Ditherer::processPixel(Image& input_image, Image& output_image, Palette palette, int row, int column) const
	{
		auto optimal_color = 0;
		std::array<int, 3> mistake = { 0 };
		const auto color = color_selectors_[(int)palette]->findOptimalColor(input_image, row, column, mistake);
		output_image.setColor(color, row, column);

		auto rows_count = 0;
		auto columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		const std::array<int, 3> mistake_7_48 = { (int)(mistake[0] * coeff_7_48_), (int)(mistake[1] * coeff_7_48_), (int)(mistake[2] * coeff_7_48_) };
		const std::array<int, 3> mistake_5_48 = { (int)(mistake[0] * coeff_5_48_), (int)(mistake[1] * coeff_5_48_), (int)(mistake[2] * coeff_5_48_) };
		const std::array<int, 3> mistake_3_48 = { (int)(mistake[0] * coeff_3_48_), (int)(mistake[1] * coeff_3_48_), (int)(mistake[2] * coeff_3_48_) };
		const std::array<int, 3> mistake_1_48 = { (int)(mistake[0] * coeff_1_48_), (int)(mistake[1] * coeff_1_48_), (int)(mistake[2] * coeff_1_48_) };

		Color tmp_color = { 0 };
		if (column + 1 < columns_count)
		{
			tmp_color = input_image.getColor(row, column + 1);
			tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_7_48[0], 0, 255);
			tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_7_48[1], 0, 255);
			tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_7_48[2], 0, 255);
			input_image.setColor(tmp_color, row, column + 1);
		}
		if (column + 2 < columns_count)
		{
			tmp_color = input_image.getColor(row, column + 2);
			tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_5_48[0], 0, 255);
			tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_5_48[1], 0, 255);
			tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_5_48[2], 0, 255);
			input_image.setColor(tmp_color, row, column + 2);
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				tmp_color = input_image.getColor(row, column - 2);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_3_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_3_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_3_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column - 2);
			}
			if (column - 1 > 0)
			{
				tmp_color = input_image.getColor(row, column - 1);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_5_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_5_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_5_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column - 1);
			}

			tmp_color = input_image.getColor(row, column);
			tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_7_48[0], 0, 255);
			tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_7_48[1], 0, 255);
			tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_7_48[2], 0, 255);
			input_image.setColor(tmp_color, row, column);

			if (column + 1 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 1);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_5_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_5_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_5_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 2);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_3_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_3_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_3_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column + 2);
			}
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				tmp_color = input_image.getColor(row, column - 2);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_1_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_1_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_1_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column - 2);
			}
			if (column - 1 > 0)
			{
				tmp_color = input_image.getColor(row, column - 1);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_3_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_3_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_3_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column - 1);
			}

			tmp_color = input_image.getColor(row, column);
			tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_5_48[0], 0, 255);
			tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_5_48[1], 0, 255);
			tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_5_48[2], 0, 255);
			input_image.setColor(tmp_color, row, column);

			if (column + 1 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 1);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_3_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_3_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_3_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 2);
				tmp_color[0] = (uint8_t)std::clamp((int)tmp_color[0] + mistake_1_48[0], 0, 255);
				tmp_color[1] = (uint8_t)std::clamp((int)tmp_color[1] + mistake_1_48[1], 0, 255);
				tmp_color[2] = (uint8_t)std::clamp((int)tmp_color[2] + mistake_1_48[2], 0, 255);
				input_image.setColor(tmp_color, row, column + 2);
			}
		}
	}
}
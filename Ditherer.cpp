#include <cmath>
#include <omp.h>
#include <vector>
#include "Ditherer.h"

namespace
{
	__forceinline _NODISCARD uint8_t clamp_color(int val)
	{
		auto result = (val < 0) ? 0 : val;
		result = (val > 255) ? 255 : val;
		return result;
	}
}

namespace Dithering
{
	const std::string& IDitherer::get_name() const
	{
		return name_;
	}

	JJNDitherer::JJNDitherer(int algorithm_id, bool use_speed_up_structures) :
		algorithm_id_(algorithm_id), use_speed_up_structures_(use_speed_up_structures)
	{
		name_ = "Jarvis-Judice-Ninke ditherer";

		palette_handlers_[(int)Palette::BLACK_AND_WHITE].reset(new BlackAndWhiteHandler());
		palette_handlers_[(int)Palette::BLACK_GRAY_AND_WHITE].reset(new BlackGrayAndWhiteHandler());
		palette_handlers_[(int)Palette::TWO_BIT_GRAYSCALE].reset(new TwoBitGrayscaleHandler());
		palette_handlers_[(int)Palette::FOUR_BIT_GRAYSCALE].reset(new FourBitGrayscaleHandler());
		palette_handlers_[(int)Palette::BLACK_RED_GREEN_BLUE].reset(new BlackRedGreenBlueHandler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_1].reset(new Palette1Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_2].reset(new Palette2Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_3].reset(new Palette3Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_6].reset(new Palette6Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_7].reset(new Palette7Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_8].reset(new Palette8Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_9].reset(new Palette9Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_10].reset(new Palette10Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_11].reset(new Palette11Handler());
		palette_handlers_[(int)Palette::BK_0011_PALETTE_12].reset(new Palette12Handler());
		palette_handlers_[(int)Palette::EGA_16_COLORS].reset(new Ega16ColorsHandler());
		palette_handlers_[(int)Palette::VGA_256_COLORS].reset(new Vga256ColorsHandler());

		palette_handlers_names_.resize((int)Palette::COUNT);
		for (int i = 0; i < palette_handlers_.size(); ++i)
		{
			palette_handlers_names_[i] = palette_handlers_[i]->get_name();
		}
	}

	bool JJNDitherer::process(Image& input_image, Image& output_image, int palette, int threads_count) const
	{
		if (!algorithm_id_)
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

		else if (algorithm_id_ == 1)
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
			return false;
		}

		return true;
	}

	int JJNDitherer::get_palletes_count() const
	{
		return (int)palette_handlers_.size();
	}

	const std::vector<std::string>& JJNDitherer::get_palletes_names() const
	{
		return palette_handlers_names_;
	}

	void JJNDitherer::processSingleThread(Image& input_image, Image& output_image, int palette) const
	{
		const auto* color_selector = palette_handlers_[palette].get();

		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		for (int i = 0; i < rows_count; ++i)
		{
			for (int j = 0; j < columns_count; ++j)
			{
				processPixel(input_image, output_image, color_selector, i, j);
			}
		}
	}

	void JJNDitherer::processMultiThread(Image& input_image, Image& output_image, int palette, int threads_count) const
	{
		if (threads_count % 3 && threads_count != 1)
		{
			threads_count -= threads_count % 3;
		}
		omp_set_num_threads(threads_count);

		const auto* color_selector = palette_handlers_[palette].get();

		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		const auto iterations_count = columns_count + threads_count * 3;
		std::vector<int> column_counters(threads_count, 0);

#pragma omp parallel default(shared)
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
							processPixel(input_image, output_image, color_selector, row + thread_id, column_counters[thread_id]);
							++column_counters[thread_id];
						}
					}

#pragma omp barrier
				}
			}
		}
	}

	void JJNDitherer::processSingleThreadTwo(Image& input_image, Image& output_image, int palette) const
	{
		const auto* color_selector = palette_handlers_[palette].get();

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
				processPixel(input_image, output_image, color_selector, row, column);
				++row;
				column -= 3;
			}
		}
	}

	void JJNDitherer::processMultiThreadTwo(Image& input_image, Image& output_image, int palette, int threads_count) const
	{
		omp_set_num_threads(threads_count);

		const auto* color_selector = palette_handlers_[palette].get();

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
#pragma omp parallel for default(shared)
			for (int j = 0; j < elements_count; ++j)
			{
				processPixel(input_image, output_image, color_selector, row + j, column - 3 * j);
			}
		}
	}

	void JJNDitherer::processPixel(Image& input_image, Image& output_image, const IPaletteHandler* color_selector, int row, int column) const
	{
		auto optimal_color = 0;
		std::array<int, 3> mistake;
		const auto color = color_selector->findOptimalColor(input_image, row, column, mistake, use_speed_up_structures_);
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
			tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_7_48[0]);
			tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_7_48[1]);
			tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_7_48[2]);
			input_image.setColor(tmp_color, row, column + 1);
		}
		if (column + 2 < columns_count)
		{
			tmp_color = input_image.getColor(row, column + 2);
			tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_5_48[0]);
			tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_5_48[1]);
			tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_5_48[2]);
			input_image.setColor(tmp_color, row, column + 2);
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				tmp_color = input_image.getColor(row, column - 2);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_3_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_3_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_3_48[2]);
				input_image.setColor(tmp_color, row, column - 2);
			}
			if (column - 1 > 0)
			{
				tmp_color = input_image.getColor(row, column - 1);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_5_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_5_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_5_48[2]);
				input_image.setColor(tmp_color, row, column - 1);
			}

			tmp_color = input_image.getColor(row, column);
			tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_7_48[0]);
			tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_7_48[1]);
			tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_7_48[2]);
			input_image.setColor(tmp_color, row, column);

			if (column + 1 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 1);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_5_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_5_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_5_48[2]);
				input_image.setColor(tmp_color, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 2);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_3_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_3_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_3_48[2]);
				input_image.setColor(tmp_color, row, column + 2);
			}
		}

		++row;
		if (row < rows_count)
		{
			if (column - 2 > 0)
			{
				tmp_color = input_image.getColor(row, column - 2);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_1_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_1_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_1_48[2]);
				input_image.setColor(tmp_color, row, column - 2);
			}
			if (column - 1 > 0)
			{
				tmp_color = input_image.getColor(row, column - 1);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_3_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_3_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_3_48[2]);
				input_image.setColor(tmp_color, row, column - 1);
			}

			tmp_color = input_image.getColor(row, column);
			tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_5_48[0]);
			tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_5_48[1]);
			tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_5_48[2]);
			input_image.setColor(tmp_color, row, column);

			if (column + 1 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 1);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_3_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_3_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_3_48[2]);
				input_image.setColor(tmp_color, row, column + 1);
			}
			if (column + 2 < columns_count)
			{
				tmp_color = input_image.getColor(row, column + 2);
				tmp_color[0] = clamp_color((int)tmp_color[0] + mistake_1_48[0]);
				tmp_color[1] = clamp_color((int)tmp_color[1] + mistake_1_48[1]);
				tmp_color[2] = clamp_color((int)tmp_color[2] + mistake_1_48[2]);
				input_image.setColor(tmp_color, row, column + 2);
			}
		}
	}
}
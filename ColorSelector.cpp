#include "ColorSelector.h"

namespace Dithering
{
	Dithering::BlackAndWhiteColorSelector::BlackAndWhiteColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 255, 255, 255 } };
	}

	Color Dithering::BlackAndWhiteColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	BlackGrayAndWhiteColorSelector::BlackGrayAndWhiteColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 128, 128, 128 },{ 255, 255, 255 } };
	}

	Color BlackGrayAndWhiteColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	TwoBitGrayscaleColorSelector::TwoBitGrayscaleColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 85, 85, 85 },{ 170, 170, 170 },{ 255, 255, 255 } };
	}

	Color TwoBitGrayscaleColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	FourBitGrayscaleColorSelector::FourBitGrayscaleColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 17, 17, 17 },{ 34, 34, 34 },{ 51, 51, 51 },{ 68, 68, 68 },{ 85, 85, 85 },{ 102, 102, 102 },{ 119, 119, 119 },
			{ 136, 136, 136 },{ 153, 153, 153 },{ 170, 170, 170 },{ 187, 187, 187 },{ 204, 204, 204 },{ 221, 221, 221 },{ 238, 238, 238 },{ 255, 255, 255 } };
	}

	Color FourBitGrayscaleColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	BlackRedGreenBlueColorSelector::BlackRedGreenBlueColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 } };
	}

	Color BlackRedGreenBlueColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette1ColorSelector::Palette1ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 255, 255, 0 },{ 255, 0, 255 },{ 255, 0, 0 } };
	}

	Color Palette1ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette2ColorSelector::Palette2ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 0, 255, 255 },{ 0, 0, 255 },{ 255, 0, 255 } };
	}

	Color Palette2ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette3ColorSelector::Palette3ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 0, 255, 0 },{ 0, 255, 255 },{ 255, 255, 0 } };
	}

	Color Palette3ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette6ColorSelector::Palette6ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 192, 0, 0 },{ 144, 0, 0 },{ 255, 0, 0 } };
	}

	Color Palette6ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette7ColorSelector::Palette7ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 192, 255, 0 },{ 144, 255, 0 },{ 255, 255, 0 } };
	}

	Color Palette7ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette8ColorSelector::Palette8ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 192, 0, 255 },{ 144, 0, 255 },{ 255, 0, 255 } };
	}

	Color Palette8ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette9ColorSelector::Palette9ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 144, 255, 0 },{ 144, 0, 255 },{ 144, 0, 0 } };
	}

	Color Palette9ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette10ColorSelector::Palette10ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 192, 255, 0 },{ 192, 0, 255 },{ 192, 0, 0 } };
	}

	Color Palette10ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette11ColorSelector::Palette11ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 0, 255, 255 },{ 255, 255, 0 },{ 255, 0, 0 } };
	}

	Color Palette11ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Palette12ColorSelector::Palette12ColorSelector()
	{
		palette_ = { { 0, 0, 0 },{ 255, 0, 0 },{ 0, 255, 0 },{ 0, 255, 255 } };
	}

	Color Palette12ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Ega16ColorsColorSelector::Ega16ColorsColorSelector()
	{
		palette_ = {
			{ 0, 0, 0 },{ 0, 0, 170 },{ 0, 170, 0 },{ 0, 170, 170 },{ 170, 0, 0 },{ 170, 0, 170 },{ 170, 85, 0 },{ 170, 170, 170 },
			{ 85, 85, 85 },{ 85, 85, 255 },{ 85, 255, 85 },{ 85, 255, 85 },{ 255, 85, 85 },{ 255, 85, 255 },{ 255, 255, 85 },{ 255, 255, 255 } };
	}

	Color Ega16ColorsColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}

	Vga256ColorsColorSelector::Vga256ColorsColorSelector()
	{
		palette_ = {
			{ 0, 0, 0 },{ 0, 2, 170 },{ 20, 170, 0 },{ 0, 170, 170 },{ 170, 0, 3 },{ 170, 0, 170 },{ 170, 85, 0 },{ 170, 170, 170 },
			{ 85, 85, 85 },{ 85, 85, 255 },{ 85, 255, 85 },{ 85, 255, 255 },{ 255, 85, 85 },{ 253, 85, 255 },{ 255, 255, 85 },{ 255, 255, 255 },
			{ 0, 0, 0 },{ 16, 16, 16 },{ 32, 32, 32 },{ 53, 53, 53 },{ 69, 69, 69 },{ 85, 85, 85 },{ 101, 101, 101 },{ 117, 117, 117 },
			{ 138, 138, 138 },{ 154, 154, 154 },{ 170, 170, 170 },{ 186, 186, 186 },{ 202, 202, 202 },{ 223, 223, 223 },{ 239, 239, 239 },{ 255, 255, 255 },
			{ 0, 4, 255 },{ 65, 4, 255 },{ 130, 3, 255 },{ 190, 2, 255 },{ 253, 0, 255 },{ 254, 0, 190 },{ 255, 0, 130 },{ 255, 0, 65 },
			{ 255, 0, 8 },{ 255, 65, 5 },{ 255, 130, 0 },{ 255, 190, 0 },{ 255, 255, 0 },{ 190, 255, 0 },{ 130, 255, 0 },{ 65, 255, 1 },
			{ 36, 255, 0 },{ 34, 255, 66 },{ 29, 255, 130 },{ 18, 255, 190 },{ 0, 255, 255 },{ 0, 190, 255 },{ 1, 130, 255 },{ 0, 65, 255 },
			{ 130, 130, 255 },{ 158, 130, 255 },{ 190, 130, 255 },{ 223, 130, 255 },{ 253, 130, 255 },{ 254, 130, 223 },{ 255, 130, 190 },{ 255, 130, 158 },
			{ 255, 130, 130 },{ 255, 158, 130 },{ 255, 190, 130 },{ 255, 223, 130 },{ 255, 255, 130 },{ 223, 255, 130 },{ 190, 255, 130 },{ 158, 255, 130 },
			{ 130, 255, 130 },{ 130, 255, 158 },{ 130, 255, 190 },{ 130, 255, 223 },{ 130, 255, 255 },{ 130, 223, 255 },{ 130, 190, 255 },{ 130, 158, 255 },
			{ 186, 186, 255 },{ 202, 186, 255 },{ 223, 186, 255 },{ 239, 186, 255 },{ 254, 186, 255 },{ 254, 186, 239 },{ 255, 186, 223 },{ 255, 186, 202 },
			{ 255, 186, 186 },{ 255, 202, 186 },{ 255, 223, 186 },{ 255, 239, 186 },{ 255, 255, 186 },{ 239, 255, 186 },{ 223, 255, 186 },{ 202, 255, 187 },
			{ 186, 255, 186 },{ 186, 255, 202 },{ 186, 255, 223 },{ 186, 255, 239 },{ 186, 255, 255 },{ 186, 239, 255 },{ 186, 223, 255 },{ 186, 202, 255 },
			{ 1, 1, 113 },{ 28, 1, 113 },{ 57, 1, 113 },{ 85, 0, 113 },{ 113, 0, 113 },{ 113, 0, 85 },{ 113, 0, 57 },{ 113, 0, 28 },
			{ 113, 0, 1 },{ 113, 28, 1 },{ 113, 57, 0 },{ 113, 85, 0 },{ 113, 113, 0 },{ 85, 113, 0 },{ 57, 113, 0 },{ 28, 113, 0 },
			{ 9, 113, 0 },{ 9, 113, 28 },{ 6, 113, 57 },{ 3, 113, 85 },{ 0, 113, 113 },{ 0, 85, 113 },{ 0, 57, 113 },{ 0, 28, 113 },
			{ 57, 57, 113 },{ 69, 57, 113 },{ 85, 57, 113 },{ 97, 57, 113 },{ 113, 57, 113 },{ 113, 57, 97 },{ 113, 57, 85 },{ 113, 57, 69 },
			{ 113, 57, 57 },{ 113, 69, 57 },{ 113, 85, 57 },{ 113, 97, 57 },{ 113, 113, 57 },{ 97, 113, 57 },{ 85, 113, 57 },{ 69, 113, 58 },
			{ 57, 113, 57 },{ 57, 113, 69 },{ 57, 113, 85 },{ 57, 113, 97 },{ 57, 113, 113 },{ 57, 97, 113 },{ 57, 85, 113 },{ 57, 69, 114 },
			{ 81, 81, 113 },{ 89, 81, 113 },{ 97, 81, 113 },{ 105, 81, 113 },{ 113, 81, 113 },{ 113, 81, 105 },{ 113, 81, 97 },{ 113, 81, 89 },
			{ 113, 81, 81 },{ 113, 89, 81 },{ 113, 97, 81 },{ 113, 105, 81 },{ 113, 113, 81 },{ 105, 113, 81 },{ 97, 113, 81 },{ 89, 113, 81 },
			{ 81, 113, 81 },{ 81, 113, 90 },{ 81, 113, 97 },{ 81, 113, 105 },{ 81, 113, 113 },{ 81, 105, 113 },{ 81, 97, 113 },{ 81, 89, 113 },
			{ 0, 0, 66 },{ 17, 0, 65 },{ 32, 0, 65 },{ 49, 0, 65 },{ 65, 0, 65 },{ 65, 0, 50 },{ 65, 0, 32 },{ 65, 0, 16 },
			{ 65, 0, 0 },{ 65, 16, 0 },{ 65, 32, 0 },{ 65, 49, 0 },{ 65, 65, 0 },{ 49, 65, 0 },{ 32, 65, 0 },{ 16, 65, 0 },
			{ 3, 65, 0 },{ 3, 65, 16 },{ 2, 65, 32 },{ 1, 65, 49 },{ 0, 65, 65 },{ 0, 49, 65 },{ 0, 32, 65 },{ 0, 16, 65 },
			{ 32, 32, 65 },{ 40, 32, 65 },{ 49, 32, 65 },{ 57, 32, 65 },{ 65, 32, 65 },{ 65, 32, 57 },{ 65, 32, 49 },{ 65, 32, 40 },
			{ 65, 32, 32 },{ 65, 40, 32 },{ 65, 49, 32 },{ 65, 57, 33 },{ 65, 65, 32 },{ 57, 65, 32 },{ 49, 65, 32 },{ 40, 65, 32 },
			{ 32, 65, 32 },{ 32, 65, 40 },{ 32, 65, 49 },{ 32, 65, 57 },{ 32, 65, 65 },{ 32, 57, 65 },{ 32, 49, 65 },{ 32, 40, 65 },
			{ 45, 45, 65 },{ 49, 45, 65 },{ 53, 45, 65 },{ 61, 45, 65 },{ 65, 45, 65 },{ 65, 45, 61 },{ 65, 45, 53 },{ 65, 45, 49 },
			{ 65, 45, 45 },{ 65, 49, 45 },{ 65, 53, 45 },{ 65, 61, 45 },{ 65, 65, 45 },{ 61, 65, 45 },{ 53, 65, 45 },{ 49, 65, 45 },
			{ 45, 65, 45 },{ 45, 65, 49 },{ 45, 65, 53 },{ 45, 65, 61 },{ 45, 65, 65 },{ 45, 61, 65 },{ 45, 53, 65 },{ 45, 49, 65 } };
	}

	Color Vga256ColorsColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const
	{
		const auto input_color = input_image.getColor(row, column);

		auto min_delta = FLT_MAX;
		auto delta = 0.0f;
		auto optimal_color_index = 0;

		for (int i = 0; i < palette_.size(); ++i)
		{
			const auto& color = palette_[i];

			delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
			if (delta < min_delta)
			{
				min_delta = delta;
				mistake = { input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2] };
				optimal_color_index = i;
			}
		}

		return palette_[optimal_color_index];
	}
}
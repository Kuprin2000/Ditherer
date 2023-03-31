#pragma once
#include <vector>
#include <array>
#include "Image.h"

namespace Dithering
{
	static constexpr auto PALLETTES_COUNT = 17;
	static constexpr auto SEGMENTS_PER_AXIS = 8;
	static constexpr auto STEP = 256 / SEGMENTS_PER_AXIS;
	static constexpr uint8_t COLORS_PER_PALETTE[PALLETTES_COUNT] = { 2, 3, 4, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16, 249 };

	using ColorsForSegments = std::vector<uint8_t>[SEGMENTS_PER_AXIS][SEGMENTS_PER_AXIS][SEGMENTS_PER_AXIS];

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

	class IColorSelector
	{
	public:
		IColorSelector() = default;

		IColorSelector(const IColorSelector& selector) = delete;

		void operator=(const IColorSelector& selector) = delete;

		_NODISCARD virtual Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const = 0;

		virtual ~IColorSelector() = default;
	};

	class BlackAndWhiteColorSelector : public IColorSelector
	{
	public:
		BlackAndWhiteColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BLACK_AND_WHITE]];
		ColorsForSegments colors_for_segments_;
	};

	class BlackGrayAndWhiteColorSelector : public IColorSelector
	{
	public:
		BlackGrayAndWhiteColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BLACK_GRAY_AND_WHITE]];
		ColorsForSegments colors_for_segments_;
	};

	class TwoBitGrayscaleColorSelector : public IColorSelector
	{
	public:
		TwoBitGrayscaleColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::TWO_BIT_GRAYSCALE]];
		ColorsForSegments colors_for_segments_;
	};

	class FourBitGrayscaleColorSelector : public IColorSelector
	{
	public:
		FourBitGrayscaleColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::FOUR_BIT_GRAYSCALE]];
		ColorsForSegments colors_for_segments_;
	};

	class BlackRedGreenBlueColorSelector : public IColorSelector
	{
	public:
		BlackRedGreenBlueColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BLACK_RED_GREEN_BLUE]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette1ColorSelector : public IColorSelector
	{
	public:
		Palette1ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_1]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette2ColorSelector : public IColorSelector
	{
	public:
		Palette2ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_2]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette3ColorSelector : public IColorSelector
	{
	public:
		Palette3ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_3]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette6ColorSelector : public IColorSelector
	{
	public:
		Palette6ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_6]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette7ColorSelector : public IColorSelector
	{
	public:
		Palette7ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_7]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette8ColorSelector : public IColorSelector
	{
	public:
		Palette8ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_8]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette9ColorSelector : public IColorSelector
	{
	public:
		Palette9ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_9]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette10ColorSelector : public IColorSelector
	{
	public:
		Palette10ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_10]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette11ColorSelector : public IColorSelector
	{
	public:
		Palette11ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_11]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette12ColorSelector : public IColorSelector
	{
	public:
		Palette12ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_12]];
		ColorsForSegments colors_for_segments_;
	};

	class Ega16ColorsColorSelector : public IColorSelector
	{
	public:
		Ega16ColorsColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::EGA_16_COLORS]];
		ColorsForSegments colors_for_segments_;
	};

	class Vga256ColorsColorSelector : public IColorSelector
	{
	public:
		Vga256ColorsColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::VGA_256_COLORS]];
		ColorsForSegments colors_for_segments_;
	};

	__forceinline Color findOptimalColorInternal1(const Image& input_image, int row, int column,
		const Color* palette, int palette_colors_count, std::array<int, 3>& min_mistake)
	{
		const auto input_color = input_image.getColor(row, column);

		int min_delta = INT_MAX;
		auto delta = 0;
		auto optimal_color_index = 0;
		std::array<int, 3> mistake = { 0 };

		for (int i = 0; i < palette_colors_count; ++i)
		{
			const auto& color = palette[i];

			mistake = { (int)input_color[0] - (int)color[0],(int)input_color[1] - (int)color[1],(int)input_color[2] - (int)color[2] };
			delta = mistake[0] * mistake[0] + mistake[1] * mistake[1] + mistake[2] * mistake[2];
			if (delta < min_delta)
			{
				min_delta = delta;
				min_mistake = mistake;
				optimal_color_index = i;
			}
		}

		return palette[optimal_color_index];
	}

	__forceinline Color findOptimalColorInternal2(const Image& input_image, int row, int column,
		const Color* palette, const ColorsForSegments& colors_for_segments, std::array<int, 3>& min_mistake)
	{
		const auto input_color = input_image.getColor(row, column);

		const auto r_index = input_color[0] / STEP;
		const auto g_index = input_color[1] / STEP;
		const auto b_index = input_color[2] / STEP;

		const auto& candidate_colors = colors_for_segments[r_index][g_index][b_index];

		int min_delta = INT_MAX;
		auto delta = 0;
		auto optimal_color_index = 0;
		std::array<int, 3> mistake = { 0 };

		for (int i = 0; i < candidate_colors.size(); ++i)
		{
			const auto& color = palette[candidate_colors[i]];

			mistake = { (int)input_color[0] - (int)color[0],(int)input_color[1] - (int)color[1],(int)input_color[2] - (int)color[2] };
			delta = mistake[0] * mistake[0] + mistake[1] * mistake[1] + mistake[2] * mistake[2];
			if (delta < min_delta)
			{
				min_delta = delta;
				min_mistake = mistake;
				optimal_color_index = candidate_colors[i];
			}
		}

		return palette[optimal_color_index];
	}

	__forceinline Color Dithering::BlackAndWhiteColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BLACK_AND_WHITE], mistake);
		}
	}

	__forceinline Color BlackGrayAndWhiteColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BLACK_GRAY_AND_WHITE], mistake);
		}
	}

	__forceinline Color TwoBitGrayscaleColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::TWO_BIT_GRAYSCALE], mistake);
		}
	}

	__forceinline Color FourBitGrayscaleColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::FOUR_BIT_GRAYSCALE], mistake);
		}
	}

	__forceinline Color BlackRedGreenBlueColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BLACK_RED_GREEN_BLUE], mistake);
		}
	}

	__forceinline Color Palette1ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_1], mistake);
		}
	}

	__forceinline Color Palette2ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_2], mistake);
		}
	}

	__forceinline Color Palette3ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_3], mistake);
		}
	}

	__forceinline Color Palette6ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_6], mistake);
		}
	}

	__forceinline Color Palette7ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_7], mistake);
		}
	}

	__forceinline Color Palette8ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_8], mistake);
		}
	}

	__forceinline Color Palette9ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_9], mistake);
		}
	}

	__forceinline Color Palette10ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_10], mistake);
		}
	}

	__forceinline Color Palette11ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_11], mistake);
		}
	}

	__forceinline Color Palette12ColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_12], mistake);
		}
	}

	__forceinline Color Ega16ColorsColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::EGA_16_COLORS], mistake);
		}
	}

	__forceinline Color Vga256ColorsColorSelector::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
	{
		if (use_speed_up_structure)
		{
			return findOptimalColorInternal2(input_image, row, column, palette_, colors_for_segments_, mistake);
		}
		else
		{
			return findOptimalColorInternal1(input_image, row, column, palette_, COLORS_PER_PALETTE[(int)Palette::VGA_256_COLORS], mistake);
		}
	}
}
#pragma once
#include <vector>
#include <array>
#include "Image.h"

namespace Dithering
{
	static constexpr auto SEGMENTS_PER_AXIS = 8;
	static constexpr auto STEP = 256 / SEGMENTS_PER_AXIS;
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
		VGA_256_COLORS,
		COUNT
	};

	static constexpr uint8_t COLORS_PER_PALETTE[(int)Palette::COUNT] = { 2, 3, 4, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16, 249 };

	class IPaletteHandler
	{
	public:
		IPaletteHandler() = default;

		IPaletteHandler(const IPaletteHandler& Handler) = delete;

		void operator=(const IPaletteHandler& Handler) = delete;

		_NODISCARD virtual Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const = 0;

		_NODISCARD const std::string& get_name() const;

		virtual ~IPaletteHandler() = default;

	protected:
		std::string name_ = "No name";
	};

	class BlackAndWhiteHandler : public IPaletteHandler
	{
	public:
		BlackAndWhiteHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[2];
		ColorsForSegments colors_for_segments_;
	};

	class BlackGrayAndWhiteHandler : public IPaletteHandler
	{
	public:
		BlackGrayAndWhiteHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[3];
		ColorsForSegments colors_for_segments_;
	};

	class TwoBitGrayscaleHandler : public IPaletteHandler
	{
	public:
		TwoBitGrayscaleHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class FourBitGrayscaleHandler : public IPaletteHandler
	{
	public:
		FourBitGrayscaleHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[16];
		ColorsForSegments colors_for_segments_;
	};

	class BlackRedGreenBlueHandler : public IPaletteHandler
	{
	public:
		BlackRedGreenBlueHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette1Handler : public IPaletteHandler
	{
	public:
		Palette1Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette2Handler : public IPaletteHandler
	{
	public:
		Palette2Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette3Handler : public IPaletteHandler
	{
	public:
		Palette3Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette6Handler : public IPaletteHandler
	{
	public:
		Palette6Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette7Handler : public IPaletteHandler
	{
	public:
		Palette7Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette8Handler : public IPaletteHandler
	{
	public:
		Palette8Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette9Handler : public IPaletteHandler
	{
	public:
		Palette9Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette10Handler : public IPaletteHandler
	{
	public:
		Palette10Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[COLORS_PER_PALETTE[(int)Palette::BK_0011_PALETTE_10]];
		ColorsForSegments colors_for_segments_;
	};

	class Palette11Handler : public IPaletteHandler
	{
	public:
		Palette11Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Palette12Handler : public IPaletteHandler
	{
	public:
		Palette12Handler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[4];
		ColorsForSegments colors_for_segments_;
	};

	class Ega16ColorsHandler : public IPaletteHandler
	{
	public:
		Ega16ColorsHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[16];
		ColorsForSegments colors_for_segments_;
	};

	class Vga256ColorsHandler : public IPaletteHandler
	{
	public:
		Vga256ColorsHandler();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake, bool use_speed_structure) const override;

	private:
		Color palette_[256];
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

	__forceinline Color Dithering::BlackAndWhiteHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color BlackGrayAndWhiteHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color TwoBitGrayscaleHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color FourBitGrayscaleHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color BlackRedGreenBlueHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette1Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette2Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette3Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette6Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette7Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette8Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette9Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette10Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette11Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Palette12Handler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Ega16ColorsHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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

	__forceinline Color Vga256ColorsHandler::findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake, bool use_speed_up_structure) const
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
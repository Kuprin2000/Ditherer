#pragma once
#include <vector>
#include "Image.h"

namespace Dithering
{
	static const int PALLETTES_COUNT = 17;

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
		_NODISCARD virtual Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const = 0;

		virtual ~IColorSelector() = default;

	protected:
		std::vector<Color> palette_;
	};

	class BlackAndWhiteColorSelector : public IColorSelector
	{
	public:
		BlackAndWhiteColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class BlackGrayAndWhiteColorSelector : public IColorSelector
	{
	public:
		BlackGrayAndWhiteColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class TwoBitGrayscaleColorSelector : public IColorSelector
	{
	public:
		TwoBitGrayscaleColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class FourBitGrayscaleColorSelector : public IColorSelector
	{
	public:
		FourBitGrayscaleColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class BlackRedGreenBlueColorSelector : public IColorSelector
	{
	public:
		BlackRedGreenBlueColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette1ColorSelector : public IColorSelector
	{
	public:
		Palette1ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette2ColorSelector : public IColorSelector
	{
	public:
		Palette2ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette3ColorSelector : public IColorSelector
	{
	public:
		Palette3ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette6ColorSelector : public IColorSelector
	{
	public:
		Palette6ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette7ColorSelector : public IColorSelector
	{
	public:
		Palette7ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette8ColorSelector : public IColorSelector
	{
	public:
		Palette8ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette9ColorSelector : public IColorSelector
	{
	public:
		Palette9ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette10ColorSelector : public IColorSelector
	{
	public:
		Palette10ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette11ColorSelector : public IColorSelector
	{
	public:
		Palette11ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Palette12ColorSelector : public IColorSelector
	{
	public:
		Palette12ColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Ega16ColorsColorSelector : public IColorSelector
	{
	public:
		Ega16ColorsColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row,
			int column, std::array<int, 3>& mistake) const override;
	};

	class Vga256ColorsColorSelector : public IColorSelector
	{
	public:
		Vga256ColorsColorSelector();

		_NODISCARD Color findOptimalColor(const Image& input_image, int row, int column, std::array<int, 3>& mistake) const override;
	};
}
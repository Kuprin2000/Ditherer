#pragma once
#define _USE_MATH_DEFINES
#include <array>
#include <vector>
#include "Image.h"

namespace Dithering
{
	class Ditherer
	{
	public:
		Ditherer(int min_distance, int test_points_count);

		void process(const Image& input_image, Image& output_image) const;

	private:
		// [0] - row, [1] - column
		using Point = std::array<uint16_t, 2>;

		enum class BlueNoisePixel : uint8_t
		{
			EMPTY,
			RESERVED,
			POINT
		};

		union BlueNoiseElem
		{
			struct
			{
				BlueNoisePixel pixel_1 : 2;
				BlueNoisePixel pixel_2 : 2;
				BlueNoisePixel pixel_3 : 2;
				BlueNoisePixel pixel_4 : 2;
			} pixels;

			uint8_t raw_data = 0;
		};

		class BlueNoiseMap
		{
		public:
			BlueNoiseMap() = delete;

			BlueNoiseMap(int rows_count, int columns_count, int min_distance);

			void setPoint(const Point& point);

			_NODISCARD BlueNoisePixel getValue(const Point& point) const;

			_NODISCARD int getRowsCount() const;

			_NODISCARD int getColumnsCount() const;

		private:
			std::vector<std::vector<BlueNoiseElem>> data_;

			int min_distance_;

			int origirnal_columns_count_ = 0;
		};

		_NODISCARD void generateBlueNoise(BlueNoiseMap& blue_noise) const;

		_NODISCARD Point generateRandomPoint(int max_row, int max_column) const;

		_NODISCARD Point generateRandomPointNearby(const Point& point, int max_row, int max_column) const;

		void ditherImage(const Image& input_image, const BlueNoiseMap& blue_noise, Image& output_image) const;

		int min_distance_;

		int test_points_count_;
	};
}
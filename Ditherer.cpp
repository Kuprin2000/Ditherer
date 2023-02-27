#include <cmath>
#include <algorithm>
#include "Ditherer.h"

namespace Dithering
{
	Ditherer::Ditherer(int min_distance, int test_points_count) : min_distance_(min_distance), test_points_count_(test_points_count)
	{
		srand((unsigned int)time(NULL));
	}

	void Ditherer::process(const Image& input_image, Image& output_image) const
	{
		int rows_count = 0;
		int columns_count = 0;
		input_image.getSize(rows_count, columns_count);

		BlueNoiseMap blue_noise(rows_count, columns_count, min_distance_);
		generateBlueNoise(blue_noise);

		ditherImage(input_image, blue_noise, output_image);

		for (int i = 0; i < rows_count; ++i)
		{
			for (int j = 0; j < columns_count; ++j)
			{
				Point curent_point = { i, j };
				if (blue_noise.getValue(curent_point) == BlueNoisePixel::POINT)
				{
					output_image.setColor({ 255, 255, 255 }, i, j);
				}
			}
		}
	}

	Ditherer::BlueNoiseMap::BlueNoiseMap(int rows_count, int columns_count, int min_distance) :
		origirnal_columns_count_(columns_count), min_distance_(min_distance)
	{
		data_.resize(rows_count);

		const auto elements_per_row = columns_count / 4 + (int)((columns_count % 4) != 0);
		for (auto& row : data_)
		{
			row.resize(elements_per_row);
		}
	}

	void Ditherer::BlueNoiseMap::setPoint(const Point& point)
	{
		const auto min_row = std::max(point[0] - min_distance_, 0);
		const auto max_row = std::min(point[0] + min_distance_, (int)data_.size() - 1);
		const auto min_column = std::max(point[1] - min_distance_, 0);
		const auto max_column = std::min(point[1] + min_distance_, origirnal_columns_count_ - 1);

		auto real_column = 0;
		auto shift = 0;
		uint8_t mask = UINT8_MAX;

		for (int i = min_row; i <= max_row; ++i)
		{
			for (int j = min_column; j <= max_column; ++j)
			{
				real_column = j / 4;
				shift = 2 * (j % 4);
				mask = UINT8_MAX - ((uint8_t)1 << shift) - ((uint8_t)1 << (shift + 1));
				data_[i][real_column].raw_data &= mask;
				data_[i][real_column].raw_data |= (uint8_t)BlueNoisePixel::RESERVED << shift;
			}
		}

		real_column = point[1] / 4;
		shift = 2 * (point[1] % 4);
		mask = UINT8_MAX - ((uint8_t)1 << shift) - ((uint8_t)1 << (shift + 1));
		data_[point[0]][real_column].raw_data &= mask;
		data_[point[0]][real_column].raw_data |= (uint8_t)BlueNoisePixel::POINT << shift;
	}

	Ditherer::BlueNoisePixel Ditherer::BlueNoiseMap::getValue(const Point& point) const
	{
		const auto real_column = point[1] / 4;
		const auto shift = 2 * (point[1] % 4);
		uint8_t mask = 0x3;
		return (BlueNoisePixel)((data_[point[0]][real_column].raw_data >> shift) & mask);
	}

	int Ditherer::BlueNoiseMap::getRowsCount() const
	{
		return (int)data_.size();
	}

	int Ditherer::BlueNoiseMap::getColumnsCount() const
	{
		return origirnal_columns_count_;
	}

	void Ditherer::generateBlueNoise(Ditherer::BlueNoiseMap& blue_noise) const
	{
		std::vector<Point> processing_list;

		auto first_point = generateRandomPoint(blue_noise.getRowsCount(), blue_noise.getColumnsCount());
		blue_noise.setPoint(first_point);
		processing_list.push_back(std::move(first_point));

		auto current_point_index = 0;
		Point random_point;
		while (!processing_list.empty())
		{
			current_point_index = rand() % (int)processing_list.size();

			for (int i = 0; i < test_points_count_; ++i)
			{
				random_point = generateRandomPointNearby(processing_list[current_point_index], (int)blue_noise.getRowsCount(), (int)blue_noise.getColumnsCount());
				if (blue_noise.getValue(random_point) != BlueNoisePixel::EMPTY)
				{
					continue;
				}

				blue_noise.setPoint(random_point);
				processing_list.push_back(random_point);
			}

			processing_list.erase(processing_list.begin() + current_point_index);
		}
	}

	Ditherer::Point Ditherer::generateRandomPoint(int max_row, int max_column) const
	{
		return { (uint16_t)(rand() % max_row),  (uint16_t)(rand() % max_column) };
	}

	Ditherer::Point Ditherer::generateRandomPointNearby(const Ditherer::Point& point, int max_row, int max_column) const
	{
		const auto distance = ((float)min_distance_ * (1.0f + (float)(rand() % 1024) / 1024.0f));
		const auto angle = (float)M_PI * (((float)(rand() % 2024) / 1024.0f) - 1.0f);

		const auto new_row = (uint16_t)std::clamp((int)point[0] + (int)(distance * sinf(angle)), 0, max_row - 1);
		const auto new_column = (uint16_t)std::clamp((int)point[1] + (int)(distance * cosf(angle)), 0, max_column - 1);

		return { new_row, new_column };
	}

	void Ditherer::ditherImage(const Image& input_image, const Ditherer::BlueNoiseMap& blue_noise, Image& output_image) const
	{
		// TODO
	}
}
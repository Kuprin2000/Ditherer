#include <cmath>
#include <omp.h>
#include <vector>
#include "Ditherer.h"

namespace Dithering
{
    Ditherer::Ditherer()
    {
        palettes_[(int)Palette::BLACK_AND_WHITE] = {{0, 0, 0}, {255, 255, 255}};
        palettes_[(int)Palette::BLACK_GRAY_AND_WHITE] = {{0, 0, 0}, {128, 128, 128}, {255, 255, 255}};
        palettes_[(int)Palette::TWO_BIT_GRAYSCALE] = {{0, 0, 0}, {85, 85, 85}, {170, 170, 170}, {255, 255, 255}};
        palettes_[(int)Palette::FOUR_BIT_GRAYSCALE] = {
            {0, 0, 0}, {17, 17, 17}, {34, 34, 34}, {51, 51, 51}, {68, 68, 68}, {85, 85, 85}, {102, 102, 102}, {119, 119, 119}, 
            {136, 136, 136}, {153, 153, 153}, {170, 170, 170}, {187, 187, 187}, {204, 204, 204}, {221, 221, 221}, {238, 238, 238}, {255, 255, 255}};

        palettes_[(int)Palette::BLACK_RED_GREEN_BLUE] = {{0, 0, 0}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

        palettes_[(int)Palette::BK_0011_PALETTE_1] = {{0, 0, 0}, {255, 255, 0}, {255, 0, 255}, {255, 0, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_2] = {{0, 0, 0}, {0, 255, 255}, {0, 0, 255}, {255, 0, 255}};
        palettes_[(int)Palette::BK_0011_PALETTE_3] = {{0, 0, 0}, {0, 255, 0}, {0, 255, 255}, {255, 255, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_6] = {{0, 0, 0}, {192, 0, 0}, {144, 0, 0}, {255, 0, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_7] = {{0, 0, 0}, {192, 255, 0}, {144, 255, 0}, {255, 255, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_8] = {{0, 0, 0}, {192, 0, 255}, {144, 0, 255}, {255, 0, 255}};
        palettes_[(int)Palette::BK_0011_PALETTE_9] = {{0, 0, 0}, {144, 255, 0}, {144, 0, 255}, {144, 0, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_10] = {{0, 0, 0}, {192, 255, 0}, {192, 0, 255}, {192, 0, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_11] = {{0, 0, 0}, {0, 255, 255}, {255, 255, 0}, {255, 0, 0}};
        palettes_[(int)Palette::BK_0011_PALETTE_12] = {{0, 0, 0}, {255, 0, 0}, {0, 255, 0}, {0, 255, 255}};

        palettes_[(int)Palette::EGA_16_COLORS] = {
            {0, 0, 0}, {0, 0, 170}, {0, 170, 0}, {0, 170, 170}, {170, 0, 0}, {170, 0, 170}, {170, 85, 0}, {170, 170, 170}, 
            {85, 85, 85}, {85, 85, 255}, {85, 255, 85}, {85, 255, 85}, {255, 85, 85}, {255, 85, 255}, {255, 255, 85}, {255, 255, 255}};

        palettes_[(int)Palette::VGA_256_COLORS] = {
            {0, 0, 0}, {0, 2, 170}, {20, 170, 0}, {0, 170, 170}, {170, 0, 3}, {170, 0, 170}, {170, 85, 0}, {170, 170, 170},
            {85, 85, 85}, {85, 85, 255}, {85, 255, 85}, {85, 255, 255}, {255, 85, 85}, {253, 85, 255}, {255, 255, 85}, {255, 255, 255},
            {0, 0, 0}, {16, 16, 16}, {32, 32, 32}, {53, 53, 53}, {69, 69, 69}, {85, 85, 85}, {101, 101, 101}, {117, 117, 117},
            {138, 138, 138}, {154, 154, 154}, {170, 170, 170}, {186, 186, 186}, {202, 202, 202}, {223, 223, 223}, {239, 239, 239}, {255, 255, 255},
            {0, 4, 255}, {65, 4, 255}, {130, 3, 255}, {190, 2, 255}, {253, 0, 255}, {254, 0, 190}, {255, 0, 130}, {255, 0, 65},
            {255, 0, 8}, {255, 65, 5}, {255, 130, 0}, {255, 190, 0}, {255, 255, 0}, {190, 255, 0}, {130, 255, 0}, {65, 255, 1},
            {36, 255, 0}, {34, 255, 66}, {29, 255, 130}, {18, 255, 190}, {0, 255, 255}, {0, 190, 255}, {1, 130, 255}, {0, 65, 255},
            {130, 130, 255}, {158, 130, 255}, {190, 130, 255}, {223, 130, 255}, {253, 130, 255}, {254, 130, 223}, {255, 130, 190}, {255, 130, 158},
            {255, 130, 130}, {255, 158, 130}, {255, 190, 130}, {255, 223, 130}, {255, 255, 130}, {223, 255, 130}, {190, 255, 130}, {158, 255, 130},
            {130, 255, 130}, {130, 255, 158}, {130, 255, 190}, {130, 255, 223}, {130, 255, 255}, {130, 223, 255}, {130, 190, 255}, {130, 158, 255},
            {186, 186, 255}, {202, 186, 255}, {223, 186, 255}, {239, 186, 255}, {254, 186, 255}, {254, 186, 239}, {255, 186, 223}, {255, 186, 202},
            {255, 186, 186}, {255, 202, 186}, {255, 223, 186}, {255, 239, 186}, {255, 255, 186}, {239, 255, 186}, {223, 255, 186}, {202, 255, 187},
            {186, 255, 186}, {186, 255, 202}, {186, 255, 223}, {186, 255, 239}, {186, 255, 255}, {186, 239, 255}, {186, 223, 255}, {186, 202, 255},
            {1, 1, 113}, {28, 1, 113}, {57, 1, 113}, {85, 0, 113}, {113, 0, 113}, {113, 0, 85}, {113, 0, 57}, {113, 0, 28},
            {113, 0, 1}, {113, 28, 1}, {113, 57, 0}, {113, 85, 0}, {113, 113, 0}, {85, 113, 0}, {57, 113, 0}, {28, 113, 0},
            {9, 113, 0}, {9, 113, 28}, {6, 113, 57}, {3, 113, 85}, {0, 113, 113}, {0, 85, 113}, {0, 57, 113}, {0, 28, 113},
            {57, 57, 113}, {69, 57, 113}, {85, 57, 113}, {97, 57, 113}, {113, 57, 113}, {113, 57, 97}, {113, 57, 85}, {113, 57, 69},
            {113, 57, 57}, {113, 69, 57}, {113, 85, 57}, {113, 97, 57}, {113, 113, 57}, {97, 113, 57}, {85, 113, 57}, {69, 113, 58},
            {57, 113, 57}, {57, 113, 69}, {57, 113, 85}, {57, 113, 97}, {57, 113, 113}, {57, 97, 113}, {57, 85, 113}, {57, 69, 114},
            {81, 81, 113}, {89, 81, 113}, {97, 81, 113}, {105, 81, 113}, {113, 81, 113}, {113, 81, 105}, {113, 81, 97}, {113, 81, 89},
            {113, 81, 81}, {113, 89, 81}, {113, 97, 81}, {113, 105, 81}, {113, 113, 81}, {105, 113, 81}, {97, 113, 81}, {89, 113, 81},
            {81, 113, 81}, {81, 113, 90}, {81, 113, 97}, {81, 113, 105}, {81, 113, 113}, {81, 105, 113}, {81, 97, 113}, {81, 89, 113},
            {0, 0, 66}, {17, 0, 65}, {32, 0, 65}, {49, 0, 65}, {65, 0, 65}, {65, 0, 50}, {65, 0, 32}, {65, 0, 16},
            {65, 0, 0}, {65, 16, 0}, {65, 32, 0}, {65, 49, 0}, {65, 65, 0}, {49, 65, 0}, {32, 65, 0}, {16, 65, 0},
            {3, 65, 0}, {3, 65, 16}, {2, 65, 32}, {1, 65, 49}, {0, 65, 65}, {0, 49, 65}, {0, 32, 65}, {0, 16, 65},
            {32, 32, 65}, {40, 32, 65}, {49, 32, 65}, {57, 32, 65}, {65, 32, 65}, {65, 32, 57}, {65, 32, 49}, {65, 32, 40},
            {65, 32, 32}, {65, 40, 32}, {65, 49, 32}, {65, 57, 33}, {65, 65, 32}, {57, 65, 32}, {49, 65, 32}, {40, 65, 32},
            {32, 65, 32}, {32, 65, 40}, {32, 65, 49}, {32, 65, 57}, {32, 65, 65}, {32, 57, 65}, {32, 49, 65}, {32, 40, 65},
            {45, 45, 65}, {49, 45, 65}, {53, 45, 65}, {61, 45, 65}, {65, 45, 65}, {65, 45, 61}, {65, 45, 53}, {65, 45, 49},
            {65, 45, 45}, {65, 49, 45}, {65, 53, 45}, {65, 61, 45}, {65, 65, 45}, {61, 65, 45}, {53, 65, 45}, {49, 65, 45},
            {45, 65, 45}, {45, 65, 49}, {45, 65, 53}, {45, 65, 61}, {45, 65, 65}, {45, 61, 65}, {45, 53, 65}, {45, 49, 65} };
    }

    void Ditherer::process(Image &input_image, Image &output_image, Palette palette, int algorithm_id, int threads_count) const
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

    void Ditherer::processSingleThread(Image &input_image, Image &output_image, Palette palette) const
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

    void Ditherer::processMultiThread(Image &input_image, Image &output_image, Palette palette, int threads_count) const
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

    void Ditherer::processSingleThreadTwo(Image &input_image, Image &output_image, Palette palette) const
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

    void Ditherer::processMultiThreadTwo(Image &input_image, Image &output_image, Palette palette, int threads_count) const
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

    void Ditherer::processPixel(Image &input_image, Image &output_image, Palette palette, int row, int column) const
    {
        auto optimal_color = 0;
        std::array<int, 3> mistake = {0};
        findOptimalColor(input_image, row, column, palette, optimal_color, mistake);

        output_image.setColor(palettes_[(int)palette][optimal_color], row, column);

        auto rows_count = 0;
        auto columns_count = 0;
        input_image.getSize(rows_count, columns_count);

        const std::array<int, 3> mistake_7_48 = {(int)(mistake[0] * coeff_7_48_), (int)(mistake[1] * coeff_7_48_), (int)(mistake[2] * coeff_7_48_)};
        const std::array<int, 3> mistake_5_48 = {(int)(mistake[0] * coeff_5_48_), (int)(mistake[1] * coeff_5_48_), (int)(mistake[2] * coeff_5_48_)};
        const std::array<int, 3> mistake_3_48 = {(int)(mistake[0] * coeff_3_48_), (int)(mistake[1] * coeff_3_48_), (int)(mistake[2] * coeff_3_48_)};
        const std::array<int, 3> mistake_1_48 = {(int)(mistake[0] * coeff_1_48_), (int)(mistake[1] * coeff_1_48_), (int)(mistake[2] * coeff_1_48_)};

        Color tmp_color = {0};
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

    void Ditherer::findOptimalColor(const Image &input_image, int row, int column, Palette palette, int &optimal_color, std::array<int, 3> &mistake) const
    {
        const auto input_color = input_image.getColor(row, column);

        auto min_delta = FLT_MAX;
        auto delta = 0.0f;

        for (int i = 0; i < palettes_[(int)palette].size(); ++i)
        {
            const auto &color = palettes_[(int)palette][i];

            delta = powf((float)color[0] - input_color[0], 2) + powf((float)color[1] - input_color[1], 2) + powf((float)color[2] - input_color[2], 2);
            if (delta < min_delta)
            {
                min_delta = delta;
                mistake = {input_color[0] - color[0], input_color[1] - color[1], input_color[2] - color[2]};
                optimal_color = i;
            }
        }
    }
}
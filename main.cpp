#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Ditherer.h"

int main(int argc, char* argv[])
{
	if (argc != 6)
	{
		std::cout << "You must type following arguments:" <<
			std::endl << "I) Input image path;" <<
			std::endl << "II) Output image path;" <<
			std::endl << "III) Color palette:" <<
			std::endl << "0) Black and white (0010, 0011, Neon);" <<
			std::endl << "1) Black, gray and white (0011);" <<
			std::endl << "2) Two-bit grayscale (Neon);" <<
			std::endl << "3) Four-bit grayscale (Neon);" <<
			std::endl << "4) Black, red, green, blue (0010, 0011);" <<
			std::endl << "5) BK-0011 pallete 1 (0011);" <<
			std::endl << "6) BK-0011 pallete 2 (0011);" <<
			std::endl << "7) BK-0011 pallete 3 (0011);" <<
			std::endl << "8) BK-0011 pallete 6 (0011);" <<
			std::endl << "9) BK-0011 pallete 7 (0011);" <<
			std::endl << "10) BK-0011 pallete 8 (0011);" <<
			std::endl << "11) BK-0011 pallete 9 (0011);" <<
			std::endl << "12) BK-0011 pallete 10 (0011);" <<
			std::endl << "13) BK-0011 pallete 11 (0011);" <<
			std::endl << "14) BK-0011 pallete 12 (0011);" <<
			std::endl << "15) VGA 16 colors (Neon);" <<
			std::endl << "16) VGA 256 colors (Neon);" <<
			std::endl << "IV) Parallel algorithm type (0 or 1);" <<
			std::endl << "V) Threads count;";

		return 0;
	}

	std::string input_path = argv[1];
	std::string output_path = argv[2];

	const auto palette_int = atoi(argv[3]);
	const auto algorithm_id = atoi(argv[4]);
	const auto threads_count = atoi(argv[5]);

	if (threads_count < 1 || threads_count > 1000
		|| algorithm_id < 0 || algorithm_id > 1
		|| palette_int < 0 || palette_int >= Dithering::PALLETES_COUNT)
	{
		std::cout << "You typed wrong parameters" << std::endl;
		return 1;
	}

	const auto pallete = (Dithering::Palette)palette_int;

	Dithering::Image input_image;
	try
	{
		input_image.openImage(input_path);
	}
	catch (...)
	{
		std::cout << "Can't open input file";
	}

	auto rows = 0;
	auto columns = 0;
	input_image.getSize(rows, columns);

	Dithering::Image output_image;
	try
	{
		output_image.createImage(output_path, rows, columns);
	}
	catch (...)
	{
		std::cout << "Can't create output file";
	}

	Dithering::Ditherer ditherer;
	const auto start_time = std::chrono::high_resolution_clock::now();

	try
	{
		ditherer.process(input_image, output_image, pallete, algorithm_id, threads_count);
	}
	catch (...)
	{
		std::cout << "Can't dither image";
	}

	const auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << "We proceeded image with resolution " << columns << "x" << rows << " at " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " milliseconds";

	try
	{
		output_image.saveImage();
	}
	catch (...)
	{
		std::cout << "Can't save the result";
	}

	return 0;
}
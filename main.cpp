#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Ditherer.h"

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "You must type following arguments:" <<
			std::endl << "1) Input image path;" <<
			std::endl << "2) Output image path;" <<
			std::endl << "3) Parallel algorithm type (0 or 1);" <<
			std::endl << "4) Threads count;";

		return 0;
	}

	std::string input_path = argv[1];
	std::string output_path = argv[2];

	const auto algorithm_id = atoi(argv[3]);
	const auto threads_count = atoi(argv[4]);

	if (threads_count < 1 || threads_count > 1000 || algorithm_id < 0 || algorithm_id > 1)
	{
		std::cout << "You typed wrong threads count or wrong algorithm id" << std::endl;
		return 1;
	}

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
		ditherer.process(input_image, output_image, algorithm_id, threads_count);
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
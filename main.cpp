#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Ditherer.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "You must type following arguments:" << std::endl << "1) Input image path;"
			<< std::endl << "2) Output image path;" << std::endl << "3) Thread count (should be multiple of 3);";

		return 0;
	}

	std::string input_path = argv[1];
	std::string output_path = argv[2];

	Dithering::Image input_image;
	input_image.openImage(input_path);

	auto rows = 0;
	auto columns = 0;
	input_image.getSize(rows, columns);

	Dithering::Image output_image;
	output_image.createImage(output_path, rows, columns);

	const auto start_time = std::chrono::high_resolution_clock::now();

	const auto threads_count = atoi(argv[3]);
	Dithering::Ditherer ditherer(threads_count);
	ditherer.process(input_image, output_image);

	const auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << "We proceded image with resolution " << columns << "x" << rows << " at " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " milliseconds";

	output_image.saveImage(Dithering::Image::pathToFormat(output_path));

	return 0;
}
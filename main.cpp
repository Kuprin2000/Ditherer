#include <iostream>
#include <cstdlib>
#include "Image.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "You must type folowing argumets:" << std::endl << "1) Input image path;" 
			<< std::endl << "2) Output image path;" << std::endl << std::endl << "3) Quality;";

		return 0;
	}


	std::string input_path = argv[1];
	std::string output_path = argv[2];

	Dithering::Image input_image;
	input_image.openImage(input_path);

	auto rows = 0;
	int columns = 0;
	input_image.getSize(rows, columns);

	Dithering::Image output_image;
	output_image.createImage(output_path, rows, columns);

	// TODO: Ditherer

	output_image.saveImage(Dithering::Image::pathToFormat(output_path), std::atoi(argv[3]));

	return 0;
}
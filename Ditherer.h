#pragma once
#include "Image.h"

namespace Dithering
{
	class Ditherer
	{
	public:
		void process(const Image& imput_image, const Image& output_image) const;
	};
}
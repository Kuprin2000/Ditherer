#pragma once
#include <memory>
#include "Image.h"
#include "PaletteHandler.h"

namespace Dithering
{
	enum class Ditherer : uint8_t
	{
		JJNDITHERER,
		COUNT
	};

	class IDitherer
	{
	public:
		IDitherer() = default;

		IDitherer(const IDitherer& ditherer) = delete;

		void operator=(const IDitherer& selector) = delete;

		_NODISCARD virtual bool process(Image& input_image, Image& output_image, int palette, int threads_count) const = 0;

		_NODISCARD const std::string& get_name() const;

		_NODISCARD virtual int get_palletes_count() const = 0;

		_NODISCARD virtual const std::vector<std::string>& get_palletes_names() const = 0;

		virtual ~IDitherer() = default;

	protected:
		std::string name_ = "No name";
	};

	class JJNDitherer : public IDitherer
	{
	public:
		JJNDitherer(int algorithm_id, bool use_speed_up_structures);

		_NODISCARD bool process(Image& input_image, Image& output_image, int palette, int threads_count) const final;

		_NODISCARD int get_palletes_count() const final;

		_NODISCARD const std::vector<std::string>& get_palletes_names() const final;

	private:
		void processSingleThread(Image& input_image, Image& output_image, int palette) const;

		void processMultiThread(Image& input_image, Image& output_image, int palette, int threads_count) const;

		void processSingleThreadTwo(Image& input_image, Image& output_image, int palette) const;

		void processMultiThreadTwo(Image& input_image, Image& output_image, int palette, int threads_count) const;

		void processPixel(Image& input_image, Image& output_image, const IPaletteHandler* color_selector, int row, int column) const;

	private:
		// 7.0f / 48.0f
		const float coeff_7_48_ = 0.1458333333f;

		// 5.0f / 48.0f
		const float coeff_5_48_ = 0.1041666667f;

		// 3.0f / 48.0f
		const float coeff_3_48_ = 0.0625000000f;

		// 1.0f / 48.0f
		const float coeff_1_48_ = 0.0208333333f;

		int algorithm_id_;
		bool use_speed_up_structures_;
		std::array<std::unique_ptr<IPaletteHandler>, (int)Palette::COUNT> palette_handlers_;
		std::vector<std::string> palette_handlers_names_;
	};
}
#include "utils.h"
#include <boost/gil/extension/io/png_io.hpp>

using namespace boost::gil;

template <typename SrcView>
PicturePixels getPixels(const SrcView& src) 
{
	PicturePixels pixels(src.height(), std::vector<channel_t>(src.width(), 0));
    for (int y=0; y<src.height(); ++y) 
    {
        typename SrcView::x_iterator src_it = src.row_begin(y);
        for (int x=0; x<src.width(); ++x) 
        {
            pixels[y][x] = src_it[x];
        }
    }
	return pixels;
}

template <typename DstView>
void copyPixelsToImage(const DstView& dst, const PicturePixels& pixels)
{
    for (int y=0; y<dst.height(); ++y) 
    {
        typename DstView::x_iterator dst_it = dst.row_begin(y);
        for (int x=0; x<dst.width(); ++x) 
        {
            dst_it[x] = pixels[y][x];
        }
    }
}

PicturePixels getPixelsFromPngImage(const std::string& FileName)
{
	rgb8_image_t img;
	png_read_image(FileName.c_str(), img);
	return getPixels(const_view(img));
}

void writePixelsToPngImage(const std::string& FileName, const PicturePixels& pixels)
{
	rgb8_image_t::point_t dimension(pixels[0].size(), pixels.size());
	rgb8_image_t img_out(dimension);
	copyPixelsToImage(view(img_out), pixels);
	png_write_view(FileName.c_str(), const_view(img_out));
}
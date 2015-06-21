#pragma once

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <vector>
#include <string>

typedef boost::gil::rgb8c_pixel_t channel_t;
typedef std::vector<std::vector<channel_t>> PicturePixels;

PicturePixels getPixelsFromPngImage(const std::string& FileName);
void writePixelsToPngImage(const std::string& FileName, const PicturePixels& pixels);
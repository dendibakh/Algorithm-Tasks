#include "Seam Carving.h"

int main()
{
        PicturePixels pixels = getPixelsFromPngImage("E:\\HJoceanSmall.png");
        SeamCarver seamCarver(pixels);
        for (int i = 0; i < 250; ++i)
        {
                DijkstraSP::PathToStack actual = std::move(seamCarver.findVerticalSeam());
                seamCarver.removeVerticalSeam(actual);
        }
        writePixelsToPngImage("E:\\new_HJoceanSmall.png", seamCarver.getPixels());
}
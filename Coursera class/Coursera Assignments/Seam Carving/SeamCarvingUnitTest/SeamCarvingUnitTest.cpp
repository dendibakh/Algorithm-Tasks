#include "stdafx.h"
#include "Seam Carving.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace SeamCarvingUnitTest
{
   [TestClass]
   public ref class SeamCarvingUnitTest
   {
   public:
      [TestMethod]
      void TestgetPixelsFromPngImage()
      {
         try
         {
            PicturePixels pixels = getPixelsFromPngImage("E:\\6x5.png");
            Assert::AreEqual(size_t(5), pixels.size());
            Assert::AreEqual(size_t(6), pixels[0].size());
         }
         catch(std::exception &)
         {
            Assert::Fail("smth wrong");
         }
      };

      [TestMethod]
      void TestwritePixelsToPngImage()
      {
         try
         {
            PicturePixels pixels = getPixelsFromPngImage("E:\\6x5.png");
            writePixelsToPngImage("E:\\new_6x5.png", pixels);
            PicturePixels newPixels = getPixelsFromPngImage("E:\\new_6x5.png");
            Assert::AreEqual(size_t(5), newPixels.size());
            Assert::AreEqual(size_t(6), newPixels[0].size());
         }
         catch(std::exception &)
         {
            Assert::Fail("smth wrong");
         }
      };

      [TestMethod]
      void TestcalcPixelsEnergy()
      {
         try
         {
            PicturePixels pixels = getPixelsFromPngImage("E:\\6x5.png");
            pixelsEnergy pixEnegry = calcPixelsEnergy(pixels);

            Assert::AreEqual(size_t(5), pixEnegry.size());
            Assert::AreEqual(size_t(6), pixEnegry[0].size());

            Assert::AreEqual(195075, pixEnegry[0][0]);
            Assert::AreEqual(195075, pixEnegry[0][1]);
            Assert::AreEqual(195075, pixEnegry[0][2]);
            Assert::AreEqual(195075, pixEnegry[0][3]);
            Assert::AreEqual(195075, pixEnegry[0][4]);
            Assert::AreEqual(195075, pixEnegry[0][5]);

            Assert::AreEqual(195075, pixEnegry[1][0]);
            Assert::AreEqual(23346, pixEnegry[1][1]);
            Assert::AreEqual(51304, pixEnegry[1][2]);
            Assert::AreEqual(31519, pixEnegry[1][3]);
            Assert::AreEqual(55112, pixEnegry[1][4]);
            Assert::AreEqual(195075, pixEnegry[1][5]);

            Assert::AreEqual(195075, pixEnegry[2][0]);
            Assert::AreEqual(47908, pixEnegry[2][1]);
            Assert::AreEqual(61346, pixEnegry[2][2]);
            Assert::AreEqual(35919, pixEnegry[2][3]);
            Assert::AreEqual(38887, pixEnegry[2][4]);
            Assert::AreEqual(195075, pixEnegry[2][5]);

            Assert::AreEqual(195075, pixEnegry[3][0]);
            Assert::AreEqual(31400, pixEnegry[3][1]);
            Assert::AreEqual(37927, pixEnegry[3][2]);
            Assert::AreEqual(14437, pixEnegry[3][3]);
            Assert::AreEqual(63076, pixEnegry[3][4]);
            Assert::AreEqual(195075, pixEnegry[3][5]);
            
            Assert::AreEqual(195075, pixEnegry[4][0]);
            Assert::AreEqual(195075, pixEnegry[4][1]);
            Assert::AreEqual(195075, pixEnegry[4][2]);
            Assert::AreEqual(195075, pixEnegry[4][3]);
            Assert::AreEqual(195075, pixEnegry[4][4]);
            Assert::AreEqual(195075, pixEnegry[4][5]);
         }
         catch(std::exception &)
         {
            Assert::Fail("smth wrong");
         }
      };

      [TestMethod]
      void TestfindAndRemoveVerticalSeam()
      {
         try
         {
             PicturePixels pixels = getPixelsFromPngImage("E:\\6x5.png");
             SeamCarver seamCarver(pixels);
             DijkstraSP::PathToStack actual = seamCarver.findVerticalSeam();
             Assert::IsTrue(std::find(actual.begin(), actual.end(), 9) != actual.end());
			 Assert::IsTrue(std::find(actual.begin(), actual.end(), 15) != actual.end());
			 Assert::IsTrue(std::find(actual.begin(), actual.end(), 21) != actual.end());
             seamCarver.removeVerticalSeam(actual);
             writePixelsToPngImage("E:\\new_6x5.png", seamCarver.getPixels());
             PicturePixels newPixels = getPixelsFromPngImage("E:\\new_6x5.png");
             Assert::AreEqual(size_t(5), newPixels.size());
             Assert::AreEqual(size_t(5), newPixels[0].size());
         }
         catch(std::exception &)
         {
            Assert::Fail("smth wrong");
         }
      };

      [TestMethod]
      void TestfindAndRemoveVerticalSeamBigPicture()
      {
         try
         {
             PicturePixels pixels = getPixelsFromPngImage("E:\\HJoceanSmall.png");
             Assert::AreEqual(size_t(285), pixels.size());
             Assert::AreEqual(size_t(507), pixels[0].size());
             SeamCarver seamCarver(pixels);

             DijkstraSP::PathToStack actual = std::move(seamCarver.findVerticalSeam());
             seamCarver.removeVerticalSeam(actual);

             writePixelsToPngImage("E:\\new_HJoceanSmall.png", seamCarver.getPixels());
             PicturePixels newPixels = getPixelsFromPngImage("E:\\new_HJoceanSmall.png");
             Assert::AreEqual(size_t(285), newPixels.size());
             Assert::AreEqual(size_t(506), newPixels[0].size());
         }
         catch(std::exception &)
         {
            Assert::Fail("smth wrong");
         }
      };
   };
}

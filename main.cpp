// Copyright 2022 Eric Smith <spacewar@gmail.com>

#include <iostream>

#include <QImage>

#include "deskew.h"

int main(int argc, char **argv)
{
  Deskew deskew;

  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " image\n";
      return 1;
    }

  QImage image(argv[1]);

  if (image.isNull())
    {
      std::cerr << "unable to load image\n";
      return 1;
    }

  if (image.format() != QImage::Format_Grayscale8)
    {
      std::cerr << "image must be 8-bit grayscale\n";
      return 1;
    }

  

  deskew.Init(image.bits(), image.width(), image.height());
  double angle = deskew.GetSkewAngle();
  std::cout << angle << "\n";
  return 0;
}

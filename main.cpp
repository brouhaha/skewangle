// Copyright 2022 Eric Smith <spacewar@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

/*
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* The names of its contributors may not be used to
  endorse or promote products derived from this software without specific prior
  written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>

#include <QImage>

#include "skewangle.h"

int main(int argc, char **argv)
{
  SkewAngle skewangle;

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

  

  skewangle.Init(image.bits(), image.width(), image.height());
  double angle = skewangle.GetSkewAngle();
  std::cout << angle << "\n";
  return 0;
}

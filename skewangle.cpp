// skewangle
// from http://sydlogan.com/deskew.html
// SPDX-License-Identifier: BSD-3-Clause

/* 
Copyright (c) 2009, Syd Logan All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
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

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "skewangle.h"
#include <math.h>

SkewAngle::SkewAngle() : 
   m_cAlphaStart(-20.0),
   m_cAlphaStep(0.2),
   m_cSteps(40 * 5),
   m_cDStep(1.0),
   m_cHMatrix(NULL)
{
}

SkewAngle::~SkewAngle()
{
   if (m_cHMatrix) {
      free(m_cHMatrix);
   }
}

void 
SkewAngle::Init(uint8_t *buf, const int width, const int height)
{
   m_buf = buf;
   m_width = width;
   m_height = height;
   m_cDMin = -width;
   int cDCount = 2 * (width + height) / m_cDStep;
   m_cHMatrixSize = cDCount * m_cSteps;
   m_cHMatrix = (int *) malloc(sizeof(int) * m_cHMatrixSize);
}

double 
SkewAngle::GetSkewAngle()
{
   int count = 20;
   double sum = 0.0;
   HoughLine **top;

   // Calculate Hough transform

   Calc();

   // Get the best 20 results

   top = GetTop(count);

   if (!top) {
      return 0.0;
   }

   // Return the average of the best

   for (int i = 0; i < count; i++) {
      sum += top[i]->alpha;
      // printf("Best %d is %f\n", i, top[i]->alpha);
      delete top[i];
   }
  
   // printf("Sum is %f\n", sum); 
   free(top);
   double ret = (sum / count);
   // printf("ret is %f\n", ret);
   return ret;
}

HoughLine **
SkewAngle::GetTop(const int count)
{
   HoughLine **hl;
   HoughLine *tmp;
   int dIndex;
   int alphaIndex;

   hl = (HoughLine **) malloc(count * sizeof(HoughLine *));

   for (int i = 0; i < count; i++) {
       hl[i] = new HoughLine;
   }

   for (int i = 0; i < m_cHMatrixSize; i++) {
      if (m_cHMatrix[i] > hl[count - 1]->count) {
         hl[count - 1]->count = m_cHMatrix[i];
         hl[count - 1]->index = i;
         int j = count - 1;
         while (j > 0 && hl[j]->count > hl[j - 1]->count) {
            tmp = hl[j];
            hl[j] = hl[j - 1];
            hl[j - 1] = tmp;
            j -= 1;
         }
      }
   }

   for (int i = 0; i < count; i++) {
      dIndex = hl[i]->index / m_cSteps;
      alphaIndex = hl[i]->index - dIndex * m_cSteps;
      hl[i]->alpha = GetAlpha(alphaIndex);
      hl[i]->d = dIndex + m_cDMin;
   }
   return hl;
}

void 
SkewAngle::Calc()
{
   int hMin = m_height / 4;
   int hMax = m_height * 3 / 4;

   for (int y = hMin; y <= hMax; y++) {
      for (int x = 1; x < m_width - 1; x++) {
         if (IsBlack(x, y)) {
            if (!IsBlack(x, y + 1)) {
               Calc(x, y);
            }
         }
      }
   }
}

void 
SkewAngle::Calc(const int x, const int y)
{
   double d;
   int dIndex;
   int index;

   for (int alpha = 0; alpha < m_cSteps; alpha++) {
      double rads = GetAlpha(alpha) * 3.14159265354 / 180.0;
      d = y * cos(rads) - x * sin(rads);
      dIndex = CalcDIndex(d);
      index = dIndex * m_cSteps + alpha;
      m_cHMatrix[index]++; 
   }
}

bool 
SkewAngle::IsBlack(const int x, const int y)
{
   //luminance = (c.R * 0.299) + (c.G * 0.587) + (c.B * 0.114)
   return (*(m_buf + y * m_width + x) < 140 ? true : false);
}

double 
SkewAngle::GetAlpha(const int index)
{
   return m_cAlphaStart + index * m_cAlphaStep;
}

int 
SkewAngle::CalcDIndex(const double d)
{
   return (int) (d - m_cDMin);
}

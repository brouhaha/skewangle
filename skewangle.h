// skewangle
// from http://sydlogan.com/deskew.html
// based on VB.net code from http://imaging.gmse.net/download/gmseDeskew_vb.html
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

#if !defined(__SKEWANGLE_H__)
#define __SKEWANGLE_H__

#include <cstdint>

struct HoughLine
{
   int count = 0;
   int index = 0;
   double alpha = 0.0;
   double d = 0.0;
};

class SkewAngle
{
public:
   SkewAngle();
   ~SkewAngle();
   void Init(uint8_t *buf, const int width, const int height);
   double GetSkewAngle();

private:
   HoughLine **GetTop(const int count);
   void Calc();
   void Calc(const int x, const int y);
   bool IsBlack(const int x, const int y);
   double GetAlpha(const int index);
   int CalcDIndex(const double d);

   int m_width;
   int m_height;
   uint8_t *m_buf;
   int m_cDMin;
   double m_cAlphaStart;
   double m_cAlphaStep;
   int m_cSteps;
   double m_cDStep;
   int *m_cHMatrix;
   int m_cHMatrixSize;
};

#endif

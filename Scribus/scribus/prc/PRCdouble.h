/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/
#ifndef __PRC_DOUBLE_H
#define __PRC_DOUBLE_H

#include <cstdlib>
#include <cmath>

#ifdef HAVE_CONFIG_H
#include "scconfig.h"
#endif
// from Adobe's documentation

union ieee754_double
{
 double d;
 /* This is the IEEE 754 double-precision format. */
 struct
 {
#if defined(WORDS_BIGENDIAN)
  unsigned int negative:1;
  unsigned int exponent:11;
  /* Together these comprise the mantissa.  */
  unsigned int mantissa0:20;
  unsigned int mantissa1:32;
#else
  /* Together these comprise the mantissa.  */
  unsigned int mantissa1:32;
  unsigned int mantissa0:20;
  unsigned int exponent:11;
  unsigned int negative:1;
#endif
 } ieee;
};




enum ValueType {VT_double,VT_exponent};

struct sCodageOfFrequentDoubleOrExponent
{
  short Type;
  short NumberOfBits;
  unsigned Bits;
  union {
    unsigned ul[2];
    double Value;
  } u2uod;
};
#if defined(WORDS_BIGENDIAN)
#       define DOUBLEWITHTWODWORD(upper,lower)  upper,lower
#       define UPPERPOWER       (0)
#       define LOWERPOWER       (!UPPERPOWER)

#       define NEXTBYTE(pbd)                            ((pbd)++)
#       define PREVIOUSBYTE(pbd)                ((pbd)--)
#       define MOREBYTE(pbd,pbend)              ((pbd)<=(pbend))
#       define OFFSETBYTE(pbd,offset)   ((pbd)+=offset)
#       define BEFOREBYTE(pbd)                  ((pbd)-1)
#       define DIFFPOINTERS(p1,p2)              ((p1)-(p2))
#       define SEARCHBYTE(pbstart,b,nb) (unsigned char *)memrchr((pbstart),(b),(nb))
#       define BYTEAT(pb,i)     *((pb)-(i))
#else
#       define DOUBLEWITHTWODWORD(upper,lower)  lower,upper
#       define UPPERPOWER       (1)
#       define LOWERPOWER       (!UPPERPOWER)

#       define NEXTBYTE(pbd)                            ((pbd)--)
#       define PREVIOUSBYTE(pbd)                ((pbd)++)
#       define MOREBYTE(pbd,pbend)              ((pbd)>=(pbend))
#       define OFFSETBYTE(pbd,offset)   ((pbd)-=offset)
#       define BEFOREBYTE(pbd)                  ((pbd)+1)
#       define DIFFPOINTERS(p1,p2)              ((unsigned)((p2)-(p1)))
#       define SEARCHBYTE(pbstart,b,nb) (unsigned char *)memchr((pbstart),(b),(nb))
#       define BYTEAT(pb,i)     *((pb)+(i))
#endif

#define MAXLENGTHFORCOMPRESSEDTYPE      ((22+1+1+4+6*(1+8))+7)/8

#define NEGATIVE(d)     (((union ieee754_double *)&(d))->ieee.negative)
#define EXPONENT(d)     (((union ieee754_double *)&(d))->ieee.exponent)
#define MANTISSA0(d)    (((union ieee754_double *)&(d))->ieee.mantissa0)
#define MANTISSA1(d)    (((union ieee754_double *)&(d))->ieee.mantissa1)

typedef unsigned char PRCbyte;
typedef unsigned short PRCword;
typedef unsigned PRCdword;

extern PRCdword stadwZero[2],stadwNegativeZero[2];

#define NUMBEROFELEMENTINACOFDOE   (2077)

#if defined( WORDS_BIGENDIAN )
#       define DOUBLEWITHTWODWORDINTREE(upper,lower)    {upper,lower} 
#else
#       define DOUBLEWITHTWODWORDINTREE(upper,lower)    {lower,upper}
#endif
extern sCodageOfFrequentDoubleOrExponent acofdoe[NUMBEROFELEMENTINACOFDOE];

struct sCodageOfFrequentDoubleOrExponent* getcofdoe(unsigned,short);

#define STAT_V
#define STAT_DOUBLE

int stCOFDOECompare(const void*,const void*);

#if defined(WORDS_BIGENDIAN)
void *memrchr(const void *,int,size_t);
#endif


#endif // __PRC_DOUBLE_H

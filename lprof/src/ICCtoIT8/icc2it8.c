//
//  Little cms - profiler construction set
//  Copyright (C) 1998-2001 Marti Maria
//
// THIS SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL MARTI MARIA BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
// INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#include "lcmsprf.h"


// getopt() interface -----------------------------------------------------

extern int   xoptind;
extern char *xoptarg;
extern int   xopterr;
int    cdecl xgetopt(int argc, char *argv[], char *optionS);

// ------------------------------------------------------------------------

static int  Verbose = 0;
static int  Intent  = INTENT_ABSOLUTE_COLORIMETRIC;
static BOOL lUseLab = FALSE;

static BOOL lDontRGB = FALSE;
static BOOL lReverse = FALSE;
static char *cInProf = NULL;
static char *cSheet  = NULL;
static double Noise  = 0.0;
static double Intensity = 100.0;

// These are the RGB values of a mockup of hIT8 target

typedef struct {
               const char* Patch;
               int R, G, B;

               } RGBPATCH;


typedef struct {
               const char* Patch;
               double L, a, b;

               } LabPATCH;


// Emulated RGB of hIT8 patches
static RGBPATCH EmulatedRGB[] = {

{"A1",  50,        30,        32},
{"A2",  63,        24,        27},
{"A3",  74,        10,        27},
{"A4",  83,        0,         30},
{"A5",  98,        68,        68},
{"A6",  119,       56,        65},
{"A7",  136,       42,        58},
{"A8",  149,       29,        57},
{"A9",  171,      151,       152},
{"A10", 184,      145,       148},
{"A11", 196,      140,       143},
{"A12", 205,      135,       143},
{"A13", 237,      252,       255},
{"A14", 254,      245,       248},
{"A15", 255,      248,       245},
{"A16", 244,      244,       244},
{"A17", 255,      238,       233},
{"A18", 224,      255,       233},
{"A19", 246,      243,       252},



{"B1",  50,     32,     28},
{"B2",  58,     28,     20},
{"B3",  67,     20,     14},
{"B4",  73,     14,     0},
{"B5",  103,    66,     57},
{"B6",  123,    57,     45},
{"B7",  142,    42,     27},
{"B8",  157,    26,     18},
{"B9",  170,    151,    145},
{"B10", 186,    147,    132},
{"B11", 199,    140,    124},
{"B12", 211,    136,    115},
{"B13", 209,    243,    255},
{"B14", 255,    221,    235},
{"B15", 255,    244,    226},
{"B16", 221,    221,    221},
{"B17", 254,    218,    210},
{"B18", 192,    248,    207},
{"B19", 233,    228,    250},



{"C1",  53,     43,     31},
{"C2",  59,     42,     24},
{"C3",  66,     39,     9},
{"C4",  72,     36,     0},
{"C5",  139,    105,    77},
{"C6",  158,    99,     43},
{"C7",  175,    92,     0},
{"C8",  185,    90,     0},
{"C9",  184,    167,    151},
{"C10", 199,    162,    133},
{"C11", 212,    160,    113},
{"C12", 221,    156,    100},
{"C13", 171,    232,    250},
{"C14", 255,    196,    218},
{"C15", 255,    240,    206},
{"C16", 191,    191,    191},
{"C17", 254,    182,    170},
{"C18", 146,    234,    174},
{"C19", 210,    203,    237},



{"D1",  49,     46,     31},
{"D2",  53,     46,     20},
{"D3",  54,     46,     9},
{"D4",  56,     45,     0},
{"D5",  138,    126,    88},
{"D6",  145,    126,    50},
{"D7",  150,    127,    0},
{"D8",  151,    128,    0},
{"D9",  196,    185,    165},
{"D10", 202,    185,    139},
{"D11", 206,    186,    117},
{"D12", 210,    185,    105},
{"D13", 136,    220,    246},
{"D14", 252,    167,    198},
{"D15", 255,    238,    186},
{"D16", 163,    163,    163},
{"D17", 254,    158,    142},
{"D18", 123,    215,    150},
{"D19", 189,    179,    232},



{"E1",  45,     47,     34},
{"E2",  41,     50,     23},
{"E3",  35,     52,     7},
{"E4",  34,     52,     0},
{"E5",  83,     92,     65},
{"E6",  77,     96,     41},
{"E7",  75,     98,     18},
{"E8",  68,     100,    0},
{"E9",  155,    158,    139},
{"E10", 151,    162,    122},
{"E11", 149,    162,    106},
{"E12", 148,    165,    95},
{"E13", 119,    205,    232},
{"E14", 233,    148,    179},
{"E15", 254,    238,    173},
{"E16", 136,    136,    136},
{"E17", 255,    143,    123},
{"E18", 102,    193,    132},
{"E19", 168,    158,    210},



{"F1",  20,     31,     23},
{"F2",  10,     34,     21},
{"F3",  0,      36,     19},
{"F4",  0,      37,     20},
{"F5",  49,     69,     57},
{"F6",  27,     77,     50},
{"F7",  0,      81,     43},
{"F8",  0,      82,     44},
{"F9",  143,    160,    150},
{"F10", 136,    163,    144},
{"F11", 127,    167,    143},
{"F12", 119,    169,    140},
{"F13", 84,     191,    223},
{"F14", 223,    125,    164},
{"F15", 253,    235,    159},
{"F16", 111,    111,    111},
{"F17", 248,    119,    98},
{"F18", 77,     176,    112},
{"F19", 148,    137,    197},



{"G1",  24,     40,     37},
{"G2",  1,      43,     41},
{"G3",  0,      45,     42},
{"G4",  1,      47,     44},
{"G5",  53,     82,     78},
{"G6",  26,     87,     80},
{"G7",  0,      93,     87},
{"G8",  0,      95,     89},
{"G9",  141,    160,    156},
{"G10", 127,    163,    159},
{"G11", 112,    167,    161},
{"G12", 112,    170,    146},
{"G13", 54,     178,    214},
{"G14", 216,    100,    147},
{"G15", 254,    233,    144},
{"G16", 88,     88,     88},
{"G17", 233,    98,     79},
{"G18", 58,     157,    90},
{"G19", 129,    117,    183},



{"H1",  24,     39,     42},
{"H2",  1,      41,     53},
{"H3",  0,      48,     62},
{"H4",  0,      52,     66},
{"H5",  54,     81,     90},
{"H6",  24,     85,     103},
{"H7",  0,      94,     118},
{"H8",  0,      100,    132},
{"H9",  139,    159,    166},
{"H10", 125,    163,    176},
{"H11", 110,    165,    185},
{"H12", 97,     169,    194},
{"H13", 0,      167,    209},
{"H14", 207,    76,     128},
{"H15", 255,    233,    129},
{"H16", 67,     67,     67},
{"H17", 223,    73,     58},
{"H18", 38,     138,    76},
{"H19", 110,    96,     173},



{"I1",  38,     45,     61},
{"I2",  24,     47,     78},
{"I3",  0,      50,     95},
{"I4",  0,      57,     110},
{"I5",  81,     88,     104},
{"I6",  72,     88,     121},
{"I7",  62,     89,     136},
{"I8",  48,     90,     150},
{"I9",  152,    156,    167},
{"I10", 148,    156,    177},
{"I11", 140,    157,    187},
{"I12", 135,    157,    194},
{"I13", 0,      158,    197},
{"I14", 193,    55,     115},
{"I15", 254,    232,    104},
{"I16", 49,     49,     49},
{"I17", 199,    48,     41},
{"I18", 6,      122,    59},
{"I19", 93,     79,     164},



{"J1",  29,     27,     41},
{"J2",  25,     24,     56},
{"J3",  18,     21,     76},
{"J4",  0,      22,     89},
{"J5",  77,     74,     93},
{"J6",  77,     71,     105},
{"J7",  73,     68,     124},
{"J8",  73,     66,     136},
{"J9",  157,    154,    163},
{"J10", 157,    154,    175},
{"J11", 157,    151,    185},
{"J12", 154,    151,    196},
{"J13", 0,      152,    193},
{"J14", 182,    23,     103},
{"J15", 255,    231,    73},
{"J16", 33,     33,     33},
{"J17", 187,    29,     30},
{"J18", 0,      105,    48},
{"J19", 77,     61,     150},



{"K1",  56,     39,     57},
{"K2",  64,     32,     73},
{"K3",  74,     19,     86},
{"K4",  81,     0,      95},
{"K5",  99,     82,     101},
{"K6",  111,    72,     116},
{"K7",  120,    66,     128},
{"K8",  131,    57,     142},
{"K9",  163,    153,    164},
{"K10", 171,    146,    175},
{"K11", 180,    141,    186},
{"K12", 186,    139,    193},
{"K13", 0,      143,    185},
{"K14", 174,    0,      97},
{"K15", 255,    230,    55},
{"K16", 20,     20,     20},
{"K17", 176,    0,      38},
{"K18", 0,      91,     44},
{"K19", 58,     48,     137},



{"L1",  50,     30,     39},
{"L2",  61,     22,     43},
{"L3",  71,     10,     44},
{"L4",  77,     1,      50},
{"L5",  95,     67,     79},
{"L6",  116,    55,     88},
{"L7",  133,    39,     91},
{"L8",  151,    16,     93},
{"L9",  170,    150,    159},
{"L10", 179,    145,    162},
{"L11", 193,    139,    165},
{"L12", 201,    134,    165},
{"L13", 0,      132,    171},
{"L14", 151,    0,      82},
{"L15", 254,    230,    33},
{"L16", 0,      0,      0},
{"L17", 154,    1,      47},
{"L18", 0,      75,     37},
{"L19", 39,     34,     126},



{"DMIN", 255,    255,    255},
{"GS1",  250,    250,    250},
{"GS2",  238,    238,    238},
{"GS3",  221,    221,    221},
{"GS4",  205,    205,    205},
{"GS5",  190,    190,    190},
{"GS6",  175,    175,    175},
{"GS7",  160,    160,    160},
{"GS8",  146,    146,    146},
{"GS9",  133,    133,    133},
{"GS10", 119,    119,    119},
{"GS11", 107,    107,    107},
{"GS12", 95,     95,     95},
{"GS13", 83,     83,     83},
{"GS14", 72,     72,     72},
{"GS15", 63,     63,     63},
{"GS16", 53,     53,     53},
{"GS17", 44,     44,     44},
{"GS18", 36,     36,     36},
{"GS19", 29,     29,     29},
{"GS20", 21,     21,     21},
{"GS21", 15,     15,     15},
{"GS22",  4,      4,      4},
{"DMAX",  0,      0,      0}};


// Emulated Lab values

static LabPATCH EmulatedLab[] = {

{"A1",  18.31,  10.83,  2.22},
{"A2",  18.55,  22.76,  5.41},
{"A3",  22.03,  33.79,  10.00},
{"A4",  18.58,  27.51,  6.53},
{"A5",  37.73,  14.40,  4.75},
{"A6",  38.49,  28.96,  9.70},
{"A7",  39.03,  43.00,  14.76},
{"A8",  39.53,  62.22,  20.12},
{"A9",  69.05,  7.09,   2.49},
{"A10", 68.98,  13.83,  4.30},
{"A11", 69.32,  20.41,  6.61},
{"A12", 69.55,  29.35,  9.79},
{"A13", 93.18,  -0.82,  -1.70},
{"A14", 92.20,  1.05,   -2.90},
{"A15", 93.00,  -1.36,  1.00},
{"A16", 91.90,  0.73,   -0.27},
{"A17", 91.88,  0.76,   -0.32},
{"A18", 93.00,  -1.38,  1.08},
{"A19", 92.12,  1.24,   -3.00},
{"A20", 8.47,   8.06,   2.20},
{"A21", 20.01,  27.39,  21.24},
{"A22", 28.53,  42.33,  34.46},

{"B1",  18.20,  8.55,   5.78},
{"B2",  18.58,  16.67,  14.26},
{"B3",  21.47,  25.06,  22.14},
{"B4",  18.71,  24.53,  20.68},
{"B5",  37.87,  15.06,  13.57},
{"B6",  38.46,  27.42,  23.59},
{"B7",  39.43,  41.22,  35.57},
{"B8",  39.91,  59.45,  51.99},
{"B9",  69.17,  6.62,   5.95},
{"B10", 68.93,  12.32,  11.21},
{"B11", 69.16,  18.60,  16.74},
{"B12", 69.37,  26.99,  23.72},
{"B13", 90.09,  -7.06,  -5.30},
{"B14", 88.11,  8.49,   -7.56},
{"B15", 92.36,  -2.87,  10.25},
{"B16", 84.03,  0.20,   -0.03},
{"B17", 86.81,  7.11,   3.47},
{"B18", 89.18,  -9.38,  6.17},
{"B19", 85.01,  2.10,   -11.03},
{"B20", 14.36,  17.39,  12.57},
{"B21", 25.90,  38.01,  30.29},
{"B22", 55.45,  22.21,  21.29},

{"C1",  23.06,  3.51,   8.51},
{"C2",  23.44,  6.97,   18.19},
{"C3",  25.57,  12.50,  27.41},
{"C4",  22.88,  10.67,  24.08},
{"C5",  53.32,  9.02,   21.78},
{"C6",  53.95,  17.02,  40.81},
{"C7",  54.78,  24.93,  60.66},
{"C8",  53.88,  29.42,  66.87},
{"C9",  74.17,  3.92,   9.86},
{"C10", 74.44,  7.76,   19.51},
{"C11", 74.54,  12.15,  28.92},
{"C12", 74.74,  17.47,  40.70},
{"C13", 86.71,  -13.05, -9.06},
{"C14", 83.28,  16.99,  -12.71},
{"C15", 91.65,  -3.91,  19.92},
{"C16", 75.86,  0.46,   -0.09},
{"C17", 81.23,  14.13,  7.16},
{"C18", 85.06,  -16.89, 11.05},
{"C19", 77.61,  3.92,   -18.79},
{"C20", 10.97,  8.66,   7.36},
{"C21", 47.62,  31.91,  34.49},
{"C22", 61.99,  15.52,  19.25},

{"D1",  22.97,  -0.69,  7.94},
{"D2",  23.33,  -1.42,  17.13},
{"D3",  25.68,  -0.96,  26.03},
{"D4",  22.67,  -0.73,  22.47},
{"D5",  58.28,  -0.50,  20.82},
{"D6",  58.35,  -0.96,  40.18},
{"D7",  58.99,  -3.02,  58.63},
{"D8",  57.82,  -0.40,  68.90},
{"D9",  79.36,  -0.80,  10.72},
{"D10", 79.49,  -0.86,  22.26},
{"D11", 79.38,  -1.02,  32.32},
{"D12", 79.91,  -3.00,  85.89},
{"D13", 83.11,  -18.62, -12.82},
{"D14", 78.51,  25.14,  -17.50},
{"D15", 90.75,  -4.45,  30.18},
{"D16", 67.96,  0.12,   0.64},
{"D17", 75.78,  20.66,  11.44},
{"D18", 80.64,  -23.69, 15.92},
{"D19", 70.40,  5.74,   -25.73},
{"D20", 37.49,  25.67,  29.38},
{"D21", 51.35,  7.26,   14.86},
{"D22", 65.98,  10.64,  18.87},

{"E1",  23.03,  -5.69,  7.59},
{"E2",  23.19,  -10.63, 17.07},
{"E3",  25.84,  -14.65, 25.03},
{"E4",  22.80,  -12.27, 21.27},
{"E5",  42.24,  -8.07,  13.45},
{"E6",  43.08,  -16.33, 27.49},
{"E7",  43.92,  -26.23, 40.12},
{"E8",  42.92,  -28.05, 46.44},
{"E9",  69.28,  -4.55,  9.31},
{"E10", 68.67,  -8.43,  16.37},
{"E11", 68.65,  -12.38, 25.02},
{"E12", 69.59,  -30.56, 53.00},
{"E13", 79.28,  -23.61, -16.47},
{"E14", 73.36,  33.43,  -22.01},
{"E15", 89.86,  -4.44,  40.14},
{"E16", 59.84,  0.37,   0.70},
{"E17", 70.22,  27.34,  15.27},
{"E18", 75.93,  -29.92, 20.08},
{"E19", 62.92,  8.32,   -32.31},
{"E20", 46.67,  41.47,  59.43},
{"E21", 43.63,  19.74,  39.11},
{"E22", 56.35,  20.45,  35.47},

{"F1",  13.99,  -7.55,  2.66},
{"F2",  13.42,  -17.55, 5.73},
{"F3",  17.03,  -24.72, 7.76},
{"F4",  13.19,  -18.11, 6.26},
{"F5",  32.62,  -13.01, 4.81},
{"F6",  33.10,  -25.71, 9.56},
{"F7",  35.00,  -40.06, 16.18},
{"F8",  33.67,  -51.71, 18.37},
{"F9",  69.05,  -6.12,  2.49},
{"F10", 69.04,  -11.19, 4.35},
{"F11", 68.63,  -17.29, 6.18},
{"F12", 68.54,  -39.23, 13.59},
{"F13", 74.82,  -28.76, -20.43},
{"F14", 68.44,  41.32,  -26.34},
{"F15", 88.81,  -3.89,  50.32},
{"F16", 51.51,  -0.22,  0.81},
{"F17", 64.76,  33.71,  19.71},
{"F18", 70.68,  -36.12, 23.61},
{"F19", 55.05,  10.40,  -38.72},
{"F20", 55.53,  8.57,   22.34},
{"F21", 60.94,  15.30,  34.66},
{"F22", 64.96,  12.50,  28.12},

{"G1",  18.30,  -8.92,  -1.43},
{"G2",  19.13,  -17.00, -1.96},
{"G3",  20.95,  -27.52, -4.14},
{"G4",  18.55,  -23.94, -4.05},
{"G5",  37.16,  -12.71, -2.20},
{"G6",  37.80,  -24.58, -3.81},
{"G7",  39.28,  -38.51, -4.31},
{"G8",  38.10,  -49.18, -7.98},
{"G9",  69.05,  -6.17,  -0.96},
{"G10", 68.86,  -12.81, -2.12},
{"G11", 68.70,  -19.29, -3.45},
{"G12", 68.89,  -38.09, -6.21},
{"G13", 70.41,  -33.05, -23.99},
{"G14", 63.32,  49.09,  -30.26},
{"G15", 87.76,  -2.94,  59.80},
{"G16", 43.31,  -0.35,  0.40},
{"G17", 59.51,  39.82,  24.08},
{"G18", 65.46,  -41.58, 26.59},
{"G19", 47.13,  13.39,  -44.74},
{"G20", 64.14,  9.25,   28.90},
{"G21", 62.83,  9.74,   42.23},
{"G22", 72.04,  13.85,  87.12},

{"H1",  18.01,  -5.60,  -6.63},
{"H2",  18.60,  -10.59, -11.87},
{"H3",  19.29,  -16.87, -19.22},
{"H4",  18.25,  -15.93, -18.06},
{"H5",  37.29,  -8.13,  -8.36},
{"H6",  37.74,  -15.70, -17.72},
{"H7",  39.51,  -25.18, -26.36},
{"H8",  38.76,  -30.32, -36.79},
{"H9",  69.01,  -4.85,  -5.11},
{"H10", 69.12,  -8.46,  -9.84},
{"H11", 68.54,  -13.31, -15.79},
{"H12", 68.95,  -22.29, -25.83},
{"H13", 66.10,  -36.54, -27.19},
{"H14", 58.16,  56.58,  -33.77},
{"H15", 86.49,  -1.50,  69.64},
{"H16", 35.06,  0.06,   0.50},
{"H17", 54.22,  45.88,  29.15},
{"H18", 60.27,  -46.21, 30.29},
{"H19", 39.37,  17.53,  -50.41},
{"H20", 68.93,  3.44,   35.30},
{"H21", 61.87,  0.03,   12.10},
{"H22", 66.29,  -4.83,  42.38},

{"I1",  22.48,  1.02,   -11.29},
{"I2",  22.73,  1.80,   -23.50},
{"I3",  23.19,  2.96,   -34.81},
{"I4",  23.64,  5.75,   -51.98},
{"I5",  42.45,  0.32,   -8.78},
{"I6",  42.30,  1.47,   -19.15},
{"I7",  42.22,  2.41,   -28.97},
{"I8",  42.76,  3.67,   -46.96},
{"I9",  69.17,  0.67,   -4.76},
{"I10", 69.20,  0.71,   -9.89},
{"I11", 68.95,  1.18,   -15.33},
{"I12", 69.01,  1.59,   -26.70},
{"I13", 61.58,  -39.33, -30.20},
{"I14", 53.35,  63.17,  -36.62},
{"I15", 85.22,  0.27,   78.66},
{"I16", 27.15,  0.08,   0.28},
{"I17", 49.49,  51.14,  34.30},
{"I18", 54.94,  -50.20, 32.85},
{"I19", 31.79,  22.13,  -55.49},
{"I20", 71.43,  -5.91,  38.67},
{"I21", 43.54,  -23.67, 34.03},
{"I22", 64.05,  -25.30, 24.73},

{"J1",  13.22,  6.68,   -12.65},
{"J2",  13.28,  12.91,  -23.66},
{"J3",  13.66,  20.35,  -37.48},
{"J4",  14.36,  35.92,  -63.16},
{"J5",  37.27,  4.66,   -8.91},
{"J6",  37.43,  10.14,  -18.88},
{"J7",  37.40,  16.06,  -29.69},
{"J8",  36.87,  29.85,  -52.03},
{"J9",  69.25,  3.62,   -5.08},
{"J10", 69.16,  6.26,   -9.49},
{"J11", 68.99,  9.34,   -15.17},
{"J12", 68.92,  14.99,  -26.91},
{"J13", 57.20,  -40.91, -32.90},
{"J14", 48.96,  68.67,  -38.73},
{"J15", 83.77,  2.29,   86.48},
{"J16", 19.81,  0.04,   -0.04},
{"J17", 45.16,  55.50,  39.52},
{"J18", 49.65,  -53.14, 34.64},
{"J19", 24.89,  27.19,  -59.60},
{"J20", 66.19,  -26.07, 16.74},
{"J21", 33.02,  -37.17, 32.39},
{"J22", 14.74,  -16.26, 10.21},

{"K1",  22.66,  12.31,  -8.44},
{"K2",  23.23,  25.79,  -17.68},
{"K3",  23.79,  38.62,  -26.75},
{"K4",  24.11,  43.06,  -30.38},
{"K5",  42.96,  11.50,  -7.23},
{"K6",  42.88,  22.71,  -15.40},
{"K7",  43.18,  35.11,  -23.49},
{"K8",  43.92,  61.72,  -43.72},
{"K9",  69.08,  7.08,   -4.33},
{"K10", 69.01,  13.78,  -9.45},
{"K11", 68.61,  20.14,  -14.11},
{"K12", 68.94,  35.98,  -26.17},
{"K13", 52.42,  -41.02, -35.63},
{"K14", 44.55,  73.40,  -40.19},
{"K15", 82.11,  4.63,   93.12},
{"K16", 12.59,  0.17,   -0.99},
{"K17", 40.93,  59.22,  44.06},
{"K18", 43.93,  -54.81, 34.83},
{"K19", 18.31,  32.92,  -62.54},
{"K20", 19.08,  -11.47, 4.37},
{"K21", 13.87,  -9.30,  -0.35},
{"K22", 15.51,  -8.95,  -8.04},

{"L1",  18.07,  12.21,  -2.52},
{"L2",  18.22,  24.75,  -4.04},
{"L3",  21.80,  34.10,  -3.81},
{"L4",  18.26,  27.32,  -4.34},
{"L5",  37.71,  15.74,  -2.28},
{"L6",  38.54,  31.11,  -3.99},
{"L7",  39.13,  47.25,  -4.58},
{"L8",  39.63,  66.83,  -8.22},
{"L9",  68.83,  8.55,   -1.14},
{"L10", 68.82,  15.12,  -2.41},
{"L11", 68.96,  22.23,  -3.64},
{"L12", 69.59,  32.78,  -4.66},
{"L13", 44.57,  -35.93, -40.24},
{"L14", 39.97,  76.66,  -40.50},
{"L15", 78.94,  9.05,   99.76},
{"L16", 5.03,   -0.51,  -0.89},
{"L17", 36.28,  61.48,  50.38},
{"L18", 34.29,  -52.50, 32.51},
{"L19", 11.30,  38.64,  -63.35},
{"L20", 5.48,   -1.64,  -2.64},
{"L21", 7.11,   3.97,   -3.56},
{"L22", 11.19,  11.32,  -2.28},

{"GS0", 93.14,  -0.80,  -1.74},
// {"DMIN", 100,   0,     0},
{"GS1", 86.56,  0.61,   -0.02},
{"GS2", 82.37,  -0.23,  -0.08},
{"GS3", 77.91,  0.14,   -0.24},
{"GS4", 73.94,  0.70,   -0.16},
{"GS5", 70.26,  0.23,   0.77},
{"GS6", 65.61,  0.18,   0.20},
{"GS7", 61.58,  0.48,   0.30},
{"GS8", 57.52,  -0.18,  0.88},
{"GS9", 53.40,  -0.57,  0.96},
{"GS10",        48.97,  0.05,   1.34},
{"GS11",        44.76,  0.17,   0.72},
{"GS12",        40.65,  -0.57,  -0.10},
{"GS13",        36.63,  -0.18,  0.30},
{"GS14",        32.46,  0.03,   0.22},
{"GS15",        28.39,  0.08,   0.07},
{"GS16",        24.60,  0.11,   -0.35},
{"GS17",        20.79,  0.02,   -0.39},
{"GS18",        16.96,  0.03,   -0.97},
{"GS19",        13.36,  0.34,   -1.27},
{"GS20",        9.89,   0.59,   0.21},
{"GS21",        8.22,   0.98,   0.99},
{"GS22",        5.70,   -0.20,  -0.25},
// {"GS23",        4.82,   -0.37,  -1.17}
{"DMAX",        4.82,   -0.37,  -1.17}
};



static
void FatalError(const char *frm, ...)
{
       va_list args;

       va_start(args, frm);
       vfprintf(stderr, frm, args);
       va_end(args);

       exit(1);
}



// The toggles stuff

static
void HandleSwitches(int argc, char *argv[])
{
       int s;
      
       while ((s = xgetopt(argc,argv,"yYVvRrLlT:t:N:n:S:s:")) != EOF) {

       switch (s){


	   case 'y':
	   case 'Y': 
		   lDontRGB = TRUE;
		   break;

       case 's':
       case 'S':
           Intensity = atof(xoptarg);
           break;

       case 'n':
       case 'N':
            Noise = atof(xoptarg);
            break;

       case 'l':
       case 'L': 
           lUseLab = TRUE;
           break;

	   
       case 'v':
       case 'V':
            Verbose = TRUE;
            break;


       case 'r':
       case 'R': 
           lReverse = TRUE;
           break;

       case 't':
       case 'T':
            Intent = atoi(xoptarg);
            if (Intent > 3) Intent = 3;
            if (Intent < 0) Intent = 0;
            break;
     

  default:

       FatalError("Unknown option - run without args to see valid ones.\n");
    }
       
    }
}


static
void Help(void)
{
         
     fprintf(stderr, "usage: icc2it8 [flags] profile.icm target.hIT8\n\n");

     fprintf(stderr, "\nflags:\n\n");
     fprintf(stderr, "-v - Verbose\n");
     fprintf(stderr, "-l - Use D50 L*a*b*\n");
	 fprintf(stderr, "-y - Don't generate RGB at all\n");
     fprintf(stderr, "-r - Reverse, generates target from Lab values\n");
     fprintf(stderr, "-t<0,1,2,3> - Intent (0=Perceptual, 1=Colorimetric, 2=Saturation, 3=Absolute)\n");    
     fprintf(stderr, "-n<%%noise>  - Add white noise (value as percentage)\n");    
     fprintf(stderr, "-s<%%Y>      - Scale intensity (value as percentage)\n");    

     fprintf(stderr, "\n");
     fprintf(stderr, "default is absolute colorimetric intent\n");    

     fprintf(stderr, "\n");
     
     fprintf(stderr, "This program is intended to be a demo of the little cms\n"
                     "engine. Both lcms and this program are freeware. You can\n"
                     "obtain both in source code at http://www.littlecms.com\n"
                     "For suggestions, comments, bug reports etc. send mail to\n"
                     "marti@littlecms.com\n\n");
     exit(0);
}



// Does create the target

static
LCMSHANDLE CreateIT8(const char* Origin, int nP)
{
		int nFlds, n;

        LCMSHANDLE hIT8 = cmsxIT8Alloc();

	
		nFlds = 1;
	    if (!lDontRGB) nFlds += 3;
		nFlds += 3;
		if (lUseLab) nFlds += 3;
			
		
        cmsxIT8SetSheetType(hIT8, "LCMS_MEASUREMENT");
        cmsxIT8SetProperty(hIT8, "ORIGINATOR", Origin);
        cmsxIT8SetPropertyDbl(hIT8, "NUMBER_OF_SETS", nP);
        cmsxIT8SetPropertyDbl(hIT8, "NUMBER_OF_FIELDS", nFlds);

		cmsxIT8SetDataFormat(hIT8, 0, "SAMPLE_ID");

		n = 1;
		if (!lDontRGB) {
	   
        cmsxIT8SetDataFormat(hIT8, n++, "RGB_R");
        cmsxIT8SetDataFormat(hIT8, n++, "RGB_G");
        cmsxIT8SetDataFormat(hIT8, n++, "RGB_B");
		}
        

        cmsxIT8SetDataFormat(hIT8, n++, "XYZ_X");
        cmsxIT8SetDataFormat(hIT8, n++, "XYZ_Y");
        cmsxIT8SetDataFormat(hIT8, n++, "XYZ_Z");

        if (lUseLab) {

            cmsxIT8SetDataFormat(hIT8, n++, "LAB_L");
            cmsxIT8SetDataFormat(hIT8, n++, "LAB_A");
            cmsxIT8SetDataFormat(hIT8, n++, "LAB_B");
        }
		

        return hIT8;
}


static
WORD NoisyValue(double d)
{
    
    double NoisePercent = (Noise / 100.);
    double nnoise = (double) (rand() * 65535.) / RAND_MAX;
    double val;
    
    nnoise -= 32768;
    val = d * 257.0 + (nnoise * NoisePercent);

    if (val > 65535.0) return 0xFFFF;
    if (val < 0) return 0;

    return (WORD) floor(val + .5);

}


static
void GenerateForward(void)
{
        int i;
        cmsCIELab Lab;
        cmsCIEXYZ WhitePoint, xyz;
        cmsCIExyY WPxyY;
        WORD RGB[3], EncodedXYZ[3];     
        const char* cPatch;
        int nPatches;
        cmsHPROFILE hXYZ, hProfile;
        cmsHTRANSFORM hXFORM;
        LCMSHANDLE hIT8;

        hProfile = cmsOpenProfileFromFile(cInProf, "r");
        cmsTakeMediaWhitePoint(&WhitePoint, hProfile);
            
        cmsXYZ2xyY(&WPxyY, &WhitePoint);
        hXYZ     = cmsCreateXYZProfile();

        hXFORM   = cmsCreateTransform(hProfile, TYPE_RGB_16, hXYZ, TYPE_XYZ_16,
                                            Intent, cmsFLAGS_NOTPRECALC);

        nPatches = sizeof(EmulatedRGB) / sizeof(RGBPATCH);          

        hIT8 = CreateIT8(cmsTakeProductName(hProfile), nPatches);

        for (i=0; i < nPatches; i++) {

            RGBPATCH* p  = EmulatedRGB + i;

            cPatch = p -> Patch;

            RGB[0] = NoisyValue(p -> R);
            RGB[1] = NoisyValue(p -> G);
            RGB[2] = NoisyValue(p -> B);

            cmsDoTransform(hXFORM, RGB, EncodedXYZ, 1);
            cmsXYZEncoded2Float(&xyz, EncodedXYZ);

            xyz.X *= (Intensity / 100.);
            xyz.Y *= (Intensity / 100.);
            xyz.Z *= (Intensity / 100.);

            cmsxIT8SetDataSet(hIT8,    cPatch, "SAMPLE_ID", (char*) cPatch);

			if (!lDontRGB) {
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_R", (double) p->R );
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_G", (double) p->G );
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_B", (double) p->B );
			}

			if (lUseLab) {

            cmsXYZ2Lab(NULL, &Lab, &xyz);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_L", Lab.L);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_A", Lab.a);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_B", Lab.b);

            }


            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_X", xyz.X * 100.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_Y", xyz.Y * 100.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_Z", xyz.Z * 100.);
			

        }

        cmsDeleteTransform(hXFORM);
        cmsCloseProfile(hXYZ);
        cmsCloseProfile(hProfile);

        cmsxIT8SaveToFile(hIT8, cSheet);
        cmsxIT8Free(hIT8);

}

static
void GenerateReverse(void)
{
        int i;
        cmsCIELab Lab;
        cmsCIEXYZ xyz, WhitePoint;
        cmsCIExyY WPxyY;
        WORD RGB[3], EncodedLab[3];
        const char* cPatch;
        int nPatches;
        cmsHPROFILE hLab, hProfile;
        cmsHTRANSFORM hXFORM;
        LCMSHANDLE hIT8;

        // From Lab to RGB
        hProfile = cmsOpenProfileFromFile(cInProf, "r");
        cmsTakeMediaWhitePoint(&WhitePoint, hProfile);

        cmsXYZ2xyY(&WPxyY, &WhitePoint);
        hLab     = cmsCreateLabProfile(NULL);


        hXFORM   = cmsCreateTransform(hLab, TYPE_Lab_16, hProfile, TYPE_RGB_16, 
                                            Intent, cmsFLAGS_NOTPRECALC);

        nPatches = sizeof(EmulatedLab) / sizeof(LabPATCH);          

        hIT8 = CreateIT8(cmsTakeProductName(hProfile), nPatches);

        for (i=0; i < nPatches; i++) {

            LabPATCH* p  = EmulatedLab + i;

            cPatch = p -> Patch;
            Lab.L = p -> L; Lab.a = p -> a; Lab.b = p -> b;

            cmsLab2XYZ(cmsD50_XYZ(),  &xyz, &Lab);
            cmsFloat2LabEncoded(EncodedLab, &Lab);

            cmsDoTransform(hXFORM, EncodedLab, RGB, 1);
            
            cmsxIT8SetDataSet(hIT8,    cPatch, "SAMPLE_ID", (char*) cPatch);

			if (!lDontRGB) {
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_R", (double) RGB[0] / 257.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_G", (double) RGB[1] / 257.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "RGB_B", (double) RGB[2] / 257.);
			}

			
            if (lUseLab) {

            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_L", Lab.L);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_A", Lab.a);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "LAB_B", Lab.b);
            }

            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_X", xyz.X * 100.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_Y", xyz.Y * 100.);
            cmsxIT8SetDataSetDbl(hIT8, cPatch, "XYZ_Z", xyz.Z * 100.);

        }
		

        cmsDeleteTransform(hXFORM);
        cmsCloseProfile(hLab);

        cmsxIT8SaveToFile(hIT8, cSheet);
        cmsxIT8Free(hIT8);

}



int main(int argc, char *argv[])
{

    fprintf(stderr, "little cms profile sampler - v1.2\n\n");

    HandleSwitches(argc, argv);

    if ((argc - xoptind) != 2)  
              Help();              

    cInProf = argv[xoptind];
    cSheet  = argv[xoptind + 1];

    
    if (lReverse) 
            GenerateReverse();          
    else
            GenerateForward();

    fprintf(stderr, "Done.\n");
    return 0;
}


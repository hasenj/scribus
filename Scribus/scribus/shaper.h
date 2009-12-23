#ifndef SHAPER_H
#define SHAPER_H

#include "pageitem_textframe.h"
extern "C" {
#include "harfbuzz/harfbuzz-shaper.h"
#include "harfbuzz/harfbuzz-unicode.h"
#include "harfbuzz/harfbuzz-freetype.h"
}

HB_Script charScript(uint cp);
HB_Script stringScript(QVector<uint> ustr);

/**
    This is an attempt to encapsulate and streamline the font stuff
    in the harfbuzz API with freetype
 */
class ShaperFontInfo
{
public:
    HB_Face hbFace;
    HB_FontRec hbFont;

public:    
    /**
        The FT_Face should be initialized already in scribus

        based on tests/fuzzing/fuzz.cc
     */
    ShaperFontInfo(FT_Face face);
};


/**
    Attempt to simplify and streamline the HarfBuzz shaper item stuff
 */
class ShaperItemInfo
{
private:
    HB_ShaperItem shaper_item;
    static const int maxLength = 1024;
    uint8_t str[maxLength];

public:
    ShaperItemInfo(ShaperFontInfo *font);
    ~ShaperItemInfo();
    void shapeItem(QString str);
};

struct ShaperOutput
{
    HB_Glyph* glyphs;
    HB_GlyphAttributes* attributes;
    HB_Fixed* advances;
    ushort* log_clusters;
};

#endif


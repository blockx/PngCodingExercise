#ifndef __SEGDISPLAYBITMAP_H__
#define __SEGDISPLAYBITMAP_H__

#include "assetid.h"

#include <vector>

class SegDisplayBitmap
{
public:
    SegDisplayBitmap(AssetID aid)
    {
        unsigned x_pos = 0;  // Index into rgba_bitmap;

        for (/*x_pos = 0*/; x_pos < 8; x_pos++)
        {
            rgba_bitmap[x_pos] = rgba_white;
        }
        // Lookup the 7 seg display corresponding to each of the AssetID digits
        // and store the x-offset of each black bit.
        for (unsigned u = 0; u < aid.get_width(); u++)
        {
            uint8_t x = seg_digit_lookup[aid[u]];   // Get 7-seg display bitmap for AssetID digit
            uint8_t mask = 0b10000000;              // Initialise bitmask

            for (int i = 0; i < 8; i++)             // For bits in 7-seg display bitmap
            {
                if ((x & mask) != 0) 
                    rgba_bitmap[x_pos] = rgba_black;
                else
                    rgba_bitmap[x_pos] = rgba_white;

                x_pos++;
                mask >>= 1;
            }
        }
        for (/*x_pos = 56*/; x_pos < 256; x_pos++)
        {
            rgba_bitmap[x_pos] = rgba_white;
        }
    }

    uint32_t rgba_bitmap[256 * 1];   // Store for bitmap

    static const uint32_t rgba_white = 0xFFFFFFFF;
    static const uint32_t rgba_black = 0xFF000000;

private:
    const std::vector<uint8_t> seg_digit_lookup // Used to convert digit to 7 seg display bits
    {
        0b01110111, // 0
        0b01000010, // 1
        0b10110110, // 2
        0b11010110, // 3
        0b11000011, // 4
        0b11010101, // 5
        0b11110101, // 6
        0b01000110, // 7
        0b11110111, // 8
        0b11010111  // 9
    };
};

#endif // ndef __SEGDISPLAYBITMAP_H__
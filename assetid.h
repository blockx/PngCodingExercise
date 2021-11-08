#ifndef __ASSETID_H__
#define __ASSETID_H__

#include <string>
#include <stdexcept>

class AssetID
{
public:
    AssetID(std::string s)
    {
        unsigned long val = std::stoul(s);  // throws if string doesn't start with numeric

        for (unsigned i = csum_width; i < get_width(); i++)
        {
            id_digits[5 - i + 2] = val % 10;    // digits given by remainder when residual val divided by 10
            val /= 10;                  // prep for next digit    
        }

        // Validate val as originally lying between 0 and 9999 by ensuring that it does not need more than 4 decimal digits
        if (val) throw std::runtime_error("Initial data value too big.");

        checksum();
    }

    uint8_t operator[] (unsigned u) // Returned digit guaranteed to be n range 0-9
    {
        if (u >= get_width()) throw std::runtime_error("Index past last digit in Asset ID.");
        return id_digits[u];
    }

    constexpr unsigned get_width() { return data_width + csum_width; }

private:
    void checksum()
    {
        /*  c = (a1 + (10 * a2) + (100 * a3) + (1000 * a4)) mod 97
            For example, the checksum for the asset ID 1337 can be calculated as follows:
            (1 + (10 * 3) + (100 * 3) + (1000 * 7)) mod 97 = 7331 mod 97 = 56 */
        int checksum = (id_digits[csum_width] + 10 * id_digits[csum_width+1] + 100 * id_digits[csum_width+2] + 1000 * id_digits[csum_width+3]) % 97;

        // checksum guaranteed to be 2 digits or fewer
        id_digits[1] = checksum % 10;
        id_digits[0] = checksum / 10;
    }

    const static int data_width = 4;   // 4 decimal digits of item ID
    const static int csum_width = 2;   // 2 decimal digits of checksum

    uint8_t id_digits[data_width + csum_width];       // Digits guaranteed to be in range 0-9        
};

#endif // ndef __ASSETID_H__
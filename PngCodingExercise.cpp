// BotsAndUsCodingExcercise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "assetid.h"
#include "segdisplaybitmap.h"

#include "lodepng.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void encode_to_png(std::string filename, const uint32_t* image)
{
    unsigned error = lodepng_encode32_file(filename.c_str(),            // const char* filename,
                                           (const unsigned char*)image, // const unsigned char* image,
                                            256,                        // unsigned w,
                                            1);                         // unsigned h

    if (error) throw std::runtime_error("Problem encoding .png file : " + std::to_string(error) + "\n");
}


int main()
{
    std::ifstream ifs;
    ifs.open("test.txt");

    if (!ifs.is_open()) throw std::runtime_error("Can't open file test.txt.");

    // Read file lines into vector file_lines
    std::vector<std::string> file_lines;
    while (ifs)
    {
        std::string s;
        std::getline(ifs, s, '\n');
        if (ifs)
        {
            file_lines.push_back(s);
        }
    }

    // For each file line create a .PNG file and write the data as per spec
    for (auto s : file_lines)
    {
#if 1
        //TEST : write lines out to console to verify
        std::cout << "Line data was : " << s << '\n';
#endif // 0

        // Create a checksummed Asset ID for each file line
        AssetID aid{ s };

        // Convert the AssetID into 7 segment display form
        auto db = SegDisplayBitmap(aid);
        
        // Write bitmap data to file having name as per Asset ID and suffix ".png"
        std::ofstream ofs;
        std::string output_filename = s;
        output_filename += ".png";

        encode_to_png(output_filename, db.rgba_bitmap);
    }

    return 0;
}

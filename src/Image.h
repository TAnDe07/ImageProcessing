//
// Created by TanaD on 3/18/2022.
//

#ifndef PROJECT2_PIXEL_H
#define PROJECT2_PIXEL_H

#endif //PROJECT2_PIXEL_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Image {
    struct Header
    {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
    struct Pixel {
        unsigned char B;
        unsigned char G;
        unsigned char R;
    };

    Header header;
    vector<Pixel> pixels;
};

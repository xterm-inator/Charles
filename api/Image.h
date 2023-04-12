//
// Created by charles on 12/04/23.
//

#ifndef CHARLES_IMAGE_H
#define CHARLES_IMAGE_H

#include <vector_types.h>

class Image {
public:
    Image();

private:
    uchar3* RawImage{};

public:
    inline uchar3* GetRawImage() { return RawImage; }
};


#endif //CHARLES_IMAGE_H

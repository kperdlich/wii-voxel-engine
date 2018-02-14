#ifndef ZIP_H
#define ZIP_H

#include <zlib.h>
#include <cstdlib>
#include <cstring>

class Zip
{
private:
    Zip();
public:
    static unsigned char* Decompress(unsigned char* compressedData, size_t compressedSize, size_t decompressedSize)
    {
        unsigned char* decompressedData = (unsigned char*) malloc(decompressedSize);

        z_stream infstream;
        infstream.zalloc = Z_NULL;
        infstream.zfree = Z_NULL;
        infstream.opaque = Z_NULL;
        infstream.avail_in = (uInt) compressedSize;
        infstream.next_in = (Bytef *) compressedData;
        infstream.avail_out = (uInt)decompressedSize;
        infstream.next_out = (Bytef*) decompressedData;

        inflateInit(&infstream);
        inflate(&infstream, Z_NO_FLUSH);
        inflateEnd(&infstream);

        return decompressedData;
    }
};

#endif // ZIP_H

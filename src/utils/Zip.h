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
    static size_t Decompress(unsigned char* inputData, size_t compressedSize, unsigned char* outputData, size_t decompressedSize)
    {
        z_stream infstream;
        infstream.zalloc = Z_NULL;
        infstream.zfree = Z_NULL;
        infstream.opaque = Z_NULL;
        infstream.avail_in = (uInt) compressedSize;
        infstream.next_in = (Bytef *) inputData;
        infstream.avail_out = (uInt)decompressedSize;
        infstream.next_out = (Bytef*) outputData;

        inflateInit(&infstream);
        inflate(&infstream, Z_NO_FLUSH);
        inflateEnd(&infstream);

        return infstream.total_out;
    }
};

#endif // ZIP_H

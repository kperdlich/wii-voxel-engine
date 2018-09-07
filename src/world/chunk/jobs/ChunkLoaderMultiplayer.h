#ifndef CHUNKLOADERMULTIPLAYER_H
#define CHUNKLOADERMULTIPLAYER_H

#include "../chunkdata.h"
#include "../../../utils/Job.h"

class ChunkLoaderMultiplayer : public Job<ChunkLoadingData>
{
protected:
    void Execute() override;

};

#endif // CHUNKLOADERMULTIPLAYER_H

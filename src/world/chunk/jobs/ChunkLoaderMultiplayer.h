#pragma once

#include "utils/Job.h"
#include "world/chunk/chunkdata.h"

class ChunkLoaderMultiplayer : public Job<ChunkLoadingData>
{
protected:
    void Execute() override;

};

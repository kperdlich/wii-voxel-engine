#pragma once

#include "../chunkdata.h"
#include "../../../utils/Job.h"

class ChunkLoaderMultiplayer : public Job<ChunkLoadingData>
{
protected:
    void Execute() override;

};

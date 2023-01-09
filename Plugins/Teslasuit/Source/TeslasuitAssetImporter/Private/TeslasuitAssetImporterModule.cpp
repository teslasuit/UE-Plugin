#include "ITeslasuitAssetImporter.h"

class FTeslasuitAssetImporterModule : public ITeslasuitAssetImporter
{
public:
    virtual void StartupModule() override
    {
    }

    virtual void ShutdownModule() override
    {
    }
};

IMPLEMENT_MODULE(FTeslasuitAssetImporterModule, TeslasuitAssetImporter);

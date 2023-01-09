// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "ITeslasuitEditor.h"

/**
* SpeedTreeImporter module implementation (private)
*/
class FTeslasuitEditorModule : public ITeslasuitEditor
{
public:
    virtual void StartupModule() override
    {
    }


    virtual void ShutdownModule() override
    {
    }

};

IMPLEMENT_MODULE(FTeslasuitEditorModule, TeslasuitEditor);

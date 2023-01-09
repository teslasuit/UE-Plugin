// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
 
using System.IO;
using UnrealBuildTool;
using Microsoft.Win32;
 
public class TeslasuitEditor : ModuleRules
{

    public TeslasuitEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.Add("Teslasuit/Public");
        PublicIncludePaths.Add("TeslasuitEditor/Public");
 
        PrivateIncludePaths.Add("Teslasuit/Private");
        PrivateIncludePaths.Add("TeslasuitEditor/Private");

 
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Teslasuit"
      }
            );
 
 
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
            "Slate",
            "SlateCore",			
			"Teslasuit", "AnimGraph", "BlueprintGraph",
			
        // ... add private dependencies that you statically link with here ...  
      }
            );
 
 
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
        // ... add any modules that your module loads dynamically here ...
      }
            );
 
    }
}    
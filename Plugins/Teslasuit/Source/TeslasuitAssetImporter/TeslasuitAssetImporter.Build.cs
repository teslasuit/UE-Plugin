// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
 
using System.IO;
using UnrealBuildTool;
using Microsoft.Win32;
 
public class TeslasuitAssetImporter : ModuleRules
{

    public TeslasuitAssetImporter(ReadOnlyTargetRules Target) : base(Target)
    {
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.Add("Teslasuit/Public");
        PublicIncludePaths.Add("TeslasuitAssetImporter/Public");
 
        PrivateIncludePaths.Add("Teslasuit/Private");
        PrivateIncludePaths.Add("TeslasuitAssetImporter/Private");

 
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "UnrealEd",
                "Teslasuit"
            }
        );
 
 
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
            "Slate",
            "SlateCore",
            "UnrealEd",
            "Teslasuit"	
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
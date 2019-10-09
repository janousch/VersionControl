// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonFunctionLibrary.h"

#include "FileFunctionLibrary.generated.h"

/**
 * Static functions to read or change files
 */
UCLASS()
class VERSIONCONTROL_API UFileFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Version Control|File|Config")
		static FString GetVersion();

	UFUNCTION(BlueprintCallable, Category = "Version Control|File|Config")
		static void SetVersion(FString NewVersion);

	UFUNCTION(BlueprintPure, Category = "Version Control|File|Config")
		static FString GetConfigValue(FString Key);

	UFUNCTION(BlueprintCallable, Category = "Version Control|File|Config")
		static void SetConfigValue(FString Key, FString Value);

	UFUNCTION(BlueprintPure, Category = "Version Control|File")
		static int32 GetFileSizeInKb(FString FullFilePath);

	/*
	Return the directory to the paks folder of the released game folder
	*/
	UFUNCTION(BlueprintPure, Category = "Version Control|File")
		static FString GetGamePaksDirectory();

	/*
	Return the directory to the exe folder of the released game folder
	*/
	UFUNCTION(BlueprintPure, Category = "Version Control|File")
		static FString GetGameExeDirectory();

	UFUNCTION(BlueprintCallable, Category = "Version Control|File")
		static void SaveFile(TArray<uint8> Data, FString FilePath);

	UFUNCTION(BlueprintPure, Category = "Version Control|Utilities")
		static int32 GetAdditionalFilesSize(TArray<FAdditionalFile> AdditionalFiles);
};

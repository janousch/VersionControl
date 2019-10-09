// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonFunctionLibrary.h"

#include "VersionControlFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VERSIONCONTROL_API UVersionControlFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*
	Append the raw json string and upload the new versions file
	*/
	UFUNCTION(BlueprintCallable, Category = "Version Control|Json", Meta = (Keywords = "Append Changelog"))
		static FString AppendVersion(FString VersionsAsJsonString, FVersion NewVersion);

	UFUNCTION(BlueprintPure, Category = "Version Control|Json", Meta = (Keywords = "Version String"))
		static FString GetVersionAsJsonString(FVersion Version);

	UFUNCTION(BlueprintPure, Category = "Version Control|Json", Meta = (Keywords = "Version String"))
		static FVersion GetVersionFromJsonString(FString VersionAsJsonString);

	/*
	Increments the current version depending on the current version and the change significance and pre release identifier
	*/
	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Increment Version Identifier"))
		static FVersionIdentifier IncrementVersion(EChangeSignificance ChangeSignificance, EPreReleaseIdentifier PreReleaseIdentifier);

	/*
	Is version 1 newer than 2?
	*/
	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Compare Version"))
		static bool IsVersionNewer(FVersionIdentifier V1, FVersionIdentifier V2);

	/*
	Is version 1 equal to 2?
	*/
	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Compare Version"))
		static bool IsVersionEqual(FVersionIdentifier V1, FVersionIdentifier V2);

	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Version Identifier String"))
		static FString VersionIdentifierToString(FVersionIdentifier VersionIdentifier);

	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Version Identifier String"))
		static FVersionIdentifier StringToVersionIdentifier(FString VersionIdentifierAsString);

	/*
	Deletes old files and renames the exe file if neccassary
	*/
	UFUNCTION(BlueprintCallable, Category = "Versioning", Meta = (Keywords = "Version External Exe Application"))
		static void StartExternalVersioningTool(FString Argument = "");

	UFUNCTION(BlueprintCallable, Category = "Versioning", Meta = (Keywords = "Web Browser"))
		static void OpenUrlInBrowser(FString Url);

	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Version External Exe Application Tool"))
		static FString GetVersioningToolInstructionJson(FInstructions Instructions);

	UFUNCTION(BlueprintPure, Category = "Versioning", Meta = (Keywords = "Version External Exe Application Tool"))
		static FString GetVersioningToolPath();

	UFUNCTION(BlueprintCallable, Category = "Version Control|Utilities", Meta = (Keywords = "Split String Array"))
		static TArray<FString> SplitStringToArray(FString String, FString Delimiter);

private:

	static FVersions GetAllVersions(FString VersionsAsJsonString);
};

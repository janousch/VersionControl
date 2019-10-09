// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonFunctionLibrary.generated.h"


USTRUCT(BlueprintType)
struct FAdditionalFile {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Version Control")
		FString TargetFileFullFilePath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Version Control")
		FString TargetDirectory;
};

UENUM(BlueprintType)
enum class EChangeSignificance : uint8 {
	Major UMETA(ToolTip = "Incompatible changes (Major.Minor.Patch)"),
	Minor UMETA(ToolTip = "Added functionality (Major.Minor.Patch)"),
	Patch UMETA(ToolTip = "Bug fixes (Major.Minor.Patch)")
};

UENUM(BlueprintType)
enum class EPreReleaseIdentifier : uint8 {
	Alpha UMETA(ToolTip = "Alpha (status) - suffix a"),
	Beta UMETA(ToolTip = "Beta (status) - suffix b"),
	Release UMETA(ToolTip = "Release candidate - suffix rc"),
	Final UMETA(ToolTip = "(final) release / commercial distribution - suffix r")
};

USTRUCT(BlueprintType)
struct FVersionIdentifier {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 major;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 minor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 patch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		EPreReleaseIdentifier preReleaseIdentifier;
};

USTRUCT(BlueprintType)
struct FVersion {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		FVersionIdentifier versionIdentifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		FVersionIdentifier previousVersionIdentifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		FString changelog;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		bool bHasUpdatedPakFile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		bool bHasUpdatedExeFile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 pakFileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 exeFileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		TArray<FAdditionalFile> additionalFiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		int32 additionalFilesSize;
};

USTRUCT()
struct FVersions {
	GENERATED_BODY()

		/*
		Wrapper for the json
		*/
		UPROPERTY()
		TArray<FVersion> versions;
};

USTRUCT(BlueprintType)
struct FInstructions {
	GENERATED_BODY()

		UPROPERTY()
		FString ApplicationName;
	UPROPERTY()
		FString ApplicationProcessId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		bool HasChangedPakFile;
	UPROPERTY()
		FString PakFilesFolderPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		FString NewPakFileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		bool HasChangedExeFile;
	UPROPERTY()
		FString ExeFilesFolderPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Versioning")
		FString NewExeFileName;
};

/**
 * 
 */
UCLASS()
class VERSIONCONTROL_API UJsonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	template <typename StructType>
	static void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);

	template <typename StructType>
	static void GetStructFromJsonString(FString JsonString, StructType& StructOutput);
};

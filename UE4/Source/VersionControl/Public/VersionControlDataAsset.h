// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VersionControlDataAsset.generated.h"

/**
 * Holds all the sharable data
 */
UCLASS(BlueprintType)
class VERSIONCONTROL_API UVersionControlDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StorageUrl;
};

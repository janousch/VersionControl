// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Request.h"

#include "HttpFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VERSIONCONTROL_API UHttpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Http")
		static URequest* CreateRequest(ERequestType Type, FString Url);

	UFUNCTION(BlueprintPure, Category = "Http|Request")
		static float GetProgressFromRequests(TArray<URequest*> Requests);
};

// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"

#include "Response.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VERSIONCONTROL_API UResponse : public UObject
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable, Category = "Version Control|Http")
		TArray<FString> GetAllHeaders();

	UFUNCTION(BlueprintCallable, Category = "Version Control|Http")
		TArray<uint8> GetContent();

	UFUNCTION(BlueprintCallable, Category = "Version Control|Http")
		FString GetContentAsString();

	UFUNCTION(BlueprintPure, Category = "Version Control|Http")
		int32 GetContentLength();

	UFUNCTION(BlueprintPure, Category = "Version Control|Http")
		FString GetContentType();

	UFUNCTION(BlueprintCallable, Category = "Version Control|Http")
		FString GetHeader(const FString& HeaderName);

	UFUNCTION(BlueprintPure, Category = "Version Control|Http")
		FString GetURL();

	UFUNCTION(BlueprintCallable, Category = "Version Control|Http")
		FString GetUrlParameter(const FString& ParameterName);

	FHttpResponsePtr Response;
};

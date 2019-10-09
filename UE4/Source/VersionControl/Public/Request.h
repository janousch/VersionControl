// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"

#include "Request.generated.h"


class UHttpAsyncAction;

UENUM()
enum ERequestType
{
	Get,
	Put,
	Post,
	Delete
};

USTRUCT(BlueprintType)
struct FRequestHeader {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Value;
};

/**
 * 
 */
UCLASS(Blueprintable)
class VERSIONCONTROL_API URequest : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly)
		float Progress;

	// Received/Send bytes
	int32 ProcessedBytes;
	int32 TotalBytesNeeded;

	UFUNCTION(BlueprintCallable, Category = "Http")
		void SetHeader(FRequestHeader Header);

	UFUNCTION(BlueprintCallable, Category = "Http")
		void SetContent(UPARAM(ref) TArray<uint8>& Bytes);

	UFUNCTION(BlueprintCallable, Category = "Http")
		void SetContentAsString(UPARAM(ref) FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Http")
		void SetContentFromFile(FString FilePath);

	void Send(UHttpAsyncAction* HttpAsyncAction);

	//UFUNCTION(BlueprintCallable, Category = "Http")
		//void SendWithCallback(FOnResponse OnResponse);

	void SetUrl(FString Url);

	void SetType(ERequestType Type);

private:

	FString Url;
	ERequestType Type;
	TArray<FRequestHeader> Headers;
	TArray<uint8>* Content;
	FString* ContentAsString;
	FString ContentFromFile;
	
	void OnUpdateProgress(FHttpRequestPtr HttpRequest, int32 BytesSend, int32 InBytesReceived);

	FString GetTypeAsString();
};

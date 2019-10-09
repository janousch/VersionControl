// Copyright Ramon Janousch. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Request.h"
#include "Response.h"

#include "HttpAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResponseDelegate, bool, bSuccess, int32, ResponseCode, UResponse*, Response);

/**
 * Async action for the http send request
 */
UCLASS()
class VERSIONCONTROL_API UHttpAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
		FOnResponseDelegate Finished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Http")
		static UHttpAsyncAction* Send(const UObject* WorldContextObject, URequest* Request);

	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;

private:
	const UObject* WorldContextObject;
	URequest* Request;

	bool bIsActive;
};

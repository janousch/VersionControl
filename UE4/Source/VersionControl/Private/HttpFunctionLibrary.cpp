// Copyright Ramon Janousch. MIT License.


#include "HttpFunctionLibrary.h"


URequest* UHttpFunctionLibrary::CreateRequest(ERequestType Type, FString Url) {
	URequest* request = NewObject<URequest>();
	request->SetType(Type);
	request->SetUrl(Url);

	return request;
}

float UHttpFunctionLibrary::GetProgressFromRequests(TArray<URequest*> Requests) {
	int32 TotalBytesNeeded = 0;
	int32 ProcessBytes = 0;
	for (auto& request : Requests) {
		TotalBytesNeeded += request->TotalBytesNeeded;
		ProcessBytes += request->ProcessedBytes;
	}

	if (TotalBytesNeeded == 0 || ProcessBytes == 0) {
		return .0f;
	}

	float Progress = (float)ProcessBytes / (float)TotalBytesNeeded;
	return Progress;
}
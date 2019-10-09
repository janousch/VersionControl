// Copyright Ramon Janousch. MIT License.


#include "HttpAsyncAction.h"


UHttpAsyncAction* UHttpAsyncAction::Send(const UObject* WorldContextObject, URequest* Request) {
	UHttpAsyncAction* Node = NewObject<UHttpAsyncAction>();
	Node->WorldContextObject = WorldContextObject;
	Node->Request = Request;

	return Node;
}

void UHttpAsyncAction::Activate() {
	if (nullptr == WorldContextObject) {
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute LoadSaveGameAsync!"), ELogVerbosity::Error);
		return;
	}
	if (bIsActive) {
		FFrame::KismetExecutionMessage(TEXT("AsyncAction is already running!"), ELogVerbosity::Warning);
		return;
	}
	if (Request == nullptr) {
		FFrame::KismetExecutionMessage(TEXT("Request cannot be empty!"), ELogVerbosity::Warning);
		return;
	}

	bIsActive = true;
	Request->Send(this);
}

void UHttpAsyncAction::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UResponse* response = NewObject<UResponse>();
	response->Response = Response;
	bIsActive = false;

	if (bWasSuccessful) {
		Finished.Broadcast(bWasSuccessful, Response->GetResponseCode(), response);
	}
	else {
		Finished.Broadcast(bWasSuccessful, 400, nullptr);
	}
}
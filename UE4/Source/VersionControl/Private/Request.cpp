// Copyright Ramon Janousch. MIT License.


#include "Request.h"

#include "HttpAsyncAction.h"
#include "FileHelper.h"


void URequest::SetHeader(FRequestHeader Header) {
	Headers.Add(Header);
}

void URequest::SetContent(UPARAM(ref) TArray<uint8>& Bytes) {
	Content = &Bytes;

	ContentAsString = nullptr;
	ContentFromFile = "";
}

void URequest::SetContentAsString(UPARAM(ref) FString& Value) {
	ContentAsString = &Value;

	Content = nullptr;
	ContentFromFile = "";
}

void URequest::SetContentFromFile(FString FilePath) {
	ContentFromFile = FilePath;

	ContentAsString = nullptr;
	Content = nullptr;

}

FString URequest::GetTypeAsString() {
	switch (Type)
	{
	case Get:
		return "GET";
		break;
	case Put:
		return "PUT";
		break;
	case Post:
		return "POST";
		break;
	case Delete:
		return "DELETE";
		break;
	default:
		return "GET";
		break;
	}
}

void URequest::Send(UHttpAsyncAction* HttpAsyncAction) {
	// Create http request
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb(GetTypeAsString());
	Request->SetURL(Url);

	// Set optional headers
	for (auto& header : Headers) {
		Request->SetHeader(header.Name, header.Value);
	}

	// Set optional content
	if (Content != nullptr) {
		Request->SetContent(*Content);
	}
	else if (ContentAsString != nullptr) {
		Request->SetContentAsString(*ContentAsString);
	}
	else if (!ContentFromFile.IsEmpty()) {
		Request->SetContentAsStreamedFile(*ContentFromFile);
	}

	Request->OnRequestProgress().BindUObject(this, &URequest::OnUpdateProgress);
	Request->OnProcessRequestComplete().BindUObject(HttpAsyncAction, &UHttpAsyncAction::OnResponse);
	Request->ProcessRequest();
}

void URequest::OnUpdateProgress(FHttpRequestPtr HttpRequest, int32 BytesSend, int32 InBytesReceived) {
	FHttpResponsePtr HttpResponse = HttpRequest->GetResponse();

	if (HttpResponse.IsValid())
	{
		TotalBytesNeeded = HttpRequest.Get()->GetContentLength();
		ProcessedBytes = BytesSend + InBytesReceived;
		Progress = (float)ProcessedBytes / (float)TotalBytesNeeded;
	}
}

//void URequest::SendWithCallback(FOnResponse OnResponse) {
//
//}

void URequest::SetUrl(FString Url) {
	this->Url = Url;
}

void URequest::SetType(ERequestType Type) {
	this->Type = Type;
}
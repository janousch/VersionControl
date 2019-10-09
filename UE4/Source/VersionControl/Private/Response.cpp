// Copyright Ramon Janousch. MIT License.


#include "Response.h"

TArray<FString> UResponse::GetAllHeaders() {
	return Response->GetAllHeaders();
}

TArray<uint8> UResponse::GetContent() {
	return Response->GetContent();
}

FString UResponse::GetContentAsString() {
	return Response->GetContentAsString();
}

int32 UResponse::GetContentLength() {
	return Response->GetContentLength();
}

FString UResponse::GetContentType() {
	return Response->GetContentType();
}

FString UResponse::GetHeader(const FString& HeaderName) {
	return Response->GetHeader(HeaderName);
}

FString UResponse::GetURL() {
	return Response->GetURL();
}

FString UResponse::GetUrlParameter(const FString& ParameterName) {
	return Response->GetURLParameter(ParameterName);
}
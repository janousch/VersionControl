// Copyright Ramon Janousch. MIT License.


#include "JsonFunctionLibrary.h"

// Json
#include "Json.h"
#include "JsonUtilities.h"


template <typename StructType>
void UJsonFunctionLibrary::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	FJsonObjectConverter::UStructToJsonObjectString<StructType>(FilledStruct, StringOutput);
}

template <typename StructType>
void UJsonFunctionLibrary::GetStructFromJsonString(FString JsonString, StructType& StructOutput) {
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}
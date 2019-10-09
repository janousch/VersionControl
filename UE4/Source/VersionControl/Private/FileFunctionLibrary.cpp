// Copyright Ramon Janousch. MIT License.


#include "FileFunctionLibrary.h"

#include "Engine.h"
#include "FileManager.h"
#include "JsonFunctionLibrary.h"


FString UFileFunctionLibrary::GetVersion() {
	FString ProjectVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);

	if (ProjectVersion.IsEmpty()) {
		ProjectVersion = "0.0.0-a";
	}

	return ProjectVersion;
}

void UFileFunctionLibrary::SetVersion(FString NewVersion) {
	GConfig->SetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		*NewVersion,
		GGameIni
	);
	// Sometimes the config file wont save changes if you don't call this function after you've set all your config keys.
	GConfig->Flush(false, GGameIni);
}

FString UFileFunctionLibrary::GetConfigValue(FString Key) {
	FString Value;
	if (GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		*Key,
		Value,
		GGameIni
	)) {
		return Value;
	}

	return TEXT("Missing Config Value!");
}

void UFileFunctionLibrary::SetConfigValue(FString Key, FString Value) {
	GConfig->SetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		*Key,
		*Value,
		GGameIni
	);
	// Sometimes the config file wont save changes if you don't call this function after you've set all your config keys.
	GConfig->Flush(false, GGameIni);
}

int32 UFileFunctionLibrary::GetFileSizeInKb(FString FullFilePath) {
	//return IFileManager::Get().FileSize(*FullFilePath);
	int64 sizeInBytes = FPlatformFileManager::Get().GetPlatformFile().FileSize(*FullFilePath);
	int32 sizeInKb = sizeInBytes / 1024;

	return sizeInKb;
}

FString UFileFunctionLibrary::GetGamePaksDirectory() {
	// C:\Users\Ramon\Desktop\Versioning\Patching\Content\Paks\Patching_0_P_pak
	return FPaths::Combine(FPaths::GameContentDir(), FString("/Paks/"));
}

FString UFileFunctionLibrary::GetGameExeDirectory() {
	// C:\Users\Ramon\Desktop\Versioning\Patching\Binaries\Win64\Patching.exe
	return FPaths::Combine(FPaths::GameDir(), FString("/Binaries/Win64/"));
}

void UFileFunctionLibrary::SaveFile(TArray<uint8> Data, FString FilePath) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString Directory = FPaths::GetPath(FilePath);
	if (!PlatformFile.DirectoryExists(*Directory)) {
		PlatformFile.CreateDirectory(*Directory);
	}

	FFileHelper::SaveArrayToFile(Data, *FilePath);
}

int32 UFileFunctionLibrary::GetAdditionalFilesSize(TArray<FAdditionalFile> AdditionalFiles) {
	int32 Size = 0;
	for (auto& File : AdditionalFiles) {
		Size += GetFileSizeInKb(File.TargetFileFullFilePath);
	}

	return Size;
}
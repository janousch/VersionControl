// Copyright Ramon Janousch. MIT License.


#include "VersionControlFunctionLibrary.h"


#include "FileFunctionLibrary.h"

// Json
#include "Json.h"
#include "JsonUtilities.h"


FVersionIdentifier UVersionControlFunctionLibrary::IncrementVersion(EChangeSignificance ChangeSignificance, EPreReleaseIdentifier PreReleaseIdentifier) {
	FString currentVersionAsString = UFileFunctionLibrary::GetVersion();
	FVersionIdentifier versionIdentifier = StringToVersionIdentifier(currentVersionAsString);

	versionIdentifier.preReleaseIdentifier = PreReleaseIdentifier;
	switch (ChangeSignificance)
	{
	case EChangeSignificance::Major:
		versionIdentifier.major++;
		versionIdentifier.minor = 0;
		versionIdentifier.patch = 0;
		break;
	case EChangeSignificance::Minor:
		versionIdentifier.minor++;
		versionIdentifier.patch = 0;
		break;
	case EChangeSignificance::Patch:
		versionIdentifier.patch++;
		break;
	default:
		break;
	}

	UFileFunctionLibrary::SetVersion(VersionIdentifierToString(versionIdentifier));

	return versionIdentifier;
}

FString UVersionControlFunctionLibrary::AppendVersion(FString VersionsAsJsonString, FVersion NewVersion) {
	FVersions allVersions = GetAllVersions(VersionsAsJsonString);
	allVersions.versions.Insert(NewVersion, 0);
	FString newVersionsAsJsonString;
	FJsonObjectConverter::UStructToJsonObjectString(allVersions, newVersionsAsJsonString);

	return newVersionsAsJsonString;
}

FString UVersionControlFunctionLibrary::VersionIdentifierToString(FVersionIdentifier VersionIdentifier) {
	FString versionIdentifierAsString = "";
	versionIdentifierAsString.AppendInt(VersionIdentifier.major);
	versionIdentifierAsString.AppendChar('.');
	versionIdentifierAsString.AppendInt(VersionIdentifier.minor);
	versionIdentifierAsString.AppendChar('.');
	versionIdentifierAsString.AppendInt(VersionIdentifier.patch);

	switch (VersionIdentifier.preReleaseIdentifier)
	{
	case EPreReleaseIdentifier::Alpha:
		versionIdentifierAsString.Append("-a");
		break;
	case EPreReleaseIdentifier::Beta:
		versionIdentifierAsString.Append("-b");
		break;
	case EPreReleaseIdentifier::Release:
		versionIdentifierAsString.Append("-rc");
		break;
	case EPreReleaseIdentifier::Final:
		versionIdentifierAsString.Append("-r");
		break;
	default:
		break;
	}

	return versionIdentifierAsString;
}

FString UVersionControlFunctionLibrary::GetVersionAsJsonString(FVersion Version) {
	FString versionAsJsonString;
	FJsonObjectConverter::UStructToJsonObjectString(Version, versionAsJsonString);

	return versionAsJsonString;
}

FVersionIdentifier UVersionControlFunctionLibrary::StringToVersionIdentifier(FString VersionIdentifierAsString) {
	FString majorAsString;
	FString minorAsString;
	FString patchAsString;
	FString preReleaseIdentifierAsString;
	VersionIdentifierAsString.Split(".", &majorAsString, &VersionIdentifierAsString);
	VersionIdentifierAsString.Split(".", &minorAsString, &VersionIdentifierAsString);
	VersionIdentifierAsString.Split("-", &patchAsString, &preReleaseIdentifierAsString);

	FVersionIdentifier versionIdentifier;
	versionIdentifier.major = FCString::Atoi(*majorAsString);
	versionIdentifier.minor = FCString::Atoi(*minorAsString);
	versionIdentifier.patch = FCString::Atoi(*patchAsString);
	if (preReleaseIdentifierAsString.IsEmpty()) {
		versionIdentifier.preReleaseIdentifier = EPreReleaseIdentifier::Final;
	}
	else if (preReleaseIdentifierAsString.Equals("a", ESearchCase::IgnoreCase)) {
		versionIdentifier.preReleaseIdentifier = EPreReleaseIdentifier::Alpha;
	}
	else if (preReleaseIdentifierAsString.Equals("b", ESearchCase::IgnoreCase)) {
		versionIdentifier.preReleaseIdentifier = EPreReleaseIdentifier::Beta;
	}
	else if (preReleaseIdentifierAsString.Equals("rc", ESearchCase::IgnoreCase)) {
		versionIdentifier.preReleaseIdentifier = EPreReleaseIdentifier::Release;
	}

	return versionIdentifier;
}

bool UVersionControlFunctionLibrary::IsVersionNewer(FVersionIdentifier V1, FVersionIdentifier V2) {
	if (V1.major > V2.major) {
		return true;
	}
	if (V1.major == V2.major && V1.minor > V2.minor) {
		return true;
	}
	if (V1.major == V2.major && V1.minor == V2.minor && V1.patch > V2.patch) {
		return true;
	}
	if (V1.major == V2.major && V1.minor == V2.minor && V1.patch == V2.patch && V1.preReleaseIdentifier > V2.preReleaseIdentifier) {
		return true;
	}

	return false;
}

bool UVersionControlFunctionLibrary::IsVersionEqual(FVersionIdentifier V1, FVersionIdentifier V2) {
	return V1.major == V2.major && V1.minor == V2.minor && V1.patch == V2.patch;
}

FVersions UVersionControlFunctionLibrary::GetAllVersions(FString VersionsAsJsonString) {
	FVersions allVersions;
	FJsonObjectConverter::JsonObjectStringToUStruct<FVersions>(VersionsAsJsonString, &allVersions, 0, 0);

	return allVersions;
}

void UVersionControlFunctionLibrary::StartExternalVersioningTool(FString Argument) {
	FString versioningToolFullPath = GetVersioningToolPath();
	FPlatformProcess::CreateProc(*versioningToolFullPath, *Argument, true, false, false, nullptr, 0, nullptr, nullptr);
}

FString UVersionControlFunctionLibrary::GetVersioningToolPath() {
	//FString fullFilePath = FPaths::Combine(FPaths::GameDir(), FString("VersioningTool"));
	FString fullFilePath = FPaths::Combine(FPaths::ProjectDir(), FString("VersioningTool"));
	fullFilePath = FPaths::Combine(fullFilePath, FString("VersioningTool.exe"));

	return fullFilePath;
}

void UVersionControlFunctionLibrary::OpenUrlInBrowser(FString Url) {
	FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
}

FString UVersionControlFunctionLibrary::GetVersioningToolInstructionJson(FInstructions Instructions) {
	Instructions.ApplicationName.Append(FApp::GetProjectName());
	Instructions.ApplicationProcessId = FString::FromInt(FPlatformProcess::GetCurrentProcessId());
	Instructions.PakFilesFolderPath.Append(FPaths::Combine(FPaths::ProjectContentDir(), FString("/Paks")));
	Instructions.ExeFilesFolderPath.Append(FPaths::Combine(FPaths::ProjectDir(), FString("/Binaries/Win64")));

	FString instructions;
	FJsonObjectConverter::UStructToJsonObjectString(Instructions, instructions);

	return instructions;
}

TArray<FString> UVersionControlFunctionLibrary::SplitStringToArray(FString String, FString Delimiter) {
	TArray<FString> elements;
	FString leftSide;
	while (String.Split(Delimiter, &leftSide, &String)) {
		elements.Add(leftSide);
	}
	elements.Add(String);

	return elements;
}

FVersion UVersionControlFunctionLibrary::GetVersionFromJsonString(FString VersionAsJsonString) {
	FVersion version;
	FJsonObjectConverter::JsonObjectStringToUStruct<FVersion>(VersionAsJsonString, &version, 0, 0);

	return version;
}
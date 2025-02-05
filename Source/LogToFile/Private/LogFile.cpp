#include "LogFile.h"
#include "LogToFile.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "LogToFileBPLibrary.h"

DEFINE_LOG_CATEGORY(LogLogToFile)

void ULogFile::Initialize(FString In_FilePath, bool In_bPrintTimestamps)
{
	bPrintTimestamps = In_bPrintTimestamps;
	FilePath = In_FilePath;

	bool bSuccess = FFileHelper::SaveStringToFile(TEXT("File created\n"), *FilePath);

	if(bSuccess) UE_LOG(LogLogToFile, Log, TEXT("File created at: %s"), *FilePath)
	else UE_LOG(LogLogToFile, Warning, TEXT("File failed to create at: %s"), *FilePath);

}

bool ULogFile::WriteToFile(ELogCategory Category, FString Content)
{
	FString modifiedContent = Content;

	modifiedContent = AddLogCategory(Category, Content);

	if (bPrintTimestamps)
	{
		modifiedContent = AddTime(modifiedContent);
	}

    const FString wNewlineChar = modifiedContent + TEXT("\n");

    return FFileHelper::SaveStringToFile(wNewlineChar, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void ULogFile::AsyncWriteToFile(ELogCategory Category, FString Content)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, Category, Content]()
	{
		WriteToFile(Category, Content);
	});
}



FString ULogFile::AddTime(FString String)
{
	const FString CurrentTime = TEXT("[") + ULogToFileBPLibrary::GetCurrentTime() + TEXT("] - ");
	return CurrentTime + String;
}

FString ULogFile::AddLogCategory(ELogCategory Category, FString String)
{
	const FString CategoryName = StaticEnum<ELogCategory>()->GetNameStringByValue(static_cast<int64>(Category));
	const FString wBrackets = TEXT("[") + CategoryName + TEXT("] - ");
	return wBrackets + String;
}


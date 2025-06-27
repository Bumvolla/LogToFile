#include "LogFile.h"
#include "LogToFile.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"
#include "LogToFileBPLibrary.h"

DEFINE_LOG_CATEGORY(LogLogToFile)


ULogFile::ULogFile()
{
}

void ULogFile::ChangeFileSavePath(const FString& NewSaveDir)
{

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	const FString oldPath = FilePath;
	
	FileDir = NewSaveDir;
	FilePath = FString::Printf(TEXT("%s%s.txt"), *FileDir, *FileName);

	if (PlatformFile.FileExists(*oldPath))
	{
		if (FString DestDirectory = FPaths::GetPath(FilePath); !PlatformFile.DirectoryExists(*DestDirectory))
		{
			PlatformFile.CreateDirectoryTree(*DestDirectory);
		}

		if (PlatformFile.MoveFile(*FilePath, *oldPath))
		{
			UE_LOG(LogLogToFile, Log, TEXT("File moved successfully."));
			return;
		}
		
		UE_LOG(LogLogToFile, Warning, TEXT("Failed to move file."));
	}
	else
	{
		UE_LOG(LogLogToFile, Log, TEXT("Source file does not exist"));
	}

	
	
}

void ULogFile::Initialize(bool bRegenerateFile, FString In_FileDir, FString In_FileName, bool In_bPrintTimestamps)
{
	bPrintTimestamps = In_bPrintTimestamps;
	FileDir = In_FileDir;
	FileName = In_FileName;
	
	if (!FileDir.EndsWith("/"))
		FileDir += "/";
	
	FilePath = FString::Printf(TEXT("%s%s.txt"), *FileDir, *FileName);

	bool bSuccess;

	if (bRegenerateFile)
		bSuccess = FFileHelper::SaveStringToFile(TEXT(""), *FilePath,  FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
	else
		bSuccess = FFileHelper::SaveStringToFile(TEXT(""), *FilePath);

	if(bSuccess) UE_LOG(LogLogToFile, Log, TEXT("File created at: %s"), *FilePath)
	else UE_LOG(LogLogToFile, Warning, TEXT("Failed to create file at: %s"), *FilePath);

}

bool ULogFile::WriteToFile(FString Content)
{
	const FString wNewlineChar = Content + TEXT("\n");
	LogLines.Add(Content);
	OnLogLineAddedEvent(Content);
	return FFileHelper::SaveStringToFile(wNewlineChar, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

bool ULogFile::LogToFile(ELogCategory Category, FString Content)
{
	FString modifiedContent = Content;

	modifiedContent = AddLogCategory(Category, Content);

	if (bPrintTimestamps)
	{
		modifiedContent = AddTime(modifiedContent);
	}

	OnLogLineAdded.Broadcast(Content, Category);
	
    return WriteToFile(modifiedContent);
}

void ULogFile::AsyncLogToFile(ELogCategory Category, FString Content)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, Category, Content]()
	{
		LogToFile(Category, Content);
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


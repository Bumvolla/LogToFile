#include "LogToFileBPLibrary.h"
#include "LogToFile.h"
#include "Misc/DateTime.h"

ULogFile* ULogToFileBPLibrary::CreateLogFile(bool bRegenerateFile, FString FileCreationPath, FString FileName, bool bPrintTimestamps)
{
	ULogFile* LogFile = NewObject<ULogFile>();
	
	FString FullRoute = FString::Printf(TEXT("%s%s.txt"), *FileCreationPath, *FileName);
	
	if (FPaths::FileExists(FullRoute) && !bRegenerateFile)
	{
		TArray<FString> Lines;
		FFileHelper::LoadFileToStringArray(Lines, *FullRoute);
		LogFile->Initialize(bRegenerateFile,FileCreationPath, FileName, bPrintTimestamps);
		for (FString Line : Lines)
		{
			LogFile->WriteToFile(Line);
		}
	}
	LogFile->Initialize(bRegenerateFile,FileCreationPath, FileName, bPrintTimestamps);
	return LogFile;
}

FString ULogToFileBPLibrary::GetCurrentTime()
{
	FDateTime Now = FDateTime::Now();
	int32 Day = Now.GetDay();
	int32 Month = Now.GetMonth();
	int32 Year = Now.GetYear();
	int32 Hour = Now.GetHour();
	int32 Minute = Now.GetMinute();
	int32 Second = Now.GetSecond();

	return Now.ToString(TEXT("%d-%m-%Y %H:%M:%S"));
}



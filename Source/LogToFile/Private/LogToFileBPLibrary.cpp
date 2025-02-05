#include "LogToFileBPLibrary.h"
#include "LogToFile.h"
#include "Misc/DateTime.h"

ULogFile* ULogToFileBPLibrary::CreateLogFile(FString FileCreationPath, bool bPrintTimestamps)
{
	ULogFile* createdLogFile = NewObject<ULogFile>();
	createdLogFile->Initialize(FileCreationPath, bPrintTimestamps);
	return createdLogFile;
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



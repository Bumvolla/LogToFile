// Copyright (c) 2025 Sora Mas \n All rights reserved. 


#include "CSVFile.h"
#include "CSVToFile.h"

DEFINE_LOG_CATEGORY(LogCSVToFile)

void UCSVFile::Initialize(const TSubclassOf<UStruct>& In_StructClass, FString In_FileName, FString In_FileDir)
{
	FileDir = In_FileDir;
	FileName = In_FileName;

	if (!FileDir.EndsWith("/"))
		FileDir += "/";
	
	const FString NewFilePath = FString::Printf(TEXT("%s%s.csv"), *FileDir, *FileName);
	FilePath = NewFilePath;


	bool bSuccess = FFileHelper::SaveStringToFile(TEXT(""), *FilePath);


	if(bSuccess) UE_LOG(LogCSVToFile, Log, TEXT("CSV file created at: %s"), *FilePath)
	else UE_LOG(LogCSVToFile, Warning, TEXT("CSV file failed to create at: %s"), *FilePath);
	
}

bool UCSVFile::WriteCSVLine(const FString& Content)
{
	const FString wNewlineChar = Content + TEXT("\n");
	return FFileHelper::SaveStringToFile(wNewlineChar, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

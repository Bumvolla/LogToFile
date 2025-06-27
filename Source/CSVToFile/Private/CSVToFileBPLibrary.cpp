// Copyright (c) 2025 Sora Mas \n All rights reserved. 


#include "CSVToFileBPLibrary.h"

#include "CSVFile.h"

TObjectPtr<UCSVFile> UCSVToFileBPLibrary::CreateCSVFile(FString FileDir, FString FileName,
                                                        TSubclassOf<UStruct> TemplateStruct)
{
	UCSVFile* newCSVFile = NewObject<UCSVFile>();
	newCSVFile->Initialize(TemplateStruct, FileName, FileDir);
	return newCSVFile;
	
}

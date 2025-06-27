// Copyright (c) 2025 Sora Mas \n All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CSVFile.generated.h"

/**
 * 
 */
UCLASS()
class CSVTOFILE_API UCSVFile : public UObject
{
	GENERATED_BODY()

public:
	explicit UCSVFile::UCSVFile(const TSubclassOf<UScriptStruct>& In_StructClass, const FString& FileName, const FString& FileDir) :
	StructClass(In_StructClass), FileName(FileName), FileDir(FileDir) {Initialize(StructClass, FileName, FileDir);};
	
	void Initialize(const TSubclassOf<UStruct>& In_StructClass, FString In_FileName, FString In_FileDir);

	UPROPERTY(BlueprintReadOnly)
	FString FileName;

	UPROPERTY(BlueprintReadOnly)
	FString FileDir;

	UFUNCTION(BlueprintCallable)
	template <typename T>
	void AddCSVLine(const T* LineValues);
	
private:
	UPROPERTY()
	FString FilePath;

	UPROPERTY()
	TSubclassOf<UScriptStruct> StructClass;

	UFUNCTION()
	bool WriteCSVLine(const FString& Content);
	
};


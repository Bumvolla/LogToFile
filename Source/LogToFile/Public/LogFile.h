#pragma once

#include "CoreMinimal.h"
#include "LogToFileHelpers.h"
#include "LogFile.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLogLineAdded, const FString&, AddedLine, const ELogCategory&, LogCategory);

/**
 * 
 */
UCLASS(Blueprintable)
class LOGTOFILE_API ULogFile : public UObject
{
	GENERATED_BODY()

public:

	ULogFile::ULogFile();
	ULogFile::ULogFile(bool bIn_RegenerateFile,const FString& In_FileDir,const FString& In_FileName,const bool bIn_PrintTimestamps)
		: bPrintTimestamps(bIn_PrintTimestamps), FileDir(In_FileDir), FileName(In_FileName)
	{
		Initialize(bIn_RegenerateFile, FileDir, FileName, bPrintTimestamps);
	}
	;
	
	UFUNCTION(NotBlueprintable, Category = "Logger")
	void Initialize(bool bRegenerateFile, FString In_FileDir, FString In_FileName, bool In_bPrintTimestamps);

	UFUNCTION(NotBlueprintable, Category = "Logger")
	void ChangeFileSavePath(const FString& NewSaveDir);

	UFUNCTION()

	UFUNCTION(BlueprintCallable, Category = "Logger")
	bool WriteToFile(FString Content = TEXT("Hello world!"));
	
	UFUNCTION(BlueprintCallable, Category = "Logger")
	bool LogToFile(ELogCategory Category = ELogCategory::Log, FString Content = TEXT("Hello world!"));

	UFUNCTION(BlueprintCallable, Category = "Logger")
	void AsyncLogToFile(ELogCategory Category = ELogCategory::Log, FString Content = TEXT("Hello world!"));

	UFUNCTION(BlueprintImplementableEvent, Category = "Logger")
	void OnLogLineAddedEvent(const FString& Value);

	UPROPERTY(BlueprintReadOnly)
	bool bPrintTimestamps;
	UPROPERTY(BlueprintReadOnly)
	FString FileDir;
	UPROPERTY(BlueprintReadOnly)
	FString FileName;
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> LogLines;

	UPROPERTY(BlueprintReadOnly)
	FOnLogLineAdded OnLogLineAdded;
	
private:
	UPROPERTY()
	FString FilePath;

	UFUNCTION()
	FString AddTime(FString String);

	UFUNCTION()
	FString AddLogCategory(ELogCategory Category, FString String);
};

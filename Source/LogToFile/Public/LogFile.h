#pragma once

#include "CoreMinimal.h"
#include "LogToFileHelpers.h"
#include "LogFile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOGTOFILE_API ULogFile : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(FString In_FilePath, bool In_bPrintTimestamps);
	
	UFUNCTION(BlueprintCallable, Category = "Logger")
	bool WriteToFile(ELogCategory Category = ELogCategory::Log, FString Content = TEXT("Hello world!"));

private:
	bool bPrintTimestamps;
	FString FilePath;

	FString AddTime(FString String);
	FString AddLogCategory(ELogCategory Category, FString String);
};

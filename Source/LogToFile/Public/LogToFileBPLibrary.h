#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogFile.h"
#include "LogToFileBPLibrary.generated.h"

UCLASS()
class LOGTOFILE_API ULogToFileBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "LogToFile")
	static ULogFile* CreateLogFile(bool bRegenerateFile, FString FileCreationPath, FString FileName, bool bPrintTimestamps);

	UFUNCTION(BlueprintCallable, Category = "LogToFile")
	static FString GetCurrentTime();
};

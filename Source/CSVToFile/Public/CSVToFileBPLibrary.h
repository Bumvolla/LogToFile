// Copyright (c) 2025 Sora Mas \n All rights reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSVToFileBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CSVTOFILE_API UCSVToFileBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CSVToFile")
	static TObjectPtr<UCSVFile>  CreateCSVFile(FString FileDir, FString FileName, TSubclassOf<UStruct> TemplateStruct);
};

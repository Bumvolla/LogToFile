// Dont copy.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ELogCategory : uint8
{
	Log		UMETA(DisplayName = "Log"),
	Warning		UMETA(DisplayName = "Warning"),
	Error		UMETA(DisplayName = "Error"),
};

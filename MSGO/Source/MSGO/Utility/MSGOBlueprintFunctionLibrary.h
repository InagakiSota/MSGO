// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MSGOBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MSGO_API UMSGOBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// フレームを秒数に変換(60fps)
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float FrameToSeconds(const int32 InFrame);

	// 秒数をフレームに変換(60fps)
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 SecondsToFrame(const float InSeconds);
	
};

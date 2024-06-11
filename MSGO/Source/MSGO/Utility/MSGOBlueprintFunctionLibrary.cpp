// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MSGOBlueprintFunctionLibrary.h"

// フレームを秒数に変換(60fps)
float UMSGOBlueprintFunctionLibrary::FrameToSeconds(const int32 InFrame)
{
    float oneFrameSeconds = 1.0f / 60.f;

    return oneFrameSeconds * InFrame;
}

// 秒数をフレームに変換(60fps)
int32 UMSGOBlueprintFunctionLibrary::SecondsToFrame(const float InSeconds)
{
    float oneFrameSeconds = 1.0f / 60.f;
    
    return int32(InSeconds / oneFrameSeconds);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MSGOBlueprintFunctionLibrary.h"

// �t���[����b���ɕϊ�(60fps)
float UMSGOBlueprintFunctionLibrary::FrameToSeconds(const int32 InFrame)
{
    float oneFrameSeconds = 1.0f / 60.f;

    return oneFrameSeconds * InFrame;
}

// �b�����t���[���ɕϊ�(60fps)
int32 UMSGOBlueprintFunctionLibrary::SecondsToFrame(const float InSeconds)
{
    float oneFrameSeconds = 1.0f / 60.f;
    
    return int32(InSeconds / oneFrameSeconds);
}

// �X�g�����O�e�[�u����CSV�ɃG�N�X�|�[�g
bool UMSGOBlueprintFunctionLibrary::ExportCSVFromCSVString(const FString& CSVString, FString FileName)
{
    return FFileHelper::SaveStringToFile(CSVString, *FileName);
}

bool UMSGOBlueprintFunctionLibrary::ExportCSVFromDataTable(UDataTable* DataTable, FString FileName)
{
    if (DataTable)
    {
        return FFileHelper::SaveStringToFile(DataTable->GetTableAsCSV(), *FileName);
    }
    return false;
}
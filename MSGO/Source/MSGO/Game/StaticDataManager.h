#pragma once

#include "CoreMinimal.h"
#include "Structs/ParameterStructs.h"
#include "DataAssets/CharacterStatusDataAsset.h"
#include "StaticDataManager.generated.h"

UCLASS(config = Game, defaultconfig)
class MSGO_API UStaticDataManager : public UObject
{
	GENERATED_BODY()

public: 
    // データアセットのファイルパス
    UPROPERTY(EditAnywhere, Config, meta = (AllowedClasses = "CharacterStatusDataAsset"))
    FSoftObjectPath CharacterParameterDataAssetPath;

    UPROPERTY(BlueprintReadOnly)
    class UCharacterStatusDataAsset* CharacterParameterDataAsset;

public:
    // データアセットの取得
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static class UCharacterStatusDataAsset* GetCharacterParameterDataAsset(const UObject* WorldContextObject);

    // 任意のキャラクターパラメータデータの取得
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static void GetCharacterParameterData(const UObject* WorldContextObject, int InCharacterID, FCharacterStatusParameter& OutCharacterParameterData);

};
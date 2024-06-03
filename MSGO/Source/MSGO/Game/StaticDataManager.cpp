#include "StaticDataManager.h"
#include "MSGOGameInstance.h"
// データアセットの取得
class UCharacterStatusDataAsset* UStaticDataManager::GetCharacterParameterDataAsset(const UObject* WorldContextObject)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if (World == nullptr)
        return nullptr;

    // ゲームインスタンスからStaticDataManagerのインスタンスを取得
    UStaticDataManager* StaticDataManager = Cast<UMSGOGameInstance>(World->GetGameInstance())->StaticDataManager;

    // アセットが読み込まれているかチェック
    if (StaticDataManager->CharacterParameterDataAsset == nullptr)
    {
        // iniファイルで指定したデータアセットのファイルパス
        FString DataAssetPath = StaticDataManager->CharacterParameterDataAssetPath.ToString();

        // アセットを読み込む
        StaticDataManager->CharacterParameterDataAsset = Cast<UCharacterStatusDataAsset>(StaticLoadObject(UCharacterStatusDataAsset::StaticClass(), nullptr, *DataAssetPath));
    }
    return StaticDataManager->CharacterParameterDataAsset;
}

// 任意のキャラクターパラメータデータの取得
void UStaticDataManager::GetCharacterParameterData(const UObject* WorldContextObject, int InCharacterID, FCharacterStatusParameter& OutCharacterParameterData)
{
    UCharacterStatusDataAsset* DataAsset = GetCharacterParameterDataAsset(WorldContextObject);
    if (DataAsset != nullptr)
    {
        FCharacterStatusParameter* CharacterParameter = DataAsset->CharacterParameterMap.Find(InCharacterID);
        if (CharacterParameter != nullptr)
        {
            OutCharacterParameterData = *CharacterParameter;
        }
    }
}

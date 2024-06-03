#include "MSGOGameInstance.h"
#include "Game/StaticDataManager.h"

void UMSGOGameInstance::Init()
{
    Super::Init();

    StaticDataManager = NewObject<UStaticDataManager>();
}
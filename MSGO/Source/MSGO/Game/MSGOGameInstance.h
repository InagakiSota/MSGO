#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MSGOGameInstance.generated.h"

UCLASS()
class MSGO_API UMSGOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public: 

	UPROPERTY()
	class UStaticDataManager* StaticDataManager;

public:

	virtual void Init() override;
};
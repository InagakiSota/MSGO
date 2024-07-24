#pragma once
//
#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "MyHudWidget.generated.h"

class ULockonMarkerWidget;
class UHPGaugeWidget;
class UDownPointGaugeWidget;
class UBoostGaugeWidget;
class UReticleWidget;

/**
 * HUDのウィジェットクラス
 */
UCLASS()
class MSGO_API UMyHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta= (BindWidgetOptional))
	TObjectPtr<ULockonMarkerWidget> LockonMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UHPGaugeWidget> HPGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UDownPointGaugeWidget> DownPointGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UBoostGaugeWidget> BoostGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UReticleWidget> Reticle;

};

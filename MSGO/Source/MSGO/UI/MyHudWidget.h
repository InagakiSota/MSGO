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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta= (BindWidget))
	TObjectPtr<ULockonMarkerWidget> LockonMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHPGaugeWidget> HPGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UDownPointGaugeWidget> DownPointGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBoostGaugeWidget> BoostGauge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UReticleWidget> Reticle;

public:
	UFUNCTION(BlueprintCallable)
	ULockonMarkerWidget* GetLockonMarker()
	{
		return LockonMarker;
	}

	UFUNCTION(BlueprintCallable)
	UHPGaugeWidget* GetHPGauge()
	{
		return HPGauge;
	}

	UFUNCTION(BlueprintCallable)
	UDownPointGaugeWidget* GetDownPointGauge()
	{
		return DownPointGauge;
	}

	UFUNCTION(BlueprintCallable)
	UBoostGaugeWidget* GetBoostGauge()
	{
		return BoostGauge;
	}

	UFUNCTION(BlueprintCallable)
	UReticleWidget* GetReticle()
	{
		return Reticle;
	}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "AttackCollisionPool.generated.h"

class AAttackCollision;

/**
 * 
 */
UCLASS()
class MSGO_API UAttackCollisionPool : public UObject
{
	GENERATED_BODY()

public:
	// �I�u�W�F�N�g�v�[���̍ő吔
	static const int32 AttackCollisionPoolNum;

public:
	// �U���R���W�����̔z��
	UPROPERTY()
	TArray<TObjectPtr<AAttackCollision>> AttackCollisions;

public:
	// �Q�[���J�n������
	void BeginPlay();

	// �Q�[���I��������
	void BeginDestroy();

};

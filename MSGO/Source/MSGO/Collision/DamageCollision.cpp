// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/DamageCollision.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AttackCollision.h"
#include "../Characters/MSGOCharacter.h"

// Sets default values for this component's properties
UDamageCollision::UDamageCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxCollision")));
	//if (BoxCollision)
	//{
	//	BoxCollision->SetBoxExtent(FVector(0.f));
	//	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	BoxCollision->SetComponentTickEnabled(false);
	//}

	// ...
}


// Called when the game starts
void UDamageCollision::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddUniqueDynamic(this, &UDamageCollision::OnBeginOverlap);
	// ...
	
}

void UDamageCollision::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnComponentBeginOverlap.RemoveDynamic(this, &UDamageCollision::OnBeginOverlap);
}


// Called every frame
void UDamageCollision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// �R���W�����̃Z�b�g�A�b�v
bool UDamageCollision::SetupCollision(const FDamageCollisionParametr& InDamageCollParam)
{
	this->SetBoxExtent(InDamageCollParam.CollisionSize);

	return true;
}

// �I�[�o�[���b�v�J�n����(��e����)
void UDamageCollision::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, "BeginOverlap");

	// �U���R���W�������q�b�g���������`�F�b�N
	if (AAttackCollision* attackColl = Cast<AAttackCollision>(Other))
	{
		// ���g�̎g�p�҂��擾
		AMSGOCharacter* ownerChara = Cast<AMSGOCharacter>(GetOwner());
		if (!ownerChara)
		{
			return;
		}

		// �U���R���W�����̎g�p�҂��擾
		AMSGOCharacter* attackOwner = attackColl->GetOwnerCharacter();
		//�@�U���̎g�p�҂�Null�A�������͎��g�̎g�p�҂Ɠ����ꍇ�͏������Ȃ�
		if (!attackOwner || ownerChara == attackOwner)
		{
			return;
		}

		// �����܂ŗ�����q�b�g
		UKismetSystemLibrary::PrintString(this, "BeginOverlap");
		// �U���R���W�������폜�i��������j
		attackColl->SleepObject();

		// �U���҂ƃ`�[��ID���قȂ�ꍇ�̓_���[�W����
		if (attackOwner->TeamId != ownerChara->TeamId)
		{
			// �����Ƀ_���[�W����������
		}
	}
}

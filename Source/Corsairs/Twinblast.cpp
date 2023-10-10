// Fill out your copyright notice in the Description page of Project Settings.


#include "Twinblast.h"

ATwinblast::ATwinblast()
{
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -97.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Twinblast(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ShadowOps/Meshes/TwinBlast_ShadowOps"));
	if (SK_Twinblast.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Twinblast.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Twinblast(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Twinblast_AnimBlueprint_1"));
	if (ABP_Twinblast.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP_Twinblast.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Twinblast_BasicAttack(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Animations/Primary_Fire_Med_A_Montage"));
	if (AM_Twinblast_BasicAttack.Succeeded())
	{
		BasicAttackAnimMontage = AM_Twinblast_BasicAttack.Object;
	}

	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
}

void ATwinblast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LMB Attack", IE_Pressed, this, &ATwinblast::SetupBasicAttack);
}

void ATwinblast::SetupBasicAttack()
{
	if (bIsAttacking == true)
	{
		bSaveAttack = true;
	}
	else
	{
		bIsAttacking = true;

		PlayBasicComboAttack();
	}
}

void ATwinblast::SaveComboAttack()
{
	if (bSaveAttack == true)
	{
		bSaveAttack = false;

		PlayBasicComboAttack();
	}
}

void ATwinblast::PlayBasicComboAttack()
{
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		PlayAnimMontage(BasicAttackAnimMontage);
		break;
	case 1:
		AttackCount = 0;
		PlayAnimMontage(BasicAttackAnimMontage);
		break;
	default:
		break;
	}
}

void ATwinblast::ResetCombo()
{
	AttackCount = 0;
	bSaveAttack = false;
	bIsAttacking = false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Twinblast.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Twinblast_primaryAttack(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Animations/Primary_Fire_Med_A_Montage"));
	if (AM_Twinblast_primaryAttack.Succeeded())
	{
		PrimaryAttackAnimMontage = AM_Twinblast_primaryAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Twinblast_PrimayAttack_1(TEXT("/Game/ParagonTwinblast/FX/Particles/Abilities/Primary/FX/P_TwinBlast_Primary_MuzzleFlash"));
	if (PS_Twinblast_PrimayAttack_1.Succeeded())
	{
		FirstPrimaryAttackParticle = PS_Twinblast_PrimayAttack_1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Twinblast_PrimayAttack_2(TEXT("/Game/ParagonTwinblast/FX/Particles/Abilities/Primary/FX/P_TwinBlast_Primary_MuzzleFlash"));
	if (PS_Twinblast_PrimayAttack_2.Succeeded())
	{
		SecondPrimaryAttackParticle = PS_Twinblast_PrimayAttack_2.Object;
	}

	FirstPistolStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirstPistolStartPoint"));
	FirstPistolStartPoint->SetupAttachment(GetMesh(), TEXT("Muzzle_01"));

	SecondPistolStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SecondPistolStartPoint"));
	SecondPistolStartPoint->SetupAttachment(GetMesh(), TEXT("Muzzle_02"));

	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
}

void ATwinblast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LMB Attack", IE_Pressed, this, &ATwinblast::SetupPrimaryAttack);
}

void ATwinblast::SetupPrimaryAttack()
{
	if (bIsAttacking == true)
	{
		bSaveAttack = true;
	}
	else
	{
		bIsAttacking = true;

		PlayPrimaryComboAttack();
	}
}

void ATwinblast::SaveComboAttack()
{
	if (bSaveAttack == true)
	{
		bSaveAttack = false;

		PlayPrimaryComboAttack();
	}
}

void ATwinblast::PlayPrimaryComboAttack()
{
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		PlayAnimMontage(PrimaryAttackAnimMontage);
		UGameplayStatics::SpawnEmitterAttached(FirstPrimaryAttackParticle, FirstPistolStartPoint);
		break;
	case 1:
		AttackCount = 0;
		PlayAnimMontage(PrimaryAttackAnimMontage);
		UGameplayStatics::SpawnEmitterAttached(FirstPrimaryAttackParticle, FirstPistolStartPoint);
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

void ATwinblast::SecondFire()
{
	UGameplayStatics::SpawnEmitterAttached(SecondPrimaryAttackParticle, SecondPistolStartPoint);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorsairsCharacter.h"
#include "Twinblast.generated.h"

/**
 * 
 */
UCLASS()
class CORSAIRS_API ATwinblast : public ACorsairsCharacter
{
	GENERATED_BODY()

public:
	ATwinblast();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupBasicAttack();

	UFUNCTION(BlueprintCallable)
	void SaveComboAttack();

	void PlayBasicComboAttack();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int AttackCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BasicAttackAnimMontage;
};

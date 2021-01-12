// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ComoPicaro/Enemies/Components/FireComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class COMOPICARO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


		/** The camera */
		UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
protected:
	UPROPERTY(Category = Fire, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UFireComponent* MFireComponent;

	UPROPERTY(Category = Fire, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UFireComponent* UltimateFireComponent;
public:
	// Sets default values for this character's properties
	AMainCharacter();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SimpleAttackSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ActualHealth;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsLeftClickPressed;

	bool IsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ExtraDamageSimpleAttack;

	//TArray<APowerUp*> ListOfHabilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 PointsToUltimate;

private:
	float TimeSinceLastSimpleAttack;


private:
	void RotationToAttack(FLatentActionInfo info);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void OnSimpleAttack();
	virtual void OnUltimate();

	UFUNCTION(BlueprintCallable)
		void AddHability(APowerUp* Hability);


public:
	UFUNCTION(BlueprintCallable)
		virtual void SimpleShoot();

	virtual void MUltimate();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	void Damage(int32 Dmg);

	virtual void StartDeathAnimation();

	void DisableLeftClickPressed();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

public:
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};

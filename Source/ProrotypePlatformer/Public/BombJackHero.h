// Let us start with spring component, camera to Character and go on later to add more
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "BombJackHero.generated.h"

UCLASS()
class PROROTYPEPLATFORMER_API ABombJackHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABombJackHero();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputMappingContext* IMCBombJack;
	
	UPROPERTY(EditAnywhere, Category = "mInput")
	UInputAction* MoveAction;
	
	void Move(const FInputActionValue& Value );
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
	UCameraComponent* Camera;
};

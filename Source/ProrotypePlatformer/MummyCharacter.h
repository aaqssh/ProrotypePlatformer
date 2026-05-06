// i need this for box collision for mummy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MummyCharacter.generated.h"

class UBoxComponent;
UCLASS()
class PROROTYPEPLATFORMER_API AMummyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMummyCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* DamageBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FVector MummyPatrolPoint;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent*OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

};

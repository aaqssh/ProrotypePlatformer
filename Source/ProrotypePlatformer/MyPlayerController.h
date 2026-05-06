// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyPlayerController.generated.h"

class UBehaviorTree;



UCLASS()
class PROROTYPEPLATFORMER_API AMyPlayerController : public AAIController
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UBehaviorTree* BehaviorTree;
	
	protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};

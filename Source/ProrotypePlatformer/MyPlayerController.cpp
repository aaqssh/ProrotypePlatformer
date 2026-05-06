// 


#include "MyPlayerController.h"
#include "MummyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	AMummyCharacter* MummyPawn = Cast<AMummyCharacter>(InPawn);
	if (MummyPawn && GetBlackboardComponent())
	{
		FVector StartLocation = MummyPawn->GetActorLocation();
		FVector PatrolLocation = StartLocation + MummyPawn->MummyPatrolPoint;
		
		GetBlackboardComponent()->SetValueAsVector("StartPatrol", StartLocation);
		GetBlackboardComponent()->SetValueAsVector("PatrolLocation", PatrolLocation);
	}
}


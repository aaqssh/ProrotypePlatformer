// For enemy 


#include "MummyCharacter.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Setting a default value
AMummyCharacter::AMummyCharacter()
{
	//box component and attached to roots
	DamageBox = CreateDefaultSubobject<UBoxComponent>(FName("DamageBox"));
	DamageBox->SetupAttachment(RootComponent);
	
	MummyPatrolPoint=FVector(500,0,0);
}

// Called when the game starts or when spawned
void AMummyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (DamageBox)
	{
		DamageBox->OnComponentBeginOverlap.AddDynamic(this,&AMummyCharacter::OnBoxOverlap);
	}
}

void AMummyCharacter::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent,AActor*OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 1.0f, GetController(),this ,UDamageType::StaticClass());
	}
}

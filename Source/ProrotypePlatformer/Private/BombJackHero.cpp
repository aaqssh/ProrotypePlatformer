
#include "BombJackHero.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// these were values that i used in blueprint first and putting this in code now
ABombJackHero::ABombJackHero()
{
	//Just start things
	PrimaryActorTick.bCanEverTick = true;
	
	//For Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = true;
	SpringArm-> TargetArmLength = 2000.0f;
	
	//For camera 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	Camera->SetupAttachment(SpringArm);
	
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 8.492264f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	
	//Just fixing max speed to 500 and additional default setting change to true
	GetCharacterMovement()->MaxWalkSpeed=500.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// After setting Enhanced Input then this 
void ABombJackHero::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* BombJackController = Cast<APlayerController>(GetController());
	
	if (BombJackController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(BombJackController->GetLocalPlayer());
		
		if (Subsystem)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCBombJack,0);
		}
	}
}



// Runs every frame for gameplay
void ABombJackHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// bind functionality to input
void ABombJackHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &ABombJackHero::Move);
	}

}

void ABombJackHero::Move(const FInputActionValue& Value)
{
	FVector2D RCVValue = Value.Get<FVector2D>();
	
	FRotator ControlRotation = GetControlRotation();
	FVector FrontVector = FRotationMatrix(FRotator(0,ControlRotation.Yaw,0)).GetUnitAxis(EAxis::X);
	AddMovementInput(FrontVector,RCVValue.Y);
}
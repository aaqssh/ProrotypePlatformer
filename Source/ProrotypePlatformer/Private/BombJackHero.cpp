
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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 8.49220f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = true;
	SpringArm-> TargetArmLength = 2000.0f;
	
	//For camera 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 8.492264f));
	
	
	//Just fixing max speed to 500 and additional default setting change to true
	GetCharacterMovement()->MaxWalkSpeed=500.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity=1500.0f;
	GetCharacterMovement()->AirControl=0.35f;
	//Rotates player backward to walk 
	bUseControllerRotationYaw = false;
	
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
		//for moving
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &ABombJackHero::Move);
	   // Jumping and stop jump
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started, this, &ABombJackHero::Jump);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed, this, &ABombJackHero::StopJumping);
	}
	

}

void ABombJackHero::Move(const FInputActionValue& Value)
{
	FVector2D RCVValue = Value.Get<FVector2D>();
	
	if (Controller)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,ControlRotation.Yaw,0);
		
		const FVector Forward = -FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Forward,RCVValue.Y);
		//AddMovementInput(Right,RCVValue.X);
		
		//FVector FrontVector = FRotationMatrix(FRotator(0,ControlRotation.Yaw,0)).GetUnitAxis(EAxis::X);
		//AddMovementInput(FrontVector,RCVValue.Y);
		
	}

}


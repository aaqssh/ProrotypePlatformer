// Fill out your copyright notice in the Description page of Project Settings.


#include "BombJackHero.h"

// Sets default values
ABombJackHero::ABombJackHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABombJackHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombJackHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABombJackHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


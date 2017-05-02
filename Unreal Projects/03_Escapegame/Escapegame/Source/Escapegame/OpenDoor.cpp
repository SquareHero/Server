// Fill out your copyright notice in the Description page of Project Settings.

#include "Escapegame.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();	
}

void UOpenDoor::OpenDoor()
{
	// Find the owing object
	AActor* Owner = GetOwner();

	//Create the rotatator
	FRotator NewRotation = FRotator(0.0f, -60.0, 0.0f);
	//set the door rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//Poll the Trigger Volum
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();

	}
	//If the ActorThat opens is in the volum
		

}


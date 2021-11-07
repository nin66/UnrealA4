// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/GameEngine.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUD.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth); //Replicate the current health just like the labs
}

void UHealthComponent::OnTakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0; //if the player's health is 0, it will die and then proceed to the OnDeath function
		OnDeath();
	}
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority && Pawn->IsLocallyControlled())
		{
			UpdateHealthBar(); //update the healthbar for a listen server
		}
	}
}

void UHealthComponent::OnDeath()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()); //gets the dying character
	if (PlayerCharacter)
	{
		PlayerCharacter->OnDeath(); //proceed to with the on death procedure, then respawns 
	}
}

float UHealthComponent::HealthPercentageRemaining()
{
	return CurrentHealth / MaxHealth * 100.0f; //returns the current health
}

void UHealthComponent::UpdateHealthBar()
{
	if (APawn* Pawn = Cast<APawn>(GetOwner())) {
		if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy || (GetOwner()->GetLocalRole() == ROLE_Authority && Pawn->IsLocallyControlled()))
		{
			APlayerHUD* PlayerHUD = dynamic_cast<APlayerHUD*>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
			if (PlayerHUD)
			{
				PlayerHUD->SetPlayerHealthBarPercent(CurrentHealth / MaxHealth); //is able to set the health bar for a listen/dedicated server
			}
		}
	}
}


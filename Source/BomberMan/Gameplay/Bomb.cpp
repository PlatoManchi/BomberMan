// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Gameplay/LevelCreator.h"
#include "Characters/BomberManCharacter.h"

// Engine includes
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABomb::ABomb() :
	TimeElapsed(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	BoxCollider->bGenerateOverlapEvents = true;
	BoxCollider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);

	

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleTemplateClass(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if (ExplosionParticleTemplateClass.Object != NULL)
	{
		ExplosionParticleTemplate = ExplosionParticleTemplateClass.Object;
	}
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeElapsed += DeltaTime;

	if (TimeElapsed >= ExplosionDelay)
	{
		Explode();
	}
}

void ABomb::SetOwningCharacter_Implementation(ABomberManCharacter * NewOwningCharacter)
{
	OwningCharacter = NewOwningCharacter;
}

void ABomb::Explode()
{
	// Visual and damage
	if (ExplosionParticleTemplate)
	{
		FTransform transform(GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);

		for (int i = 0; i < ExplosionLength; ++i)
		{
			// Right
			FVector location = GetActorLocation() + FVector(1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * i;
			transform.SetLocation(location);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);



			// Left
			location = GetActorLocation() + FVector(-1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * i;
			transform.SetLocation(location);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);

			// Up
			location = GetActorLocation() + FVector(0.0f, 1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * i;
			transform.SetLocation(location);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);

			// Down
			location = GetActorLocation() + FVector(0.0f, -1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * i;
			transform.SetLocation(location);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);
		}
	}
	Destroy();
}

void ABomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("OnOverlapBegin"));
}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("OnOverlapEnd"));
}

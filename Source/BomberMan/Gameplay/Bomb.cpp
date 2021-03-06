// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "BomberManGameMode.h"
#include "Gameplay/LevelCreator.h"
#include "Characters/BomberManCharacter.h"

// Engine includes
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABomb::ABomb() :
	TimeElapsed(0.0f),
	IsExploding(false),
	PlayerCountOverlappingBomb(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	BoxCollider->bGenerateOverlapEvents = true;
	BoxCollider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	
	USceneComponent* StraightColliders = CreateDefaultSubobject<USceneComponent>(TEXT("StraightColliders"));
	StraightColliders->SetupAttachment(RootComponent);

	HorizontalBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HorizontalBoxCollider"));
	HorizontalBoxCollider->SetupAttachment(StraightColliders);
	HorizontalBoxCollider->bGenerateOverlapEvents = true;
	HorizontalBoxCollider->SetBoxExtent(FVector(0.0f, 0.0f, 0.0f));

	VerticalBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("VerticalBoxCollider"));
	VerticalBoxCollider->SetupAttachment(StraightColliders);
	VerticalBoxCollider->bGenerateOverlapEvents = true;
	VerticalBoxCollider->SetBoxExtent(FVector(0.0f, 0.0f, 0.0f));

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleTemplateClass(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if (ExplosionParticleTemplateClass.Object != NULL)
	{
		ExplosionParticleTemplate = ExplosionParticleTemplateClass.Object;
	}
}

void ABomb::SetExplosionLength(int32 NewExplosionLength)
{
	ExplosionLength = NewExplosionLength;
}

void ABomb::SetExplosionDelay(float NewExplosionDelay)
{
	ExplosionDelay = NewExplosionDelay;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);

	BomberManGameMode = Cast<ABomberManGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (BomberManGameMode->GetIsRoundOver()) return;

	TimeElapsed += DeltaTime;
	if (TimeElapsed >= ExplosionDelay)
	{
		Explode();
	}
}


void ABomb::Explode_Implementation()
{
	if (IsExploding)
	{
		return;
	}

	IsExploding = true;

	DealDamage();

	// Fire event that this bomb is exploding
	if (OnBombExploded.IsBound())
	{
		OnBombExploded.Broadcast(this);
	}

	// Visual and damage
	if (ExplosionParticleTemplate)
	{
		FTransform transform(GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);

		for (int i = 0; i < ExplosionLength; ++i)
		{
			// Right - Spawn particles
			FVector location = FVector(1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * i;
			if (FMath::Abs(location.X) < rightDistance)
			{
				transform.SetLocation(location + GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);
			}
			
			// Left - Spawn particles
			location = FVector(-1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * i;
			if (FMath::Abs(location.X) < leftDistance)
			{
				transform.SetLocation(location + GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);
			}
			
			// Up - Spawn particles
			location = FVector(0.0f, -1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * i;
			if (FMath::Abs(location.Y) < upDistance)
			{
				transform.SetLocation(location + GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);
			}
			
			// Down - Spawn particles
			location = FVector(0.0f, 1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * i;
			if (FMath::Abs(location.Y) < downDistance)
			{
				transform.SetLocation(location + GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleTemplate, transform, true);
			}
			
		}
	}

	Destroy();
}

float ABomb::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Explode the bomb
	if (!IsExploding)
	{
		Explode();
	}
	
	return actualDamage;
}

void ABomb::SetOwningCharacter_Implementation(ABomberManCharacter* NewOwningCharacter)
{
	OwningCharacter = NewOwningCharacter;
	OnBombExploded.AddDynamic(OwningCharacter, &ABomberManCharacter::OnBombExploded);
}

void ABomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	ABomberManCharacter* character = Cast<ABomberManCharacter>(OtherActor);
	if(character)
	{
		PlayerCountOverlappingBomb++;
	}
}

void ABomb::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ABomberManCharacter* character = Cast<ABomberManCharacter>(OtherActor);
	if (character)
	{
		PlayerCountOverlappingBomb--;
	}

	if (PlayerCountOverlappingBomb == 0)
	{
		BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);
	}
}


void ABomb::DealDamage()
{
	/** All bombs have two colliders one horizontal and one vertical
		Ray cast right and left side to see if there are any blocks that block the explosion.
		Then calculate the distance between them and extend the collider to that size.
		Do the same for up and down.
		Get all the actors inside the colliders and damage them.
	*/
	TArray<AActor*> AllOverlappingActors;

	TArray<AActor*> tmpActors;

	// Right - Increase the collider and get overlapping actors in the area
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart + FVector(1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * ExplosionLength;
	traceEnd = GetLineTraceLocation(traceStart, traceEnd);

	float distanceX = traceEnd.X - traceStart.X;
	rightDistance = FMath::Abs(distanceX);

	// Left - Increase the collider and get overlapping actors in the area
	traceEnd = traceStart + FVector(-1.0f, 0.0f, 0.0f) * ALevelCreator::TILE_X_LENGTH * ExplosionLength;
	traceEnd = GetLineTraceLocation(traceStart, traceEnd);

	distanceX = traceEnd.X - traceStart.X;
	leftDistance = FMath::Abs(distanceX);

	distanceX = rightDistance + leftDistance;
	float x = (rightDistance - leftDistance) / 2.0f;
	
	// Resize the horizontal collider to fit the size of collision
	HorizontalBoxCollider->SetBoxExtent(FVector(distanceX / 2.0f, ALevelCreator::TILE_Y_LENGTH / 2.0f, ALevelCreator::TILE_Z_LENGTH / 2.0f));
	HorizontalBoxCollider->SetRelativeLocation(FVector(x , 0.0f, 0.0f));

	// Get all actors overlapping with right collider
	HorizontalBoxCollider->GetOverlappingActors(tmpActors, AActor::StaticClass());
	for (AActor* actor : tmpActors)
	{
		AllOverlappingActors.AddUnique(actor);
	}
	tmpActors.Empty();

	
	// UP - Increase the collider and get overlapping actors in the area
	traceEnd = traceStart + FVector(0.0f, -1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * ExplosionLength;
	traceEnd = GetLineTraceLocation(traceStart, traceEnd);

	float distanceY = traceEnd.Y - traceStart.Y;
	upDistance = FMath::Abs(distanceY);

	// Down - Increase the collider and get overlapping actors in the area
	traceEnd = traceStart + FVector(0.0f, 1.0f, 0.0f) * ALevelCreator::TILE_Y_LENGTH * ExplosionLength;
	traceEnd = GetLineTraceLocation(traceStart, traceEnd);

	distanceY = traceEnd.Y - traceStart.Y;
	downDistance = FMath::Abs(distanceY);

	distanceY = upDistance + downDistance;
	float y = (downDistance - upDistance) / 2.0f;

	// Resize vertical collider to fit the size of collision
	VerticalBoxCollider->SetBoxExtent(FVector(ALevelCreator::TILE_X_LENGTH / 2.0f, distanceY / 2.0f, ALevelCreator::TILE_Z_LENGTH / 2.0f));
	VerticalBoxCollider->SetRelativeLocation(FVector(0.0f, y, 0.0f));

	// Get all actors overlapping with up collider
	VerticalBoxCollider->GetOverlappingActors(tmpActors, AActor::StaticClass());
	for (AActor* actor : tmpActors)
	{
		AllOverlappingActors.AddUnique(actor);	
	}
	tmpActors.Empty();

	// Deal damage to all overlapping actors.
	for (AActor* actor : AllOverlappingActors)
	{
		UGameplayStatics::ApplyDamage(actor, 50.0f, OwningCharacter->Controller, this, UDamageType::StaticClass());
	}
}

FVector ABomb::GetLineTraceLocation(FVector Start, FVector End)
{
	FCollisionQueryParams traceParams = FCollisionQueryParams();
	traceParams.AddIgnoredActor(this);
	traceParams.bTraceAsyncScene = false;
	traceParams.bReturnPhysicalMaterial = false;

	FVector result = End;
	TArray<FHitResult> hitResults;

	// Do a line trace and get all objects in the line of site
	if (GetWorld()->LineTraceMultiByChannel(hitResults, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
	{
		for (FHitResult hitResult : hitResults)
		{
			if (hitResult.bBlockingHit)
			{
				if (hitResult.GetActor()->ActorHasTag("BaseBlock"))
				{
					result = hitResult.ImpactPoint;
					break;
				}
				else
				{
					AStaticMeshActor* staticMesh = Cast<AStaticMeshActor>(hitResult.GetActor());
					if (staticMesh)
					{
						result = hitResult.ImpactPoint;
						break;
					}
				}
			}
		}
	}

	return result;
}

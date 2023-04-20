// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

#include "MeshAttributes.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACoinItem::ACoinItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.0f,32.0f,32.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SuperMesh->AttachToComponent(CollisionBox, FAttachmentTransformRules::SnapToTargetIncludingScale);
	RootComponent = CollisionBox;
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::OnOverlapBegin);
	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 1.f;
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(PitchValue, YawValue, RollValue), false, 0, ETeleportType::None);

}

void ACoinItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Yellow, "OverlapBeginFunctionCalled");
	
	this->Destroy();
}


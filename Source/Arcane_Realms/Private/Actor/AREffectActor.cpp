// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AREffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ARAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAREffectActor::AAREffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAREffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UARAttributeSet* ARAttributeSet = Cast<UARAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UARAttributeSet::StaticClass()));

		UARAttributeSet* MutableARAttributeSet = const_cast<UARAttributeSet*>(ARAttributeSet);
		MutableARAttributeSet->SetHealth(ARAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAREffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AAREffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAREffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAREffectActor::EndOverlap);
}

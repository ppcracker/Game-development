#include "Actors/BoxActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "YourProjectGameModeBase.h"

ABoxActor::ABoxActor()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = BoxMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (BoxMeshAsset.Succeeded())
    {
        BoxMesh->SetStaticMesh(BoxMeshAsset.Object);
    }

    HealthComponent = CreateDefaultSubobject<UBoxHealthComponent>(TEXT("HealthComponent"));
}

void ABoxActor::BeginPlay()
{
    Super::BeginPlay();
}

void ABoxActor::Initialize(FLinearColor InColor, int32 InHealth, int32 InScore)
{
    DynamicMaterial = UMaterialInstanceDynamic::Create(BoxMesh->GetMaterial(0), this);
    DynamicMaterial->SetVectorParameterValue("BaseColor", InColor);
    BoxMesh->SetMaterial(0, DynamicMaterial);

    HealthComponent->Initialize(InHealth);
    ScoreValue = InScore;
}

void ABoxActor::TakeDamage()
{
    if (HealthComponent->ApplyDamage(1))
    {
        OnBoxDestroyed();
    }
}

void ABoxActor::OnBoxDestroyed()
{
    AYourProjectGameModeBase* GM = Cast<AYourProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GM)
    {
        GM->AddScore(ScoreValue);
    }

    Destroy();
}

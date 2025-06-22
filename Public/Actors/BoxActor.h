#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class UBoxHealthComponent;

UCLASS()
class YOURPROJECT_API ABoxActor : public AActor
{
    GENERATED_BODY()
    
public:    
    ABoxActor();

    void Initialize(FLinearColor InColor, int32 InHealth, int32 InScore);

    void TakeDamage();

    int32 GetScore() const { return ScoreValue; }

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BoxMesh;

    UPROPERTY()
    UMaterialInstanceDynamic* DynamicMaterial;

    UPROPERTY(VisibleAnywhere)
    UBoxHealthComponent* HealthComponent;

    int32 ScoreValue;

    void OnBoxDestroyed();
};

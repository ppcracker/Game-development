#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoxHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOURPROJECT_API UBoxHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    void Initialize(int32 InHealth);
    bool ApplyDamage(int32 DamageAmount);

private:
    int32 Health;
};

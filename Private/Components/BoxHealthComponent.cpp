#include "Components/BoxHealthComponent.h"

void UBoxHealthComponent::Initialize(int32 InHealth)
{
    Health = InHealth;
}

bool UBoxHealthComponent::ApplyDamage(int32 DamageAmount)
{
    Health -= DamageAmount;
    return Health <= 0;
}

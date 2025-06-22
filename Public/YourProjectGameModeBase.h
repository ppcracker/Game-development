#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YourProjectGameModeBase.generated.h"

class UScoreWidget;

UCLASS()
class YOURPROJECT_API AYourProjectGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
    
public:
    void AddScore(int32 Amount);

protected:
    virtual void BeginPlay() override;

private:
    int32 CurrentScore;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UScoreWidget> ScoreWidgetClass;

    UPROPERTY()
    UScoreWidget* ScoreWidget;
};

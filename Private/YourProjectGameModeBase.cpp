#include "YourProjectGameModeBase.h"
#include "UI/ScoreWidget.h"
#include "Blueprint/UserWidget.h"

void AYourProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (ScoreWidgetClass)
    {
        ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
        if (ScoreWidget)
        {
            ScoreWidget->AddToViewport();
            ScoreWidget->UpdateScore(CurrentScore);
        }
    }
}

void AYourProjectGameModeBase::AddScore(int32 Amount)
{
    CurrentScore += Amount;
    if (ScoreWidget)
    {
        ScoreWidget->UpdateScore(CurrentScore);
    }
}

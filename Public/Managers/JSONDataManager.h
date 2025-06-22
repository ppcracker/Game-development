#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JSONDataManager.generated.h"

USTRUCT()
struct FBoxType
{
    GENERATED_BODY()

    FString Name;
    FLinearColor Color;
    int32 Health;
    int32 Score;
};

USTRUCT()
struct FBoxObject
{
    GENERATED_BODY()

    FString Type;
    FVector Location;
    FRotator Rotation;
    FVector Scale;
};

UCLASS()
class YOURPROJECT_API AJSONDataManager : public AActor
{
    GENERATED_BODY()

public:    
    AJSONDataManager();

protected:
    virtual void BeginPlay() override;

private:
    FString JSONUrl;
    TMap<FString, FBoxType> Types;
    TArray<FBoxObject> Objects;

    void DownloadJSON();
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void ParseJSON(const FString& JSONString);
    void SpawnBoxes();
};

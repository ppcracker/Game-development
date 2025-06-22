#include "Managers/JSONDataManager.h"
#include "Actors/BoxActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

AJSONDataManager::AJSONDataManager()
{
    JSONUrl = TEXT("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
}

void AJSONDataManager::BeginPlay()
{
    Super::BeginPlay();
    DownloadJSON();
}

void AJSONDataManager::DownloadJSON()
{
    FHttpModule* Http = &FHttpModule::Get();
    if (!Http) return;

    TSharedRef<IHttpRequest> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &AJSONDataManager::OnResponseReceived);
    Request->SetURL(JSONUrl);
    Request->SetVerb("GET");
    Request->ProcessRequest();
}

void AJSONDataManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
        return;
    }

    ParseJSON(Response->GetContentAsString());
}

void AJSONDataManager::ParseJSON(const FString& JSONString)
{
    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);

    if (FJsonSerializer::Deserialize(Reader, Root))
    {
        // Types
        TArray<TSharedPtr<FJsonValue>> TypesArray = Root->GetArrayField("types");
        for (const auto& Item : TypesArray)
        {
            TSharedPtr<FJsonObject> Obj = Item->AsObject();
            FBoxType Type;
            Type.Name = Obj->GetStringField("name");

            const TArray<TSharedPtr<FJsonValue>> ColorArray = Obj->GetArrayField("color");
            Type.Color = FLinearColor(
                ColorArray[0]->AsNumber() / 255.f,
                ColorArray[1]->AsNumber() / 255.f,
                ColorArray[2]->AsNumber() / 255.f
            );

            Type.Health = Obj->GetIntegerField("health");
            Type.Score = Obj->GetIntegerField("score");

            Types.Add(Type.Name, Type);
        }

        // Objects
        TArray<TSharedPtr<FJsonValue>> ObjectsArray = Root->GetArrayField("objects");
        for (const auto& Item : ObjectsArray)
        {
            TSharedPtr<FJsonObject> Obj = Item->AsObject();
            FBoxObject Object;
            Object.Type = Obj->GetStringField("type");

            TArray<TSharedPtr<FJsonValue>> LocArray = Obj->GetObjectField("transform")->GetArrayField("location");
            Object.Location = FVector(LocArray[0]->AsNumber(), LocArray[1]->AsNumber(), LocArray[2]->AsNumber());

            TArray<TSharedPtr<FJsonValue>> RotArray = Obj->GetObjectField("transform")->GetArrayField("rotation");
            Object.Rotation = FRotator(RotArray[1]->AsNumber(), RotArray[2]->AsNumber(), RotArray[0]->AsNumber());

            TArray<TSharedPtr<FJsonValue>> ScaleArray = Obj->GetObjectField("transform")->GetArrayField("scale");
            Object.Scale = FVector(ScaleArray[0]->AsNumber(), ScaleArray[1]->AsNumber(), ScaleArray[2]->AsNumber());

            Objects.Add(Object);
        }

        SpawnBoxes();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("JSON Parse Error"));
    }
}

void AJSONDataManager::SpawnBoxes()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (const auto& Obj : Objects)
    {
        if (!Types.Contains(Obj.Type)) continue;

        FBoxType TypeData = Types[Obj.Type];
        FActorSpawnParameters SpawnParams;
        ABoxActor* Box = World->SpawnActor<ABoxActor>(Obj.Location, Obj.Rotation, SpawnParams);
        Box->SetActorScale3D(Obj.Scale);
        Box->Initialize(TypeData.Color, TypeData.Health, TypeData.Score);
    }
}

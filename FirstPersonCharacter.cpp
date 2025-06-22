// Inside the fire function
FHitResult Hit;
FVector Start = CameraLocation;
FVector End = Start + (CameraForwardVector * 10000);

FCollisionQueryParams Params;
Params.AddIgnoredActor(this);

if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
{
    ABoxActor* Box = Cast<ABoxActor>(Hit.GetActor());
    if (Box)
    {
        Box->TakeDamage();
    }
}

#ifndef RESOURCES_H
#define RESOURCES_H

namespace Body
{
    // chose body picture by enum
    enum BodyName
    {
        Body = 0,
        BlueBody,
        PinkBody,
        IceFireBody,
        CatBody,
        GundamBody,
        DrillBody,
        AngelBody
    };

    char* getBody(BodyName index);
}

namespace Ear
{
    // chose ear picture by enum
    enum EarName
    {
        Ear = 0,
        BlueEar,
        PinkEar,
        IceFireEar,
        CatEar,
        GundamEar,
        DrillEar,
        Ear2,
        AngelEar,
        BlueEar2,
        PinkEar2,
        IceFireEar2,
        CatEar2,
        GundamEar2,
        DrillEar2,
        AngelEar2
    };

    char* getEar(EarName index);
}

namespace Eye
{
    // chose eye picture by enum
    enum EyeName
    {
        Eye = 0
    };

    char* getEye(EyeName index);
} // namespace Eye

namespace Stripe
{
    // chose stripe picture by enum
    enum StripeName
    {
        Stripe = 0
    };

    char* getStripe(StripeName index);
} // namespace Stripe

#endif
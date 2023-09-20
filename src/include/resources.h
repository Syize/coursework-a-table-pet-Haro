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
        AngelBody,
        Dummy = 99
    };

    // body number except `Dummy`
    const int BodyNum = 8;

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
        AngelEar
    };

    // store ear animation in two enum so we can get picture path with same index
    enum EarName2
    {
        Ear2,
        BlueEar2,
        PinkEar2,
        IceFireEar2,
        CatEar2,
        GundamEar2,
        DrillEar2,
        AngelEar2
    };

    // Ear number except Ear followed by 2
    const int EarNum = 8;

    char* getEar(EarName index);

    char* getEar2(EarName2 index);
}

namespace Eye
{
    // chose eye picture by enum
    enum EyeName
    {
        Eye = 0,
        ByeEye = 99
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

namespace HaroIcon
{
    // chose icon by enum
    enum IconName
    {
        Add = 0,
        Calendar,
        Choose,
        Close,
        Dress,
        Game,
        Icon,
        Last,
        Min,
        More,
        Music,
        Next,
        Pause,
        Play,
        Setting
    };

    char* getIcon(IconName index);
}

namespace Movement
{
    enum MovementKind
    {
        Blink = 0,
        CloseEyes,
        Cruel,
        Error,
        Fly,
        Hand,
        Heart,
        Question,
        Wink,
    };
    const int movementNum = 9;
    // get picture number of specific movement
    int getMovementNum(MovementKind index);
    // get path name of specific movement
    char* getMovementName(MovementKind index);
} // namespace Movement

#endif
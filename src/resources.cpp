#include "resources.h"

// return body picture path
char* Body::getBody(Body::BodyName index)
{
    switch (index)
    {
    case Body:
        return ":/body/res/images/appearance/body/def_body.png";
        break;
    case BlueBody:
        return ":/body/res/images/appearance/body/blue_body.png";
        break;
    case PinkBody:
        return ":/body/res/images/appearance/body/pink_body.png";
        break;
    case IceFireBody:
        return ":/body/res/images/appearance/body/icefire_body.png";
        break;
    case CatBody:
        return ":/body/res/images/appearance/body/cat_body.png";
        break;
    case GundamBody:
        return ":/body/res/images/appearance/body/Gundam_body.png";
        break;
    case DrillBody:
        return ":/body/res/images/appearance/body/drill_body.png";
        break;
    case AngelBody:
        return ":/body/res/images/appearance/body/angel_body.png";
        break;
    case Dummy:
        return ":/body/res/images/appearance/body/dummy.png";
    default:
        throw "Invalid index";
        break;
    }
}

// return ear picture path
char* Ear::getEar(Ear::EarName index)
{
    switch (index)
    {
    case Ear:
        return ":/ear/res/images/appearance/ears/def_ears1.png";
        break;
    case BlueEar:
        return ":/ear/res/images/appearance/ears/blue_ears1.png";
        break;
    case PinkEar:
        return ":/ear/res/images/appearance/ears/pink_ears1.png";
        break;
    case IceFireEar:
        return ":/ear/res/images/appearance/ears/icefire_ears1.png";
        break;
    case CatEar:
        return ":/ear/res/images/appearance/ears/cat_ears1.png";
        break;
    case GundamEar:
        return ":/ear/res/images/appearance/ears/Gundam_ears1.png";
        break;
    case DrillEar:
        return ":/ear/res/images/appearance/ears/drill_ears1.png";
        break;
    case AngelEar:
        return ":/ear/res/images/appearance/ears/angel_ears1.png";
        break;
    case Ear2:
        return ":/ear/res/images/appearance/ears/def_ears2.png";
        break;
    case BlueEar2:
        return ":/ear/res/images/appearance/ears/blue_ears2.png";
        break;
    case PinkEar2:
        return ":/ear/res/images/appearance/ears/pink_ears2.png";
        break;
    case IceFireEar2:
        return ":/ear/res/images/appearance/ears/icefire_ears2.png";
        break;
    case CatEar2:
        return ":/ear/res/images/appearance/ears/cat_ears2.png";
        break;
    case GundamEar2:
        return ":/ear/res/images/appearance/ears/Gundam_ears2.png";
        break;
    case DrillEar2:
        return ":/ear/res/images/appearance/ears/drill_ears2.png";
        break;
    case AngelEar2:
        return ":/ear/res/images/appearance/ears/angel_ears2.png";
        break;
    default:
        throw "Invalid index";
        break;
    }
}

// return eye picture path
char* Eye::getEye(Eye::EyeName index)
{
    switch (index)
    {
    case Eye:
        return ":/eye/res/images/appearance/eyes/def_eyes.png";
        break;
    
    default:
        throw "Invalid index";
        break;
    }
}

// return stripe picture path
char* Stripe::getStripe(Stripe::StripeName index)
{
    switch (index)
    {
    case Stripe:
        return ":/stripe/res/images/appearance/stripe.png";
        break;
    
    default:
        throw "Invalid index";
        break;
    }
}

// return icon picture path
char* HaroIcon::getIcon(HaroIcon::IconName index)
{
    switch (index)
    {
    case Icon:
        return ":/icon/res/images/icon/haro_icon.ico";
        break;
    case Add:
        return ":/icon/res/images/icon/add.png";
        break;
    case Calendar:
        return ":/icon/res/images/icon/calendar.png";
        break;
    case Choose:
        return ":/icon/res/images/icon/choose.png";
        break;
    case Close:
        return ":/icon/res/images/icon/close.png";
        break;
    case Dress:
        return ":/icon/res/images/icon/dress.png";
        break;
    case Game:
        return ":/icon/res/images/icon/game.png";
        break;
    case Last:
        return ":/icon/res/images/icon/last.png";
        break;
    case Min:
        return ":/icon/res/images/icon/min.png";
    case More:
        return ":/icon/res/images/icon/more.png";
    case Music:
        return ":/icon/res/images/icon/music.png";
    case Next:
        return ":/icon/res/images/icon/next.png";
    case Pause:
        return ":/icon/res/images/icon/pause.png";
    case Play:
        return ":/icon/res/images/icon/play.png";
    case Setting:
        return ":/icon/res/images/icon/setting.png";
    
    default:
        throw "Invalid index";
        break;
    }
}

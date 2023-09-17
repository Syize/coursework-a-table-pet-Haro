#include "resources.h"

// return body picture path
char* Body::getBody(Body::BodyName index)
{
    switch (index)
    {
    case Body:
        return ":/images/appearance/body/def_body.png";
        break;
    case BlueBody:
        return ":/images/appearance/body/blue_body.png";
        break;
    case PinkBody:
        return ":/images/appearance/body/pink_body.png";
        break;
    case IceFireBody:
        return ":/images/appearance/body/icefire_body.png";
        break;
    case CatBody:
        return ":/images/appearance/body/cat_body.png";
        break;
    case GundamBody:
        return ":/images/appearance/body/Gundam_body.png";
        break;
    case DrillBody:
        return ":/images/appearance/body/drill_body.png";
        break;
    case AngelBody:
        return ":/images/appearance/body/angel_body.png";
        break;
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
        return ":/images/appearance/ears/def_ears1.png";
        break;
    case BlueEar:
        return ":/images/appearance/ears/blue_ears1.png";
        break;
    case PinkEar:
        return ":/images/appearance/ears/pink_ears1.png";
        break;
    case IceFireEar:
        return ":/images/appearance/ears/icefire_ears1.png";
        break;
    case CatEar:
        return ":/images/appearance/ears/cat_ears1.png";
        break;
    case GundamEar:
        return ":/images/appearance/ears/Gundam_ears1.png";
        break;
    case DrillEar:
        return ":/images/appearance/ears/drill_ears1.png";
        break;
    case AngelEar:
        return ":/images/appearance/ears/angel_ears1.png";
        break;
    case Ear2:
        return ":/images/appearance/ears/def_ears2.png";
        break;
    case BlueEar2:
        return ":/images/appearance/ears/blue_ears2.png";
        break;
    case PinkEar2:
        return ":/images/appearance/ears/pink_ears2.png";
        break;
    case IceFireEar2:
        return ":/images/appearance/ears/icefire_ears2.png";
        break;
    case CatEar2:
        return ":/images/appearance/ears/cat_ears2.png";
        break;
    case GundamEar2:
        return ":/images/appearance/ears/Gundam_ears2.png";
        break;
    case DrillEar2:
        return ":/images/appearance/ears/drill_ears2.png";
        break;
    case AngelEar2:
        return ":/images/appearance/ears/angel_ears2.png";
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
        return ":/images/appearance/eyes/def_eyes.png";
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
        return ":/images/appearance/stripe.png";
        break;
    
    default:
        throw "Invalid index";
        break;
    }
}

#include "viking.h"

CViking:: CViking ( )
 : CAttacker ( VIK_NAME, VIK_SIGN, VIK_HP, VIK_DAM, VIK_SPD, VIK_RAN, VIK_PRC )
{
}

CModel* CViking:: clone ( ) const 
{
    return new CViking ( *this );
}

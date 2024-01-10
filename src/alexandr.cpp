#include "alexandr.h"

CAlexandr:: CAlexandr ( )
 : CAttacker ( ALEX_NAME, ALEX_SIGN, ALEX_HP, ALEX_DAM, ALEX_SPD, ALEX_RAN, ALEX_PRC )
{
}

CModel* CAlexandr:: clone ( ) const 
{
    return new CAlexandr ( *this );
}

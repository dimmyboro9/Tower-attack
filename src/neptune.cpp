#include "neptune.h"
#include "constants.h"
#include "towers.h"

CNeptune:: CNeptune ( )
 : CTower ( NEP_NAME, NEP_SIGN, NEP_HP, NEP_DAM, NEP_RAN )
{
}

CModel* CNeptune:: clone ( ) const 
{
    return new CNeptune ( *this );
}

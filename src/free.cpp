#include "free.h"

CFree:: CFree ( )
 : CFixed_Model ( FREE_NAME, FREE_SIGN )
{
}

CModel* CFree:: clone ( ) const 
{
    return new CFree ( *this );
}

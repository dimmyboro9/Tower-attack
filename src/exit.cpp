#include "exit.h"

CExit:: CExit ( )
 : CFixed_Model ( EXIT_NAME, EXIT_SIGN )
{
}

CModel* CExit:: clone ( ) const
{
    return new CExit ( *this );
}

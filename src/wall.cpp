#include "wall.h"

CWall:: CWall ( )
 : CFixed_Model ( WALL_NAME, WALL_SIGN )
{
}

CModel* CWall:: clone ( ) const
{
    return new CWall ( *this );
}

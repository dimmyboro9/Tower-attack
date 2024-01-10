#include "entrance.h"

CEntrance:: CEntrance ( size_t num )
 : CFixed_Model ( ENT_NAME, ENT_SIGN )
 , m_Number ( num )
{
}

CModel* CEntrance:: clone ( ) const
{
    return new CEntrance ( *this );
}

void CEntrance:: print ( ostream& os ) const
{
    os << m_Sign << '=' << m_Number;
}

size_t CEntrance:: get_num ( ) const 
{
    return m_Number;
}

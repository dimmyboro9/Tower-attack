#include "attackers.h"

CAttacker:: CAttacker ( const string& name, char sign, size_t hp, size_t damage, size_t speed, size_t range, size_t price )
 : CNon_Fixed_Model ( name, ATT_TYPE, sign, hp, damage, range )
 , m_Speed ( speed )
 , m_Price ( price )
{
}

void CAttacker:: create_route ( list < TCoordinates > route )
{
    m_Route = route;
}

bool CAttacker:: make_move ( CMap& mappy )
{
    if ( m_Route . size ( ) <= m_Speed )
    {
        mappy . remove_model ( m_Location );
        return true;
    }
    if ( m_Location == TCoordinates ( 0, 0 ) )
        return false;
    if ( mappy . is_free ( m_Route . front ( ) ) )
    {
        mappy . swap_models ( m_Location, m_Route . front ( ) );
        m_Location = m_Route . front ( );
        m_Route . pop_front ( );
    }
    return false;
}

size_t CAttacker:: show_price ( ) const 
{
    return m_Price;
}

void CAttacker:: print_info ( ostream& os ) const
{
    os << m_Sign << ' ' << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ):   HP: " << m_Hp << "   DAM: " << m_Damage << "   SPEED: " << m_Speed << "   RANGE: " << m_Range;
}

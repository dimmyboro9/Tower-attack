#include "megadurum.h"

CMegadurum:: CMegadurum ( size_t attack_num )
 : CTower ( MEGA_NAME, MEGA_SIGN, MEGA_HP, MEGA_DAM, MEGA_RAN )
 , m_Attack_Number ( attack_num )
{
}

CModel* CMegadurum:: clone ( ) const 
{
    return new CMegadurum ( *this );
}

bool CMegadurum:: attack ( CMap& mappy, const CModel& victim ) 
{
    if ( is_dead ( ) )
        return false;
    vector < pair < TCoordinates, shared_ptr < CModel > > > neighbours = mappy . return_neighbours ( static_cast < int > ( m_Range ), m_Location );
    for ( auto v : neighbours )
    {
        if ( v . second -> type ( ) == victim . type ( ) )
        {
            m_Attack_Number++;
            if ( m_Attack_Number % ULTIMATE_FREQ == 0 )
                cout << m_Type << " " << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) uses its ultimate. It attacks twice as powerful" << endl;
            print_action ( cout, v );
            if ( v . second -> get_hit ( ( m_Attack_Number % ULTIMATE_FREQ == 0 ) ? DAM_MULTIPLIER * m_Damage : m_Damage ) )
                mappy . remove_model ( v . first );
        }
    }
    return true;
}

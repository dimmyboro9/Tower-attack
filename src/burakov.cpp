#include "burakov.h"

CBurakov:: CBurakov ( size_t attack_num )
 : CTower ( BUR_NAME, BUR_SIGN, BUR_HP, BUR_DAM, BUR_RAN )
 , m_Attack_Number ( attack_num )
{
}

CModel* CBurakov:: clone ( ) const 
{
    return new CBurakov ( *this );
}

bool CBurakov:: attack ( CMap& mappy, const CModel& victim ) 
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
                cout << m_Type << " " << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) uses its ultimate. It kills " << v . second -> name ( ) << " at position ( " << v . first . m_X << ", " << v . first . m_Y << " )" << endl;
            else
                print_action ( cout, v );
            if ( v . second -> get_hit ( ( m_Attack_Number % ULTIMATE_FREQ == 0 ) ? POWER : m_Damage ) )
                mappy . remove_model ( v . first );
        }
    }
    return true;
}

#include "patriot.h"

CPatriot:: CPatriot ( )
 : CTower ( PAT_NAME, PAT_SIGN, PAT_HP, PAT_DAM, PAT_RAN )
{
}

CModel* CPatriot:: clone ( ) const 
{
    return new CPatriot ( *this );
}

bool CPatriot:: attack ( CMap& mappy, const CModel& victim ) 
{
    if ( is_dead ( ) )
        return false;
    vector < pair < TCoordinates, shared_ptr < CModel > > > neighbours = mappy . return_neighbours ( static_cast < int > ( m_Range ), m_Location );
    for ( auto v : neighbours )
        if ( v . second -> type ( ) == victim . type ( ) )
        {
            m_Attack_Number++;
            if ( m_Attack_Number % ULTIMATE_FREQ == 0 )
            {
                cout << m_Type << " " << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) uses its ultimate. ";
                cout << "It reduces " << v . second -> name ( ) << "'s damage by half ( position ( " << v . first . m_X << ", " << v . first . m_Y << " ) )" << endl; 
                v . second -> decrease_damage ( DAM_DIVIDER );
            }
            print_action ( cout, v );
            if ( v . second -> get_hit ( m_Damage ) )
                mappy . remove_model ( v . first );
        }
    return true;
}

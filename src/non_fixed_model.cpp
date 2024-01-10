#include "non_fixed_model.h"

CNon_Fixed_Model:: CNon_Fixed_Model ( const string& name, const string& type, char sign, size_t hp, size_t damage, size_t range )
 : CModel ( name, type, sign )
 , m_Hp ( hp )
 , m_Damage ( damage )
 , m_Range ( range )
{
}        
        
bool CNon_Fixed_Model:: get_hit ( size_t damage )
{
    if ( damage < m_Hp )
        m_Hp -= damage;
    else
    {
        cout << m_Type << ' ' << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y;
        if ( m_Type == ATT_TYPE )
            cout << " ) is dead" << endl;
        else
            cout << " ) is destroyed" << endl; 
        m_Hp = 0;
        return true;
    }
    return false;
}

bool CNon_Fixed_Model:: attack ( CMap& mappy, const CModel& victim ) 
{
    if ( is_dead ( ) )
        return false;
    vector < pair < TCoordinates, shared_ptr < CModel > > > neighbours = mappy . return_neighbours ( static_cast < int > ( m_Range ), m_Location );
    for ( auto v : neighbours )
        if ( v . second -> type ( ) == victim . type ( ) )
        {
            print_action ( cout, v );
            if ( v . second -> get_hit ( m_Damage ) )
                mappy . remove_model ( v . first );
        }
    return true;
}

void CNon_Fixed_Model:: print_action ( ostream&os, const pair < TCoordinates, shared_ptr < CModel > >& victim ) const
{
    os << m_Type << " " << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) attacks " << victim . second -> type ( ) << " " << victim . second -> name ( ) << " at position ( " << victim . first . m_X << ", " << victim . first . m_Y << " )" << endl; 
}

void CNon_Fixed_Model:: add_location ( const TCoordinates& coordinates )
{
    m_Location = coordinates;
}

void CNon_Fixed_Model:: decrease_damage ( size_t divider )
{
    m_Damage = m_Damage / divider + m_Damage % divider;
}

bool CNon_Fixed_Model:: is_dead ( ) const
{
    return m_Hp == 0;
}

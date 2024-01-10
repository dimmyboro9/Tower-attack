#include "towers.h"

CTower:: CTower ( const string& name, char sign, size_t hp, size_t damage, size_t range )
 : CNon_Fixed_Model ( name, TOW_TYPE, sign, hp, damage, range )
{
} 

void CTower:: print_info ( ostream& os ) const
{
    os << m_Sign << ' ' << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ):   HP: " << m_Hp << "   DAM: " << m_Damage << "   RANGE: " << m_Range;
}


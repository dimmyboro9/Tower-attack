#include "freak.h"

CFreak:: CFreak ( )
 : CAttacker ( FRK_NAME, FRK_SIGN, FRK_HP, FRK_DAM, FRK_SPD, FRK_RAN, FRK_PRC )
{
}

CModel* CFreak:: clone ( ) const 
{
    return new CFreak ( *this );
}

bool CFreak:: get_hit ( size_t damage )
{
    if ( damage < m_Hp )
    {
        m_Hp -= damage;
        m_Hp += HEAL;
        m_Damage += POWER;
        cout << m_Type << ' ' << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) heals himself ( + 10 HP ) and increases his damage ( + 5 DAM )." << endl;
    }
    else
    {
        cout << m_Type << ' ' << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y;
        if ( m_Type == ATT_TYPE )
            cout << " ) is dead" << endl;
        else
            cout << " is destroyed" << endl; 
        m_Hp = 0;
        return true;
    }
    return false;
}

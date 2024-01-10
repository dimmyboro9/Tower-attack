#include "nagibator.h"

CNagibator:: CNagibator ( size_t attack_num )
 : CAttacker ( NAG_NAME, NAG_SIGN, NAG_HP, NAG_DAM, NAG_SPD, NAG_RAN, NAG_PRC )
 , m_Attack_Number ( attack_num )
{
}

CModel* CNagibator:: clone ( ) const 
{
    return new CNagibator ( *this );
}

bool CNagibator:: get_hit ( size_t damage )
{
    m_Attack_Number++;
    if ( m_Attack_Number % ULTIMATE_FREQ == 0 )
    {
        damage /= 2;
        cout << m_Type << " " << m_Name << " at position ( " << m_Location . m_X << ", " << m_Location . m_Y << " ) uses his ultimate. He takes half as much damage." << endl;
    }
    if ( damage < m_Hp )
        m_Hp -= damage;
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

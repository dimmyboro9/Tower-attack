#include "max.h"

CMax:: CMax ( )
 : CAttacker ( MAX_NAME, MAX_SIGN, MAX_HP, MAX_DAM, MAX_SPD, MAX_RAN, MAX_PRC )
{
}

CModel* CMax:: clone ( ) const 
{
    return new CMax ( *this );
}

bool CMax:: make_move ( CMap& mappy )
{
    if ( m_Route . size ( ) <= m_Speed )
    {
        mappy . remove_model ( m_Location );
        return true;
    }
    if ( m_Location == TCoordinates ( 0, 0 ) )
        return false;
    for ( int num_of_iter = 1; num_of_iter >= 0; num_of_iter-- )
    {
        auto next_pos = m_Route . begin ( );
        for ( int next = 0; next < num_of_iter; next++ )
            next_pos++;
        if ( mappy . is_free ( *next_pos ) )
        {
            mappy . swap_models ( m_Location, *next_pos );
            m_Location = *next_pos;
            m_Route . pop_front ( );
            if ( num_of_iter )
                m_Route . pop_front ( );
        }
    }
    return false;
}

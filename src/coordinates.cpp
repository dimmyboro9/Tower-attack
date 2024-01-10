#include "coordinates.h"

TCoordinates:: TCoordinates ( size_t x, size_t y )
 : m_X ( x ), m_Y ( y )
{
}

bool TCoordinates:: operator< ( const TCoordinates& cmp ) const 
{
    return m_Y < cmp . m_Y || ( m_Y == cmp . m_Y && m_X < cmp . m_X );
}

bool TCoordinates:: operator== ( const TCoordinates& cmp ) const 
{
    return ! ( *this < cmp || cmp < *this );
}

ostream& operator<< ( ostream& os, const TCoordinates& src )
{
    os << src . m_X << ' ' << src . m_Y;
    return os;
}

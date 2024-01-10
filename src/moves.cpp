#include "moves.h"
#include <cstddef>

void CMoves:: add_map_number ( size_t map_number )
{
    m_Map_Number = map_number;
}

void CMoves:: add_attacker ( char sign, size_t num )
{
    if ( ! m_Attackers . emplace ( sign, num ) . second )
        m_Attackers . at ( sign ) += num;
}

void CMoves:: add_game_move ( size_t game_move )
{
    m_Game_Moves . push ( game_move );
}

size_t CMoves:: get_map_number ( ) const
{
    return m_Map_Number;
}

unordered_map < char, size_t > CMoves:: get_attackers ( ) const
{
    return m_Attackers;
}

size_t CMoves:: get_game_move ( )
{
    if ( ! m_Game_Moves . size ( ) )
        return 0;
    char to_return = m_Game_Moves . front ( );
    m_Game_Moves . pop ( );
    return to_return;
}

void CMoves:: write_to_file ( ostream& file )
{
    file << m_Map_Number << endl;
    file << m_Attackers . size ( ) << endl;
    for ( auto a : m_Attackers )
        file << a . first << ' ' << a . second << endl;
    while ( m_Game_Moves . size ( ) )
    {
        file << m_Game_Moves . front ( ) << endl;
        m_Game_Moves . pop ( );
    }
}

void CMoves:: write_from_file ( istream& file )
{
    size_t num_of_att, num_of_cert_att;
    char attacker;
    int step;
    file >> m_Map_Number;
    file >> num_of_att;
    for ( size_t n = 0; n < num_of_att; n++ )
    {
        file >> attacker >> num_of_cert_att;
        m_Attackers . emplace ( attacker, num_of_cert_att );
    }
    while ( file >> step )
        m_Game_Moves . push ( step );
}

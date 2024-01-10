#include "game.h"

CGame:: CGame ( size_t score )
 : m_Score ( score )
{
}

void CGame:: show_army ( ) const
{
    for ( auto i : m_Available_Att )
        cout << i . first << ": " << i . second << endl;
}

void CGame:: make_routes ( )
{
    try 
    {
        for ( size_t i = 1; ; i++ )
            m_Routes . emplace ( i, m_Map . shortest_path ( i ) );
    }
    catch ( const exception& e )
    {
    }
}

void CGame:: start_game_text ( ) const
{
    cout << endl;
    cout << "Let's get started!" << endl;
    cout << endl;
    cout << m_Map;
    cout << endl;
}

void CGame:: enter_the_game ( )
{
    queue < size_t > entered = m_Map . enter_the_game ( );
    while ( entered . size ( ) )
    {
        m_Attackers . push_back ( m_Wait . at ( entered . front ( ) ) );
        m_Wait . erase ( entered . front ( ) );
        entered . pop ( );
    }
}

void CGame:: attack ( )
{
    cout << endl;
    for ( auto t : m_Towers )
        t -> attack ( m_Map, CViking ( ) );        
    for ( auto a = m_Attackers . begin ( ); a != m_Attackers . end ( ); )
    {
        if ( ! ( ( *a ) -> attack ( m_Map, CNeptune ( ) ) ) )
        {
            m_Attackers . erase ( a );
            continue;
        }
        a++;
    }
    for ( auto t = m_Towers . begin ( ); t != m_Towers . end ( ); )
    {
        if ( ( *t ) -> is_dead ( ) )
        {
            m_Towers . erase ( t );
            continue; 
        }
        t++;
    }
}

void CGame:: print_all_info ( ostream& os ) const
{
    size_t row = 0;
    bool is_map = true;
    while ( is_map || row < m_Attackers . size ( ) )
    {
        is_map = m_Map . print_one_row ( os, row );
        if ( row < m_Attackers . size ( ) )
        {
            cout << "      ";
            m_Attackers . at ( row ) -> print_info ( os ); 
        }
        cout << endl;
        row++;
    }
} 

void CGame:: print_tower_info ( ostream& os ) const
{
    cout << endl;
    os << "Available towers: " << m_Map . num_of_towers ( ) << endl;
    for ( auto t : m_Towers )
    {
        t -> print_info( os );
        cout << endl;
    }
    cout << endl;
}

size_t CGame:: num_of_available ( ) const
{
    size_t to_return = 0;
    for ( auto i : m_Available_Att )
        to_return += i . second;
    return to_return;
}


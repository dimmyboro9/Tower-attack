#include "record_game.h"
#include "alexandr.h"
#include "burakov.h"
#include "coordinates.h"
#include "freak.h"
#include "max.h"
#include "megadurum.h"
#include "nagibator.h"
#include "neptune.h"
#include "patriot.h"
#include "viking.h"

CRecordGame:: CRecordGame ( const CMoves& record )
{
    m_Moves = record;
}

bool CRecordGame:: choose_map ( )
{
    size_t map_number = m_Moves . get_map_number ( );
    ostringstream oss;
    oss << "./examples/maps/map" << map_number;
    m_Map . load_map ( oss . str ( ) );
    return true;
}

bool CRecordGame:: buy_units ( )
{
    unordered_map < char, size_t > attackers = m_Moves . get_attackers ( );
    for ( auto a : attackers )
        m_Available_Att . emplace ( attackers_name ( a . first ), a . second );
    return true;
}

bool CRecordGame:: play ( )
{
    char option;
    bool is_over;
    make_routes ( );
    start_game_text ( );
    while ( true )
    {
        cout << endl;
        cout << "Available attackers:" << endl;
        show_army ( );
        write_info ( "./assets/menu/record_menu" );
        cin >> option;
        if ( cin . eof ( ) )
            return false;
        if ( cin . get ( ) != '\n' )
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else if ( ! play_menu ( option, is_over ) )
            return false;
        if ( is_over )
            break;
    }
    return true;
}

string CRecordGame:: attackers_name ( char sign ) const
{
    switch ( sign )
    {
        case VIK_SIGN:
            return CViking ( ) . name ( );
        case ALEX_SIGN:
            return CAlexandr ( ) . name ( );
        case NAG_SIGN:
            return CNagibator ( ) . name ( );
        case MAX_SIGN:
            return CMax ( ) . name ( );
        case FRK_SIGN:
            return CFreak ( ) . name ( );
        default:
            throw invalid_argument ( "This attacker doesn't exist. Wrong map encoding." );
    }
}

bool CRecordGame:: play_menu ( char option, bool& is_over )
{
    switch ( option )
    {
        case CONTINUE:
            if ( simulation ( ) )
                is_over = true;
            break;
        case INFO:
            write_info ( "./assets/more_info" );
            break;
        case TOWER:
            print_tower_info ( cout );
            break;
        case RETURN:
            if ( exit ( "Do you really want to exit the record?" ) )
                return false;
            break;
        default:
            cout << "This option doesn't does not exist. Please select option again." << endl;
    }    
    return true;
}

bool CRecordGame:: simulation ( )
{
    size_t action = m_Moves . get_game_move ( );
    if ( ! action )
    {
        cout << "End of the record" << endl;
        return true;
    }
    while ( action != CONTINUE )
    {
        add_model ( action );
        action = m_Moves . get_game_move ( );
    }
    if ( ! action )
    {
        cout << "End of the record" << endl;
        return true;
    }
    if ( ! action )
    {
        cout << "End of the record" << endl;
        return true;
    }
    if ( make_move ( ) )
        return true;
    enter_the_game ( );
    attack ( );
    cout << endl;
    cout << "Score: " << m_Score << endl;
    cout << endl;
    print_all_info ( cout );
    if ( ! m_Attackers . size ( ) && ! num_of_available ( ) )
    {
        cout << "You don't have attackers anymore. You lose :(" << endl;
        return true;
    }
    return false;
}

void CRecordGame:: add_model ( size_t action )
{
    size_t x,  y;
    switch ( action )
    {
        case VIK_SIGN:
            add_att_to_map ( make_shared < CViking > ( ), m_Moves . get_game_move ( ) );
            break;
        case ALEX_SIGN:
            add_att_to_map ( make_shared < CAlexandr > ( ), m_Moves . get_game_move ( ) );
            break;
        case NAG_SIGN:
            add_att_to_map ( make_shared < CNagibator > ( ), m_Moves . get_game_move ( ) );
            break;
        case MAX_SIGN:
            add_att_to_map ( make_shared < CMax > ( ), m_Moves . get_game_move ( ) );
            break;
        case FRK_SIGN:
            add_att_to_map ( make_shared < CFreak > ( ), m_Moves . get_game_move ( ) );
            break;
        case PAT_SIGN:
            x = m_Moves . get_game_move ( );
            y = m_Moves . get_game_move ( );
            add_tower ( make_shared < CPatriot > ( ), x, y );
            break;
        case BUR_SIGN:
            x =  m_Moves . get_game_move ( );
            y = m_Moves . get_game_move ( );
            add_tower ( make_shared < CBurakov > ( ), x , y );
            break;
        case MEGA_SIGN:
            x =  m_Moves . get_game_move ( );
            y = m_Moves . get_game_move ( );
            add_tower ( make_shared < CMegadurum > ( ), x, y );
            break;
        case NEP_SIGN:
            x =  m_Moves . get_game_move ( );
            y = m_Moves . get_game_move ( );
            add_tower ( make_shared < CNeptune > ( ), x, y );
            break;
        default:
            throw invalid_argument ( "This model doesn't exist. Wrong map encoding." );
    }
}

void CRecordGame:: add_att_to_map ( const shared_ptr < CAttacker >& attacker, size_t entry )
{
    if ( m_Available_Att . find ( attacker -> name ( ) ) != m_Available_Att . end ( ) &&  m_Available_Att . at ( attacker -> name ( ) ) != 0 )
    {
        if ( m_Map . add_attacker ( attacker, entry ) )
        {
            m_Available_Att . at ( attacker -> name ( ) )--;
            m_Wait . emplace ( entry, attacker );
            attacker -> create_route ( m_Routes . at ( entry ) );
        }
    }
    else 
        throw invalid_argument ( "This attacker doesn't exist in this game. Wrong map encoding." );
}

void CRecordGame:: add_tower ( const shared_ptr < CTower >& tower, size_t x, size_t y )
{
    TCoordinates location ( x, y );
    if ( m_Map . num_of_towers ( ) )
    {
        m_Map . add_tower ( tower, location );
        m_Towers . push_back ( tower );
    }
    else 
        throw invalid_argument ( "There are no towers. Wrong map encoding." );
}

bool CRecordGame:: make_move ( )
{
    for ( auto a = m_Attackers . begin ( ); a != m_Attackers . end ( ); )
    {
        if ( ( *a ) -> make_move ( m_Map ) )
        {
            m_Attackers . erase ( a );
            m_Score++;
            if ( m_Score == 2 )
            {
                size_t action = m_Moves . get_game_move ( );
                add_model ( action );
            }
            continue;
        }
        a++;
    }
    if ( m_Score == m_Win_Score )
    {
        cout << "Congratulations!!! You won!!!";
        return true;
    }
    return false;
}

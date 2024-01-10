#include "start_game.h"
#include "clear.h"
#include "megadurum.h"
#include "neptune.h"
#include "patriot.h"
#include "burakov.h"
#include "nagibator.h"
#include "alexandr.h"
#include "viking.h"
#include "max.h"
#include "freak.h"
#include "free.h"

bool CStartGame:: choose_map ( )
{
    size_t my_map = 1;
    bool is_confirmed = false;
    cout << endl;
    cout << "Choose the map" << endl;    
    while ( true )
    {
        CMap show_map;
        text_4_cm ( show_map, my_map );
        cin >> m_Option;
        if ( cin . eof ( ) )
            return false;
        if ( cin . get ( ) != '\n' )
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else if ( ! map_menu ( my_map, is_confirmed ) )
            return false;
        if ( is_confirmed )
        {
            m_Map = show_map;
            break;
        }
    }
    cout << endl;
    cout << m_Map;
    return true;
}

bool CStartGame:: buy_units ( )
{
    bool is_ready = false;
    cout << endl;
    cout << "Buy your attacking units" << endl;
    while ( true )
    {
        text_4_by ( );
        cin >> m_Option;
        if ( cin . eof ( ) )
            return false;
        if ( cin . peek ( ) != '\n' && m_Option != BUY )
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else if ( ! purchase_menu ( is_ready ) )
            return false;
        if ( is_ready )
            break;
    }
    return true;
}

bool CStartGame:: play ( )
{
    bool is_over = false;
    add_random_towers ( );
    make_routes ( );
    start_game_text ( );
    while ( true )
    {
        cout << endl;
        cout << "Available attackers:" << endl;
        show_army ( );
        write_info ( "./assets/menu/play_menu" );
        cin >> m_Option;
        if ( cin . eof ( ) )
            return false;
        if ( cin . peek ( ) != '\n' && m_Option != ADD )
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else if ( ! play_menu ( is_over ) )
            return false;
        if ( is_over )
            break;
    }
    return true;
}

void CStartGame:: text_4_cm ( CMap& show_map, size_t my_map ) const
{
    cout << endl;
    cout << "Map " << my_map << endl;
    ostringstream oss;
    oss << "./examples/maps/map" << my_map;
    show_map . load_map ( oss . str ( ) );
    cout << show_map;
    cout << endl;
    show_map . print_map_info ( cout );
    write_info ( "./assets/menu/choose_map_menu" );
}

bool CStartGame:: map_menu ( size_t& my_map, bool& is_confirmed )
{
    switch ( m_Option )
    {
        case CONFIRM:
            is_confirmed = true;
            m_Moves . add_map_number ( my_map );
            break;
        case NEXT:
            if ( my_map == NUM_OF_MAPS )
                my_map = 1;
            else
                my_map++;
            break;
        case PREV:
            if ( my_map == 1 )
                my_map = NUM_OF_MAPS;
            else
                my_map--;
        case INFO:
            write_info ( "./assets/more_info" );
            break;
        case RETURN:
            if ( exit ( "Do you really want to return to the menu?" ) )
                return false;
            break;
        default:
            cout << "This option doesn't does not exist. Please select option again." << endl;
    }
    return true;
}

void CStartGame:: text_4_by ( ) const
{
    cout << endl;
    cout << "You have " << m_Map . show_coins ( ) << " coins" << endl;
    cout << endl;
    cout << "Your army:" << endl;
    show_army ( );
    write_info ( "./assets/menu/buy_units_menu" );
}

bool CStartGame:: purchase_menu ( bool& is_ready )
{
    switch ( m_Option )
    {
        case BUY:
            if ( ! make_transaction ( ) )
                return false;
            break;
        case START:
            if ( num_of_available ( ) < 5 )
                cout << "You can't start the game with less than five attackers. Please buy attackers." << endl;
            else 
                is_ready = true;
            break;
        case INFO:
            write_info ( "./assets/more_info" );
            break;
        case RETURN:
            if ( exit ( "Do you really want to return to the menu?" ) )
                return false;
            break;
        default:
            cout << "This option doesn't does not exist. Please select option again." << endl;
    }
    return true;
}

bool CStartGame:: make_transaction ( )
{
    char sign;
    int num;
    if ( ! ( cin >> sign >> num ) )
    {
        cin . clear ( );
        cin . ignore ( );
        clear_buffer ( );
        if ( cin . eof ( ) )
            return false;
        cout << "You wrongly entered attacker's sign or their number. Please select option again." << endl;
        return true;
    }
    if ( num <= 0 )
    {
        cout << "You can't buy less than one attacker. Please select option again." << endl;
        return true;
    }
    transaction_switch ( sign, num );
    return true;
}

void CStartGame:: transaction_switch ( char sign, int num )
{
    switch ( sign )
    {
        case VIK_SIGN:
            add_2_game ( CViking ( ), num, sign );
            break;
        case ALEX_SIGN:
            add_2_game ( CAlexandr ( ), num, sign );
            break;
        case NAG_SIGN:
            add_2_game ( CNagibator ( ), num, sign );
            break;
        case MAX_SIGN:
            add_2_game ( CMax ( ), num, sign );
            break;
        case FRK_SIGN:
            add_2_game ( CFreak ( ), num, sign );
            break;
        default:
            cout << "This attacker doesn't does not exist. Please select option again." << endl;
    }
}

void CStartGame:: add_2_game ( CAttacker && attacker, size_t num, char sign )
{
    if ( m_Map . decrease_coins ( num * attacker . show_price ( ) ) )
    {
        if ( m_Available_Att . find ( attacker . name ( ) ) == m_Available_Att . end ( ) )
            m_Available_Att . emplace ( attacker . name ( ), num );
        else
            m_Available_Att . at ( attacker . name ( ) ) += num;
        m_Moves . add_attacker ( sign, num );
    }
    else 
        cout << "Sorry, you don't have enough coins. Please select option again." << endl;
}

void CStartGame:: add_random_towers ( )
{
    for ( size_t am = 0; am < 2; am++ )
    {
        bool is_added = false;
        TCoordinates location; 
        size_t num = rand ( ) % NUM_OF_TOWERS;
        shared_ptr < CTower > tower = towers_switch ( num );
        while ( ! is_added )
            is_added = m_Map . add_random_tower ( tower, location );
        m_Towers . push_back ( tower ); 
        add_tower_2_moves ( tower -> sign ( ), location );
    }
}

shared_ptr < CTower > CStartGame:: towers_switch ( size_t num ) const
{
    switch ( num )
    {
        case 0:
            return shared_ptr < CTower > ( new CNeptune ( ) );
            break;
        case 1:
            return shared_ptr < CTower > ( new CMegadurum ( ) );
            break;
        case 2:
            return shared_ptr < CTower > ( new CPatriot ( ) );
            break;
        case 3:
            return shared_ptr < CTower > ( new CBurakov ( ) );
            break;
        default:
            throw invalid_argument ( "There is no tower with this number" );
    }
}

void CStartGame:: add_tower_2_moves ( char sign, TCoordinates location )
{
    m_Moves . add_game_move ( ( size_t ) ( unsigned char ) sign );
    m_Moves . add_game_move ( location . m_X );
    m_Moves . add_game_move ( location . m_Y );
}

bool CStartGame:: play_menu ( bool& is_over )
{
    string char_2_str;
    switch ( m_Option )
    {
        case ADD:
            if ( ! choose_unit ( ) )
                return false;
            break;
        case CONTINUE:
            m_Moves . add_game_move ( CONTINUE );
            if ( simulation ( ) )
                is_over = true;
            break;
        case TOWER:
            print_tower_info ( cout );
            break;
        case INFO:
            write_info ( "./assets/more_info" );
            break;
        case RETURN:
            if ( exit ( "Do you really want to return to the menu?" ) )
            {
                if ( exit ( "Do you want to save game process?" ) )
                    save_game ( );
                return false;
            }
            break;
        default:
            cout << "This option doesn't does not exist. Please select option again." << endl;
    }    
    return true;
}

bool CStartGame:: choose_unit ( )
{
    char sign;
    size_t entry;
    if ( ! ( cin >> sign >> entry ) )
    {
        cin . clear ( );
        cin . ignore ( );
        clear_buffer ( );
        if ( cin . eof ( ) )
            return false;
        cout << "You wrongly entered attacker's sign or entrance number. Please select option again." << endl;
        return true;
    }
    unit_switch ( sign, entry );
    return true;
}

void CStartGame:: unit_switch ( char sign, size_t entry )
{
    switch ( sign )
    {
        case VIK_SIGN:
            add_att_to_map ( make_shared < CViking > ( ), entry, sign );
            break;
        case ALEX_SIGN:
            add_att_to_map ( make_shared < CAlexandr > ( ), entry, sign );
            break;
        case NAG_SIGN:
            add_att_to_map ( make_shared < CNagibator > ( ), entry, sign );
            break;
        case MAX_SIGN:
            add_att_to_map ( make_shared < CMax > ( ), entry, sign );
            break;
        case FRK_SIGN:
            add_att_to_map ( make_shared < CFreak > ( ), entry, sign );
            break;
        default:
            cout << "This attacker doesn't does not exist. Please select option again." << endl;
    }
}

void CStartGame:: add_att_to_map ( const shared_ptr < CAttacker >& attacker, size_t entry, char sign )
{
    if ( m_Available_Att . find ( attacker -> name ( ) ) != m_Available_Att . end ( ) &&  m_Available_Att . at ( attacker -> name ( ) ) != 0 )
    {
        if ( m_Map . add_attacker ( attacker, entry ) )
        {
            m_Available_Att . at ( attacker -> name ( ) )--;
            m_Wait . emplace ( entry, attacker );
            attacker -> create_route ( m_Routes . at ( entry ) );
            m_Moves . add_game_move ( ( size_t ) ( unsigned char ) sign  );
            m_Moves . add_game_move ( entry );
        }
    }
    else 
        cout << "You don't have this type of attacker." << endl;
}

bool CStartGame:: simulation ( )
{
    if ( m_Map . num_of_towers() && ( m_Towers . size ( ) * TOW_TO_ATT <= m_Attackers . size ( ) || ( m_Score >= m_Win_Score - 1 && m_Attackers . size ( ) ) ) )
        add_towers ( );
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
        if ( exit ( "Do you want to save game process?" ) )
            save_game ( );
        return true;
    }
    return false;
}

void CStartGame:: add_towers ( )
{
    pair < string, string > most_attack = analyze_attack ( );
    size_t route = rand ( ) % m_Routes . size ( ) + 1;
    size_t pos = m_Routes . at ( route ) . size ( ) * ( double ( m_Score ) * 0.1 + 0.5 ) - rand ( ) % ( m_Routes . at ( route ) . size ( ) / PLACE_RADIUS );
    auto iter = m_Routes . at ( route ) . begin ( );
    for ( size_t p = 0; p < pos; p++ )
        iter++;
    if ( ( ( most_attack . first == CNagibator ( ) . name ( ) || most_attack . first == CAlexandr ( ) . name ( ) ) 
    && ( most_attack . second == CNagibator ( ) . name ( ) || most_attack . second == CAlexandr ( ) . name ( ) ) ) || m_Score >= m_Win_Score - 2 )
        nag_alex_defense ( iter );
    else if ( most_attack . first == CMax ( ) . name ( ) || most_attack . second == CMax ( ) . name ( ) )
        max_defense ( );
    else if ( most_attack . first == CViking ( ) . name ( ) || most_attack . first == CFreak ( ) . name ( ) || most_attack . first == CNagibator ( ) . name ( ) )
        def_with_patriot ( iter );
    else 
        classic_defense ( iter );
}

pair < string, string > CStartGame:: analyze_attack ( ) const
{
    unordered_map < string, size_t > attackers;
    for ( auto a : m_Attackers )
    {
        if ( attackers . find ( a -> name ( ) ) == attackers . end ( ) )
            attackers . emplace ( a -> name ( ), 1 );
        else 
            attackers . at ( a -> name ( ) )++;
    }
    string first = find_max ( attackers );
    attackers . erase ( first );
    string second = find_max ( attackers );
    return make_pair ( first, second );
}

string CStartGame:: find_max ( const unordered_map < string, size_t >& attackers ) const
{
    if ( attackers . begin ( ) == attackers . end ( ) )
        return "";
    string max = ( *attackers . begin ( ) ) . first;
    for ( auto a : attackers )
        if ( a . second > attackers . at ( max ) )
            max = a . first;
    return max;
}

void CStartGame:: nag_alex_defense ( list < TCoordinates >::iterator iter )
{
    shared_ptr < CTower > tower;
    size_t number_of_tower = 0;
    while ( number_of_tower < NAG_ALEX_DEF )
    {
        if ( m_Map . num_of_towers ( ) )
        {
            if ( m_Map . is_free ( *iter ) )
            {
                if ( ! number_of_tower )
                    tower = shared_ptr < CTower > ( new CMegadurum ( ) );
                else if ( number_of_tower == 1 )
                    tower = shared_ptr < CTower > ( new CNeptune ( ) );
                else
                    tower = shared_ptr < CTower > ( new CBurakov ( ) );
                m_Map . add_tower ( tower, *iter );
                m_Towers . push_back ( tower );
                add_tower_2_moves ( tower -> sign ( ), *iter );
                number_of_tower++;
            }
            if ( m_Score > 2 )
                iter--;
            else
                iter++;
        }
        else
            return;
    }
}

void CStartGame:: max_defense ( )
{
    size_t number_of_tower = 0;
    size_t route = rand ( ) % m_Routes . size ( ) + 1;
    size_t pos = m_Routes . at ( route ) . size ( ) * 0.9 - rand ( ) % ( m_Routes . at ( route ) . size ( ) / PLACE_RADIUS );
    auto iter = m_Routes . at ( route ) . begin ( );
    for ( size_t p = 0; p < pos; p++ )
            iter++;
    while ( number_of_tower < MAX_DEF )
    {
        if ( m_Map . num_of_towers ( ) )
        {
            if ( m_Map . is_free ( *iter ) )
            {
                size_t num = rand ( ) % NUM_OF_TOWERS;
                shared_ptr < CTower > tower = towers_switch ( num );
                m_Map . add_tower ( tower, *iter );
                m_Towers . push_back ( tower );
                add_tower_2_moves ( tower -> sign ( ), *iter );
                number_of_tower++;
            }
            iter--;
        }
        else
            return;
    }    
}

void CStartGame:: def_with_patriot ( list < TCoordinates >::iterator iter )
{
    shared_ptr < CTower > tower;
    TCoordinates location;
    size_t number_of_tower = 0;
    while ( number_of_tower < DEF_WITH_PATRIOT )
    {
        if ( m_Map . num_of_towers ( ) )
        {
            if ( ! number_of_tower )
            {
                size_t num = rand ( ) % NUM_OF_TOWERS;
                tower = towers_switch ( num );
                while ( ! m_Map . is_free ( *iter ) )
                    iter++;
                location = *iter;
            }    
            else
            {
                vector < pair < TCoordinates, shared_ptr < CModel > > > neighbours = m_Map . return_neighbours ( 1, location );
                for ( auto n : neighbours )
                    if ( n . second -> name ( ) == CFree ( ) . name ( ) )
                    {
                        location = n . first;
                        break;
                    }
                tower = shared_ptr < CTower > ( new CPatriot ( ) );
            }
            m_Map . add_tower ( tower, location );
            m_Towers . push_back ( tower );
            add_tower_2_moves ( tower -> sign ( ), location );
            number_of_tower++;
        }
        else
            return;
    }
}

void CStartGame:: classic_defense ( list < TCoordinates >::iterator iter )
{
    size_t num = rand ( ) % NUM_OF_TOWERS;
    shared_ptr < CTower > tower = towers_switch ( num );
    while ( ! m_Map . is_free ( *iter ) )
        iter++;
    m_Map . add_tower ( tower, *iter );
    m_Towers . push_back ( tower );
    add_tower_2_moves ( tower -> sign ( ), *iter );
}

bool CStartGame:: make_move ( )
{
    for ( auto a = m_Attackers . begin ( ); a != m_Attackers . end ( ); )
    {
        if ( ( *a ) -> make_move ( m_Map ) )
        {
            m_Attackers . erase ( a );
            m_Score++;
            if ( m_Score == 2 )
                add_towers ( );
            continue;
        }
        a++;
    }
    if ( m_Score == m_Win_Score )
    {
        cout << "Congratulations!!! You won!!!";
        if ( exit ( "Do you want to save game process?" ) )
            save_game ( );
        return true;
    }
    return false;
}

void CStartGame:: save_game ( )
{
    cout << "Please enter the name of the file:" << endl;
    string file_name;
    cin >> file_name;
    if ( cin . eof ( ) )
        return;
    ostringstream oss;
    oss << "./examples/records/" << file_name;
    fstream save ( oss . str ( ), ios::out );
    if ( save . fail ( ) )
        throw invalid_argument ( "File did not open." );
    m_Moves . write_to_file ( save );
    save_game_name ( file_name );
}

void CStartGame:: save_game_name ( const string& name ) const
{
    fstream rec_names ( "./examples/records_names", ios::out | ios::app );
    if ( rec_names . fail ( ) )
        throw invalid_argument ( "File did not open." );
    rec_names << name << endl;
}

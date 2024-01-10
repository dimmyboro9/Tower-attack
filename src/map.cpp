#include "viking.h"
#include "constants.h"
#include "exit.h"
#include "map.h"
#include "coordinates.h"
#include "entrance.h"
#include "free.h"
#include "neptune.h"
#include "wall.h"
#include <stdexcept>

CMap:: CMap ( size_t len, size_t wid, size_t coins, size_t num )
 : m_Length ( len )
 , m_Width ( wid )
 , m_Coins ( coins )
 , m_Num_Of_Towers ( num )
{
    if ( m_Length < m_Width )
        throw invalid_argument ( "The length of the map is less than the width. This map cannot be created" );
    if ( m_Num_Of_Towers < MIN_TOWERS )
        throw invalid_argument ( "Number of towers must be at least 2. This map cannot be created" );
    generate_map ( );
}

void CMap:: add_fixed_model ( const CModel& model, const TCoordinates& coordinates )
{
    if ( model . name ( ) == CEntrance ( ) . name ( ) )
    {
        if ( coordinates . m_X != m_Length - 1 || coordinates . m_Y >= m_Width - 1
            || coordinates . m_Y < 1 )
            throw invalid_argument ( "Map entrance cannot exist at this location" );
        m_Entrances . emplace ( model . get_num ( ), make_pair ( coordinates, nullptr ) );
    } 
    else if ( model . name ( ) == CExit ( ) . name ( ) )
    {
        if ( coordinates . m_X != 0 || coordinates . m_Y >= m_Width - 1
            || coordinates . m_Y < 1 )
            throw invalid_argument ( "Map exit cannot exist at this location" );
        m_Exit = coordinates;
    }
    else if ( coordinates . m_X >= m_Length - 1 || coordinates . m_Y >= m_Width - 1
        || coordinates . m_X < 1 || coordinates . m_Y < 1 || near_entry_exit ( coordinates ) )
    {
        ostringstream oss;
        oss << "Map " << model . name ( ) << " cannot exist at this location";
        throw invalid_argument ( oss . str ( ) );
    }
    else if ( ! ( model . type ( ) == CExit ( ) . type ( ) ) )
        throw invalid_argument ( "You can't add attacker or tower in this way" );
    m_Models . at ( coordinates ) = shared_ptr < CModel > ( model . clone ( ) ) ;
}

bool CMap:: add_attacker ( const shared_ptr < CModel >& attacker, size_t entry )
{
    auto it = m_Entrances . find ( entry );
    if ( it == m_Entrances . end ( ) )
    {
        cout << "This entrance doesn't exist." << endl;
        return false;
    }   
    if ( it -> second . second . get ( ) )
    {
        cout << "This entrance is already taken." << endl;
        return false;
    }
    it -> second . second = attacker;
    attacker -> add_location ( TCoordinates ( 0, 0 ) );
    return true;
}

void CMap:: add_tower ( const shared_ptr < CModel >& tower, TCoordinates& location )
{
    if ( location . m_X < 1 || location . m_X > m_Length - 1 
      || location . m_Y < 1 || location . m_Y > m_Width - 1 || near_entry_exit ( location ) 
      || ! is_free ( location ) )
        throw invalid_argument ( "Map tower cannot exist at this location" );
    m_Models . at ( location ) = tower;
    m_Models . at ( location ) -> add_location ( location );
    m_Num_Of_Towers--;
}

bool CMap:: add_random_tower ( const shared_ptr < CModel >& tower, TCoordinates& location )
{
    location . m_X = rand ( ) % m_Length - 1;
    location . m_Y = rand ( ) % m_Width - 1;
    if ( location . m_X <= 1 || location . m_X >= m_Length - 1 
      || location . m_Y <= 1 || location . m_Y >= m_Width - 1 || near_entry_exit ( location ) 
      || ! is_free ( location ) )
        return false;
    m_Models . at ( location ) = tower;
    m_Models . at ( location ) -> add_location ( location );
    m_Num_Of_Towers--;
    return true;
}

void CMap:: remove_model ( const TCoordinates& location )
{
    if ( location . m_X < 1 || location . m_X > m_Length - 1 
      || location . m_Y < 1 || location . m_Y > m_Width - 1 )
        throw invalid_argument ( "You can't remove model from this location." );
    m_Models . at ( location ) = shared_ptr < CModel > ( CFree ( ) . clone ( ) );
}

void CMap:: swap_models ( const TCoordinates& from, const TCoordinates& to )
{
    shared_ptr < CModel > tmp = m_Models . at ( from );
    m_Models . at ( from ) = m_Models . at ( to );
    m_Models . at ( to ) = tmp;
}


queue < size_t > CMap:: enter_the_game ( )
{
    queue < size_t > entered;
    for ( auto e: m_Entrances )
    {
        TCoordinates location = e . second . first;
        location . m_X--;
        if ( is_free ( location ) && e . second . second . get ( ) )
        {
            m_Models . at ( location ) = e . second . second;
            m_Models . at ( location ) -> add_location ( location );
            m_Entrances . at ( e . first ) . second = nullptr;
            entered . push ( e . first );
        }
    } 
    return entered;
}

void CMap:: save_map ( const string& file ) const
{
    fstream save ( file, ios::out );
    if ( save . fail ( ) )
        throw invalid_argument ( "File did not open." );
    save << m_Length << ' ' << m_Width << ' ' << m_Coins << ' ' << m_Num_Of_Towers << endl;
    for ( size_t w = 1; w < m_Width - 1; w++ )
        for ( size_t l = 0; l < m_Length; l++ )
        {
            TCoordinates coord ( l, w );
            if ( ! is_free ( coord ) 
                && ( m_Models . at ( coord ) -> name ( ) != CWall ( ) . name ( ) 
                || ( l != m_Length - 1  && l != 0 ) ) )
            {
                save << m_Models . at ( coord );
                save << ' ' << coord << endl;            
            }
        }
    save . close ( );
}

void CMap:: load_map ( const string& file )
{
    fstream load ( file, ios::in );
    if ( load . fail ( ) )
        throw invalid_argument ( "File did not open." );
    load >> m_Length;
    load >> m_Width;
    load >> m_Coins;
    load >> m_Num_Of_Towers;
    if ( m_Length < m_Width )
        throw invalid_argument ( "The length of the map is less than the width. Wrong map encoding." );
    if ( m_Num_Of_Towers < MIN_TOWERS )
        throw invalid_argument ( "Number of towers must be at least 2. Wrong map encoding" );
    generate_map ( );
    update_map ( load );
    load . close ( );
}

size_t CMap:: show_coins ( ) const
{
    return m_Coins;
}

size_t CMap:: num_of_towers ( ) const
{
    return m_Num_Of_Towers;
}

bool CMap:: decrease_coins ( size_t diff )
{
    if ( diff > m_Coins )
        return false;
    else
        m_Coins -= diff;
    return true;
}

bool CMap:: is_free ( const TCoordinates& coordinates ) const
{
    return m_Models . at ( coordinates ) -> name ( ) == CFree ( ) . name ( );
}

vector < pair < TCoordinates, shared_ptr < CModel > > > CMap:: return_neighbours ( int range, const TCoordinates& pos ) const
{
    vector < pair < TCoordinates, shared_ptr < CModel > > > neighbours;
    for ( int x = -range; x <= range; x++ )
        for ( int y = -range; y <= range; y++ )
        {
            if ( x + static_cast < int > ( pos . m_X ) < 1 || x + static_cast < int > ( pos . m_X ) > static_cast < int > ( m_Length ) - 1 || y + static_cast < int > ( pos . m_Y ) < 1 || y + static_cast < int > ( pos . m_Y ) > static_cast < int > ( m_Width ) - 1 )
                continue;
            neighbours . emplace_back ( TCoordinates ( x + pos . m_X, y + pos . m_Y ), m_Models . at ( TCoordinates ( x + pos . m_X, y + pos . m_Y ) ) );
        }   
    return neighbours;
}

list < TCoordinates > CMap:: shortest_path ( size_t entry ) const
{
    auto it = m_Entrances . find ( entry );
    if ( it == m_Entrances . end ( ) )
        throw invalid_argument ( "This entrance doesn't exist" );
    TCoordinates start = it -> second . first;
    start . m_X--;
    function < size_t ( const TCoordinates& ) > coord_hash = [ wid = m_Width ] 
        ( const TCoordinates& x ) -> size_t 
        { return x . m_X * wid + x . m_Y; };
    queue < TCoordinates > to_visit;
    unordered_map < TCoordinates, TCoordinates, function < size_t ( const TCoordinates& ) > > is_visit ( m_Length * m_Width, coord_hash );
    to_visit . push ( start );
    is_visit . emplace ( start, TCoordinates ( ) );
    while_in_bfs ( to_visit, is_visit ); 
    return write_path ( is_visit, start, m_Exit );
}

void CMap:: print_map ( ostream &os ) const 
{
    for ( auto model : m_Models )
    {
        os << *model . second;
        if ( model . first . m_X == m_Length - 1 )
            os << endl;
    }
}

bool CMap:: print_one_row ( ostream& os, size_t row ) const 
{
    if ( row >= m_Width )
    {
        for ( size_t l = 0; l < m_Length; l++ )
            os << char ( FREE_SIGN );
        return false;    
    }
    for ( size_t l = 0; l < m_Length; l++ )
        os << *m_Models . at ( TCoordinates ( l , row ) );
    if ( row == m_Width - 1 )
        return false;
    return true;
}

void CMap:: print_map_info ( ostream &os ) const
{
    os << "You have " << m_Coins << " coins on this map to buy attackers" << endl;
    os << "Computer can use " << m_Num_Of_Towers << " more towers" << endl;
}

ostream& operator << ( ostream& os, const CMap& src ) 
{
    src . print_map ( os );
    return os;
}

void CMap:: generate_map ( )
{
    for ( size_t w = 0; w < m_Width; w++ )
    {
        m_Models . emplace ( TCoordinates ( 0, w ), CWall ( ) . clone ( ) );
        for ( size_t l = 1; l < m_Length - 1; l++ )
        {
            if ( w == 0 || w == m_Width - 1 )
                m_Models . emplace ( TCoordinates ( l, w ), CWall ( ) . clone ( ) );
            else
                m_Models . emplace ( TCoordinates ( l, w ), CFree ( ) . clone ( ) );
        }
        m_Models . emplace ( TCoordinates ( m_Length - 1, w ), CWall ( ) . clone ( ) );
    }
} 

void CMap:: update_map ( istream& is )
{
    char sign;
    size_t x, y;
    while ( is >> sign )
    {
        switch ( sign )
        {
            case WALL_SIGN:
                is >> x >> y;
                add_fixed_model( CWall ( ),TCoordinates ( x, y ) );
                break;
            case EXIT_SIGN:
                if ( is . get ( ) == '=' )
                {
                    size_t entry;
                    is >> entry;
                    is >> x >> y;
                    add_fixed_model ( CEntrance ( entry ), TCoordinates ( x, y ) );
                }
                else
                {
                    is >> x >> y; 
                    add_fixed_model ( CExit ( ), TCoordinates ( x, y ) );
                }
                break;
            default:
                throw invalid_argument ( "Wrong map encoding." );
        }
    }
}

bool CMap:: near_entry_exit ( const TCoordinates& coordinates )
{
    TCoordinates cmp;
    for ( auto i : m_Entrances )
    {
        cmp = i . second . first; 
        cmp . m_X--;
        if ( coordinates == cmp )
            return true;
    }
    cmp = m_Exit;
    cmp . m_X++;
    if ( coordinates == cmp )
        return true;
    return false;
}

void CMap:: while_in_bfs ( queue < TCoordinates >& to_visit, unordered_map < TCoordinates, TCoordinates, function < size_t ( const TCoordinates& ) > >& is_visit ) const
{
    while ( to_visit . size ( ) && is_visit . find ( m_Exit ) == is_visit . end ( ) )
    {
        TCoordinates curr = to_visit . front ( );
        list < TCoordinates > neighbours;
        neighbours . push_back ( TCoordinates ( curr . m_X, curr . m_Y - 1 ) );
        neighbours . push_back ( TCoordinates ( curr . m_X - 1, curr . m_Y ) );
        neighbours . push_back ( TCoordinates ( curr . m_X, curr . m_Y + 1 ) );
        for ( auto i : neighbours )
        {
            if ( m_Models . at ( i ) -> name ( ) == CExit ( ) . name ( ) )
            {
                is_visit . emplace ( i, curr );
                break;
            }
            if ( m_Models . at ( i ) -> name ( ) != CWall ( ) . name ( ) )
            {
                if ( is_visit . emplace ( i, curr ) . second )
                    to_visit . push ( i );
            }
        }
        to_visit . pop ( );
    }
}

list < TCoordinates > CMap:: write_path ( const unordered_map < TCoordinates, TCoordinates, function < size_t ( const TCoordinates& ) > >& is_visit, const TCoordinates& start, const TCoordinates& exit ) const
{
    list < TCoordinates > res;
    TCoordinates curr = exit;
    while ( ! ( curr == start ) ) 
    {
        res . push_front ( curr );
        curr = is_visit . at ( curr );
    }
    return res;
}


#include "run.h"
#include "clear.h"
#include "moves.h"
#include "start_game.h"
#include "record_game.h"
#include <fstream>

void CRun:: run_programm ( )
{
    write_info ( "./assets/welcome" );
    cout << endl;
    cout << "Select option." << endl;
    write_info ( "./assets/menu/main_menu" );
    choose_option ( );
}

void CRun:: choose_option ( )
{
    while ( cin >> m_Option )
    {
        if ( cin . get ( ) != '\n' )
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else if ( ! menu ( ) )
        {
            if ( exit ( "Do you really want to exit the game?" ) )
                break;
        }
        if ( ! ( cin . eof ( ) ) )
            write_info ( "./assets/menu/main_menu" );
    }
}

bool CRun:: menu ( )
{
    CMoves record;
    switch ( m_Option )
    {
        case START:
            m_Game = make_unique < CStartGame > ( );
            if ( ! run_game ( ) )
                return true;
            break;
        case RECORD:
            if ( ! choose_file ( record ) )
                return true;
            m_Game = make_unique < CRecordGame> ( record );
            if ( ! run_game ( ) )
                return true;
            break;
        case INFO:
            write_info ( "./assets/more_info" );
            break;
        case EXIT:
            return false;
            break;
        default:
            cout << "This option doesn't does not exist. Please select option again." << endl;
    }
    return true;
}

bool CRun:: choose_file ( CMoves& record )
{
    cout << "Which replay do you want to watch?" << endl;
    cout << endl;
    fstream rec_names ( "./examples/records_names", ios::in );
    if ( rec_names . fail ( ) )
        throw invalid_argument ( "File was not opened." );
    size_t number_of_records = 0;
    string name;
    while ( rec_names >> name )
    {
        cout << name << endl;
        number_of_records++;
    }
    rec_names . close ( );
    if ( ! number_of_records )
    {
        cout << "There is no records." << endl;
        return false;
    }
    cout << endl;
    enter_name ( record );
    return true;
}

void CRun:: enter_name ( CMoves& record )
{
    string name;
    while ( cin >> name )
    {
        if ( cin . eof ( ) )
            return;
        ostringstream oss;
        oss << "./examples/records/" << name;
        fstream record_file ( oss . str ( ), ios::in );
        if ( record_file . fail ( ) )
        {
            cout << "This file doesn't exist" << endl;
            clear_buffer ( );
            continue;
        }
        record . write_from_file ( record_file );
        record_file . close ( );
        break;
    }
}

bool CRun:: run_game ( ) const
{
    if ( ! ( m_Game -> choose_map ( ) ) || ! ( m_Game -> buy_units ( ) ) || ! ( m_Game -> play ( ) ) )
        return false;
    return true;
} 

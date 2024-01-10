#include "exit_game.h"

void write_text ( const string& question )
{
    cout << endl;
    cout << question << endl;
    cout << "y - Yes" << endl;
    cout << "n - No" << endl;
}

bool exit ( const string& question )
{
    char option;
    while ( true )
    {
        write_text ( question );
        cin >> option;
        if ( cin . get ( ) != '\n' )        
        {
            clear_buffer ( );
            cout << "This option doesn't does not exist. Please select option again." << endl;
        }
        else
        {
            switch ( option )
            {
                case YES:
                    return true;
                    break;
                case NO:
                    return false;
                    break;
                default:
                    cout << "This option doesn't does not exist. Please select option again." << endl;
            }
        }
    }
}


#include "run.h"

int main ( void )
{
    srand ( time ( nullptr ) );
    try
    { 
        CRun programm;
        programm . run_programm ( );        
    }
    catch ( const invalid_argument& e )
    {
        cout << e . what ( ) << endl;
    }

    return 0;
}

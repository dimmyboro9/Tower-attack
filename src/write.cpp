#include "write.h"

void write_info ( const string& file )
{
    fstream info ( file, ios::in );
    if ( info . fail ( ) )
        throw invalid_argument ( "File did not open." );
    string to_write;
    while ( getline ( info, to_write ) )
        cout << to_write << endl;
    info . close ( );
}

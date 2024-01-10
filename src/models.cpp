#include "models.h"
#include "coordinates.h"

ostream& operator<< ( ostream& os, const CModel& src )
{
    src . print ( os );
    return os;
}

CModel:: CModel ( const string& name, const string& type, char sign )
 : m_Name ( move ( name ) )
 , m_Type ( move ( type ) )
 , m_Sign ( sign )
{
}

void CModel:: print ( ostream& os ) const
{
    os << m_Sign;
}

string CModel:: name ( ) const
{
    return m_Name;
}

char CModel:: sign ( ) const
{
    return m_Sign;
}

string CModel:: type ( ) const
{
    return m_Type;
}

size_t CModel:: get_num ( ) const
{
    throw invalid_argument ( "Cannot use method get_num () on a non-CEntrance class" );
}

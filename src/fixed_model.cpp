#include "fixed_model.h"

CFixed_Model:: CFixed_Model ( const string& name, char sign )
 : CModel ( name, FIX_TYPE, sign )
{
}

bool CFixed_Model:: get_hit ( size_t damage )
{
    throw invalid_argument ( "Cannot use method get_hit () for fixed models" );
}

bool CFixed_Model:: attack ( CMap& mappy, const CModel& victim )
{
    throw invalid_argument ( "Cannot use method attack () for fixed models" );
}

void CFixed_Model:: add_location ( const TCoordinates& coordinates )
{
    throw invalid_argument ( "Cannot use method add_location () for fixed models" );
}


bool CFixed_Model:: is_dead ( ) const
{
    throw invalid_argument ( "Cannot use method is_dead () for fixed models" );
}

void CFixed_Model:: decrease_damage ( size_t divider )
{
    throw invalid_argument ( "Cannot use method decrease_damage () for fixed models" );
}


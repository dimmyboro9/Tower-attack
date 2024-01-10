#ifndef EXIT_HPP
#define EXIT_HPP
#include "fixed_model.h"

/**
 * \brief Class that represents exit on the map
 */

class CExit : public CFixed_Model
{
    public:
                    CExit           ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*     clone           ( ) const override;
         
    private:
};

#endif

#ifndef FREE_HPP
#define FREE_HPP
#include "fixed_model.h"

/**
 * \brief Class that represents free on the map
 */

class CFree : public CFixed_Model
{
    public:
                        CFree           ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*         clone           ( ) const override;
};

#endif

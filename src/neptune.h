#ifndef NEPTUNE_HPP
#define NEPTUNE_HPP
#include "towers.h"

/**
 * \brief Class that represents one type of tower
 *
 */

class CNeptune : public CTower
{
    public:
                                CNeptune        ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;
         
    private:
        enum Stats : size_t
        {
            NEP_HP = 400,
            NEP_DAM = 40,
            NEP_RAN = 2
        };

};

#endif

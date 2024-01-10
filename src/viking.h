#ifndef VIKING_HPP
#define VIKING_HPP
#include "attackers.h"

/**
 * \brief Class that represents one type of attacking player
 *
 */

class CViking : public CAttacker
{
    public:
                                CViking         ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;
         
    private:
        enum Stats : size_t
        {
            VIK_HP = 300,
            VIK_DAM = 20,
            VIK_SPD = 1,
            VIK_RAN = 1,
            VIK_PRC = 20
        };        
};

#endif

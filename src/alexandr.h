#ifndef ALEXANDR_HPP
#define ALEXANDR_HPP
#include "attackers.h"

/**
 * \brief Class that represents one type of attacking player
 */

class CAlexandr : public CAttacker
{
    public:
                                CAlexandr       ( );
    /**
     * \brief That method makes a copy of model
     * 
     * \return Pointer on class CModel
     */
        CModel*                 clone           ( ) const override;
    private:
        enum Stats : size_t
        {
            ALEX_HP = 150,
            ALEX_DAM = 15,
            ALEX_SPD = 1,
            ALEX_RAN = 2,
            ALEX_PRC = 10
        };        
};

#endif
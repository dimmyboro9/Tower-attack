#ifndef FREAK_HPP
#define FREAK_HPP
#include "attackers.h"

/**
 * \brief Class that represents one type of attacking player
 */

class CFreak : public CAttacker
{
    public:
                                CFreak          ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;

        /**
         * \brief That method implements taking damage in a special way
         *
         * \details If this attacker get hit, he increases his damage by 5 points and heals himself by 10 points 
         * 
         * \param[in] damage The amount of damage the model receives
         *
         * \return The boolean value
         *
         * \retval return TRUE if victim has more than 0 HP
         * \retval return FALSE if victim has 0 HP
         */
        bool                    get_hit         ( size_t damage ) override;

    private:
        enum Stats : size_t
        {
            FRK_HP = 250,
            FRK_DAM = 0,
            FRK_SPD = 1,
            FRK_RAN = 1,
            FRK_PRC = 30,
        };
        const static size_t     HEAL = 10;
        const static size_t     POWER = 5;
};

#endif

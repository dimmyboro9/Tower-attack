#ifndef MAX_HPP
#define MAX_HPP
#include "attackers.h"

/**
 * \brief Class that represents one type of attacking player
 *
 */

class CMax : public CAttacker
{
    public:
                                CMax            ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;
         
        /**
         * \brief Method that moves attackers
         *
         * \details This attacker has bigger speed, so he has virtual method make_move
         * 
         * \param[in] mappy map, on which attacker moves
         *
         * \return The boolean value
         *
         * \retval return FALSE if attacker didn't reach the exit
         * \retval return TRUE if attacker reached the exit
         */
        bool                    make_move       ( CMap& mappy ) override;

    private:
        enum Stats : size_t
        {
            MAX_HP = 200,
            MAX_DAM = 10,
            MAX_SPD = 2,
            MAX_RAN = 1,
            MAX_PRC = 30
        };
};

#endif

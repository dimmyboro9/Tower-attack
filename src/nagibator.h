#ifndef NAGIBATOR_HPP
#define NAGIBATOR_HPP
#include "attackers.h"

/**
 * \brief Class that represents one type of attacking player
 *
 * \details It has:
 *          m_Attack_Number - number of attacks perfomed by tower
 */

class CNagibator : public CAttacker
{
    public:
                                CNagibator      ( size_t attack_num = 0 );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;
         
        /**
         * \brief That method implements taking damage in a special way
         *
         * \details With some frequence he gets less damage than usual 
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
        size_t                  m_Attack_Number;
        enum Stats : size_t
        {
            NAG_HP = 500,
            NAG_DAM = 50,
            NAG_SPD = 1,
            NAG_RAN = 1,
            NAG_PRC = 50
        };
        const static size_t     DAM_DIVIDER = 2;
        const static size_t     ULTIMATE_FREQ = 3;
};

#endif

#ifndef PATRIOT_HPP
#define PATRIOT_HPP
#include "towers.h"

/**
 * \brief Class that represents one type of tower
 *
 * \details It has:
 *          m_Attack_Number - number of attacks perfomed by tower
 */

class CPatriot : public CTower
{
    public:
                                CPatriot        ( );
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        CModel*                 clone           ( ) const override;
         
        /**
         * \brief That method implements attack in a special way
         * 
         * \details With some frequence it can reduce attacker's damage
         *
         * \param[in] mappy map on which model is located to find all his neighbours
         * \param[in] victim type of victim, that it attacks
         *
         * \return The boolean value
         *
         * \retval return TRUE if model has more than 0 HP
         * \retval return FALSE if model has 0 HP
         */
        bool                    attack          ( CMap& mappy, const CModel& victim ) override;
    
    private:
        size_t                  m_Attack_Number;
        enum Stats : size_t
        {
            PAT_HP = 350,
            PAT_DAM = 30,
            PAT_RAN = 2
        };
        const static size_t     DAM_DIVIDER = 2;
        const static size_t     ULTIMATE_FREQ = 4;

};

#endif

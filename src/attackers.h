#ifndef ATTACKERS_HPP
#define ATTACKERS_HPP
#include <list>
#include "map.h"
#include "non_fixed_model.h"

/**
 * \brief Class that represents all attackers on the map
 *
 * \details It has:
 *          m_Speed - number of cells that attacker moves to
 *          m_Price - attacker's price
 *          m_Route - attacker's route to the exit
 */

class CAttacker : public CNon_Fixed_Model
{
    public:
                                CAttacker       ( const string& name, char sign, size_t hp, size_t damage, size_t speed, size_t range, size_t price );
        virtual                 ~CAttacker      ( ) noexcept = default;
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        virtual CModel*         clone           ( ) const override = 0;

        /**
         * \brief Method that adds to attacker his route
         *
         * \param[in] route the path that attacker takes
         */
        virtual void            create_route    ( list < TCoordinates > route );

        /**
         * \brief Method that moves attackers
         * 
         * \param[in] mappy map, on which attacker moves
         *
         * \return The boolean value
         *
         * \retval return FALSE if attacker didn't reach the exit
         * \retval return TRUE if attacker reached the exit
         */
        virtual bool            make_move       ( CMap& mappy );

        /**
         * \brief Method that shows attacker's price
         *
         * \retval The size_t value - attacker's price
         */
        size_t                  show_price      ( ) const;

        /**
         * \brief Method that prints all model's stats
         *
         * \param[in] os Stream, where will be sign printed
         */
        void                    print_info      ( ostream& os ) const override;

    protected:
        const size_t            m_Speed;
        size_t                  m_Price;           
        list < TCoordinates >   m_Route;
};

#endif

#ifndef NON_FIXED_MODEL_HPP
#define NON_FIXED_MODEL_HPP
#include "map.h"
#include "models.h"

/**
 * \brief Class that represents all non-fixed models on the map
 *
 * \details It has:
 *          m_HP - amount of model's hp
 *          m_Damage - model's damage
 *          m_Range - range of model's attack
 *          m_Location - model's location
 */

class CNon_Fixed_Model : public CModel
{
    public:
                        CNon_Fixed_Model    ( const string& name, const string& type, char sign, size_t hp, size_t damage, size_t range );
        virtual         ~CNon_Fixed_Model   ( ) noexcept = default;
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        virtual CModel* clone               ( ) const override = 0;

        /**
         * \brief That method implements taking damage
         * 
         * \param[in] damage The amount of damage the model receives
         *
         * \return The boolean value
         *
         * \retval return TRUE if victim has more than 0 HP
         * \retval return FALSE if victim has 0 HP
         */
        bool            get_hit             ( size_t damage ) override;

        /**
         * \brief That method implements attack
         * 
         * \param[in] mappy map on which model is located to find all his neighbours
         * \param[in] victim type of victim, that it attacks
         *
         * \return The boolean value
         *
         * \retval return TRUE if model has more than 0 HP
         * \retval return FALSE if model has 0 HP
         */
        bool            attack              ( CMap& mappy, const CModel& victim ) override;

        /**
         * \brief That method implements adding location to model's atributes
         * 
         * \param[in] coordinates location coordinates
         */
        void            add_location        ( const TCoordinates& coordinates ) override;

         /**
         * \brief That method implements decreasing damage
         * 
         * \param[in] divider how much to reduce damage
         */
        void            decrease_damage     ( size_t divider ) override;

        /**
         * \brief Method that finds out if attacker is dead ( tower is destroyed )
         * 
         * \return The boolean value
         *
         * \retval return FALSE if model has more than 0 HP
         * \retval return TRUE if model has 0 HP
         */
        bool            is_dead             ( ) const override;

        /**
         * \brief Method that prints all model's stats
         *
         * \param[in] os Stream, where will be sign printed
         */
        virtual void    print_info          ( ostream& os ) const = 0;

    protected:  
        virtual void    print_action        ( ostream& os, const pair < TCoordinates, shared_ptr < CModel > >& victim ) const;
         
        size_t          m_Hp;
        size_t          m_Damage;
        const size_t    m_Range;
        TCoordinates    m_Location;

};

#endif

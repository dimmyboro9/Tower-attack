#ifndef FIXED_MODEL_HPP
#define FIXED_MODEL_HPP
#include "models.h"

/**
 * \brief Class that represents all fixed models on the map
 */

class CFixed_Model : public CModel
{
    public:
                        CFixed_Model    ( const string& name, char sign );
        virtual         ~CFixed_Model   ( ) noexcept = default;
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        virtual CModel* clone           ( ) const override = 0;
         
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
        bool            get_hit         ( size_t damage ) override;

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
        bool            attack          ( CMap& mappy, const CModel& victim ) override;

        /**
         * \brief That method implements adding location to model's atributes
         * 
         * \param[in] coordinates location coordinates
         */
        void            add_location    ( const TCoordinates& coordinates ) override;

        /**
         * \brief That method implements decreasing damage
         * 
         * \param[in] divider how much to reduce damage
         */
        void            decrease_damage ( size_t divider ) override;

        /**
         * \brief Method that finds out if attacker is dead ( tower is destroyed )
         * 
         * \return The boolean value
         *
         * \retval return FALSE if model has more than 0 HP
         * \retval return TRUE if model has 0 HP
         */
        bool            is_dead         ( ) const override;

};

#endif

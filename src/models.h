#ifndef MODELS_HPP
#define MODELS_HPP
#include <iostream>
#include "coordinates.h" 
#include "constants.h"
#include "map.h"
using namespace string_constants;

class CMap;

/**
 * \brief Abstract class that represents all models on the map
 *
 * \details It has:
 *          m_Name - name of model
 *          m_Type - type of model
 *          m_Sign - sign of model
 */

class CModel
{
    public:
                        CModel          ( const string& name, const string& type, char sign );
        virtual         ~CModel         ( ) noexcept = default;
        /**
         * \brief That method makes a copy of model
         * 
         * \return Pointer on class CModel
         */
        virtual CModel* clone           ( ) const = 0;

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
        virtual bool    get_hit         ( size_t damage ) = 0;

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
        virtual bool    attack          ( CMap& mappy, const CModel& victim ) = 0;

        /**
         * \brief That method implements adding location to model's atributes
         * 
         * \param[in] coordinates location coordinates
         */
        virtual void    add_location    ( const TCoordinates& coordinates ) = 0;

        /**
         * \brief That method implements decreasing damage
         * 
         * \param[in] divider how much to reduce damage
         */
        virtual void    decrease_damage ( size_t divider ) = 0;

        /**
         * \brief Method that finds out if attacker is dead ( tower is destroyed )
         * 
         * \return The boolean value
         *
         * \retval return FALSE if model has more than 0 HP
         * \retval return TRUE if model has 0 HP
         */
        virtual bool    is_dead         ( ) const = 0;

        /**
         * \brief That method prints model's sign
         * 
         * \param[in] os Stream, where will be sign printed
         */
        virtual void    print           ( ostream& os ) const;

        /**
         * \brief That method returns model's name
         *
         * \retval return string - model's name
         */
        string          name            ( ) const;

        /**
         * \brief That method returns model's sign
         *
         * \retval return char - model's sign
         */
        char            sign            ( ) const;

        /**
         * \brief That method returns model's type
         *
         * \retval return string - model's type
         */
        string          type            ( ) const;

        /**
         * \brief That method returns entry number ( only if model is an entrance )
         * 
         * \return The size_t - number of entrance
         */
        virtual size_t  get_num         ( ) const;

    protected:
        const string    m_Name;
        const string    m_Type;
        const char      m_Sign;
};

ostream& operator<<      ( ostream& os, const CModel& src ); 

#endif
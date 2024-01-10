#ifndef RECORD_GAME_HPP
#define RECORD_GAME_HPP
#include "game.h"

/**
 * \brief Class that represents game records
 */

class CRecordGame : public CGame 
{
    public:
                            CRecordGame         ( const CMoves& record );

        /**
         * \brief This method implements map choice
         * 
         * \details There are some private methods that help this method ( entry treatment, different switches ... )
         *
         * \return The boolean value
         *
         * \retval return TRUE if this method is fully complited
         * \retval return FALSE if player decide to exit the game
         */
        bool                choose_map          ( ) override;
        
        /**
         * \brief This method implements buying attackers
         * 
         * \details There are some private methods that help this method ( entry treatment, different switches ... )
         *
         * \return The boolean value
         *
         * \retval return TRUE if this method is fully complited
         * \retval return FALSE if player decide to exit the game
         */
        bool                buy_units           ( ) override;

        /**
         * \brief This method implements main engine of the game
         * 
         * \details It provides player moves, light AI, that puts towers, and simulation of the game process
         *
         * \return The boolean value
         *
         * \retval return TRUE if this method is fully complited
         * \retval return FALSE if player decide to exit the game
         */        
        bool                play                ( ) override;
    private:
        string              attackers_name      ( char sign ) const;
        bool                play_menu           ( char option, bool& is_over );
        bool                simulation          ( );
        void                add_model           ( size_t action );
        void                add_att_to_map      ( const shared_ptr < CAttacker >& attacker, size_t entry );
        void                add_tower           ( const shared_ptr < CTower >& tower, size_t x, size_t y );
        bool                make_move           ( );

};

#endif
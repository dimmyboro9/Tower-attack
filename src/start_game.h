#ifndef START_GAME_HPP
#define START_GAME_HPP
#include "game.h"

/**
 * \brief Class that represents real step game between player and computer
 *
 * \details It has:
 *          m_Option - the last player's choise
 */

class CStartGame : public CGame 
{
    public:
                                CStartGame          ( ) = default;
        
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
        bool                    choose_map          ( ) override;
        
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
        bool                    buy_units           ( ) override;
        
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
        bool                    play                ( ) override;
    private:
        char                    m_Option;

        void                    text_4_cm           ( CMap& show_map, size_t my_map ) const;
        bool                    map_menu            ( size_t& my_map, bool& is_confirmed );
        void                    text_4_by           ( ) const;
        bool                    purchase_menu       ( bool& is_ready );
        bool                    make_transaction    ( );
        void                    transaction_switch  ( char sign, int num );
        void                    add_2_game          ( CAttacker && attacker, size_t num, char sign );
        void                    add_random_towers   ( );
        shared_ptr < CTower >   towers_switch       ( size_t num ) const;
        void                    add_tower_2_moves   ( char sign, TCoordinates location );
        bool                    play_menu           ( bool& is_over );
        bool                    choose_unit         ( );
        void                    unit_switch         ( char sign, size_t num );
        void                    add_att_to_map      ( const shared_ptr < CAttacker >& attacker, size_t entry, char sign );
        bool                    simulation          ( );
        void                    add_towers          ( );
        pair < string, string > analyze_attack      ( ) const;
        string                  find_max            ( const unordered_map < string, size_t >& attackers ) const;
        void                    nag_alex_defense    ( list < TCoordinates >::iterator iter );
        void                    max_defense         ( );
        void                    def_with_patriot    ( list < TCoordinates >::iterator iter );
        void                    classic_defense     ( list < TCoordinates >::iterator iter );
        bool                    make_move           ( );
        void                    save_game           ( );
        void                    save_game_name      ( const string& name ) const;
};

#endif 

#ifndef GAME_HPP
#define GAME_HPP
#include "coordinates.h"
#include "neptune.h"
#include "viking.h"
#include "map.h"
#include "moves.h"
#include "write.h"
#include "exit_game.h"

const size_t TOW_TO_ATT = 5;
const size_t PLACE_RADIUS = 4;
const size_t NAG_ALEX_DEF = 3;
const size_t VIK_ALEX_DEF = 2;
const size_t MAX_DEF = 2;
const size_t DEF_WITH_PATRIOT = 2;

/**
 * \brief Abstract class that represents all ways to provide the game ( real step game or record )
 *
 * \details It has:
 *          m_Score - number of attackers who reached the exit
 *          m_Map - map on which the game takes place
 *          m_Moves - all player's actions
 *          m_Routes - paths that attackers walk
 *          m_Towers - towers in active game
 *          m_Attackers - attackers in active game
 *          m_Available_Att - available attackers
 *          m_Wait - attackers< who are waiting on enter the game ( not in m_Attackers and not in m_Available_Att )
 */


class CGame
{
    public:
                                                            CGame               ( size_t score = 0 );
        virtual                                             ~CGame              ( ) noexcept = default;
        
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
        virtual bool                                        choose_map          ( ) = 0;
        
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
        virtual bool                                        buy_units           ( ) = 0;
        
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
        virtual bool                                        play                ( ) = 0;
    protected:      
        size_t                                              m_Score;
        const static size_t                                 m_Win_Score = 5;
        CMap                                                m_Map;
        CMoves                                              m_Moves;
        unordered_map < size_t, list < TCoordinates > >     m_Routes;
        vector < shared_ptr < CTower > >                    m_Towers;
        vector < shared_ptr < CAttacker > >                 m_Attackers;
        unordered_map < string, size_t >                    m_Available_Att;
        unordered_map < size_t, shared_ptr < CAttacker > >  m_Wait;

        void                                                show_army           ( ) const;
        void                                                make_routes         ( );
        void                                                start_game_text     ( ) const;
        void                                                enter_the_game      ( );
        void                                                attack              ( );
        void                                                print_all_info      ( ostream& os ) const;
        void                                                print_tower_info    ( ostream& os ) const;
        size_t                                              num_of_available    ( ) const;
};

#endif
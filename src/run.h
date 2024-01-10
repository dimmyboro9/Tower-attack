#ifndef RUN_HPP
#define RUN_HPP
#include "game.h"

/**
 * \brief Class that provides running of the program ( start the game, exit the game, watch record game )
 *
 * \details It has:
 *          m_Option - the last player's choise
 *          m_Game - pointer on abstract class CGame, which provides the game
 */


class CRun
{
    public:
                                        CRun            ( ) = default;
        /**
         * \brief This method implements program running
         *
         * \details Asks player what he wants to do ( start the game, watch a record game, exit the program ) 
         */
        void                            run_programm    ( );        
    private:                        
        char                            m_Option;
        unique_ptr < CGame >            m_Game;

        void                            choose_option   ( );
        bool                            menu            ( );
        bool                            choose_file     ( CMoves& record );
        void                            enter_name      ( CMoves& record );
        bool                            run_game        ( ) const;
};

#endif

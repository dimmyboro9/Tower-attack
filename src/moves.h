#ifndef MOVES_HPP
#define MOVES_HPP
#include <cstdlib>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * \brief Class that keeps all player's and computer's actions during the game.
 *
 * \details It has:
 *          m_Map_Number - number of chosen map
 *          m_Attackers - all attackers bought by the player
 *          m_Game_Moves - all additions of attackers and towers to the game and simulation starts
 */

class CMoves
{
    public:
                                        CMoves          ( ) = default;
        
        /**
         * \brief This method add map number chosen by player 
         * 
         * \param[in] map_number number of the map chosen by player
         */
        void                            add_map_number  ( size_t map_number );
        
        /**
         * \brief This method add attacker bought by player 
         * 
         * \param[in] sign attacker's sign on the map
         * \param[in] num how many attackers were bought
         */
        void                            add_attacker    ( char sign, size_t num );
        
        /**
         * \brief This method add attackers and towers, that was added to the map, and their locations to the class.
         *        Also it adds information about when the player simulated the game
         * 
         * \details all signs and numbers are saved in size_t
         * 
         * \param[in] game_move number of the map chosen by player
         */
        void                            add_game_move   ( size_t game_move );
        
        /**
         * \brief Return map number chosen by player 
         * 
         * \retval size_t - map number 
         */
        size_t                          get_map_number  ( ) const; 
        
        /**
         * \brief Return all attackers that was bought by player 
         * 
         * \retval unordered_map < char, size_t > - map of attacker's sign and amount of this type of attacker
         */
        unordered_map < char, size_t >  get_attackers   ( ) const; 
        
        /**
         * \brief Return game moves in right order
         * 
         * \retval size_t - game move in size_t 
         */
        size_t                          get_game_move   ( ); 
        
        /**
         * \brief This method writes noves to the file to keep record
         * 
         * \param[in] file file, where the moves will be written 
         */
        void                            write_to_file   ( ostream& file );
        
        /**
         * \brief This method writes moves from the file to get as a record
         * 
         * \param[in] file file, from where the moves will be written
         */
        void                            write_from_file ( istream& file );
    private:        
        size_t                          m_Map_Number;
        unordered_map < char, size_t >  m_Attackers;
        queue < size_t >                m_Game_Moves; 
};

#endif

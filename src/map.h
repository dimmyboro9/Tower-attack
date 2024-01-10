#ifndef MAP_HPP
#define MAP_HPP
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <functional>
#include "coordinates.h"
using namespace std;

const size_t NUM_OF_MAPS = 3;
const size_t MIN_TOWERS = 2;

class CModel;

/**
 * \brief Class that represents the map on which all game actions take place
 *
 * \details It has:
 *          m_Length - length of map
 *          m_Width - width of map
 *          m_Coins - amount of coins on which player can buy attackers
 *          m_Num_of towers - the number of towers that are available to the computer
 *          m_Models - all map models ( even free ) that together create a whole map
 *          m_Entrances - all map entrances and their coordinates
 *          m_Exit - coordinates of map exit
 */

class CMap
{
    public:
                                                    CMap                ( ) = default;
                                                    CMap                ( size_t len, size_t wid, size_t coins, size_t num );
                                                    ~CMap               ( ) noexcept = default;

        /**
         * \brief This method implements adding fixed model
         * 
         * \param[in] model fixed model that will be added to the map
         * \param[in] coordinates coordinates, on which will fixed model be added to the map
         */

        void                                        add_fixed_model     ( const CModel& model, const TCoordinates& coordinates ); 

        /**
         * \brief This method implements adding attackers
         * 
         * \param[in] attacker pointer on attacker that will enter the entrance
         * \param[in] entry entry, on which will attacker enter the game
         *
         * \return The boolean value
         *
         * \retval return TRUE if attacker entered the game
         * \retval return FALSE if attacker didn't enter the game 
         */
        bool                                        add_attacker        ( const shared_ptr < CModel >& attacker, size_t entry ); // !!! not ready

        /**
         * \brief This method implements adding towers
         * 
         * \param[in] tower pointer on tower that will be added to the map
         * \param[in] location coordinates, on which will tower be added to the map
         */
        void                                        add_tower           ( const shared_ptr < CModel >& tower, TCoordinates& location );

        /**
         * \brief This method implements adding towers to the random places of the map
         * 
         * \param[in] tower pointer on tower that will be added to the map
         * \param[in] location coordinates, on which will tower be added to the map
         *
         * \return The boolean value
         *
         * \retval return TRUE if tower was added to the game
         * \retval return FALSE if tower wasn't added to the game 
         */
        bool                                        add_random_tower    ( const shared_ptr < CModel >& tower, TCoordinates& location );

        /**
         * \brief This method removes models from the map
         * 
         * \param[in] coordinates coordinates, from which will model be removed
         */
        void                                        remove_model        ( const TCoordinates& coordinates );

        /**
         * \brief This method swaps models on the map
         * 
         * \param[in] from coordinates, from which will model be swapped
         * \param[in] to coordinates, to which will model be swapped
         */
        void                                        swap_models         ( const TCoordinates& from, const TCoordinates& to );

        /**
         * \brief This method add all attackers, who are waiting on the entrance
         * 
         * \return queue < size_t > - queue entries, from which were attackers added to the game
         */
        queue < size_t >                            enter_the_game      ( );
        
        /**
         * \brief This method saves map to the file
         * 
         * \param[in] file file, where the map will be saved
         */
        void                                        save_map            ( const string& file ) const;

        /**
         * \brief This method loades map from the file
         * 
         * \param[in] file file, from where the map will be loaded
         */
        void                                        load_map            ( const string& file );

        /**
         * \brief This method return amount of coins on which player can buy attackers
         * 
         * \return size_t - amount of coins on which player can buy attackers
         */
        size_t                                      show_coins          ( ) const;

        /**
         * \brief This method return the number of towers that are available to the computer
         * 
         * \return size_t - number of towers that are available to the computer
         */
        size_t                                      num_of_towers       ( ) const;

        /**
         * \brief This method decreases amount of coins after a purchase
         * 
         * \param[in] diff amount of coins that were spent on the purchase
         *
         * \return the boolean value
         *
         * \retval return TRUE if there were enough coins to make a purchase
         * \retval return FALSE if there weren't enough coins to make a purchase
         */
        bool                                        decrease_coins      ( size_t diff );

        /**
         * \brief This method returns information about whether this position is free
         * 
         * \param[in] coordinates coordinate of this position
         *
         * \return the boolean value
         *
         * \retval return TRUE if this position is free ( on this position is located model of the class CFree )
         * \retval return FALSE if this position isn't free
         */
        bool                                        is_free             ( const TCoordinates& coordinates ) const;

        /**
         * \brief This method returns all neighbours of a given position on the map in given range 
         * 
         * \param[in] range range in which to look for neighbours
         * \param[in] pos coordinate of given position
         *
         * \retval vector < pair < TCoordinates, shared_ptr < CModel > > > - vector of all neighbours 
         *         in given range from given position with neigbour coordinates and pointer on him
         */
        vector < pair < TCoordinates,
                        shared_ptr < CModel > > >   return_neighbours   ( int range, const TCoordinates& pos ) const;

        /**
         * \brief This method returns the shortest path from given entrance to the exit 
         * 
         * \details Using BFS-algorithm to implement this task
         * 
         * \param[in] entry entry from which the path to the end is saught
         *
         * \retval list < TCoordinates > - path from entry to the exit 
         */
        list < TCoordinates >                       shortest_path       ( size_t entry ) const;

        /**
         * \brief This method prints map 
         * 
         * \param[in] os output stream where to print the map
         */
        void                                        print_map           ( ostream& os ) const;

        /**
         * \brief This method prints one row of the map 
         * 
         * \details This method is used for beautiful image of the progress of the game
         *          due to the fact that ncourses library is not used
         * 
         * \param[in] row which row has been printed
         * \param[in] os output stream where to print the row of the map
         *
         * \return the boolean value 
         *
         * \retval return TRUE if map's width is more than or equal to the given row
         * \retval return FALSE if map's width is less than or equal to the given row
         */
        bool                                        print_one_row       ( ostream& os, size_t row ) const;

        /**
         * \brief This method prints such information about the map
         *        as amount of coins and number of towers on this map 
         * 
         * \param[in] os output stream where to print this information
         */
        void                                        print_map_info      ( ostream& os ) const;

        /**
          * \brief Overloaded operator ==
          * 
          * \param[in] os output stream
          * \param[in] src map that will be write out 
          *
          * \retval output stream
          */
        friend ostream&                             operator<<          ( ostream& os, const CMap& src );
    private:                
        size_t                                      m_Length;   
        size_t                                      m_Width;    
        size_t                                      m_Coins;    
        size_t                                      m_Num_Of_Towers;                             
        map < TCoordinates, shared_ptr < CModel > > m_Models;   
        unordered_map < size_t, 
                        pair < TCoordinates, 
                        shared_ptr < CModel > > >   m_Entrances;    
        TCoordinates                                m_Exit; 
        void                                        generate_map        ( );
        void                                        update_map          ( istream& is );
        bool                                        near_entry_exit     ( const TCoordinates& coordinates );
        void                                        while_in_bfs        ( queue < TCoordinates >& to_visit, unordered_map < TCoordinates, TCoordinates, function < size_t ( const TCoordinates& ) > >& is_visit ) const;
        list < TCoordinates >                       write_path          ( const unordered_map < TCoordinates, TCoordinates, function < size_t ( const TCoordinates& ) > >& is_visit, const TCoordinates& start, const TCoordinates& exit ) const;
};

#endif
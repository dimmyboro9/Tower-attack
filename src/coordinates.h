#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#include <cstdlib>
#include <iostream>
using namespace std;

/**
 * \brief Struct that indicates the coordinates on the map 
 *
 * \details It has:
 *          m_X - Abcscissa coordinate
 *          m_Y - Ordinate coordinate
 */


struct TCoordinates
{
                        TCoordinates    ( ) = default;
                        TCoordinates    ( size_t x, size_t y );
    /**
     * \brief Overloaded operator <
     * 
     * \param[in] cmp The structure to compare against
     *
     * \return The boolean value
     *
     * \retval return TRUE if this structure is smaller
     * \retval return FALSE if this structure is bigger
     */
    bool                operator<       ( const TCoordinates& cmp ) const;

    /**
     * \brief Overloaded operator ==
     * 
     * \param[in] cmp The structure to compare against
     *
     * \return The boolean value
     *
     * \retval return TRUE if this structure and structure to compare against are equal 
     * \retval return FALSE if this structure and structure to compare against are not equal 
     */
    bool                operator==      ( const TCoordinates& cmp ) const;

    /**
     * \brief Overloaded operator ==
     * 
     * \param[in] os output stream
     * \param[in] src structure that will be write out 
     *
     * \retval output stream
     */
    friend ostream&     operator<<      ( ostream& os, const TCoordinates& src );
    
    size_t  m_X;
    size_t  m_Y;
};

#endif
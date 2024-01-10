#ifndef EXIT_GAME_HPP
#define EXIT_GAME_HPP
#include "clear.h"

enum Yorn : char 
{
    YES = 'y',
    NO = 'n'
};

/**
 * \brief Function that writes question before the exit 
 *
 * \param[in] question this question
 */
void write_text ( const string& question );


/**
 * \brief Function that asks the player if he wants to exit the game 
 *
 * \param[in] question that question is written before the exit
 *
 * \return The boolean value
 *
 * \retval return TRUE if player want to exit the game or programm
 * \retval return FALSE if player don't want to exit the game or programm
 *
 */
bool exit ( const string& question );


#endif

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <string>
using namespace std;

/**
 * \brief header that keeps all constants 
 */
 
namespace string_constants
{
    const string VIK_NAME = "Viking";
    const string ALEX_NAME = "Alexandr";
    const string NAG_NAME = "Nagibator";
    const string MAX_NAME = "Max";
    const string FRK_NAME = "Freak";
    const string WALL_NAME = "Wall";
    const string FREE_NAME = "Free";
    const string ENT_NAME = "Entrance";
    const string EXIT_NAME = "Exit";
    const string NEP_NAME = "Neptune";
    const string MEGA_NAME = "Megadurum";
    const string PAT_NAME = "Patriot";
    const string BUR_NAME = "Burakov";
    const string ATT_TYPE = "Attacker";
    const string TOW_TYPE = "Tower";
    const string FIX_TYPE = "Fixed";
}

enum char_constants : char
{
    VIK_SIGN = 'V',
    ALEX_SIGN = 'A',
    NAG_SIGN = 'N',
    MAX_SIGN = 'M',
    FRK_SIGN = 'F',
    WALL_SIGN = '#',
    FREE_SIGN = ' ',
    ENT_SIGN = '<',
    EXIT_SIGN = '<',
    NEP_SIGN = '!',
    MEGA_SIGN = 'i',
    PAT_SIGN = 'l',
    BUR_SIGN = '1',
    START = 's',
    CONTINUE = 'c',
    INFO = 'i',
    EXIT = 'e',
    NEXT = 'n',
    PREV = 'p',
    RECORD = 'r',
    CONFIRM = 'c',
    RETURN = 'r',
    BUY = 'b',
    ADD = 'a',
    TOWER = 't'
};

#endif

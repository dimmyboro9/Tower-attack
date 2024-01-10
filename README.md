# Tower-attack
This is my project written in the spring of 2022 during my studies at FIT CTU. In this project, I implement a terminal game: `Tower Attack`, the essence of which is to reach the end of the map with your units while facing towers that hinder their progress.

## Game description
Welcome to the game **Tower Attack** (the name is not yet finalized). It's not hard to guess that in this game, you must attack towers. Would you like to start?

What can you do in this game?

* Choose a map on which you want to attack towers,
* Buy attackers,
* Send your warriors into battle: indicate which entrance each attacker will use to enter the battlefield,
* Fight against a unique (ha-ha) artificial intelligence technology that will position towers to prevent your attackers from reaching their goal,
* Save and load ongoing games,
* The engine of this game functions as a turn-based game.

At the beginning, you'll be greeted by a menu that provides basic information about the game and offers options such as:
* starting the game, 
* selecting and loading recordings, 
* obtaining information about attackers and towers,
* quitting the game. 

Naturally, you are most interested in the game itself. Initially, you will be asked to select one of the n-th number of maps available in the game. Then you will have a certain amount of gold to buy attackers.

The map will then be printed to the console. At this point, artificial intelligence (or something similar) will place towers on the map. Then the real fun begins. Each round, you will have the opportunity to enter three purchased attackers through three different entrances. With each move, they will move depending on their speed and priority. And once they get close to the towers, the real battle begins. All information about the attack will be displayed below the map.

Different attackers and towers will attack differently, with different attack ranges, superpowers, and other properties. In the end, the goal is to reach a certain number of attackers before the exit. If the player succeeds, the console will show that they won and return to the main menu, where they can watch the recording of their incredible victory.

How can the map look?

``` plaintext
#################################################
#                        #       @@  #   @@  @@<=3
#         #              #    %I  @  ###        #
#         #              #    %#  @    #    I   #
<=%%%     #              I    %#       #@  @@  <=1
#         #              I    %#       @@   I   #
#                        I    %#                #
#                 %%%       %%%#    @          <=2
#################################################

" " - empty spaces for attacker movement and tower construction,
I - represents towers,
# - represents walls,
@ and % - represent different types of attackers,
<= - represents inputs/outputs from the map.
```

Player selects entrance and types of attackers.

The path that attackers will take will always be the shortest possible given the walls and towers.

Where to use polymorphism:

* Map elements: wall, tower, attacker
* Types of game launches: actual game or recording

Implemented features:

* Load attacker definitions from a file (name, lives, speed, attack, range)
* Load possible maps and types of defensive towers from a file (lives, range, attack)
* Simple interaction between towers and attackers (attack, passage, etc.)
* Score counter, victory detection (if 5 attackers reach the end)
* Simple AI controlling the placement of towers
* Allows saving and loading ongoing games

# SDL-Game-Mission-Control
Handmade game using the SDL library. Utilizes a tile sets, sprites and a particle system

Author: Payton Beans


Controls:
Move left    --> Left Arrow key
Move Right   --> Right Arrow key
Jump         --> Up Arrow Key
Stop         --> Down Arrow Key


The program can be compiled with the "make all" command
The program can be run with the "./my_game" or "make run" command


Currently the only collision possible in the game is the player and the ground
and the player with an enemy.
When the player-ground collision occurs if the player is moving fast enough
sparks will be emitted behind the player. Looks more like dust though.
The player-enemy collision ends the game.

For the final project I implemented these three topics.
-Enemies, enemies spawn and try to follow the player. The enemies movement has
some minor variations from a straight line. They also speed up over time.

-True-type font, I used a true type font for the Fuel label and score.

-UI, I created a UI that displays the score and current fuel. You can't change
your direction of movement without fuel so be careful!

I used linked lists for storing the particles and collision objects. I know this
isn't how it is shown in the demo but I believe this will allow for greater
flexibility in the future as there's only one instance of collision detection
and particle generation and any system in the game will have access to them in
a dynamic implementation. No size limited arrays also means that any number of
particles and collision objects can be used with out wasted memory space if the
array is not filled. linked lists will only occupy the space required for each
element and manage their own memory destruction. This does mean I have to be
careful to actually deconstruct these nodes as they are not needed.



Player sprite source:
http://3.bp.blogspot.com/-I2UsoJVFJSE/T1FRZCSQf7I/AAAAAAAAAfU/g8b81MCcjII/s1600/arrows.png

Background sourse:
https://wallup.net/wp-content/uploads/2016/01/171007-pixels-pixel_art-8-bit-moon-stars-video_games-space-dragon-clouds-cave_story.jpg

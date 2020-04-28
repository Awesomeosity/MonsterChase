ABOUT GAMEPLAY:
You move the left paddle with 'W' and 'S', and the right paddle with 'I' and 'K'.
Once either player has scored 5 points, the game closes.

Notable things:
Collision Callbacks used in lines 316 - 366 of Engine.cpp, called when colliding with objects.
World system that stores all objects used, and hands out references to systems that ask for them. (World.cpp and World.h)
Collision system that discriminates objects based on whether or not they're non-movable or movable (Physics.cpp line 241).
Differing collision response based on type of objects that collide (Physics.cpp lines 609-660).
Collision system that can use both universal axis of collision or object-axis-based collision (Physics.cpp collisionCheck functions, private vs public).
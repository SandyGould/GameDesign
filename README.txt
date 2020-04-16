Controller is working (but not much is actually mapped in the demo).

Joystick: Move

All buttons are xbox mapping -- other controllers will be whatever button is in
the equivalent position.

A: Bigger
B: Smaller

The game ignores keyboard input while there is controller input.


Animated sprites didn't get finished in time and were on a different branch
which doesn't have controller support, so this branch doesn't have any
spritesheet functionality. Our team is planning to finish both the spritesheets
and the devtool over break. This week was mostly focused on the devtool for us,
which is why spritesheets aren't done (devtool has made a lot of progress).

So unfortunately we haven't been able to fully implement the Collision System or get the demo running. However, we've made substantial progress on hitboxes and figuring out if there are collisions between them (including all of those annoying repeated equations). We have yet to work on the overarching detection structure (as in, the part that actually listens for collisions between particular objects and stuff) and collision resolution. Our work can be found in the DisplayObject and CollisionSystem .cpp and .h files.

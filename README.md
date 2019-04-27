# sphere-flake-player
SphereFlake fractal player in openGL

The project is done with MicrosoftVisualStudio Express 2013, using the Debug/Win32 configurations.

It is a fractal player that allows the player to look around, move, set his speed, zoom in and out, and render.

Due to time constraints there were a lot of optimizations and algorithms I couldn't implement. As a result it is somewhat clumsy.

The rerender is currently not automatic due to lack of optimizations. In the future it should be done incrementally and not from grounnd zero each time a rerender is required. Another feature that will improve the speed will be to add another filter to the sphereTree to not create in the first place spheres that are hidden behind others.

Screenshots of the results:

<img src="https://github.com/perushinkov/sphere-flake-player/blob/master/demo_images/quality.png">

And associated controls:

<img src="https://github.com/perushinkov/sphere-flake-player/blob/master/demo_images/controls.jpg">

NOTE: 
  This was coded within a single week, where day 1 was my first encounter with OpenGL.
  The challenge also required that I do not reference any of the required maths and algorithms.
  The only exception was looking up the actual technical specification (OpenGL docs).

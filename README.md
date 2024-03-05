This game/project can:
 
 • This project contains only C++ code and the code is minimal
 
 • Renders the screen 50 times per second using OpenGL
 
 • Works on an old tablet, phone with version Android 4 (this version was released in 2011)
 
 • The project is very, very simple. Contains 2 files:
  
    main.cpp ... with 150 lines of Android system code (init device, gain focus, kill focus, handle use events like finger touch, move). This file is finished and you don't need to edit it.
     
    my_game.cpp ... with 130 lines of OpenGL code (init OpenGL surface, fill background, close OpenGL). This file needs to be edited to add drawing and game logic.
         
 • This project uses Android NDK (native C++ library)
 
 • This project uses  OpenGL ES (2D & 3D graphic library)
  

You will see result:

 it was first 
![image](https://github.com/EvgenProjects/AndroidNative_BasicGame/assets/38002631/1cf96e17-2848-4375-b45a-ec7d93680ed3)

I added graphic.cpp file for drawing figures with color
And created game with airplane, lakes, enemy airplanes:
![image](https://github.com/EvgenProjects/AndroidNative_BasicGame/assets/38002631/652f2215-7abf-4651-9eb1-e3c81112fcc9)



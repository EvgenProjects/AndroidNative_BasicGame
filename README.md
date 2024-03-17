Game "Flying airplane" ![image](https://github.com/EvgenProjects/AndroidNative_BasicGame/assets/38002631/118ae6b0-f710-4c7c-8dc1-68d329f74245)

Rule:
You can move airplane by touching screen. Also you will see enemy airplanes, trees, lake. Be careful :) while flying...

  
This game/project can:
   
 • This project contains only C++ code and the code is minimal
 
 • Renders the screen 50 times per second using OpenGL
 
 • Works on an old tablet, phone with version Android 4 (this version was released in 2011)
 
 • This project uses Android NDK (native C++ library)
 
 • This project uses  OpenGL ES (2D graphic)

 • The project is very, very simple. Contains 4 files:
  
    main.cpp ... with 150 lines of Android system code (init device, gain focus, kill focus, handle use events like finger touch, move). This file graphic.cpp is finished and you don't need to edit it (you can edit it if you really want to).
     
    graphic.cpp ... with 180 lines of OpenGL code (initialize OpenGL surface, close OpenGL, has implemented class MyPolygon for drawing connected lines with fill color inside). This file graphic.cpp is finished and you don't need to edit it (you can edit it if you really want to).
 
    my_game.cpp ... with 90 lines of code: Put on scene my plane, enemy planes, trees, lake. Moving camera on each frame. Handling tapping on the screen and moving my plane left, right.
 
    my_game_assets.h ... 130 lines: here are only vector points and colors for my plane, enemy plane, lake, tree. Vector graphics were drawn in Adobe Illustrator and exported to SVG files, and from SVG files I copied points and colors here.

    
  
Run project in Android Studio or APK file in your phone and you will see result:
  
  
1 november 2023: implemented base functionality for drawing green background using openGL 50 times per second: 
![image](https://github.com/EvgenProjects/AndroidNative_BasicGame/assets/38002631/1cf96e17-2848-4375-b45a-ec7d93680ed3)
  
  
  
17 March 2024: I added graphic.cpp file for drawing polygons using OpenGL. Added my_game_assets.h file with vector points and colors for my airplane, enemy airplanes, lake, trees:
![image](https://github.com/EvgenProjects/AndroidNative_BasicGame/assets/38002631/a61833b4-6741-462c-9ff7-26c8d9dee845)

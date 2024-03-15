#include <EGL/egl.h>

#define colorBlue           RGBA{0.0f, 0.0f, 0.7f, 0.8f}
#define colorLightBlue      RGBA{0.0f, 0.0f, 0.5f, 0.7f}
#define colorWhite          RGBA{0.9f, 0.9f, 0.9f, 1.0f}
#define colorVeryLightBlue  RGBA{0.3f, 0.4f, 0.8f, 0.7f}

#define colorBrown  RGBA{0.44f, 0.4f, 0.34f, 0.7f}

MyObject g_MyAirPlane = MyObject({

     MyPolygon(GL_TRIANGLE_FAN, { // cabin (points from Adobe Illustrator)
         {XY(50, 14), colorLightBlue}, // center point
         {XY(48, 6),  colorBlue}, // first point
         {XY(53, 6),  colorBlue},
         {XY(56, 10), colorBlue},
         {XY(56, 20), colorBlue},
         {XY(44, 20), colorBlue},
         {XY(44, 10), colorBlue},
         {XY(48, 6),  colorBlue}, // first point
     }),

     MyPolygon(GL_TRIANGLE_FAN, { // body (points from Adobe Illustrator)
         {XY(50,50), colorVeryLightBlue}, // center point
         {XY(41,10), colorVeryLightBlue}, // first point
         {XY(47,4),  colorVeryLightBlue},
         {XY(54,4),  colorVeryLightBlue},
         {XY(59,10), colorVeryLightBlue},
         {XY(55,93), colorWhite},
         {XY(45,93), colorWhite},
         {XY(41,10), colorVeryLightBlue}, // first point
     }),

     MyPolygon(GL_TRIANGLE_FAN, { // front wing (points from Adobe Illustrator)
         {XY(50,40), colorWhite}, // center point
         {XY(2,30), colorVeryLightBlue}, // first point
         {XY(98,30),  colorVeryLightBlue},
         {XY(98,43),  colorWhite},
         {XY(70,47), colorWhite},
         {XY(29, 47), colorWhite},
         {XY(2,43), colorWhite},
         {XY(2,30), colorVeryLightBlue}, // first point
     }),

     MyPolygon(GL_TRIANGLE_FAN, { // back wing (points from Adobe Illustrator)
         {XY(50,84), colorWhite}, // center point
         {XY(34,80), colorVeryLightBlue}, // first point
         {XY(66,80),  colorVeryLightBlue},
         {XY(66,88),  colorWhite},
         {XY(34,88), colorWhite},
         {XY(34,80), colorVeryLightBlue}, // first point
     }),
 });

MyObject g_Lake = MyObject({

    MyPolygon(GL_TRIANGLE_FAN, { // lake (points from Adobe Illustrator)
        {XY(50,50),  colorLightBlue}, // center point
        {XY(43,0),   colorBlue}, // first point
        {XY(68,2),   colorBlue},
        {XY(85,10),  colorBlue},
        {XY(94,23),  colorBlue},
        {XY(100,36), colorBlue},
        {XY(100,64), colorBlue},
        {XY(84,88),  colorBlue},
        {XY(59,100), colorBlue},
        {XY(41,100), colorBlue},
        {XY(19,94),  colorBlue},
        {XY(4,75),   colorBlue},
        {XY(1,50),   colorBlue},
        {XY(5,27),   colorBlue},
        {XY(14,10),  colorBlue},
        {XY(43,0),   colorBlue}, // first point
    }),
});

MyObject g_EnemyAirPlane = MyObject({

     MyPolygon(GL_TRIANGLE_FAN, { // cabin (points from Adobe Illustrator)
             {XY(50, 50), colorBrown}, // center point
             {XY(46, 5),  colorBrown}, // first point
             {XY(49, 3),  colorBrown},
             {XY(51, 3),  colorBrown},
             {XY(53, 5),  colorBrown},
             {XY(54, 15), colorBrown},
             {XY(55, 24), colorBrown},
             {XY(55, 44), colorBrown},
             {XY(56, 52), colorBrown},
             {XY(56, 69), colorBrown},
             {XY(58, 71), colorBrown},
             {XY(58, 79), colorBrown},
             {XY(59, 80), colorBrown},
             {XY(59, 85), colorBrown},
             {XY(57, 87), colorBrown},
             {XY(56, 89), colorBrown},
             {XY(42, 89), colorBrown},
             {XY(42, 87), colorBrown},
             {XY(40, 85), colorBrown},
             {XY(40, 80), colorBrown},
             {XY(41, 79), colorBrown},
             {XY(41, 70), colorBrown},
             {XY(42, 69), colorBrown},
             {XY(43, 51), colorBrown},
             {XY(44, 44), colorBrown},
             {XY(45, 25), colorBrown},
             {XY(45.5,16),colorBrown},
             {XY(46, 5),  colorBrown}, // first point
     }),
});

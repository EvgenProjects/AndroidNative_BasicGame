#include <EGL/egl.h>

#define colorBlue           RGBA{0.0f, 0.0f, 0.7f, 0.8f}
#define colorLightBlue      RGBA{0.0f, 0.0f, 0.5f, 0.7f}
#define colorWhite          RGBA{0.9f, 0.9f, 0.9f, 1.0f}
#define colorVeryLightBlue  RGBA{0.3f, 0.4f, 0.8f, 0.7f}

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

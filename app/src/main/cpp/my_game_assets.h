#include <EGL/egl.h>

#define colorBlue           RGBA{0.0f, 0.0f, 0.7f, 0.8f}
#define colorLightBlue      RGBA{0.0f, 0.0f, 0.5f, 0.7f}
#define colorWhite          RGBA{0.9f, 0.9f, 0.9f, 1.0f}
#define colorVeryLightBlue  RGBA{0.3f, 0.4f, 0.8f, 0.7f}

MyObject TEMPLATE_Lake = MyObject({

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

MyObject TEMPLATE_MyAirPlane = MyObject({

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

MyObject TEMPLATE_EnemyAirPlane = MyObject({

    // Cabin
    MyPolygon(GL_TRIANGLE_FAN, "#D10000", XY(50, 79), "45.928,71.216 53.928,71.216 54.72,77.501 55.047,80.93 53.948,84.656 45.948,84.656 "
                                                                                              "44.733,81.084 45.011,77.667 "),
    // Gun_right_on_wing
    MyPolygon(GL_TRIANGLE_FAN, "#726658", XY(75, 75), "72.636,71.216 72.636,77.438 79.303,77.438 79.303,71.344 "),

    // Gun_right_on_wing
    MyPolygon(GL_TRIANGLE_FAN, "#726658", XY(22, 75), "18.386,71.216 18.386,77.438 25.053,77.438 25.053,71.344"),

    // Wing_back_right
    MyPolygon(GL_TRIANGLE_FAN, "#D10000", XY(60, 13), "52.594,7.364 56,7.364 56,4.958 60.656,4.958 60.656,6.161 66.094,6.161 "
                                                      "68.844,9.989 68.844,15.958 65.969,18.896 53.656,19.864 "),

    // Wing_back_left
    MyPolygon(GL_TRIANGLE_FAN, "#D10000", XY(40, 13), "47.219,7.208 44.052,7.208 44.052,4.375 38.719,4.375 38.719,5.792 "
                                                      "34.886,5.792 30.886,9.708 30.886,15.542 32.219,18.542 46.552,20.042 "),

    // Body
    MyPolygon(GL_TRIANGLE_FAN, "#726658", XY(50, 50), "46.511,4.959 48.886,2.875 50.886,2.875 53.323,4.875 54.011,15.688 54.636,24.563 "
                                                      "55.636,44.75 56.448,51.875 56.948,69.5 58.011,71.125 58.011,78.813 59.073,80.813 59.073,85.375 57.323,87.375 56.886,89.563 "
                                                      "42.886,89.563 42.386,87.531 40.604,85.375 40.604,80.813 41.698,79.209 41.714,70.969 42.636,69.126 43.481,51.883 44.167,44.656 "
                                                      "44.979,24.75 45.677,16"),

    // BlackBody
    MyPolygon(GL_TRIANGLE_FAN, "#414042", XY(50, 60), "38.698,75.25 41.448,77.438 58.011,77.438 60.261,75.625 59.636,49.125 "
                                                      "56.323,46.219 43.448,46.219 39.698,49.125 "),

    // Wings_Front
    MyPolygon(GL_TRIANGLE_FAN, "#D10000", XY(50, 60), "41.802,48.792 5.802,54.209 2.302,58.125 2.302,65.959 5.469,71.292 "
                                                      "37.886,75.042 61.136,75.042 95.053,70.959 98.219,67.459 98.219,59.709 94.469,53.959 58.553,48.792 "),

    // Propeller_center
    MyPolygon(GL_TRIANGLE_FAN, "#414042", XY(50, 92), "47.386,88.375 47.386,94.375 49.479,97.125 50.386,97.125 51.995,94.281"
                                                      "51.995,88.375 "),

    // Propeller_left
    MyPolygon(GL_TRIANGLE_FAN, "#414042", XY(40, 93), "47.823,92.75 31.636,92.75 31.636,93.938 33.636,95.75 40.604,95.75 "
                                                      "45.261,93.688 47.823,93.625 "),

    // Propeller_right
    MyPolygon(GL_TRIANGLE_FAN, "#414042", XY(61, 93), "51.636,93.688 67.823,93.688 67.823,92.5 65.823,90.688 58.854,90.688 "
                                                      "54.198,92.75 51.636,92.813 "),
});

MyObject TEMPLATE_Tree = MyObject({

    // Body
    MyPolygon(GL_TRIANGLE_FAN, "#7E4E35", XY(50, 83), "43.145,67.725 55.25,67.725 56.729,98.876 40.25,98.876 "),

    // Leaves
    MyPolygon(GL_TRIANGLE_FAN, "#619E5B", XY(52, 35), "8.187,21.838 7.687,18.922 8.52,15.797 12.104,12.547 16.937,11.047 17.979,8.755 "
                                                      "20.02,6.38 22.687,4.63 26.604,4.213 28.729,3.047 31.437,2.213 34.687,2.213 37.937,3.213 40.104,4.838 43.187,3.463 46.979,2.213 "
                                          "49.854,2.713 53.813,4.963 56.188,3.63 59.979,2.422 63.229,2.713 66.563,4.255 68.938,6.63 69.688,9.922 73.354,9.963 "
                                          "76.729,11.005 79.563,12.755 81.646,15.797 84.729,15.922 87.438,16.797 90.063,18.505 91.896,20.088 93.646,23.38 93.188,27.547 "
                                          "94.479,29.463 96.938,31.255 97.813,32.713 98.396,35.506 98.188,37.756 96.063,41.006 96.813,43.297 97.104,45.963 96.271,47.797 "
                                          "93.688,49.962 91.146,50.837 89.479,52.838 87.479,54.129 86.979,55.129 85.771,57.088 83.854,59.297 79.938,60.172 79.313,61.963 "
                                          "77.438,63.588 76.646,65.547 75.188,67.588 72.479,69.254 70.146,69.879 68.563,70.797 64.521,71.504 60.979,70.422 57.688,72.004 "
                                          "54.313,73.213 52.396,73.213 39.813,73.213 32.771,69.547 31.438,66.172 25.063,65.547 22.021,62.754 18.896,59.588 15.313,58.504 "
                                          "12.688,54.422 12.438,49.13 8.854,47.756 3.896,43.422 3.604,39.172 6.271,35.463 2.854,33.005 1.604,29.505 3.646,24.588 "),
});

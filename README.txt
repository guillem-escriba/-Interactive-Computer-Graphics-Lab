Computer Graphics Application README
Contributors
Name: Guillem Escriba Molto
NIA: 242123
Email: guillem.escriba01@estudiant.upf.edu
Name: David Pérez Carrasco
NIA: 241375
Email: david.perez18@estudiant.upf.edu

LAB 1 CONTROLS: ("1", "2", "3", "4", "5", "6", "7", "8", "P", ",", ".")
Some actions print messages to the console to indicate what is happening, such as when the minimum or maximum brush size is reached or when applying a filter. All tasks are applied by holding down their respective key, so releasing them redraws the original image, except for Paint, where pressing 'P' creates a new state for drawing.

Task 1:
Holding "1" draws our design with geometric shapes. A black background is applied first to highlight the figure. We considered an option to draw our figure over the image, but this way it's more noticeable.
Task 2:
At any time, apply a radial gradient by holding "2" or a normal gradient with "3". This temporarily erases the framebuffer's content and displays the gradient on screen with predefined colors, despite other configured options. This is set by default to avoid errors.
Task 3:
Apply Inverse and Channel Swap filters at any time by holding "4" for Inverse and "5" for Channel Swap. Despite many channel changes, the used ones are R->B, G->R, and B->G.
Task 4:
Holding "6" applies image rotation with degrees specified in the function call in task4_1 in the application. It's changeable from there. Similarly, press "7" to change the scale, either less than 1 or greater.
Task 5:
Holding "8" displays our gif. Particles created in the init and updated in the update are drawn only while holding this key.
Task 6:
Press "P" for Paint mode. The framebuffer is cleared and Paint is initialized. From this point, interact with the mouse as a brush and select different paint icons. From left to right: New Sketch (erases everything drawn), Save Sketch (saved as "newcanvas"), and various colors (click to change brush color). Use "," and "." to decrease or increase the brush size, with a maximum range of 1 to 100 px. Press "P" again to exit Paint and return to the previously loaded image in the framebuffer.


LAB 2 CONTROLS: ("P", ",", ".", "F", "L", "C", "T", "D", "V")
To draw shapes, press "P" for Paint mode. Shapes follow the same variables as the brush, meaning they increase and decrease in size (for circles) with "," and "." and change color by selecting from the Paint toolbar. Press "F" to fill circles and triangles, toggled on by default.

Task 1:
To draw lines, press "D" and select the start and end points on the screen. Press the key again to deactivate.
Task 2:
To draw lines, press "L" and select the start and end points on the screen. Press the key again to deactivate.
Task 3:
To draw Circles, press "C" and select the location on the screen. Press the key again to deactivate.
Task 4:
To draw Triangles, press "T" and select the three vertices on the screen. To draw an interpolated triangle, press "V" (and again to cancel) and select the colors in the toolbar before selecting each point, e.g., select blue, then place v0 (vertex), select red, place v1, and finally select green and place v2.
If the respective keys are not pressed again, the shapes will accumulate, allowing the creation of lines and triangles with vertices marked by points.

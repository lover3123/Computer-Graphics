#include <GL/glut.h>   // Provides OpenGL + GLUT functions for windowing and rendering
#include <math.h>      // Required for cos() and sin() → used in circular/hexagon calculations
#include <stdlib.h>    // General utilities (not strictly required here, but safe to include)

// Constant representing full circle (2π radians = 360 degrees)
const double TWO_PI = 6.2831853;

// Initial window dimensions (width and height in pixels)
GLsizei winwidth = 400, winheight = 400;

// Variable to store display list ID (used for efficient rendering)
GLint reghex;

// Class representing a 2D screen point (x, y coordinates)
class screenpt {
public:
    GLint x, y;  // Integer coordinates for vertex positions
};

// Initialization function → runs once before rendering starts
static void init(void)
{
    screenpt hexvertex, circtr;  // hexvertex = each vertex, circtr = center of hexagon
    GLdouble theta;              // Angle (in radians) for each vertex
    GLint k;                     // Loop counter

    // Set center of hexagon at the middle of the window
    circtr.x = winwidth / 2;
    circtr.y = winheight / 2;

    // Set background color to magenta (R=1, G=0, B=1, Alpha=0)
    glClearColor(1.0, 0.0, 1.0, 0.0);

    // Generate one display list and store its ID in reghex
    reghex = glGenLists(1);

    // Start defining the display list (GL_COMPILE → store commands, don't execute yet)
    glNewList(reghex, GL_COMPILE);

    // Set drawing color to yellow (R=1, G=1, B=0)
    glColor3f(1.0, 1.0, 0.0);

    // Begin drawing a filled polygon (hexagon)
    glBegin(GL_POLYGON);

    // Loop to generate 6 vertices → hexagon
    for (k = 0; k < 6; k++)
    {
        // Compute angle for each vertex (divide full circle into 6 equal parts)
        theta = TWO_PI * k / 6;

        // Convert polar coordinates → Cartesian coordinates
        // radius = 120 → controls size of hexagon
        hexvertex.x = circtr.x + 120 * cos(theta);
        hexvertex.y = circtr.y + 120 * sin(theta);

        // Send computed vertex to OpenGL pipeline
        glVertex2i(hexvertex.x, hexvertex.y);
    }

    // End polygon drawing
    glEnd();

    // End display list definition (compiled and stored in GPU memory)
    glEndList();
}

// Display callback function → called whenever window needs redraw
void reghexagon(void)
{
    // Clear screen using background color
    glClear(GL_COLOR_BUFFER_BIT);

    // Execute the precompiled display list → draws hexagon instantly
    glCallList(reghex);

    // Force execution of OpenGL commands (required in single buffering mode)
    glFlush();
}

// Reshape callback → triggered whenever window is resized
void winReshapeFcn(int newwidth, int newheight)
{
    // Define viewport to match new window size
    glViewport(0, 0, (GLsizei)newwidth, (GLsizei)newheight);

    // Switch to projection matrix (controls coordinate system)
    glMatrixMode(GL_PROJECTION);

    // Reset any previous transformations
    glLoadIdentity();

    // Set 2D orthographic projection
    // Maps (0,0) → bottom-left and (newwidth,newheight) → top-right
    gluOrtho2D(0.0, (GLdouble)newwidth, 0.0, (GLdouble)newheight);

    // Clear screen and redraw hexagon with updated dimensions
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(reghex);
    glFlush();
}

// Main function → program entry point
int main(int argc, char **argv)
{
    // Initialize GLUT system
    glutInit(&argc, argv);

    // Set display mode:
    // GLUT_SINGLE → single buffer (no double buffering)
    // GLUT_RGB → color mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set initial window position on screen
    glutInitWindowPosition(100, 100);

    // Set initial window size
    glutInitWindowSize(winwidth, winheight);

    // Create window with title
    glutCreateWindow("reshape_function and display_list example");

    // Call initialization function (builds hexagon display list)
    init();

    // Register display callback function
    glutDisplayFunc(reghexagon);

    // Register reshape callback function
    glutReshapeFunc(winReshapeFcn);

    // Start event loop → keeps window alive and handles events
    glutMainLoop();

    return 0; // End of program
}

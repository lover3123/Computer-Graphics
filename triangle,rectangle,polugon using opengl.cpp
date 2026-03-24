#include <GL/glut.h>   // Includes OpenGL Utility Toolkit → handles window creation, input, and rendering setup

// Initialization function → runs once before rendering starts
void init() {
    
    // Sets the background (clear) color of the window
    // Parameters: Red=1, Green=1, Blue=1 → White background, Alpha=0 (transparency not used here)
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Sets the current drawing color
    // NOTE: (1,0,0) = Red (not blue as comment says)
    glColor3f(1, 0.0, 0.0);

    // Switch to projection matrix → used to define coordinate system
    glMatrixMode(GL_PROJECTION);

    // Reset projection matrix to identity (removes any previous transformations)
    glLoadIdentity();

    // Define a 2D orthographic projection (no perspective)
    // Left=0, Right=500, Bottom=0, Top=500 → creates coordinate system matching window size
    gluOrtho2D(0, 500, 0, 500);
}

// Display function → called whenever the window needs to be drawn
void drawHexagonalLines() {
    
    // Clears the window using the background color set earlier
    glClear(GL_COLOR_BUFFER_BIT);

    // ---------------- HEXAGON ----------------
    // Define 6 vertices of a hexagon manually
    int x1=250, y1=400;  // Top vertex
    int x2=380, y2=325;  // Upper-right
    int x3=380, y3=175;  // Lower-right
    int x4=250, y4=100;  // Bottom
    int x5=120, y5=175;  // Lower-left
    int x6=120, y6=325;  // Upper-left

    // Begin drawing a connected loop of lines
    // GL_LINE_LOOP automatically connects last vertex back to first
    glBegin(GL_LINE_LOOP);

    // Pass vertices to OpenGL in order → forms hexagon outline
    glVertex2i(x1, y1); 
    glVertex2i(x2, y2);
    glVertex2i(x3, y3); 
    glVertex2i(x4, y4);
    glVertex2i(x5, y5); 
    glVertex2i(x6, y6);

    // End line drawing
    glEnd();

    // ---------------- TRIANGLE ----------------
    // Begin drawing a filled triangle
    glBegin(GL_TRIANGLES);

    // Define 3 vertices → OpenGL automatically fills inside
    glVertex2i(10, 410);   // Left-top
    glVertex2i(110, 410);  // Right-top
    glVertex2i(60, 490);   // Top

    glEnd();

    // ---------------- RECTANGLE (QUAD) ----------------
    // Begin drawing a quadrilateral (4-sided filled shape)
    glBegin(GL_QUADS);

    // Define 4 vertices in order (clockwise or counterclockwise)
    glVertex2i(50, 200);   // Bottom-left
    glVertex2i(100, 200);  // Bottom-right
    glVertex2i(100, 300);  // Top-right
    glVertex2i(50, 300);   // Top-left

    glEnd();

    // Forces execution of OpenGL commands immediately (used in single buffering mode)
    glFlush();
}

// Main function → entry point of program
int main(int argc, char** argv) {

    // Initializes GLUT library and processes command-line arguments
    glutInit(&argc, argv);

    // Sets display mode:
    // GLUT_SINGLE → single buffer rendering
    // GLUT_RGB → color mode using RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Sets window size (500 × 500 pixels)
    glutInitWindowSize(500, 500);

    // Sets window position on screen (x=100, y=100)
    glutInitWindowPosition(100, 100);

    // Creates window with given title
    glutCreateWindow("OpenGL Integer Hexagon Lines");

    // Calls initialization function (sets projection, colors, etc.)
    init();

    // Registers display callback function → tells GLUT what to draw
    glutDisplayFunc(drawHexagonalLines);

    // Starts event processing loop → keeps window alive and responsive
    glutMainLoop();

    return 0; // Program ends (though main loop never exits normally)
}

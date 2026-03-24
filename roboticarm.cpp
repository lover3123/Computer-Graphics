#include <GL/glut.h>   // OpenGL + GLUT library for rendering and window handling

// Global variables → store rotation angles for joints
static int shoulder = 0, elbow = 0;

// Initialization function → runs once at start
void init(void)
{
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Use flat shading (single color per face)
    glShadeModel(GL_FLAT);
}

// Display function → renders robotic arm
void display(void)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Save current transformation state (important for hierarchy)
    glPushMatrix();

    // Move entire arm slightly to the right
    glTranslatef(1.0, 0.0, 0.0);

    // Rotate around shoulder joint (Z-axis rotation → 2D rotation in XY plane)
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);

    // Move to center of upper arm
    glTranslatef(1.0, 0.0, 0.0);

    // -------- Upper Arm --------
    glPushMatrix();  // Save transformation before scaling

    // Scale cube → make it rectangular (arm-like shape)
    glScalef(2.0, 0.4, 1.0);

    // Draw wireframe cube (becomes rectangular arm after scaling)
    glutWireCube(1.0);

    glPopMatrix();   // Restore transformation

    // Move to elbow joint position (end of upper arm)
    glTranslatef(1.0, 0.0, 0.0);

    // Rotate around elbow joint
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);

    // Move to center of forearm
    glTranslatef(1.0, 0.0, 0.0);

    // -------- Forearm --------
    glPushMatrix();  // Save transformation

    // Scale cube → second arm segment
    glScalef(2.0, 0.4, 1.0);

    // Draw forearm
    glutWireCube(1.0);

    glPopMatrix();   // Restore transformation

    // Restore original coordinate system
    glPopMatrix();

    // Swap buffers (double buffering → smooth rendering)
    glutSwapBuffers();
}

// Reshape function → handles window resizing
void reshape(int w, int h)
{
    // Define viewport (entire window)
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Switch to projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set perspective projection:
    // 65° field of view, aspect ratio w/h, near=1, far=20
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move camera backward so object is visible
    glTranslatef(0.0, 0.0, -5.0);
}

// Keyboard handler → controls joint rotations
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's': 
            shoulder = (shoulder + 5) % 360;  // Rotate shoulder forward
            glutPostRedisplay();              // Request redraw
            break;

        case 'S': 
            shoulder = (shoulder - 5) % 360;  // Rotate shoulder backward
            glutPostRedisplay();
            break;

        case 'e': 
            elbow = (elbow + 5) % 360;        // Rotate elbow forward
            glutPostRedisplay();
            break;

        case 'E': 
            elbow = (elbow - 5) % 360;        // Rotate elbow backward
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

// Main function → entry point
int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Enable double buffering + RGB color mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set window size
    glutInitWindowSize(500, 500);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create window (title = program name)
    glutCreateWindow(argv[0]);

    // Initialize settings
    init();

    // Register callback functions
    glutDisplayFunc(display);     // Rendering function
    glutReshapeFunc(reshape);     // Resize handling
    glutKeyboardFunc(keyboard);   // Keyboard input

    // Start event loop
    glutMainLoop();

    return 0;
}

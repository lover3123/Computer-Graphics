#include <GL/glut.h>

// Global variables for joint angles
static int shoulder = 0, elbow = 0;

// Initialization function
void init(void)
{
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Use flat shading
    glShadeModel(GL_FLAT);
}

// Display function → draws robotic arm
void display(void)
{
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Save initial transformation state
    glPushMatrix();

    // Move arm slightly right
    glTranslatef(1.0, 0.0, 0.0);

    // Rotate entire arm at shoulder
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);

    // Move to center of upper arm
    glTranslatef(1.0, 0.0, 0.0);

    // -------- Upper Arm --------
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);   // Stretch cube into rectangular arm
    glutWireCube(1.0);         // Draw upper arm
    glPopMatrix();

    // Move to elbow joint
    glTranslatef(1.0, 0.0, 0.0);

    // Rotate forearm at elbow
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);

    // Move to center of forearm
    glTranslatef(1.0, 0.0, 0.0);

    // -------- Forearm --------
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);   // Stretch cube into forearm
    glutWireCube(1.0);         // Draw forearm
    glPopMatrix();

    // Restore original matrix
    glPopMatrix();

    // Swap buffers (double buffering)
    glutSwapBuffers();
}

// Reshape function → handles window resizing
void reshape(int w, int h)
{
    // Set viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Perspective projection
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    // Switch to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move camera backward
    glTranslatef(0.0, 0.0, -5.0);
}

// Keyboard function → controls joints
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's': 
            shoulder = (shoulder + 5) % 360; 
            break;

        case 'S': 
            shoulder = (shoulder - 5) % 360; 
            break;

        case 'e': 
            elbow = (elbow + 5) % 360; 
            break;

        case 'E': 
            elbow = (elbow - 5) % 360; 
            break;

        default:
            break;
    }

    // Redraw scene
    glutPostRedisplay();
}

// Main function
int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Enable double buffering + RGB color
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Window size and position
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // Create window
    glutCreateWindow("Robotic Arm - Shoulder & Elbow");

    // Initialize settings
    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Start event loop
    glutMainLoop();

    return 0;
}

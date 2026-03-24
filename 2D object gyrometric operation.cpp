#include <GL/glut.h>
#include <stdio.h>

// Transformation variables → control movement and scaling
float tx = 0.0f, ty = 0.0f;   // Translation along x and y axes
float s = 1.0f;               // Scaling factor

// Initialization function → sets projection and background
void init() {
    // Set background color (Black)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set projection matrix (defines coordinate system)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define 2D coordinate system from -1 to 1 (centered)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Switch back to modelview matrix for transformations
    glMatrixMode(GL_MODELVIEW);
}

// Display function → draws transformed square
void display() {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Apply transformations
    // NOTE: Order matters (Translate → Scale)
    glTranslatef(tx, ty, 0.0f);   // Move square
    glScalef(s, s, 1.0f);         // Scale square

    // Draw square using 4 vertices
    glBegin(GL_QUADS);

    // Set drawing color to Red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Define square vertices (centered at origin)
    glVertex2f(-0.2f, -0.2f); // Bottom-left
    glVertex2f( 0.2f, -0.2f); // Bottom-right
    glVertex2f( 0.2f,  0.2f); // Top-right
    glVertex2f(-0.2f,  0.2f); // Top-left

    glEnd();

    // Swap buffers → required for double buffering
    glutSwapBuffers();
}

// Keyboard handler → handles normal keys
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'm': 
            s += 0.1f;  // Increase size
            break;

        case 'n': 
            s -= 0.1f;  // Decrease size
            if (s < 0.1f) s = 0.1f; // Prevent disappearing/inversion
            break;

        case ' ': 
            tx = ty = 0.0f; // Reset position
            s = 1.0f;       // Reset scale
            break;
    }

    // Request screen redraw
    glutPostRedisplay();
}

// Special keys handler → arrow keys
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:    
            ty += 0.05f;  // Move up
            break;

        case GLUT_KEY_DOWN:  
            ty -= 0.05f;  // Move down
            break;

        case GLUT_KEY_LEFT:  
            tx -= 0.05f;  // Move left
            break;

        case GLUT_KEY_RIGHT: 
            tx += 0.05f;  // Move right
            break;
    }

    // Request redraw
    glutPostRedisplay();
}

// Main function → entry point
int main(int argc, char** argv) {

    // Initialize GLUT
    glutInit(&argc, argv);

    // Enable double buffering + RGB color
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Set window size
    glutInitWindowSize(600, 600);

    // Create window
    glutCreateWindow("OpenGL: Arrows=Move, m/n=Scale");

    // Call initialization (IMPORTANT FIX)
    init();

    // Register display function
    glutDisplayFunc(display);

    // Register keyboard handlers
    glutKeyboardFunc(keyboard);      // For m, n, space
    glutSpecialFunc(specialKeys);    // For arrow keys

    // Print controls to console
    printf("Controls:\n");
    printf("Arrow Keys - Move\n");
    printf("m - Scale Up\n");
    printf("n - Scale Down\n");
    printf("Space - Reset\n");

    // Start event loop (IMPORTANT FIX)
    glutMainLoop();

    return 0;
}

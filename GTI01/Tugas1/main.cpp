#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0); 

    // 1. GL_LINE_STRIP 
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0); 
        glVertex2f(-0.9, 0.8);
        glVertex2f(-0.7, 0.9);
        glVertex2f(-0.5, 0.7);
        glVertex2f(-0.3, 0.9);
    glEnd();

    // 2. GL_LINE_LOOP 
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.3, 0.9);
        glVertex2f(0.7, 0.9);
        glVertex2f(0.8, 0.6);
        glVertex2f(0.2, 0.6);
    glEnd();

    // 3. GL_TRIANGLE_STRIP 
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0, 0.5, 1.0); 
        glVertex2f(-0.9, 0.4);
        glVertex2f(-0.9, 0.1); 
        glVertex2f(-0.6, 0.4); 
        glVertex2f(-0.6, 0.1); 
        glVertex2f(-0.3, 0.4); 
    glEnd();

    // 4. GL_TRIANGLE_FAN 
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.5, 0.0);
        glVertex2f(0.5, 0.2);  
        glVertex2f(0.3, 0.4);
        glVertex2f(0.7, 0.4);
        glVertex2f(0.8, 0.2);
        glVertex2f(0.7, 0.0);
    glEnd();

    // 5. GL_QUADS 
    glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.0); 
        glVertex2f(-0.8, -0.3);
        glVertex2f(-0.4, -0.3);
        glVertex2f(-0.4, -0.7);
        glVertex2f(-0.8, -0.7);
    glEnd();

    // 6. GL_QUAD_STRIP 
    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0, 0.0, 1.0); 
        glVertex2f(0.2, -0.3); 
        glVertex2f(0.2, -0.7); 
        glVertex2f(0.5, -0.3); 
        glVertex2f(0.5, -0.7);
        glVertex2f(0.8, -0.4); 
        glVertex2f(0.8, -0.8); 
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Implementasi Strip, Fan, dan Quads");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Koordinat sistem
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

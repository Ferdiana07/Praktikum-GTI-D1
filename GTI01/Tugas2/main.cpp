#include <GL/glut.h>

void stickman()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,0); 

    glBegin(GL_QUADS);

    // ===== KEPALA =====
    glVertex2f(-0.05,0.30);
    glVertex2f(0.05,0.30);
    glVertex2f(0.05,0.40);
    glVertex2f(-0.05,0.40);

    // ===== BADAN =====
    glVertex2f(-0.02,0.10);
    glVertex2f(0.02,0.10);
    glVertex2f(0.02,0.30);
    glVertex2f(-0.02,0.30);

    // ===== TANGAN KIRI =====
    glVertex2f(-0.15,0.20);
    glVertex2f(-0.02,0.20);
    glVertex2f(-0.02,0.24);
    glVertex2f(-0.15,0.24);

    // ===== TANGAN KANAN =====
    glVertex2f(0.02,0.20);
    glVertex2f(0.15,0.20);
    glVertex2f(0.15,0.24);
    glVertex2f(0.02,0.24);

    // ===== KAKI KIRI =====
    glVertex2f(-0.06,-0.10);
    glVertex2f(-0.02,-0.10);
    glVertex2f(-0.02,0.10);
    glVertex2f(-0.06,0.10);

    // ===== KAKI KANAN =====
    glVertex2f(0.02,-0.10);
    glVertex2f(0.06,-0.10);
    glVertex2f(0.06,0.10);
    glVertex2f(0.02,0.10);

    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Stickman GL_QUADS");

    glutDisplayFunc(stickman);

    glClearColor(1,1,1,1);

    glutMainLoop();
}

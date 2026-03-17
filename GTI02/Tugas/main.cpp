#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141592653589793

/* ---------- UTIL: LINGKARAN ---------- */
void drawCircle(float r, int segments, int filled)
{
    if(filled) glBegin(GL_POLYGON);
    else       glBegin(GL_LINE_LOOP);

    for(int i=0;i<segments;i++){
        float a = 2*PI*i/segments;
        glVertex2f(r*cos(a), r*sin(a));
    }
    glEnd();
}

/* ---------- BINTANG ---------- */
void drawStars()
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);

    for(int i=0;i<100;i++){
        float x = (rand()%200 - 100)/100.0f;
        float y = (rand()%100)/100.0f + 0.2f;
        glVertex2f(x,y);
    }

    glEnd();
}

/* ---------- BULAN ---------- */
void drawMoon()
{
    glPushMatrix();
    glTranslatef(0.7f,0.7f,0);

    glColor3f(0.95f,0.95f,0.8f);
    drawCircle(0.08f, 50, 1);

    glColor3f(0.02f,0.02f,0.08f);
    glTranslatef(0.03f,0.02f,0);
    drawCircle(0.07f, 50, 1);

    glPopMatrix();
}

/* ---------- AWAN ---------- */
void drawCloud(float x, float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);

    glColor3f(0.8f,0.8f,0.85f);

    drawCircle(0.05f,30,1);
    glTranslatef(0.05f,0,0);
    drawCircle(0.06f,30,1);
    glTranslatef(0.05f,0,0);
    drawCircle(0.05f,30,1);

    glPopMatrix();
}

/* ---------- RODA ---------- */
void drawWheel()
{
    glPushMatrix();

    glColor3f(0.05f,0.05f,0.05f);
    drawCircle(0.085f, 80, 1);

    glColor3f(0.75f,0.75f,0.75f);
    drawCircle(0.05f, 60, 1);

    glColor3f(0.2f,0.2f,0.2f);
    glBegin(GL_LINES);
        glVertex2f(-0.05f,0); glVertex2f(0.05f,0);
        glVertex2f(0,-0.05f); glVertex2f(0,0.05f);
        glVertex2f(-0.035f,-0.035f); glVertex2f(0.035f,0.035f);
        glVertex2f(-0.035f,0.035f);  glVertex2f(0.035f,-0.035f);
    glEnd();

    glPopMatrix();
}

/* ---------- GEDUNG ---------- */
void drawBuilding(float x, float w, float h)
{
    glPushMatrix();
    glTranslatef(x, -0.05f, 0);

    glColor3f(0.15f,0.15f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-w/2,0);
        glVertex2f(w/2,0);
        glVertex2f(w/2,h);
        glVertex2f(-w/2,h);
    glEnd();

    float stepX = w/6;
    float stepY = h/10;

    for(float i=-w/2+stepX; i<w/2-stepX/2; i+=stepX){
        for(float j=stepY; j<h-stepY; j+=stepY){

            if(rand()%2 == 0)
                glColor3f(1.0f,0.9f,0.5f);
            else
                glColor3f(0.2f,0.2f,0.25f);

            glBegin(GL_QUADS);
                glVertex2f(i, j);
                glVertex2f(i+stepX*0.5f, j);
                glVertex2f(i+stepX*0.5f, j+stepY*0.5f);
                glVertex2f(i, j+stepY*0.5f);
            glEnd();
        }
    }

    glPopMatrix();
}

/* ---------- KOTA ---------- */
void drawCity()
{
    drawBuilding(-0.85f, 0.18f, 0.55f);
    drawBuilding(-0.60f, 0.22f, 0.75f);
    drawBuilding(-0.35f, 0.20f, 0.60f);
    drawBuilding(-0.10f, 0.25f, 0.85f);
    drawBuilding( 0.18f, 0.22f, 0.70f);
    drawBuilding( 0.45f, 0.18f, 0.65f);
    drawBuilding( 0.70f, 0.20f, 0.55f);
}

/* ---------- JALAN ---------- */
void drawRoad()
{
    glColor3f(0.12f,0.12f,0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-1,-0.35f);
        glVertex2f( 1,-0.35f);
        glVertex2f( 1,-0.55f);
        glVertex2f(-1,-0.55f);
    glEnd();

    // glow
    glColor3f(0.2f,0.2f,0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1,-0.35f);
        glVertex2f(1,-0.35f);
        glVertex2f(1,-0.30f);
        glVertex2f(-1,-0.30f);
    glEnd();

    glColor3f(1,1,0);
    for(float x=-0.9f; x<0.9f; x+=0.25f){
        glBegin(GL_QUADS);
            glVertex2f(x,-0.44f);
            glVertex2f(x+0.12f,-0.44f);
            glVertex2f(x+0.12f,-0.46f);
            glVertex2f(x,-0.46f);
        glEnd();
    }
}

/* ---------- MOBIL ---------- */
void drawFerrari()
{
    glPushMatrix();
    glColor3f(0.1f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f,-0.08f);
        glVertex2f(0.5f,-0.08f);
        glVertex2f(0.45f,-0.12f);
        glVertex2f(-0.45f,-0.12f);
    glEnd();
    glPopMatrix();

    glColor3f(0.1f, 0.3f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f,-0.02f);
        glVertex2f(0.45f,-0.02f);
        glVertex2f(0.52f,0.06f);
        glVertex2f(0.25f,0.14f);
        glVertex2f(-0.05f,0.14f);
        glVertex2f(-0.30f,0.08f);
        glVertex2f(-0.45f,0.05f);
    glEnd();

    glColor3f(0.6f,0.85f,1);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f,0.14f);
        glVertex2f(0.18f,0.14f);
        glVertex2f(0.10f,0.06f);
        glVertex2f(-0.02f,0.06f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.20f,0.12f);
        glVertex2f(-0.05f,0.14f);
        glVertex2f(-0.02f,0.06f);
        glVertex2f(-0.16f,0.06f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.25f,-0.02f,0);
    drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25f,-0.02f,0);
    drawWheel();
    glPopMatrix();
}

/* ---------- DISPLAY ---------- */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // langit gradasi
    glBegin(GL_QUADS);
        glColor3f(0.02f,0.02f,0.08f);
        glVertex2f(-1,1);
        glVertex2f(1,1);

        glColor3f(0.05f,0.05f,0.2f);
        glVertex2f(1,-0.2f);
        glVertex2f(-1,-0.2f);
    glEnd();

    drawStars();
    drawMoon();
    drawCloud(-0.6f,0.7f);
    drawCloud(0.2f,0.6f);

    drawCity();
    drawRoad();

    glPushMatrix();
    glTranslatef(0,-0.30f,0);
    drawFerrari();
    glPopMatrix();

    glFlush();
}

/* ---------- MAIN ---------- */
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("Ferrari Night City");

    glutDisplayFunc(display);

    glClearColor(0,0,0,1);

    glutMainLoop();
    return 0;
}

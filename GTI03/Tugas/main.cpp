/*
 * Lengan Bergerak + Telapak Tangan & Jari-Jari (v4)
 *
 * +- KONTROL KEYBOARD -----------------------------------------+
 * ¦  s / S  =>  Bahu (shoulder)          +/- 5 derajat         ¦
 * ¦  e / E  =>  Siku (elbow)             +/- 5 derajat         ¦
 * ¦  w / W  =>  Pergelangan (wrist)      +/- 5 derajat         ¦
 * ¦  i / I  =>  Jari Telunjuk (index)    tekuk / buka          ¦
 * ¦  m / M  =>  Jari Tengah  (middle)    tekuk / buka          ¦
 * ¦  r / R  =>  Jari Manis   (ring)      tekuk / buka          ¦
 * ¦  l / L  =>  Jari Kelingking (little) tekuk / buka          ¦
 * ¦  t / T  =>  Ibu Jari     (thumb)     tekuk / buka          ¦
 * ¦  ESC    =>  Keluar                                          ¦
 * +------------------------------------------------------------+
 *
 * Perubahan v3:
 *  [FIX] 4 jari: arah curl dibalik menjadi POSITIF
 *        (rotasi negatif sebelumnya membuat jari menekuk
 *         ke arah yang salah, menjauhi telapak)
 *  [FIX] Sendi PIP (ruas-2) menekuk 1.4x lebih tajam dari MCP
 *        agar gerakan terasa natural seperti jari sungguhan
 *  [NEW] Penghubung pergelangan (wrist connector) antara
 *        lengan bawah dan telapak — mengisi celah visual
 *        dan bertransisi ukuran dari lengan (Y=0.4) ke
 *        telapak (Y=0.72) lewat connector (Y=0.55)
 */

#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0;
static int elbow    = 0;
static int wrist    = 0;

/* curl[0]=telunjuk [1]=tengah [2]=manis [3]=kelingking [4]=ibu jari */
static int curl[5];

#define CLAMP(v,lo,hi) ((v)<(lo)?(lo):((v)>(hi)?(hi):(v)))

/* ------------------------------------------------------------------ */
void init(void)
{
    int i;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    for (i = 0; i < 5; i++) curl[i] = 0;
}

/* ------------------------------------------------------------------ */
/*  Gambar satu jari — 2 ruas (proksimal + medial).
 *
 *  Dipanggil dengan matrix sudah berada di pivot MCP (buku-buku jari).
 *    p1  = panjang ruas proksimal
 *    p2  = panjang ruas medial
 *    th  = ketebalan jari
 *    ang = sudut tekukan MCP (0=lurus, 85=penuh tekuk)
 *
 *  Arah tekuk:
 *    Sumbu rotasi = Y (0,1,0).
 *    Jari memanjang di +X, telapak menghadap viewer (+Z).
 *    Rotasi NEGATIF di Y ? ujung jari berotasi dari +X ke -Z
 *    ? jari mengepal ke arah DEPAN (menjauhi viewer), benar secara anatomi.
 *
 *  Sendi PIP menekuk lebih tajam (× 1.4) agar mirip jari nyata.   */
static void drawFinger(float p1, float p2, float th, int ang)
{
    /* --- Ruas proksimal (MCP ? PIP) --- */
    glRotatef( (GLfloat)ang, 0.0f, 1.0f, 0.0f);  /* tekuk di MCP — sumbu Y, +ang = ke depan */
    glTranslatef(p1 * 0.5f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(p1, th, th * 1.8f);
        glutWireCube(1.0);
    glPopMatrix();

    /* --- Ruas medial (PIP ? ujung) --- */
    glTranslatef(p1 * 0.5f, 0.0f, 0.0f);                    /* ke PIP */
    glRotatef( (GLfloat)ang * 1.4f, 0.0f, 1.0f, 0.0f);      /* PIP lebih tajam */
    glTranslatef(p2 * 0.5f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(p2, th * 0.85f, th * 1.6f);
        glutWireCube(1.0);
    glPopMatrix();
}

/* ------------------------------------------------------------------ */
void display(void)
{
    /*
     * yOff: posisi Y tiap jari dilihat dari pusat telapak.
     *   [0] telunjuk  ? paling atas  (+Y)
     *   [3] kelingking ? paling bawah (-Y, di atas ibu jari)
     */
    float yOff[4] = {  0.27f,  0.09f, -0.09f, -0.27f };

    /* Dimensi ruas-1, ruas-2, ketebalan per jari */
    float p1[4]   = { 0.42f, 0.46f, 0.44f, 0.34f };
    float p2[4]   = { 0.34f, 0.38f, 0.36f, 0.28f };
    float th[4]   = { 0.11f, 0.12f, 0.11f, 0.09f };
    int f;

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();                              /* PUSH-0 */

    /* ============================================================
       LENGAN ATAS  (upper arm)
       Pivot bahu di x = -1 dari pusat, rotasi, kembali ke pusat.
       ============================================================ */
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)shoulder, 0.0f, 0.0f, 1.0f);
    glTranslatef( 1.0f, 0.0f, 0.0f);

    glPushMatrix();
        glScalef(2.0f, 0.4f, 1.0f);
        glutWireCube(1.0);
    glPopMatrix();

    /* ============================================================
       LENGAN BAWAH  (forearm)
       Pivot siku di ujung kanan lengan atas.
       ============================================================ */
    glTranslatef( 1.0f, 0.0f, 0.0f);     /* ke ujung kanan lengan atas */
    glRotatef((GLfloat)elbow, 0.0f, 0.0f, 1.0f);
    glTranslatef( 1.0f, 0.0f, 0.0f);     /* ke pusat lengan bawah      */

    glPushMatrix();
        glScalef(2.0f, 0.4f, 1.0f);
        glutWireCube(1.0);
    glPopMatrix();

    /* ============================================================
       PERGELANGAN  (wrist pivot)
       Pivot tepat di ujung kanan lengan bawah.
       ============================================================ */
    glTranslatef( 1.0f, 0.0f, 0.0f);     /* ujung kanan lengan bawah   */
    glRotatef((GLfloat)wrist, 0.0f, 0.0f, 1.0f);

    /* ============================================================
       PENGHUBUNG PERGELANGAN  (wrist connector)  [BARU v3]
       Box kecil yang menjembatani lengan bawah (Y=0.40) dengan
       telapak tangan (Y=0.72).
       Tinggi connector = 0.55, lebar = 0.46, kedalaman = 0.34.
       Diletakkan langsung setelah pivot pergelangan.
       ============================================================ */
    glTranslatef(0.23f, 0.0f, 0.0f);     /* tengah connector           */
    glPushMatrix();
        glScalef(0.46f, 0.55f, 0.34f);
        glutWireCube(1.0);
    glPopMatrix();

    /* ============================================================
       TELAPAK TANGAN  (palm)
       Ditaruh tepat setelah ujung connector.
         0.23  = setengah lebar connector
         0.45  = setengah lebar telapak (0.90 / 2)
       ============================================================ */
    glTranslatef(0.23f + 0.45f, 0.0f, 0.0f);  /* = 0.68 dari pivot wrist */

    glPushMatrix();
        glScalef(0.90f, 0.72f, 0.36f);
        glutWireCube(1.0);
    glPopMatrix();

    /* ============================================================
       4 JARI  (telunjuk, tengah, manis, kelingking)
       Dimulai dari ujung kanan telapak (x = +0.45 dari pusat).
       ============================================================ */
    for (f = 0; f < 4; f++)
    {
        glPushMatrix();
            glTranslatef(0.45f, yOff[f], 0.0f);
            drawFinger(p1[f], p2[f], th[f], curl[f]);
        glPopMatrix();
    }

    /* ============================================================
       IBU JARI  (thumb) — tetap sama seperti v2
       ---------------------------------------------------------
       Pivot metacarpal di sisi bawah telapak.
       Sudut alami -50° dari sumbu X.
       Curl positif = menekuk ke arah telapak (ke atas).
       Sendi IP menyusul × 0.6 (lebih lambat dari MCP).
       ============================================================ */
    glPushMatrix();                              /* PUSH-T */

        glTranslatef(-0.20f, -0.38f, 0.0f);     /* pivot metacarpal       */
        glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);    /* orientasi alami        */
        glRotatef((GLfloat)curl[4], 0.0f, 0.0f, 1.0f); /* tekuk MCP       */

        /* Ruas proksimal */
        glTranslatef(0.21f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(0.42f, 0.15f, 0.26f);
            glutWireCube(1.0);
        glPopMatrix();

        /* Ruas distal */
        glTranslatef(0.21f, 0.0f, 0.0f);
        glRotatef((GLfloat)curl[4] * 0.6f, 0.0f, 0.0f, 1.0f); /* IP lambat */
        glTranslatef(0.17f, 0.0f, 0.0f);
        glPushMatrix();
            glScalef(0.34f, 0.13f, 0.22f);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();                               /* POP-T */

    glPopMatrix();                               /* POP-0 */
    glutSwapBuffers();
}

/* ------------------------------------------------------------------ */
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
}

/* ------------------------------------------------------------------ */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        /* Bahu */
        case 's': shoulder = (shoulder + 5      ) % 360; break;
        case 'S': shoulder = (shoulder - 5 + 360) % 360; break;

        /* Siku */
        case 'e': elbow    = (elbow    + 5      ) % 360; break;
        case 'E': elbow    = (elbow    - 5 + 360) % 360; break;

        /* Pergelangan */
        case 'w': wrist    = (wrist    + 5      ) % 360; break;
        case 'W': wrist    = (wrist    - 5 + 360) % 360; break;

        /* Jari telunjuk */
        case 'i': curl[0] = CLAMP(curl[0] + 5, 0, 85); break;
        case 'I': curl[0] = CLAMP(curl[0] - 5, 0, 85); break;

        /* Jari tengah */
        case 'm': curl[1] = CLAMP(curl[1] + 5, 0, 85); break;
        case 'M': curl[1] = CLAMP(curl[1] - 5, 0, 85); break;

        /* Jari manis */
        case 'r': curl[2] = CLAMP(curl[2] + 5, 0, 85); break;
        case 'R': curl[2] = CLAMP(curl[2] - 5, 0, 85); break;

        /* Jari kelingking */
        case 'l': curl[3] = CLAMP(curl[3] + 5, 0, 85); break;
        case 'L': curl[3] = CLAMP(curl[3] - 5, 0, 85); break;

        /* Ibu jari */
        case 't': curl[4] = CLAMP(curl[4] + 5, 0, 85); break;
        case 'T': curl[4] = CLAMP(curl[4] - 5, 0, 85); break;

        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

/* ------------------------------------------------------------------ */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lengan Bergerak v4 - Mengepal ke Depan");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

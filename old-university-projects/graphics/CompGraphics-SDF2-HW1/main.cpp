#include <GL/glut.h>
#include <math.h>

#define Cosine(azimuth) cos(3.141592 / 180 * (azimuth))
#define Sine(azimuth) sin(3.141592 / 180 * (azimuth))

int azimuth = 0;
int elevation = 0;

GLfloat A[3] = {0.5, 0.5, 0.5};
GLfloat B[3] = {-0.5, 0.5, 0.5};
GLfloat C[3] = {-0.5, -0.5, 0.5};
GLfloat D[3] = {0.5, -0.5, 0.5};
GLfloat E[3] = {0.5, 0.5, -0.5};
GLfloat F[3] = {-0.5, 0.5, -0.5};
GLfloat G[3] = {-0.5, -0.5, -0.5};
GLfloat H[3] = {0.5, -0.5, -0.5};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    double x = -2 * 3.5 * Sine(azimuth) * Cosine(elevation);
    double y = 2 * 3.5 * Sine(elevation);
    double z = 2 * 3.5 * Cosine(azimuth) * Cosine(elevation);
    gluLookAt(x, y, z, 0, 0, 0, 0, Cosine(elevation), 0);

    glBegin(GL_QUADS);
    glColor3f(0.25, 0.0, 0.85);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
  
    glColor3f(0.2, 0.5, 0.0);
    glVertex3fv(F);
    glVertex3fv(E);
    glVertex3fv(H);
    glVertex3fv(G);
    
    glColor3f(0.45, 0.25, 0.75);
    glVertex3fv(E);
    glVertex3fv(A);
    glVertex3fv(D);
    glVertex3fv(H);
    
    glColor3f(0.75, 0.5, 0.45);
    glVertex3fv(B);
    glVertex3fv(F);
    glVertex3fv(G);
    glVertex3fv(C);
  
    glColor3f(0.5, 0.35, 0.25);
    glVertex3fv(E);
    glVertex3fv(F);
    glVertex3fv(B);
    glVertex3fv(A);
    
    glColor3f(1.0, 0.3, 0.1);
    glVertex3fv(D);
    glVertex3fv(C);
    glVertex3fv(G);
    glVertex3fv(H);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void keyHandler(int key,int x,int y)
{
    if (key == GLUT_KEY_RIGHT) azimuth += 5;
    else if (key == GLUT_KEY_LEFT) azimuth -= 5;
    else if (key == GLUT_KEY_UP) elevation += 5;
    else if (key == GLUT_KEY_DOWN) elevation -= 5;

    azimuth %= 360;
    elevation %= 360;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 3.5/4, 4*3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SDF2 HW1 - Hikmat Jafarli 150105031");
    
    glutDisplayFunc(display);
    glutSpecialFunc(keyHandler);
    glutMainLoop();
    
    return 0;
}

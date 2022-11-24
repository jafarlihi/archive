#include <GL/freeglut.h>
#include <iostream>

char t;
float angle, x, y, z;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    switch (t) {
        case 'r': case 'R': glRotatef(angle, x, y, z); break;
        case 's': case 'S': glScalef(x, y, z); break;
        case 't': case 'T': glTranslatef(x, y, z); break;
        default: break;
    }
    glutWireCube(20);

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("SDF2 HW");

    glutDisplayFunc(display);

    if (t == 'r' || t == 'R') glutIdleFunc(display);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
    glRotatef(25.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutMainLoopEvent();

    std::cout << "Rotate, scale, or translate? (R/S/T): ";
    std::cin >> t;

    if (t == 'r' || t == 'R') {
        std::cout << "Angle?: "; std::cin >> angle;
        std::cout << "Degree of rotation around x? (0.0-1.0): "; std::cin >> x;
        std::cout << "Degree of rotation around y? (0.0-1.0): "; std::cin >> y;
        std::cout << "Degree of rotation around z? (0.0-1.0): "; std::cin >> z;
    } else if (t == 's' || t == 'S') {
        std::cout << "Scale factor along x? (0.0-1.0): "; std::cin >> x;
        std::cout << "Scale factor along y? (0.0-1.0): "; std::cin >> y;
        std::cout << "Scale factor along z? (0.0-1.0): "; std::cin >> z;
    } else if (t == 't' || t == 'T') {
        std::cout << "Translation vector on x? (0.0-1.0): "; std::cin >> x;
        std::cout << "Translation vector on y? (0.0-1.0): "; std::cin >> y;
        std::cout << "Translation vector on z? (0.0-1.0): "; std::cin >> z;
    }

    if (t == 'r' || t == 'R') glutIdleFunc(display);
    glutDisplayFunc(display);
    glLoadIdentity();
    glutMainLoop();

    return 0;
}

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

void bresenham(int xCenter, int yCenter, int height, int width) {
    int x, y;
    int sig;
    int wSq = width * width;
    int hSq = height * height;

    for (x = 0, y = height, 
            sig = 2 * hSq + wSq * (1 - 2 * height); hSq * x <= wSq * y; x++) {
        glBegin(GL_POINTS);
        glVertex2i(xCenter + x, yCenter + y);
        glVertex2i(xCenter - x, yCenter + y);
        glVertex2i(xCenter + x, yCenter - y);
        glVertex2i(xCenter - x, yCenter - y);
        glEnd();

        if (sig >= 0) {
            sig += (4 * wSq) * (1 - y);
            y--;
        }
        sig += hSq * ((4 * x) + 6);
    }

    for (x = width, y = 0,
            sig = 2 * wSq + hSq * (1 - 2 * width); wSq * y <= hSq * x; y++) {
        glBegin(GL_POINTS);
        glVertex2i(xCenter + x, yCenter + y);
        glVertex2i(xCenter - x, yCenter + y);
        glVertex2i(xCenter + x, yCenter - y);
        glVertex2i(xCenter - x, yCenter - y);
        glEnd();

        if (sig >= 0) {
            sig += (4 * hSq) * (1 - x);
            x--;
        }
        sig += wSq * ((4 * y) + 6);
    }

    glFlush();
}

void display()
{
    printf("Enter height of the ellipse: ");
    int height; std::cin >> height;
    printf("Enter width of the ellipse: ");
    int width; std::cin >> width;

    printf("Enter center x coordinate of the circle: ");
    int xCenter; std::cin >> xCenter;
    printf("Enter center y coordinate of the circle: ");
    int yCenter; std::cin >> yCenter;

    glClear(GL_COLOR_BUFFER_BIT);
    bresenham(xCenter, yCenter, height, width);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Hikmat Jafarli - CompGraphics SDF2");

    glClearColor(0.0, 0.0, 0.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(0, 400, 0, 400);

    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

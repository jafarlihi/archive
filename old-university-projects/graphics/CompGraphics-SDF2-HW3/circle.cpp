#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

int xCenter, yCenter;

void fillPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xCenter + x, yCenter + y);
    glVertex2i(xCenter + x, yCenter - y);
    glVertex2i(xCenter + y, yCenter + x);
    glVertex2i(xCenter + y, yCenter - x);
    glVertex2i(xCenter - x, yCenter - y);
    glVertex2i(xCenter - y, yCenter - x);
    glVertex2i(xCenter - x, yCenter + y);
    glVertex2i(xCenter - y, yCenter + x);
    glEnd();
}

void bresenham(int radius)
{
    int x=0;
    int k;
    float z = (5.0 / 4.0) - radius;
    
    fillPixel(x, radius);

    while (x < radius) {
        x = x + 1;

        if (z < 0) {
            z = z + 2 * x + 1;
        }
        else {
            radius = radius - 1;
            z = z + 2 * (x - radius) + 1;
        }
        
        fillPixel(x, radius);
    }
  
    glFlush();
}

void display()
{
    printf("Enter radius of the circle: ");
    int radius; std::cin >> radius;

    printf("Enter center x coordinate of the circle: ");
    std::cin >> xCenter;
    printf("Enter center y coordinate of the circle: ");
    std::cin >> yCenter;

    glClear(GL_COLOR_BUFFER_BIT);
    bresenham(radius);
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

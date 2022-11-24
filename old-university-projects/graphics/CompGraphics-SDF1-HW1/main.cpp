// BMU Computer Graphics, 2016-2017-Spring
// SDF1 - HW1

#include <iostream>
#include <GL/glut.h>

void display(char figureType, int section) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
        glVertex2f(0.0, 1.0);
        glVertex2f(0.0, -1.0);

        glVertex2f(1.0, 0.0);
        glVertex2f(-1.0, 0.0);
    glEnd();

    float trianglePoints[4][6] = { {-0.75, 0.25, -0.50, 0.75, -0.25, 0.25}, {0.25, 0.25, 0.50, 0.75, 0.75, 0.25}, {-0.75, -0.75, -0.50, -0.25, -0.25, -0.75}, {0.25, -0.75, 0.5, -0.25, 0.75, -0.75} };
    float rectanglePoints[4][8] = { {-0.75, 0.25, -0.75, 0.75, -0.25, 0.75, -0.25, 0.25}, {0.25, 0.25, 0.25, 0.75, 0.75, 0.75, 0.75, 0.25}, {-0.75, -0.75, -0.75, -0.25, -0.25, -0.25, -0.25, -0.75}, {0.25, -0.75, 0.25, -0.25, 0.75, -0.25, 0.75, -0.75} };
    
    section = section - 1;

    if(figureType == 'T' || figureType == 't') {
        glBegin(GL_TRIANGLES);
            glVertex2f(trianglePoints[section][0], trianglePoints[section][1]);
            glVertex2f(trianglePoints[section][2], trianglePoints[section][3]);
            glVertex2f(trianglePoints[section][4], trianglePoints[section][5]);
        glEnd();
    }

    if(figureType == 'R' || figureType == 'r') {
        glBegin(GL_POLYGON);
            glVertex2f(rectanglePoints[section][0], rectanglePoints[section][1]);
            glVertex2f(rectanglePoints[section][2], rectanglePoints[section][3]);
            glVertex2f(rectanglePoints[section][4], rectanglePoints[section][5]);
            glVertex2f(rectanglePoints[section][6], rectanglePoints[section][7]);
        glEnd();
    }

    glFlush();
}
void caller() {
    char figureType;
    int section;
    
    while(1) {
        std::cout << "Would you like to draw a trinagle or a rectangle? (T/R) ";
        std::cin >> figureType;
   
        std::cout << "Which section of the window would you like to draw the figure at? (1/2/3/4) ";
        std::cin >> section;

        display(figureType, section);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGBA);
    glutCreateWindow("SDF1 HW1 - Hikmat Jafarli 150105031");
    glutDisplayFunc(caller);
    glutMainLoop();
    return 0;
}

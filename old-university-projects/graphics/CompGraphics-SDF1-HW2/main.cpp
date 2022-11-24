// BMU Computer Graphics, 2016-2017-Spring
// SDF1 - HW2

#include <GL/glut.h>

float y1 = -0.05;
float y2 = 0.05;
float y3 = -0.05;
float x1 = -0.05;
float x2 = 0.00;
float x3 = 0.05;

void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();

    glFlush();
}

void keyboardHandler(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            y1 += 0.02;
            y2 += 0.02;
            y3 += 0.02;
            break;
        case GLUT_KEY_DOWN:
            y1 -= 0.02;
            y2 -= 0.02;
            y3 -= 0.02;
            break;
        case GLUT_KEY_LEFT:
            x1 -= 0.02;
            x2 -= 0.02;
            x3 -= 0.02;
            break;
        case GLUT_KEY_RIGHT:
            x1 += 0.02;
            x2 += 0.02;
            x3 += 0.02;
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGBA);
    glutCreateWindow("SDF1 HW2 - Hikmat Jafarli 150105031");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboardHandler);
    glutMainLoop();
    return 0;
}

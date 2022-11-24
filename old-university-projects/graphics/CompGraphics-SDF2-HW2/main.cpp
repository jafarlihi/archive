#include <GL/glut.h>
#include <cstdio>
#include <math.h>
#include <unistd.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0;

void fillPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenham(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    
    signed char const x((dx > 0) - (dx < 0));
    dx = abs(dx) << 1;

    signed char const y((dy > 0) - (dy < 0));
    dy = abs(dy) << 1;

    if (dx >= dy) {
        int err(dy - (dx >> 1));
        while (x0 != x1) {
            if ((err >= 0) && (err || (x > 0))) {
                err -= dx;
                y0 += y;
            }

            err += dy;
            x0 += x;

            usleep(800);
            fillPixel(x0, y0);
        }
    } else {
        int err(dx - (dy >> 1));

        while (y0 != y1) {
            if ((err >= 0) && (err || (y > 0))) {
                err -= dy;
                x0 += x;
            }

            err += dx;
            y0 += y;

            usleep(800);
            fillPixel(x0, y0);
        }
    }
}

void clearDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (xStart + yStart == 0) {
            xStart = x;
            yStart = WINDOW_HEIGHT - y;
            printf("Start coordinates: %u %u\n", xStart, yStart);
            fillPixel(xStart, yStart);
        } else if (xEnd + yEnd == 0) {
            xEnd = x;
            yEnd = WINDOW_HEIGHT - y;
            printf("End coordinates: %u %u\n", xEnd, yEnd);
            fillPixel(xEnd, yEnd);
            bresenham(xStart, yStart, xEnd, yEnd);
        } else {
            xStart = 0; yStart = 0; xEnd = 0; yEnd = 0;
            clearDisplay();
            printf("Program was reset.\n");
        }

        fflush(stdout);
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("SDF2 HW2 - Hikmat Jafarli 150105031");

    glutDisplayFunc(clearDisplay);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WINDOW_WIDTH, 0.0, (GLdouble)WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

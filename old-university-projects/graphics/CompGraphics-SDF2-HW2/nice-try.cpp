#include <GL/glut.h>
#include <cstdio>
#include <vector>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

std::vector<float> startCoordinates = {2.0, 2.0};
std::vector<float> endCoordinates = {2.0, 2.0};

std::vector<float> convertCoordinates(int x, int y) {
    float coordinateX = x / (float) WINDOW_WIDTH * (1.0 - -1.0) + -1.0;
    float coordinateY = (1 - y / (float) WINDOW_HEIGHT) * (1.0 - -1.0) + -1.0;
    std::vector<float> result = {coordinateX, coordinateY};
    return result;
}

void fillPixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void bresenham() {
    float dx = startCoordinates[0] - endCoordinates[0];
    float dy = startCoordinates[1] - endCoordinates[1];
    
    float *major, *minor;
    if (dx >= dy) { major = &dx; minor = &dy; } 
    else { major = &dy; minor = &dx; }

    float fault = *major / 2;

    for (;;) {
        
    }
}

void initDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        std::vector<float> coordinates = convertCoordinates(x, y);

        if (startCoordinates[0] == 2.0) {
            startCoordinates = coordinates;
            printf("startCoordinates: %.3f %.3f\n", startCoordinates[0], startCoordinates[1]); 
        } else if (endCoordinates[0] == 2.0) {
            endCoordinates = coordinates;
            printf("endCoordinates: %.3f %.3f\n", endCoordinates[0], endCoordinates[1]);
            bresenham(); 
        } else {
            startCoordinates = {2.0, 2.0}; endCoordinates = {2.0, 2.0};
            initDisplay();
            printf("Program was reset.\n");
        }

        fflush(stdout);
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE || GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("SDF2 HW2 - Hikmat Jafarli 150105031");
    
    glutDisplayFunc(initDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

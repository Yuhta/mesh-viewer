#include "viewer.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
#define rad(deg) ((deg) * PI / 180)

/* length step and angle step */
#define LS 1
#define AS 5

static GLfloat * vertices;
static GLuint * indices;
static unsigned indicesSize;

/* distance and angles */
static GLfloat r = 5, xa = 0, ya = 0;

static GLfloat coordinateSize = 1;

static int init(const SComplex * c)
{
    unsigned i;

    vertices = calloc(3 * c->dim[0], sizeof(GLfloat));
    if (vertices == NULL) return 2;
    for (i = 0; i < c->dim[0]; ++i)
    {
        vertices[3*i] = c->e[0][i].x;
        vertices[3*i+1] = c->e[0][i].y;
        vertices[3*i+2] = c->e[0][i].z;
    }

    indicesSize = 3 * c->dim[2];
    indices = calloc(indicesSize, sizeof(GLuint));
    if (indices == NULL) return 2;
    for (i = 0; i < c->dim[2]; ++i)
    {
        indices[3*i] = c->e[2][i].a;
        indices[3*i+1] = c->e[2][i].b;
        indices[3*i+2] = c->e[2][i].c;
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    return 0;
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0, 0, -r);
    glRotatef(xa, 1, 0, 0);
    glRotatef(ya, 0, 1, 0);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(coordinateSize, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, coordinateSize, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, coordinateSize);
    glEnd();

    glColor3f(1, 1, 1);
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, indices);

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        case 'j':
            xa += AS;
            if (xa > 360) xa -= 360;
            glutPostRedisplay();
            break;
        case 'k':
            xa -= AS;
            if (xa < 0 ) xa += 360;
            glutPostRedisplay();
            break;
        case 'h':
            ya -= AS;
            if (ya < 0 ) ya += 360;
            glutPostRedisplay();
            break;
        case 'l':
            ya += AS;
            if (ya > 360 ) ya -= 360;
            glutPostRedisplay();
            break;
        case '+':
            if (r-LS > 0) r -= LS;
            glutPostRedisplay();
            break;
        case '-':
            r += LS;
            glutPostRedisplay();
            break;
        case '>':
            coordinateSize *= 2;
            glutPostRedisplay();
            break;
        case '<':
            coordinateSize /= 2;
            glutPostRedisplay();
            break;
    }
}

void view(int * argc, char ** argv, const SComplex * c)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600); 
    glutCreateWindow("Mesh Viewer");
    init(c);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

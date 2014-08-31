#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "GlutBackend.h"

static Callbacks *calls = NULL;

static void keyboardFunc(unsigned char key, int x, int y){
	calls->keyboardFunc(key, x, y);
}

static void specialKeyboard(int key, int x, int y){
	calls->specialKeyboard(key, x, y);
}

static void display(){
	calls->display();
}

static void idleDisp(){
	calls->idleDisp();
}

static void  initCalls(){
	glutDisplayFunc(display);
	glutIdleFunc(idleDisp);
	glutSpecialFunc(specialKeyboard);
}

void glutBackendInit(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

}

bool glutBackendWindow(unsigned int width, unsigned int height, const char* pTitle){
	glutInitWindowSize(width, height);
    glutInitWindowPosition(300, 300);	
    glutCreateWindow(pTitle);

	GLenum res = glewInit();
	if (res != GLEW_OK){
		fprintf(stderr, "Error Glew: %s \n", glewGetErrorString(res));
		getchar();
		return false;
	}

	return true;
}

void glutBackendRun(Callbacks *callbs){
	if (!callbs){
		printf("Fail in callbacks");
		return;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	calls=callbs;
	initCalls();
	glutMainLoop();
}
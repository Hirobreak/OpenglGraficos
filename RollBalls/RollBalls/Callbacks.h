#ifndef CALLBACKS_H
#define CALLBACKS_H

class Callbacks{
public:
	virtual void keyboardFunc(unsigned char key, int x, int y) = 0;
	
	virtual void specialKeyboard(int key, int x, int y) = 0;

	virtual void display() = 0;
	
	virtual void idleDisp() = 0;
};

#endif
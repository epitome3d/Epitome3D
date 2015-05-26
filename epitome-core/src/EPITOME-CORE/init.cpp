#include "init.h"

void EPITOME::Initialize(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
}

void EPITOME::Exit()
{
	EPITOME::System::Exit();
}

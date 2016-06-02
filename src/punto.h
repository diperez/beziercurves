#pragma comment (lib, "lib/glut32.lib")
#include "glut.h"
class punto
{
	public:
		float vx;
		float vy;
		float vz;
		bool move;
		punto();
		float GlutToOpenglx(float x);
		float GlutToOpengly(float y);
		int OpenglToGlutx(float x);
		int OpenglToGluty(float y);
		void Draw();
};
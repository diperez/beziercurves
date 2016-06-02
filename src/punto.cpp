#include "punto.h"
#include <stdio.h>
punto::punto()
{
	punto::vx=0.0;
	punto::vy=0.0;
	punto::vz=0.0;
	punto::move=false;
}
float punto::GlutToOpenglx(float x)
{
		int auxx=glutGet(GLUT_WINDOW_WIDTH)>>1;
		//printf("%d\n",auxx);
		x=(x/auxx) - 1;
		//x = (float)(2*x-(glutGet(GLUT_WINDOW_WIDTH)-1) )/(glutGet(GLUT_WINDOW_WIDTH)-1);
		return x;
}

float punto::GlutToOpengly(float y)
{
		int auxy=glutGet(GLUT_WINDOW_HEIGHT)>>1;
		y=((y/auxy)-1)*-1;
		//y= (float)((glutGet(GLUT_WINDOW_HEIGHT)-1)-2*y)/(glutGet(GLUT_WINDOW_HEIGHT)-1);
		return y;
}
int punto::OpenglToGlutx(float x)
{
		int auxx=glutGet(GLUT_WINDOW_WIDTH)>>1;
		int X;
		X = (int)((x*auxx) + auxx);
		return X;
}
int punto::OpenglToGluty(float y)
{
		int auxy=glutGet(GLUT_WINDOW_HEIGHT)>>1;
		int Y;
		Y = (int)(-1*(y*auxy)+auxy);
		return Y;
}
void punto::Draw()
{
	//int X= OpenglToGlutx(this->vx);
	//int Y= OpenglToGluty(this->vy);
	
	float X=(float)1/glutGet(GLUT_WINDOW_WIDTH);
	float Y=(float)1/glutGet(GLUT_WINDOW_HEIGHT);
	//printf("%f , %f\n",this->vx,this->vy);
	//printf("%f , %f\n",X,Y);
	glBegin (GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
	for(int i=0;i<3;i++)
	{
		glVertex3f (this->vx,this->vy,this->vz);
		glVertex3f (this->vx - X,this->vy - Y,0.0f);
		glVertex3f (this->vx,this->vy -Y,0.0f);
		glVertex3f (this->vx + X,this->vy - Y,0.0f);
		glVertex3f (this->vx - X,this->vy,0.0f);
		glVertex3f (this->vx + X,this->vy,0.0f);
		glVertex3f (this->vx - X,this->vy + Y,0.0f);
		glVertex3f (this->vx,this->vy + Y,0.0f);
		glVertex3f (this->vx + X, this->vy + Y,0.0f);
		X=X+X;
		Y=Y+Y;
	}
	glEnd ();
}
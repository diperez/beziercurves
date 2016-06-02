#include "curva.h"
curva::curva()
{
	curva::min=100000.0;
	curva::relleno=false;
	curva::r=1.0;
	curva::g=1.0;
	curva::b=1.0;
	curva::rc=1.0;
	curva::gc=1.0;
	curva::bc=1.0;
}
void curva::bezier(punto *dest, punto *a, punto *b, float t)
{
	iterlin (dest, a,b,t);
}
void curva::iterlin(punto *dest, punto *a, punto *b, float t)
{
	dest->vx = a->vx + (b->vx - a->vx)*t;
	dest->vy = a->vy + (b->vy - a->vy)*t;
}
void curva::crear_curva(std::vector<punto*> vec)
{
	this->v.clear();
	this->min=1000000.0;
	for(unsigned int i=0;i<vec.size();i++)
	{
		this->p[0][i].vx = vec[i]->vx;
		this->p[0][i].vy = vec[i]->vy;
	}
	unsigned int i=0;
	unsigned int j=0;
	for(float k=0.0;k<=1;k=k+0.005)
	{
		for(i=1;i<vec.size();i++)
		{
			for(j=i;j<vec.size();j++)
			{
				bezier (&this->p[i][j],&this->p[i-1][j-1],&this->p[i-1][j],k);
			}
		}
		punto * aux = new punto();
		aux->vx = this->p[i-1][j-1].vx;
		aux -> vy = this->p[i-1][j-1].vy;
		if(aux->vy < min)
			min =aux->vy;
		this->v.push_back(aux);
		//glVertex3f (g[i-1][j-1].vx,g[i-1][j-1].vy,0.0f);
		//printf();
	}
}
void curva::rellenar(float r, float g, float b)
{
	this->relleno=true;
	this->r = r;
	this ->g=g;
	this->b=b;
}
void curva::cambiar_color(float r, float g, float b)
{
	this->rc=r;
	this ->gc=g;
	this->bc=b;
}
void curva::Draw()
{
	//relleno prueba con quads
	unsigned int i;
	if(this->relleno)
	{
		for(i=0;i<this->v.size()-1;i++)
		{
			glBegin(GL_POLYGON);
			glColor3f(this->r,this->g,this->b);
			glVertex3f(this->v[i+1]->vx,this->min,0.0);
			glVertex3f(this->v[i+1]->vx,this->v[i+1]->vy,0.0);
			glVertex3f(this->v[i]->vx,this->v[i]->vy,0.0);
			glVertex3f(this->v[i]->vx,this->min,0.0);
			glEnd();
		}
	}
	
	glBegin (GL_LINE_STRIP);
	glColor3f(this->rc,this->gc,this->bc);
	for(i=0;i<this->v.size();i++)
	{
		glVertex3f (this->v[i]->vx,this->v[i]->vy,0.0f);
	}
	glEnd();
}
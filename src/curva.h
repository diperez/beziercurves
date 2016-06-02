#include <vector>
#include "punto.h"
using namespace std;
class curva
{
	public:
		float min,r,g,b,rc,gc,bc;
		bool relleno;
		vector<punto*> v;
		punto p [100][100];
		curva();
		void iterlin (punto *dest, punto *a, punto *b, float t);
		void bezier (punto * dest,punto *a, punto *b, float t);
		void crear_curva(vector <punto *>vec);
		void rellenar(float r, float g, float b);
		void cambiar_color(float r, float g, float b);
		void Draw();
	
};
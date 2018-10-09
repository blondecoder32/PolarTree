#define _USE_MATH_DEFINES
#define pi M_PI

#include <iostream>
using namespace std;

#include "PolarTree.h"
#include "Object.h"
int main()
{
	Object a(7*M_PI_4/2, 95, "a"), b( M_PI_2/3, 95, "b"), c(M_PI_2/4, 68, "c" ), d( 25*M_PI_4/4, 47, "d"), e( 27*M_PI_4/4, 44, "e");
	Object g( 17*M_PI_4/4, 33, "g"), h( 9*M_PI_4/2, 48, "h"), q( 3 *M_PI_4/4, 48, "q"), k( 8*M_PI_2/3, 46, "k"), v( 10*M_PI_2/3, 46, "v"), z( 19*M_PI_4/4, 33, "z");
	Object x( 19*M_PI_4/4, 45, "x"), w( 37*M_PI_4/8, 85, "w"), t( 8*M_PI_4/3, 72, "t"), u( 3 * M_PI_4 / 8, 66, "u"), m( 3 *  M_PI_4 / 8, 30, "m"), n( 4 * M_PI_4 / 8, 33, "n");
	Object p( 3 * M_PI_4 / 4, 48, "p"), s( 23 * M_PI_4 / 3, 69, "s"), y( 11  * M_PI_2/3,91, "y" );
	PolarTree T(100, 3);
	T.Insert(&a);
	T.Insert(&w);
	T.Insert(&y);

	T.Insert(&b);
	T.Insert(&c);
	T.Insert(&d);
	T.Insert(&e);
	T.Insert(&g);
	T.Insert(&h);
	T.Insert(&q);
	T.Insert(&k);
	T.Insert(&z);
	T.Insert(&x);
	T.Insert(&v);

	T.Insert(&t);
	T.Insert(&u);
	T.Insert(&m);
	T.Insert(&n);

	T.Insert(&p);
	T.Insert(&s);

	T.Show();

	T.Delete(&d);
	T.Delete(&g);
	T.Delete(&h);

	T.Delete(&x);
	T.Delete(&v);

	T.Show();

	system("pause");
	return 0;
}
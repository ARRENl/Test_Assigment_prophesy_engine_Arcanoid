/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.


    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.


	source:
		vector example

	revision history:
		Jan/01/1999 - Jukka Liimatta - initial revision
*/
#define PRMATH_TYPENAME
#include <prmath/prmath.hpp>
#include <iostream>

using namespace prmath;
using namespace std;


namespace
{

	// simple triangle type for the example

	struct MyTri
	{
		point3f v[3];
		vec3f normal;
		
		void UpdateNormal()
		{
			vec3f s = v[0] - v[1];
			vec3f t = v[0] - v[2];
			normal = Normalize(CrossProduct(s,t));
		}
	};

	point3f Example1()
	{
		point3f a(0.0f,0.0f,0.0f);
		point3f b(2.0f,2.0f,2.0f);
		
		return prmath::Lerp(a,b,0.5f);
	}

	point3f Example2()
	{
		const int count = 20;
		
		int i;

		// initialize array
		point3f array[count];
		for ( i=0; i<count; ++i )
		{
			float v = static_cast<float>(i + 1);
			array[i] = point3f(v,v,v);
		}

		// calculate average of array
		point3f average(0,0,0);
		for ( i=0; i<count; ++i )
			average += array[i];

		return average / static_cast<float>(count);
	}
	
} // namespace


int main()
{

	MyTri tri;

	tri.v[0] = point3f(0,1,2);
	tri.v[1] = point3f(1,0,0);
	tri.v[2] = point3f(2,0,1);

	tri.UpdateNormal();

	point3f lrp = Example1();
	point3f avg = Example2();

	cout << "lerp:    " << lrp.x << "  " << lrp.y << "  " << lrp.z << endl;
	cout << "average: " << avg.x << "  " << avg.y << "  " << avg.z << endl;

}

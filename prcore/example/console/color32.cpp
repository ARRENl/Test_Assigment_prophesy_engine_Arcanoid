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
		color32 example

	revision history:
		Jan/01/1999 - Jukka Liimatta - initial revision
*/
#include <iostream>
#include <prcore/color32.hpp>

using namespace std;
using namespace prcore;


int main()
{

	// create array of colors
	color32 array[20];

	// set array[5] to red
	array[5] = color32(0x00ff0000);

	// access individual color component
	// set color to green, with full alpha intensity
	array[5].b = 0;
	array[5].g = 255;
	array[5].r = 0;
	array[5].a = 255;

	// result
	cout << "color: 0x" << (hex) << array[5] << endl;

}

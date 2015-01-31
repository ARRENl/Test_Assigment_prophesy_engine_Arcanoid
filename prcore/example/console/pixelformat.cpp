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
		PixelFormat example

	revision history:
		Jun/30/1999 - Jukka Liimatta - initial revision
		Aug/24/2001 - Jukka Liimatta - cleanup reporting
*/
#include <iostream>
#include <prcore/prcore.hpp>

using namespace std;
using namespace prcore;


int main()
{

	// palette

	Color32 palette[256];

	// various custom pixelformats

	PixelFormat format0(16,0xff00,0x00ff,palette);
	PixelFormat format1(16,0xff00,0x00ff);
	PixelFormat format2(8,0x0f,0xf0);
	PixelFormat format3(24,0x0000ff,0x00ff00,0xff0000,0x0);

	// stock formats

	PixelFormat format4 = PIXELFORMAT_PALETTE8(palette);
	PixelFormat format5 = PIXELFORMAT_INTENSITY8;
	PixelFormat format6 = PIXELFORMAT_RGB565;
	PixelFormat format7 = PIXELFORMAT_ARGB1555;
	PixelFormat format8 = PIXELFORMAT_ARGB8888;

	// compile report

	const char* report1 = format5.IsIntensity() ? "I8 is intensity format." : "error";
	const char* report2 = format0.IsIndexed() ? "PA88 is indexed format." : "error";
	
	// cout report

	cout << report1 << endl;
	cout << report2 << endl;

}

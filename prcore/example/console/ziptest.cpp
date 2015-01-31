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
		zip example

	revision history:
		Mar/30/2001 - Edmond Cote - initial revision
*/
#include <iostream>
#include <prcore/prcore.hpp>

using namespace std;
using namespace prcore;


static void example()
{

	// FileStream test

	FileStream::SetBasePath( "data.zip/" );

	Bitmap map1("test1.jpg");
	Bitmap map2("test1.png");
  
	// cout information

	cout << map1.GetWidth() << " x " << map1.GetHeight() << endl;
	cout << map2.GetWidth() << " x " << map2.GetHeight() << endl;
}


int main()
{

	try
	{
		example();
	}
	catch (Exception& e)
	{
		cout << "exception: " << e.GetMessage() << endl;
	}

}

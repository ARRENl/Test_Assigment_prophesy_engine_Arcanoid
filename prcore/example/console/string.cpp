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
		String example

	revision history:
		Jan/01/1999 - Jukka Liimatta, Thomas Mannfred Carlsson - initial revision
		Dec/07/2001 - Jukka Liimatta - rewrote the example from scratch
*/
#include <iostream>
#include <prcore/stream.hpp>

using namespace std;


typedef prcore::String MyString;


int main()
{

	// strings can be added..

	MyString a = "a";
	MyString b = "b";
	MyString c = "c";
	cout << "name: " << a + b + c << endl;


	// compared..

	MyString name1("cat is a fluffy animal.");
	MyString name2("dogs are nice.");
	
	if ( name1 != name2 )
		cout << "surprisingly, the string contents do not match.." << endl;
		
	name1 = name2;
	if ( name1 == name2 )
		cout << "..perhaps they can afterall!" << endl;

	
	// indexed..

	cout << "scanning.. ";
	for ( int i=0; i<name1.GetLength(); ++i )
		cout << " " << name1[i];
		
	cout << endl;
}

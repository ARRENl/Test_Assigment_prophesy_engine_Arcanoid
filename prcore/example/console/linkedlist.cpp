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
		LinkedList example

	Revision history:
		Jun/10/1999 - Jukka Liimatta - initial revision
*/
#include <iostream>
#include <prcore/prcore.hpp>

using namespace std;
using namespace prcore;


int main()
{

	// create list

	LinkedList<int> mylist;

	// add integers to the list

	mylist.PushBack(6);
	mylist.PushBack(4);
	mylist.PushBack(2);

	// iteration example

	const LinkedList<int>::Iterator* node = mylist.Begin();
	while ( node )
	{
		int v = *node;
		cout << v << endl;
		node = node->next;
	}

}

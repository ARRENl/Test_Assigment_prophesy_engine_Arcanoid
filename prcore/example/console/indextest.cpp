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
		FileIndex example

	revision history:
		Feb/20/2002 - Francesco Montecuccoli - initial revision
*/
#include <iostream>
#include <prcore/prcore.hpp>

using namespace std;
using namespace prcore;


static void tab(int level, const char* text)
{
	for ( int i=0; i<level; ++i )
		cout << "  ";

	cout << text << endl;
}


static void recurse(const String& folder, int level = 0)
{
	cout << endl;
	tab(level,folder);
	tab(level,"======================");

	// fileindex for current folder
	FileIndex index(folder);

	// files in current folder
	for ( int j=0; j<index.GetFileCount(); ++j )
	{
		tab(level+1,index.GetFileName(j));
	}

	// recurse into subfolders
	for ( int i=0; i<index.GetFolderCount(); ++i )
	{
		recurse(folder+index.GetFolderName(i),level+1);
	}
}


int main()
{
	// enter some nice folder name here
	recurse("./");
}

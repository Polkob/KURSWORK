#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Music.h"

bool ComparisonForListening(AllTracks* a1, AllTracks* a2) 
{
	return a1->listening > a2->listening;;
}

bool ComparisonForTitle(AllTracks* a1, AllTracks* a2)
{
	return a2->title.compare(a1->title) == 1;
}

bool ComparisonForAuthor(AllTracks* a1, AllTracks* a2)
{
	return a2->author.compare(a1->author) == 1;
}


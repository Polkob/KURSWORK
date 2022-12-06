#pragma once
#include <string>

class TopMusic : public MusicCollection
{
public:
	vector<AllTracks*> GetTop();
};

class TopBelarus : public TopMusic
{
public:
	vector<AllTracks*> GetTopBel();
};
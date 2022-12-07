#pragma once
#include <string>

class TopMusic : public MusicCollection
{
public:
	vector<AllTracks*> GetTop();
};

class TopMusicGenre : public TopMusic
{
public:
	vector<AllTracks*> GetTopGenre();
};
class TopBelarus : public TopMusic
{
public:
	vector<AllTracks*> GetTopBel();
};
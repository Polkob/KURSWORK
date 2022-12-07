#pragma once
#include <vector>
#include "Music.h"
#include "Container.h"
#include "Playlist.h"

using namespace std;

class MusicCollection
{
private:
	void SaveToFile();
public:

	vector<AllTracks*> musics;
	my_vector<AllTracks*> playlist;
	vector<AllTracks*> recomendations;
	vector<AllTracks*> box;
	vector<AllTracks*> GetRecomendations();
	my_vector<AllTracks*> GetPlaylist();
	vector<AllTracks*> GetCollection();

	MusicCollection();

	void AddTrack();
	void Add(AllTracks* music);
	void Delete(string title);
	void Search();
	int SearchId();
	void Edit();
	void EditPlaylist();
	void PrintSearch(int index);
	void Sort();
	void GenreSelection();

	friend class AllPlaylist;

};
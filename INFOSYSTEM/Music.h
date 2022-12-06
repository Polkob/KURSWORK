#pragma once
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
class Track
{
public:
	int id;
	string title;
	string author;
	

	Track() {};
	~Track() {};

	Track(int _id, string _title, string author);
	
};


class AllTracks : public Track
{
public:
	string genre;
	int listening;
	int listeningBelarus;

	AllTracks() {};

	~AllTracks() {};

	AllTracks(string _genre, int _id, string _title, string _author, int _listening, int _listBel) : Track(_id, _title, _author) {
		genre = _genre;
		listening = _listening;
		listeningBelarus = _listBel;
	}
	
	void Print();
	//virtual void Sort(vector<MusicGenre>& music);
	//friend class AllPlaylists;
};




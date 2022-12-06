#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <cmath>
#include "Music.h"
#include "MusicCollection.h"
#include "Container.h"
#include "Sort.h"
#include "Top.h"

using namespace std;

void PrintParam()
{
	cout << "\n" << std::setw(10) << std::left << " Номер" << std::setw(20) << std::left
		<< " Название" << std::setw(20)
		<< " Исполнитель" << std::setw(15) << std::left
		<<  " Жанр" << setw(17) << left << " Прослешивания" 
		<< setw(15)<<left<< "Прослушивания в Беларуси" << endl;
}
void AllTracks::Print()
{
	cout << "__________________________________________________________________________________________________________" << "\n";
	cout << "\n "<<std::setw(10) << std::left << id << std::setw(20) << std::left
		<< title << std::setw(20)
		<< author << std::setw(15)<< std::left 
		<<genre<<setw(17)<<left<<listening
		<< setw(15)<<left<< listeningBelarus<< endl;
	cout << "__________________________________________________________________________________________________________" << "\n";
}

MusicCollection::MusicCollection() 
{

	try {
		ifstream f("musics.txt");

		if (!f.is_open() || f.bad()) {
			throw exception("Open error!");
		}

		while (f.good())
		{
			AllTracks* tmp = new AllTracks();
			f >> tmp->id;
			if (!f.good())
				break;

			f.get();

			getline(f, tmp->title);
			getline(f, tmp->author);
			getline(f, tmp->genre);
			f >> tmp->listening;
			f >> tmp->listeningBelarus;

			musics.push_back(tmp);
		}

		f.close();

		ifstream m("musics.txt");

		if (!m.is_open() || m.bad()) {
			throw exception("Open error!");
		}

		while (m.good())
		{
			AllTracks* tmp = new AllTracks();
			m >> tmp->id;
			if (!m.good())
				break;

			m.get();

			getline(m, tmp->title);
			getline(m, tmp->author);
			getline(m, tmp->genre);
			m >> tmp->listening;
			m >> tmp->listeningBelarus;

			box.push_back(tmp);
		}

		m.close();

		f.open("recomendations.txt");

		if (!f.is_open() || f.bad()) {
			throw exception("Open error!");
		}

		while (f.good())
		{
			int id = -1;
			f >> id;

			if (!f.good())
				break;

			for (AllTracks* music : musics)
				if (music->id == id)
					recomendations.push_back(music);
		}
		f.close();

		f.open("Playlist.txt");

		if (!f.is_open() || f.bad()) {
			throw exception("Open error!");
		}

		while (f.good())
		{
			int id = -1;
			f >> id;

			if (!f.good())
				break;

			for (AllTracks* music : musics)
				if (music->id == id)
					playlist.push_back(music);
		}
		f.close();
	}
	catch(exception& ex)
	{
		cout << ex.what();
	}
}

my_vector<AllTracks*> MusicCollection::GetPlaylist()
{
	cout << "\t\t\t\t\t <Плэйлист> \n" << endl;
	return playlist;
}
vector<AllTracks*> MusicCollection::GetCollection()
{
	return musics;
}

vector<AllTracks*> MusicCollection::GetRecomendations()
{ 
	return recomendations;
}

vector<AllTracks*> TopMusic::GetTop()
{
	vector<AllTracks*> m;

	for (AllTracks* music : musics)
		if (music->listening >= 1000000)
			m.push_back(music);
	return m;
}

vector<AllTracks*> TopBelarus::GetTopBel()
{
	vector<AllTracks*> m;

	for (AllTracks* music : musics)
		if (music->listeningBelarus >= 100000)
			m.push_back(music);
	return m;
}

void MusicCollection::Add(AllTracks* music)
{
	int newId = musics.size() + 1;
	music->id = newId;
	musics.push_back(music);

	SaveToFile();
	while (true)
	{
		try
		{
			int answ;
			cout << "Хотите отменить последнее действие?(1 - да/2 - нет): ";

			if (!(cin >> answ) || answ <= 0 || answ > 2)
			{
				throw exception("Неверный ввод, повторите попытку!");
			}
			else if (answ == 1)
			{
				musics = box;
				SaveToFile();
				break;
			}
			else if (answ == 2)
			{
				box.push_back(music);
				break;
			}	
			
		}
		catch (exception& ex)
		{
			cout << ex.what()<<endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
	}

}

void MusicCollection::Delete(string title)
{
	for (Track* f : musics)
	{
		if (!f->title.compare(title))
		{
			auto entity = find(musics.begin(), musics.end(), f);

			if (entity == musics.end())
				return;
			// удаляет диапазон (в частности один элемент как сейчас)
			musics.erase(entity, entity + 1);

		 entity = find(recomendations.begin(), recomendations.end(), f);

			if (entity != recomendations.end())
			recomendations.erase(entity, entity+1);
			
			int temp = f->id;
			
			for (AllTracks* music : playlist)
				if (temp == music->id)
					playlist.remove(music->id);

			SaveToFile();

			return;
		}
	}
}

void MusicCollection::SaveToFile()
{
	ofstream f("musics.txt");

	for (AllTracks* music : musics)
	{
		f << to_string(music->id) << endl;
		f << music->title << endl;
		f << music->author << endl;
		f << music->genre << endl;
		f << music->listening << endl;
		f << music->listeningBelarus << endl;
	}
	f.close();
	 
	f.open("recomendations.txt");
	for (AllTracks* music : recomendations)
		f << music->id << endl;
	f.close();

	f.open("Playlist.txt");
	for (AllTracks* music : playlist)
		f << music->id << endl;
	f.close();
}

void MusicCollection::Search()
{
	int sel=0;

	while (sel != 1 && sel != 2 && sel !=3)
	{
		cout << "Найти по:" << endl
			<< "1. Номеру" << endl
			<< "2. Названию" << endl
			<< "3. Автору" << endl
			<< "\n\n > ";

		rewind(stdin);
		cin.clear();
		cin >> sel;
	}

	if (sel == 1)
	{
		while (true)
		{
			try
			{
				bool BadInput = 1;
				int temp;

				cout << "Введите номер:";
				cin.clear();
				cin.ignore();

				if(!(cin >> temp) || temp < 0 )
					throw exception("Неверный ввод, повторите попытку!");


				for (AllTracks* f : musics)
				{
					if (f->id == temp)
					{ 
						f->Print();
						BadInput = 0;
					}
				}

				if (BadInput)cout << "\nТрека с таким номером не существует." << endl;

				break;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
				cin.clear();
				cin.ignore(100,'\n');
			}
		}
	}

	if (sel == 2)
	{
		bool BadInput = 1;
		string titl;
		cout << "Title:";
		cin.clear();
		cin.ignore();
		getline(cin, titl);

		for (AllTracks* f : musics)
		{
			if (f->title == titl)
			{
				f->Print();
				BadInput = 0;

			}
		}
		if (BadInput)cout << "\nMusic not found" << endl;
	}

	if (sel == 3)
	{
		bool BadInput = 1;
		string auth;
		cout << "Author:";
		cin.clear();
		cin.ignore();
		getline(cin, auth);

		for (AllTracks* f : musics)
		{
			if (f->author == auth)
			{
				f->Print();
				BadInput = 0;

			}
		}

		if (BadInput)cout << "\nMusic not found" << endl;
	}

}

int MusicCollection::SearchId()
{


	int number = 0;
	bool fail = false;

	cout << "Введите номер записи: ";
	cin >> number;
	cin.ignore();

	if (number < 1 || number > musics.size()) {
		cout << endl << "Запись не найдена..." << endl;

		return -1;
	}
	else musics[number - 1]->Print();


	return number - 1;
}

void MusicCollection::Edit() {
	
	cout << "\n\n\t\t[ Editing record ]\n\n";

	int id = SearchId();
	//vector<AllTracks*> temp = musics;

	if (id == -1)
	{
		return;
	}
	if (id == -2) {
		return;
	}

	string titl;
	string auth;
	string genr;
	int list;
	int listbel;
    int InputFlag=1;
	//musics=box;

	while(InputFlag=1)
	{
			int sel = 0;
			while (sel != 1 && sel != 2 && sel != 3 && sel != 4 && sel != 5)
			{
				cout << "Изменить:" << endl
					<< "1. Название." << endl
					<< "2. Автора." << endl
					<< "3. Жанр." << endl
					<< "4. Прослушивания в мире." << endl
					<< "5. Прослушивания в Беларуси." << endl
					<< "\n\n > ";

				rewind(stdin);
				cin.clear();
				cin >> sel;
			}

			if (sel == 1)
			{
				cout << "Введите название изменяемого трека: ";
				cin.clear();
				cin.ignore();
				getline(cin, titl);
				if (titl.size() > 0)
					musics[id]->title = titl;
				cout << endl;
				SaveToFile();
			}

			if (sel == 2)
			{
				cout << "Введите автора изменяемого трека: ";
				cin.clear();
				cin.ignore();
				getline(cin, auth);
				if (auth.size() > 0)
					musics[id]->author = auth;
				cout << endl;
				SaveToFile();
			}

			if (sel == 3)
			{
				cout << "Введите новый жанр трека: ";
				cin.clear();
				cin.ignore();
				getline(cin, genr);
				if (genr.size() > 0)
					musics[id]->genre = genr;
				SaveToFile();
			}
			if (sel == 4)
			{
				while (true)
				{
					try {
						cout << "Добавить новое кол-во прослушиваний во всем мире: ";
						cin.clear();
						cin.ignore();
						if (!(cin >> list) || list<0)
						{
							throw exception("Неверный ввод, попробуйте снова.");
						}
						break;
					}
					catch (exception& ex)
					{
						cout << ex.what() << endl;
						cin.clear();
						cin.ignore(100, '\n');
					}			
				}
				if (list > 0)
					musics[id]->listening = list;
				SaveToFile();
			}
			if (sel == 5)
			{
				while (true)
				{
					try {
						cout << "Добавьте новое кол-во прослушиваний в Беларуси: ";
						cin.clear();
						cin.ignore();
						if (!(cin >> listbel) || listbel < 0)
						{
							throw exception("Неверный ввод, попробуйте снова.");
						}
						break;
					}
					catch (exception& ex)
					{
						cout << ex.what() << endl;
						cin.clear();
						cin.ignore(100, '\n');
					}
				}

				if (listbel > 0)
					musics[id]->genre = listbel;

				SaveToFile();
			}

			cout << "\nЗапись изменена!\n" << endl;


			int answer;
			cout << "Хотите изменить еще что-нибудь?(1 - да / 2 - нет): ";

			cin >> answer;

			if (answer != 1 && answer != 2)
			{
				cout << "Неверный ввод, выход из цикла.";
				InputFlag = false;
				break;
			}
			if (answer == 1)
			{
				InputFlag = 1;
			}
			 if (answer == 2)
			{
				InputFlag = 0;
				break;
			}

		}
		int answ;
		cout << "Хотите отменить изменения?(1 - да/2 - нет): ";
		cin >> answ;

		if (answ == 1)
		{
			musics = box;
			SaveToFile();
		}
		else if (answ == 2)
		{
			box = musics;
		}
	
	
}

void MusicCollection::Sort()
{
	int select=0;
	while (select != 1 && select != 2 && select != 3)
	{
		cout << "Отсортировать по:" << endl
			<< "1. Названию." << endl
			<< "2. Автору." << endl
			<< "3. Прослушиваниям." << endl
			<< "\n\n > ";

		rewind(stdin);
		cin.clear();
		cin >> select;
	}
	if (select == 1)
	{
		
		sort(musics.begin(), musics.end(), ComparisonForTitle);
		
	}
	if (select == 2)
	{

		sort(musics.begin(), musics.end(), ComparisonForAuthor);

	}
	if (select == 3)
	{

		sort(musics.begin(), musics.end(), ComparisonForListening);

	}
}

void PrintMenu()
{
	cout << "\t <Menu>\t\n\n";

	cout << setw(3) << left << "1)" << " Просмотреть список треков.\n";
	cout << setw(3) << left << "2)" << " Добавить трек.\n";
	cout << setw(3) << left << "3)" << " Удалить трек.\n";
	cout << setw(3) << left << "4)" << " Рекомендации.\n";
	cout << setw(3) << left << "5)" << " Топ треков во всем мире.\n";
	cout << setw(3) << left << "6)" << " Топ треков в Беларуси.\n";
	cout << setw(3) << left << "7)" << " Найти трек.\n";
	cout << setw(3) << left << "8)" << " Сортировка.\n";
	cout << setw(3) << left << "9)" << " Просмотреть плейлист.\n";
	cout << setw(3) << left << "10)" << " Изменить трек.\n";

	cout << "\n\n>";
}

int main()
{

	system("chcp 1251");
	system("cls");

	MusicCollection* x = new MusicCollection();

	int code;

	while (true)
	{
		system("cls");

		PrintMenu();

		cin >> code;
		getchar(); 

		fflush(stdin);
		system("cls");
		cout << "\n";

		if (code == 1)
		{
			PrintParam();
			for (AllTracks* f : x->GetCollection())
				f->Print();
		}
		else if (code == 2)
		{
			AllTracks* tmp = new AllTracks();
			cout << "Введите название трека: ";

			getline(cin, tmp->title);

			cout << "Введите автора трека:";
			getline(cin, tmp->author);

			cout << "введите жанр трека: ";
			cin >> tmp->genre;
			
			cout << "Введите кол-во прослушиваний: ";
			cin >> tmp->listening;

			cout << "Введите кол-во прослушиваний в Беларуси: ";
			cin >> tmp->listeningBelarus;

			x->Add(tmp);
		}
		else if (code == 3)
		{
			cout << "Введите название трека: ";
			string title;
			getline(cin, title);

			x->Delete(title);
		}
		else if (code == 4)
		{
			for (AllTracks* music : x->GetRecomendations())
				music->Print();
		}
		else if (code == 5)
		{
			TopMusic* top = new TopMusic();
			for (AllTracks* music : top->GetTop())
				music->Print();

		}
		else if (code == 6)
		{
			TopBelarus* top = new TopBelarus();
			for (AllTracks* music : top->GetTopBel())
				music->Print();
		}
		else if (code == 7)
		{
			

			x->Search();
		}
		else if (code == 8)
		{
			x->Sort();
		}
		else if (code == 9)
		{

			for (AllTracks* music : x->GetPlaylist())
				music->Print();
		}
		else if (code == 10)
		{
			x->Edit();
		}
	
		cout << "\n\nВернуться в меню\n" << endl;
		rewind(stdin);
		getchar();
	}

	return 0;
}
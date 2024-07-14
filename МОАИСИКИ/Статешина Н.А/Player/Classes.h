#pragma once
#include <string>

//Класс пользователя
class User {
private:
	string Name;
	string Password;
	unsigned int phone_number;

public:
	
	//Зарегестрировать пользователя
	User(_Name, _Password, _Phone_number) {
		Name = _Name;
		Password = _Password;
		Phone_number = _Phone_number;
	}

	//Удалить пользователя
	~User(_Name, _Password, _Phone_number) {
		//Найдет пользователя по данным и удалит
	}

	//Найти пользователя по имени
	int Find_Person(_Name) {
		//Если найден такой пользователь
		return 0;
		//Если не найден
		return 1;
	}
};

class Song {
private:
	string Song_name;
	string Singer;
	float Song_time;
	int Hash;              //пускай по индивидуальному хешу хранятся песни
	Album* Album_name;

public:

	//Создает хеш для песни
	int Hash_song(_Song_name, _Singer, _Album_name) {
		//Сложит например все буковки названия песни, альбома и исполнителя
		// и поделит на что-нибудь, вернет хеш
		return Hash;
	}

	//Создать песню
	Song(_Song_name, _Singer, _Album_name) {
		Song_name = _Song_name;
		Singer = _Singer; 
		Album_name = _Album_name;
		Hash = Hash_song(_Song_name, _Singer, _Album_name);
		//И заносит куда-нибудь в базу данных
	}

	//Воспроизвести песню
	bool Play_Song(Hash) {
		//hash потому, что наверное пользователь 
		//будет жать на кнопочку и программа найдет нужный хеш и запустит нужную песню

		//если музыка играет:      
		return true
	    //по умолчанию идет false
	}

	//Удалить песню
	~Song(_Song_name, _Singer, _Album_name) {
		//Получит все параметры, вычислит хеш и удалит по нему песню
	}

	//Пауза
	bool Stop_Song(Hash) {
		//по хешу найдет нужную песню, остановит воспроизведение
		//если музыка не играет:      
		return false
	}

	//Найти по названию
	int Find_Song(Song_name) {
		//Если найдена
		return 0;
		//Если не найдена
		return 1;
	}
};

class Album{
private:
	int* album
	string Album_name;
	string Singer;
	
public:

	//Создать альбом
	Album(_Album_name, _Singer) {
		Album_name = _Album_name;
		Singer = _Singer;
		album = new int[N];
	}

	//Удалить альбом
	~Album() {
		delete[] album;
	}

	//Добавить песню в альбом
	int Add_To_Album(int* album, _Song_name) {
		//добавляет песню в массив данного альбома
		//при успешном добавлении
		return 0
		//при ошибке добавления
		return 1
	}

	//Удалить песню из альбома
	int Del_from_Album(int* album, _Song_name) {
		//удаляет песню из массива данного альбома
		//при успешном удалении
		return 0
		//при ошибке удаления
		return 1
	}

	//Найти по названию
	int Find_Album(_Album_name) {
		//Если найден
		return 0;
		//Если не найден
		return 1;
	}

	//Воспроизвести альбом
	bool Play_Album(Hash) {
		//Hash первой песни в этом альбоме
		//если музыка играет:      
		return true
	    //по умолчанию идет false
	}
};

class Playlist {
private:
	string Playlist_name;
	int* playlist;

public:

	//Создать плейлист
	Playlist(Playlist_name) {
		Playlist_name = _Playlist_name;
		playlist = new int[N];
	}

	//Удалить плейлист
	~Playlist() {
		delete[] playlist;
	}

	//Добавить песню в плейлист
	int Add_To_Playlist(int* playlist, _Song_name) {
		//добавляет песню в массив данного плейлиста
		//при успешном добавлении
		return 0
		//при ошибке добавления
		return 1
	}
		
	//Удалить песню из плейлиста 
	int Del_from_Playlist(int* playlist, _Song_name) {
		//удаляет песню из массива данного плейлиста
		//при успешном удалении
		return 0
		//при ошибке удаления
		return 1
	}

	//Воспроизвести плейлист
	bool Play_Playlist(Hash) {
		//Hash первой песни в этом плейлисте
		//если музыка играет:      
		return true
		//по умолчанию идет false
	}

	//Найти по названию
	int Find_Playlist(Playlist_name) {
		//Если найден
		return 0;
		//Если не найден
		return 1;
	}
};

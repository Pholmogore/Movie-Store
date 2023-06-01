#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Movie
{
private:

	string name;
	string director;
	string genre;
	short rating;
	short price;

public:

	Movie();

	Movie(string name, string director, string genre, short rating, short price);

	string Get_Name()
	{
		return name;
	}

	string Get_Director()
	{
		return director;
	}

	string Get_Genre()
	{
		return genre;
	}

	short Get_Rating()
	{
		return rating;
	}

	short Get_Price()
	{
		return price;
	}

	void Get_Information();

	void Set_Name(const string name)
	{
		this->name = name;
	}

	void Set_Director(const string director)
	{
		this->director = director;
	}

	void Set_Genre(const string genre)
	{
		this->genre = genre;
	}

	void Set_Rating(const short rating)
	{
		this->rating = rating;
	}

	void Set_Price(const short price)
	{
		this->price = price;
	}

	void Set_Information();

	bool Search_By_Name(const string& desired_name);

	bool Search_By_Genre(const string& desired_genre);

	bool Search_By_Director(const string& desired_director);

	void Most_Popular_In_The_Genre(const string& genre, vector <Movie>& assortment);

	bool operator ==(const Movie& object);

	bool Read_From_File(const string& file_name, vector<Movie>& assortment);

	void Save_To_File(const string& file_name, vector<Movie>& assortment);
};
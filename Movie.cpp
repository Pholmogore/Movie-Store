#include "Movie.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using std::cin;
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::exception;

Movie::Movie()
{
	name = "N/A";
	director = "N/A";
	genre = "N/A";
	rating = 0;
	price = 0;
}

Movie::Movie(string name, string director, string genre, short rating, short price)
{
	this->name = name;
	this->director = director;
	this->genre = genre;
	this->rating = rating;
	this->price = price;
}

void Movie::Get_Information()
{
	cout << endl << "Movie title: " << name << endl;
	cout << "Director: " << director << endl;
	cout << "Genre: " << genre << endl;
	cout << "Popularity rating: " << rating << " of 10" << endl;
	cout << "Disc price: " << price << "$" << endl;
}

void Movie::Set_Information()
{
	cout << endl << "Enter movie title: ";
	getline(cin, this->name);

	cout << "Enter the name of the film director: ";

	do
	{
		getline(cin, this->director);

		if (all_of(director.begin(), director.end(), [](char element) { return isalpha(element) || isspace(element); }))
		{
			break;
		}
		else
		{
			cout << endl << "The name can only contain letters! Please try again: ";
		}

	} while (true);

	cout << "Enter the name of the movie genre: ";

	do
	{
		getline(cin, this->genre);

		if (all_of(genre.begin(), genre.end(), isalpha))
		{
			break;
		}
		else
		{
			cout << endl << "Genre name can only contain letters! Please try again: ";
		}

	} while (true);

	cout << "Enter movie popularity rating: ";

	do
	{
		string verification;
		getline(cin, verification);

		if (verification.length() == 1 && isdigit(verification[0]) || verification.length() > 1 && all_of(verification.begin(), verification.end(), isdigit))
		{
			this->rating = stoi(verification);

			if (this->rating >= 1 && this->rating <= 10)
			{
				break;
			}
			else
			{
				cout << endl << "Movie rating cannot be less than one and more than ten! Please try again: ";
			}
		}
		else
		{
			cout << endl << "You have entered an invalid value! Please try again: ";
		}

	} while (true);

	cout << "Enter price per movie disc: ";

	do
	{
		string verification;
		getline(cin, verification);

		if (verification.length() == 1 && isdigit(verification[0]) || verification.length() > 1 && all_of(verification.begin(), verification.end(), isdigit))
		{
			this->price = stoi(verification);

			if (this->price >= 1 && this->price <= 500)
			{
				break;
			}
			else
			{
				cout << endl << "The price for a disk cannot be less than 1$ and more than 500$! Please try again: ";
			}
		}
		else
		{
			cout << endl << "You have entered an invalid value! Please try again: ";
		}

	} while (true);
}

bool Movie::Search_By_Name(const string& desired_name)
{
	if (name == desired_name)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Movie::Search_By_Genre(const string& desired_genre)
{
	if (genre == desired_genre)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Movie::Search_By_Director(const string& desired_director)
{
	if (director == desired_director)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Movie::Most_Popular_In_The_Genre(const string& genre, vector <Movie>& assortment)
{
	Movie temporary;
	short max_rating = 0;

	for (auto& element : assortment)
	{
		if (element.Get_Genre() == genre && element.Get_Rating() > max_rating)
		{
			max_rating = element.Get_Rating();
			temporary = element;
		}
	}

	if (temporary.Get_Rating() != 0)
	{
		cout << endl << "Most popular movie in the genre \"" << genre << "\":" << endl;
		temporary.Get_Information();
	}
	else
	{
		cout << endl << "No movies found in genre \"" << genre << "\"." << endl;
	}
}

bool Movie::operator ==(const Movie& object)
{
	if (this->name == object.name && this->director == object.director && this->genre == object.genre && this->rating == object.rating && this->price == object.price)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Movie::Read_From_File(const string& file_name, vector<Movie>& assortment)
{
	try
	{
		ifstream file(file_name);

		if (file.is_open())
		{
			string name, director, genre, str_rating, str_price;
			short rating, price;

			while (getline(file, name) && getline(file, director) && getline(file, genre) && getline(file, str_rating) && getline(file, str_price))
			{
				try
				{
					rating = stoi(str_rating);
					price = stoi(str_price);

					Movie temporary(name, director, genre, rating, price);
					assortment.push_back(temporary);
				}
				catch (const exception& error)
				{
					cout << endl << "Error reading data from file! Cause: " << error.what() << "!" << endl;

					file.close();
					return false;
				}
			}

			file.close();
			return true;
		}
		else
		{
			throw ifstream::failure("The specified file cannot be opened! Cause");
		}
	}
	catch (const ifstream::failure& error)
	{
		cout << endl << error.what() << "!" << endl;
		return false;
	}
}

void Movie::Save_To_File(const string& file_name, vector<Movie>& assortment)
{
	try
	{
		vector<Movie> existing_movies;

		ifstream file(file_name);

		if (file.is_open())
		{
			string name, director, genre, str_rating, str_price;
			short rating, price;

			while (getline(file, name) && getline(file, director) && getline(file, genre) && getline(file, str_rating) && getline(file, str_price))
			{
				try
				{
					rating = stoi(str_rating);
					price = stoi(str_price);

					Movie temporary(name, director, genre, rating, price);
					existing_movies.push_back(temporary);
				}
				catch (const exception& error)
				{
					cout << endl << "Error reading data from file! Cause: " << error.what() << "!" << endl;
				}
			}

			file.close();
		}
		else
		{
			throw ifstream::failure("The specified file cannot be opened! Cause");
		}

		ofstream saved_file(file_name, ofstream::app);

		if (saved_file.is_open())
		{
			for (auto& new_element : assortment)
			{
				bool already_existing = false;

				for (auto& retained_element : existing_movies)
				{
					if (new_element == retained_element)
					{
						already_existing = true;
						break;
					}
				}

				if (!already_existing)
				{
					saved_file << new_element.Get_Name() << endl;
					saved_file << new_element.Get_Director() << endl;
					saved_file << new_element.Get_Genre() << endl;
					saved_file << new_element.Get_Rating() << endl;
					saved_file << new_element.Get_Price() << endl;
				}
			}

			saved_file.close();

			cout << endl << "Data saved to file: " << file_name << endl;
		}
		else
		{
			throw ifstream::failure("The specified file cannot be opened! Cause");
		}
	}
	catch (ifstream::failure& error)
	{
		cout << endl << error.what() << "!" << endl;
	}
	catch (const ofstream::failure& error)
	{
		cout << endl << error.what() << "!" << endl;
	}
}
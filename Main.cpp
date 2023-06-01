#include "Movie.h"
#include <iostream>

using std::cin;
using std::endl;
using std::cout;

int main()
{
    cout << "Welcome to the movie store!" << endl;

    vector<Movie> assortment;
    short choice = 0;

    do
    {
        cout << endl << "Menu for user interaction with the store:" << endl;
        cout << "1. View an existing movie catalog." << endl;
        cout << "2. Fill up the catalog with new films." << endl;
        cout << "3. Find a movie by title." << endl;
        cout << "4. Find a movie by director." << endl;
        cout << "5. Find a movie by genre." << endl;
        cout << "6. Find the most popular movie in the genre." << endl;
        cout << "7. Save the current directory." << endl;
        cout << "8. Exit." << endl;

        string verification;
        cout << endl << "Enter the number that matches your requirements to continue: ";
        getline(cin, verification);

        if (verification.length() == 1 && isdigit(verification[0]))
        {
            choice = stoi(verification);

            if (choice >= 1 && choice <= 8)
            {
                switch (choice)
                {
                case 1:
                {
                    const std::string file_name = "Film catalog.txt";

                    if (assortment.empty())
                    {
                        Movie temporary;
                        if (temporary.Read_From_File(file_name, assortment))
                        {
                            for (auto& element : assortment)
                            {
                                element.Get_Information();
                            }
                        }
                        else
                        {
                            cout << endl << "Failed to access existing directory, probably empty!" << endl;
                        }
                    }
                    else
                    {
                        for (auto& element : assortment)
                        {
                            element.Get_Information();
                        }
                    }

                    break;
                }
                case 2:
                {
                    short amount;
                    cout << endl << "Enter the number of films you want to add to the catalog: ";

                    do
                    {
                        string verification;
                        getline(cin, verification);

                        if (verification.length() == 1 && isdigit(verification[0]))
                        {
                            amount = stoi(verification);

                            if (amount < 1)
                            {
                                cout << endl << "You cannot add less than one movie to the catalog! Please try again: ";
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            cout << endl << "You have entered an invalid value! Please try again: ";
                        }

                    } while (true);

                    for (short i = 0; i < amount; i++)
                    {
                        Movie temporary;
                        temporary.Set_Information();
                        assortment.push_back(temporary);
                    }

                    break;
                }
                case 3:
                {
                    if (assortment.empty())
                    {
                        cout << endl << "The movie catalog is empty! Please fill it up first!" << endl;
                        break;
                    }

                    string desired_name;
                    cout << endl << "Enter the title of the movie you want to search for: ";
                    getline(cin, desired_name);

                    bool found = false;

                    for (auto& element : assortment)
                    {
                        if (element.Search_By_Name(desired_name))
                        {
                            element.Get_Information();
                            found = true;
                        }
                    }

                    if (found == false)
                    {
                        cout << endl << "No movies found with the title \"" << desired_name << "\"." << endl;
                    }

                    break;
                }
                case 4:
                {
                    if (assortment.empty())
                    {
                        cout << endl << "The movie catalog is empty! Please fill it up first!" << endl;
                        break;
                    }

                    string desired_director;
                    cout << endl << "Enter the name of the director whose film you want to search for: ";
                    getline(cin, desired_director);

                    bool found = false;

                    for (auto& element : assortment)
                    {
                        if (element.Search_By_Director(desired_director))
                        {
                            element.Get_Information();
                            found = true;
                        }
                    }

                    if (found == false)
                    {
                        cout << endl << "No movies found directed by \"" << desired_director << "\"." << endl;
                    }

                    break;
                }
                case 5:
                {
                    if (assortment.empty())
                    {
                        cout << endl << "The movie catalog is empty! Please fill it up first!" << endl;
                        break;
                    }

                    string desired_genre;
                    cout << endl << "Enter the name of the genre in which you want to watch the movie: ";
                    getline(cin, desired_genre);

                    bool found = false;

                    for (auto& element : assortment)
                    {
                        if (element.Search_By_Genre(desired_genre))
                        {
                            element.Get_Information();
                            found = true;
                        }
                    }

                    if (found == false)
                    {
                        cout << endl << "No movies found in genre \"" << desired_genre << "\"." << endl;
                    }

                    break;
                }
                case 6:
                {
                    if (assortment.empty())
                    {
                        cout << endl << "The movie catalog is empty! Please fill it up first!" << endl;
                        break;
                    }

                    string desired_genre;
                    cout << endl << "Enter the genre you want to find the most popular movie in: ";
                    getline(cin, desired_genre);

                    Movie temporary;
                    temporary.Most_Popular_In_The_Genre(desired_genre, assortment);

                    break;
                }
                case 7:
                {
                    const std::string file_name = "Film catalog.txt";

                    Movie temporary;
                    temporary.Save_To_File(file_name, assortment);

                    break;
                }
                case 8:
                {
                    cout << endl << "You left the movie store!" << endl;

                    break;
                }
                }
            }
            else
            {
                cout << "There is no such item on the menu! Please try again!" << endl;
            }
        }
        else
        {
            cout << "You have entered an invalid value! Please try again!" << endl;
        }

    } while (choice != 8);

    system("Pause");

    return 0;
}
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <emscripten/emscripten.h>

using namespace std;

string exportFile = "WeeklyPlan.txt";
fstream file;
vector<string> lines;
string line;
int HomeSelection;
int choice;
string add;
fstream plan;
int dayNum;
string day = "Monday: ";

void ViewMeals();
void CreatePlan();
void AddMeal();
void clearScreen();

void home()
{
    HomeSelection = 0;
    choice = 0;
    while (HomeSelection != 1 && HomeSelection != 2 && HomeSelection != 3)
    {
        cout << "1. Create meal plan" << endl << "2. Add meal" << endl << "3. View meals" << endl;
        cin >> HomeSelection;
        if(HomeSelection == 1)
    {
        clearScreen();
        CreatePlan();
    }

    else if (HomeSelection == 2)
    {
        clearScreen();
        AddMeal();
    }

    else if (HomeSelection == 3)
    {
        clearScreen();
        ViewMeals();
    }
    }
}

void dayChange()
{
    if (dayNum == 0)
    {
        day = "Monday: ";
    }
    if (dayNum == 1)
    {
        day = "Tuesday: ";
    }
    if (dayNum == 2)
    {
        day = "Wednesday: ";
    }
    if (dayNum == 3)
    {
        day = "Thursday: ";
    }
    if (dayNum == 4)
    {
        day = "Friday: ";
    }
    if (dayNum == 5)
    {
        day = "Saturday: ";
    }
    if (dayNum == 6)
    {
        day = "Sunday: ";
    }
}


void rng()
{
    random_device rd;
    mt19937 gen(rd());
    shuffle(lines.begin(), lines.end(), gen);

    for (int i = 0; i < 7; ++i && ++dayNum) 
    {
        dayChange();
        cout << i << ". " << day << lines[i] << endl;
        plan << i << ". " << day << lines[i] << endl;
        
    }
    
}

void PlanOptions()
{
    dayNum = 0;
    cout << endl << "Enter 1 to edit..." << endl;
    cout << "Enter 2 to export..." << endl;
    cin >> choice;
    if (choice == 1)
        {
            plan.close();
            plan.open("WeeklyPlan.txt", ios::out);
            int edit;
            string change;
            plan.clear();
            cout << "Which would you like to edit?" << endl;
            cin >> edit;
            cout << "What would you like to change " << lines[edit] << " to? ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, change);
            cout << endl;
            lines[edit] = change;
            clearScreen();
            for (int i = 0; i < 7; ++i && ++dayNum) 
            {
                dayChange();
                cout << i << ". " << day << lines[i] << endl;
                plan << i << ". " << day << lines[i] << endl;
            }
        PlanOptions();
        } 

        else if (choice == 2)
        {
            plan.close();
            #ifdef _WIN32
                system(("start " + exportFile).c_str());
            #elif __APPLE__
                system(("open " + filename).c_str());
            #elif __linux__
                system(("xdg-open " + filename).c_str());
            #else
                cerr << "Unsupported OS " << endl;
            #endif
            emscripten_run_script("setTimeout(() => location.reload();");
        }
}

void CreatePlan()
{
    ifstream file("MealsFile.txt");
        
        plan.open("WeeklyPlan.txt", ios::out);

        if(!file)
        {
            cerr << "ERROR: Could not open MealsFile" << endl;
        }

        if(!plan)
        {
            cerr << "ERROR: Could not open WeeklyPlan" << endl;
        }

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();
        
        

        if (lines.empty())
        {
            cout << "The file is empty" << endl;
        }
    
        rng();

        
        PlanOptions();
        
}

void AddMeal()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (add != "exit")
    { 
        cout << "Enter meal: ";
        
        getline(cin, add);

        if (!add.empty() && add != "exit")
        {
            file << add << "\n";
            cout << "Meal added succesfully" << endl;
        }
    }

    file.close();
    emscripten_run_script("setTimeout(() => location.reload();");
    
}

void ViewMeals()
{
    fstream file;
        file.open("MealsFile.txt", ios::in | ios::out | ios::app);
        
        if(!file)
        {
            cerr << "ERROR: Could not open file" << endl;
        }


        cout << "Your current saved meals are:" << endl << endl;
        string line;
        while (getline(file, line)) 
        {
            cout << line << endl;
        }

        while (choice != 1 && choice != 2)
        {
            cout << endl << "1. Exit" << endl;
            cin >> choice;
            if (choice == 1)
            {
                emscripten_run_script("setTimeout(() => location.reload();");
            }

    }

    file.close();
}

void clearScreen()
{
    system("cls");
}

int main ()
{
    file.open("MealsFile.txt", ios::in | ios::out | ios::app);
    
    home();

    return 0;
}
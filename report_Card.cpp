#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
private:
	string name;
	int roll;
	float english, history, geography, science, maths, average;
public:

	//This function assigns values to all fields. A function is used instead of a constructor because dynamic memory 
	//extension using vector is troublesome with constructors. Otherwise, We will have to create a parameter-less constructor.

	void InsertData(string n, int r, float eng, float his, float geo, float sci, float math)
	{
		name = n;
		roll = r;
		english = eng;
		history = his;
		geography = geo;
		science = sci;
		maths = math;

		average = (english + history + geography + science + maths) / 5;
	}

	int GetRoll()
	{
		return roll;
	}

	void Report()
	{
		cout << "\nSTUDENT REPORT" << endl;
		cout << "Name: " << name << endl;
		cout << "Roll: " << roll << endl;
		cout << "English Marks: " << english << endl;
		cout << "History Marks: " << history << endl;
		cout << "Geography Marks: " << geography << endl;
		cout << "Science Marks: " << science << endl;
		cout << "Maths Marks: " << maths << endl;
		cout << "Average Marks: " << average << endl;
		cout << "GPA: " << average / 10 << endl;
	}
};

//Vector is used instead of an array due to its flexibility in size extension

vector<Student> database;
int databaseSize;

void PrintReport(int roll)
{
	for (int i = 0; i < databaseSize; i++)
		if (database[i].GetRoll() == roll)
		{
			database[i].Report();
			return;
		}

	cout << "\nTHE ENTERED ROLL(" << roll << ") DOES NOT EXIST.\n" << endl;
}

void ResizeDatabase()
{
	database.resize(databaseSize);
}

void ShowStats()
{
	cout << "\nSIZE: " << databaseSize << endl;
	cout << "STUDENT LIST (ROLL): ";

	if (databaseSize == 0)
	{
		cout << "DATABASE IS EMPTY\n" << endl;
		return;
	}

	for (int i = 0; i < databaseSize; i++)
		cout << database[i].GetRoll() + " ";

	cout << "\n" << endl;
}

void Add()
{
	string name;
	int roll;
	float english, history, geography, science, maths;

	cout << "\nPLEASE ENTER THE DETAILS OF THE STUDENT:" << endl;
	cout << "NAME: ";
	cin.ignore();
	getline(cin, name);
	cout << "ROLL: ";
	cin >> roll;
	cout << "MARKS IN ENGLISH, HISTORY, GEOGRAPHY, SCIENCE AND MATHS: ";
	cin >> english >> history >> geography >> science >> maths;
	cout << "\nSTUDENT DATA ADDED TO DATABASE" << endl;

	databaseSize++;
	ResizeDatabase();
	database[databaseSize - 1].InsertData(name, roll, english, history, geography, science, maths);
}

void Delete(int roll)
{
	for (int i = 0; i < databaseSize; i++)
		if (database[i].GetRoll() == roll)
		{
			database.erase(database.begin() + i);
			cout << "\nSTUDENT WITH ROLL " << roll << " HAS BEEN REMOVED FROM THE DATABASE\n" << endl;
			databaseSize--;
			return;
		}

	cout << "\nTHE ENTERED ROLL(" << roll << ") DOES NOT EXIST.\n" << endl;
}

int main()
{
	int choice, roll;

	cout << "STUDENT REPORT DATABASE MANAGEMENT" << endl;
	cout << "==================================" << endl;

	do
	{
		cout << "\n1. ADD NEW STUDENT DATA\n2. DELETE STUDENT DATA\n3. PRINT REPORT\n4. DATABASE STATS\n0. EXIT" << endl;
		cout << "YOUR CHOICE: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			Add();
			break;

		case 2:
			cout << "ROLL: ";
			cin >> roll;
			Delete(roll);
			break;

		case 3:
			cout << "ROLL: ";
			cin >> roll;
			PrintReport(roll);
			break;

		case 4:
			ShowStats();
			break;

		case 0:
			break;

		default:
			cout << "\nINVALID CHOICE\n" << endl;
			break;
		}
	} while (choice);

	return 0;
}

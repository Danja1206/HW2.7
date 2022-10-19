#include <iostream>
#include "Task1.h";

using namespace std;
using namespace Students;

void L123()
{
	Student stud();
	FullName names("Степан", "Иваныч", "Иван");
	Student stud2("Степан", "Иваныч", "Иван");
	StudentsGroup students;
	students.add_Student(stud2);
	cout << students.GetAllInfo() << endl;
	cout << students.GetAllInfo(names) << endl;
	cout << students.GetAverageScore(names) << endl;
	students.serialize("data.bin");
	students.deserialize("data.bin");
}

int main()
{
	setlocale(0, "rus");

	L123();

	system("pause");
	return 0;
}

#pragma once
#include <iostream>
#include <algorithm>
#include <execution>
#include <string>
#include <optional>
#include <time.h>
#include <random>
#include <fstream>

using namespace std;

namespace Students
{
	class FullName
	{
	public:

		FullName(string _name, string _surname, string _patronymic) : name(_name), surname(_surname), patronymic(_patronymic) {};

		friend class Student;
		friend class StudentsGroup;

	private:
		string name, surname;
		optional<string> patronymic;
	};

	class Student
	{
	public:

		Student() : fullName("","","")
		{
			averageScore = 0;
		};
		Student(string _name, string _surname, string _patronymic) : fullName(_name, _surname, _patronymic) 
		{
			marksCount = 8;
			marks = new int[marksCount];
			count = 0;
			add_element();
		};

		void findAverage()
		{
			int Amount = 0;
			for (int i = 0; i < 8; i++)
			{
				Amount += marks[i];
			}
			averageScore = Amount / marksCount;
		}

		void add_element()
		{
			srand(time(0));

			while(count < marksCount)
			{
				marks[count] = 1 + (rand() % (5 - 1 + 1));
				count++;
			}
			findAverage();

		}

		friend class StudentsGroup;

	private:
		FullName fullName;
		int* marks;
		size_t count, marksCount;
		double averageScore;
	};

	class StudentsGroup : Student
	{
	public:

		StudentsGroup()
		{
			groupSize = 32;
			count = 0;
			students = new Student[groupSize];
		}

		void add_Student(Student& stud)
		{
			if (count <= groupSize)
			{
				students[count] = stud;
				count++;
			}
		}

		double GetAverageScore(const FullName& name)
		{
			double out;
			string line;
			for (int i = 0; i < groupSize; i++)
				if (students[i].fullName.surname == name.surname && students[i].fullName.name == name.name)
				{
					line = to_string(i + 1) + ". " + students[i].fullName.name + " " + students[i].fullName.surname + " " + students[i].fullName.patronymic.value_or("");
					if (students[i].fullName.patronymic.has_value() && name.patronymic.has_value())
					{
						if (students[i].fullName.patronymic.value() == name.patronymic.value())
						{
							out = students[i].averageScore;
							break;
						}
					}
					else
					{
						out = students[i].averageScore;
						break;
					}
				}
			cout << line << " - ";
			return out;
		}
		string GetAllInfo(const FullName& name)
		{
			string out;
			string marks;
			for (int i = 0; i < groupSize; i++)
				if (students[i].fullName.surname == name.surname && students[i].fullName.name == name.name)
				{
					if (students[i].fullName.patronymic.has_value() && name.patronymic.has_value())
					{
						if (students[i].fullName.patronymic.value() == name.patronymic.value())
						{
							for (int j = 0; j < students[i].marksCount; j++)
								marks += " " + to_string(students[i].marks[j]);
							out = to_string(i + 1) + ". " + students[i].fullName.name + " " + students[i].fullName.surname + " " + students[i].fullName.patronymic.value_or("");
							break;
						}
					}
					else
					{
						for (int j = 0; j < students[i].marksCount; j++)
							marks += " " + to_string(students[i].marks[j]);
						out = to_string(i + 1) + ". " + students[i].fullName.name + " " + students[i].fullName.surname + " " + students[i].fullName.patronymic.value_or("");
						break;
					}
				}
				else out = "Не найдено";
			return out + marks;
		}

		string GetAllInfo()
		{
			string out;
			for (int i = 0; i < groupSize; i++)
			{
				for (int j = 0; j < students[i].marksCount; j++)
					out += " " + to_string(students[i].marks[j]);
				return to_string(i + 1) + ". " + students[i].fullName.name + " " + students[i].fullName.surname + " " + students[i].fullName.patronymic.value_or("") + out;
			}
		}

		void serialize(string path) {
			ofstream out(path, ios::binary);
			out.write(reinterpret_cast<char*>(students), sizeof(students));
		}

		void deserialize(string path) {
			ifstream in(path, ios::binary);
			in.read(reinterpret_cast<char*>(students), sizeof(students));
		}

	private:
		size_t count, groupSize;
		Student* students;
	};

	class IRepository {
		virtual void Open() = 0; 
		virtual void Save() = 0;
	};
	class IMethods {
	public:
		virtual double GetAverageScore(const FullName& name) = 0;
		virtual string GetAllInfo(const FullName& name) = 0;
		virtual string GetAllInfo() = 0;
	};
}
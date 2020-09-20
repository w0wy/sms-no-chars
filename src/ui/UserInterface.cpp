#include <iostream>
#include <algorithm>

#include "ui/UserInterface.h"

namespace ui
{
	UserInterface::UserInterface(const controller::StudentsController& controller):
		controller_(controller)
	{}
	
	void UserInterface::start()
	{
		showOptions();
	}

	void UserInterface::showOptions()
	{
		uint32_t option;
		do{
			std::cout << "\nChoose option!\n";
			std::cout << "1.Show students\n";
			std::cout << "2.Add student\n";
			std::cout << "3.Show grades of student\n";
			std::cout << "4.Show best student\n";
			std::cout << "5.Show best student at subject\n";
			std::cout << "6.Show worst student\n";
			std::cout << "7.Show worst student at subject\n";
			std::cout << "8.Show failing students\n";
			std::cout << "9.Show failing students at subject\n";
			std::cout << "10.Show students sorted by name\n";
			std::cout << "11.Show students sorted by grades\n";
			std::cout << "12.Show students sorted by subject grades\n";
			std::cout << "0.Exit\n";

			std::cin >> option;
			std::cin.ignore();
			switch (option)
			{
				case 1:
					showStudents();
					break;
				case 2:
					addStudent();
					break;
				case 3:
					showGradesOfStudent();
					break;
				case 4:
					showBestStudent();
					break;
				case 5:
					showBestStudentAtSubject();
					break;
				case 6:
					showWorstStudent();
					break;
				case 7:
					showWorstStudentAtSubject();
					break;
				case 8:
					showFailingStudents();
					break;
				case 9:
					showFailingStudentsAtSubject();
					break;
				case 10:
					showSortedStudents(SortKey::EName);
					break;
				case 11:
					showSortedStudents(SortKey::EGrades);
					break;
				case 12:
				    showSortedStudents(SortKey::ESubjectGrades);
				    break;
				default:
					if(option != 0)
					{
						std::cout << "Option is wrong. Please chose one of the above!";
					}
			};
		} while(option != 0);
	}

	bytes_t UserInterface::enterString()
	{
		bytes_t str;
		while(std::cin.peek() != '\n')
		{
			uint8_t ch;
			std::cin >> ch;
			str.push_back(ch);
			if (std::cin.peek() == 32)
				str.push_back(32);
		}
		std::cin.ignore();
		str.push_back('\0');

		return str;
	}

	uint32_t UserInterface::enterInt()
	{
		uint32_t in;
		std::cin >> in;
		std::cin.ignore();

		return in;
	}

	void UserInterface::addStudent()
	{
		model::Student st;
	
		std::cout << "\nEnter name: ";
		st.setName(enterString());
		
		std::cout << "\nEnter gender: ";
		st.setGender(enterString());

		std::cout << "\nEnter age: ";
		st.setAge(enterInt());

		std::cout << "\nEnter number of subjects: ";
		uint32_t numberOfSubjects = enterInt();

		grades_t gradesMap;
		for (uint32_t iter = 0; iter < numberOfSubjects; iter++)
		{
			bytes_t subj;
			std::cout << "\nEnter subject: ";
			subj = enterString();

			std::cout << "\nEnter number of grades: ";
			uint32_t numberOfGrades = enterInt();

			for (uint32_t sIter = 0; sIter < numberOfGrades; sIter++)
			{
				std::cout << "\nEnter grade: ";
				uint32_t grade = enterInt();
				gradesMap[subj].push_back(grade);
			}
		}
		st.setGrades(gradesMap);

		controller_.addStudent(st);
	}
	void UserInterface::showStudents()
	{
		auto students = controller_.getStudents();
		std::for_each(students.begin(), students.end(),
			[this](const auto& stud) -> void
			{
				this->showStudent(stud);
			});
	}

	void UserInterface::showGradesOfStudent()
	{
		std::cout << "\nPlease enter student name: ";
		model::Student st = controller_.getStudent(enterString());

		grades_t grades = st.getGrades();

		std::cout << "\n";
		showGrades(grades);
		std::cout << "\n";
	}

	void UserInterface::showGrades(const grades_t& grades)
	{
		for (auto it : grades)
		{
			std::cout << "Subject : " << &it.first[0] << ", Grades: ";
			for (auto sIt : it.second)
			{
				std::cout << sIt << " ";
			}
		}
	}

	void UserInterface::showBestStudentAtSubject()
	{
		std::cout << "\nPlease enter subject:";
		bytes_t subject = enterString();
		model::Student st = controller_.getBestStudentAt(subject);

		std::cout << "\n";
		showStudent(st);
		std::cout << "\n";
	}
	
	void UserInterface::showSortedStudents(SortKey key)
	{
		StudentsVec students = controller_.getStudents();
		bytes_t subject;
		auto compareName = [](const auto& lhs, const auto& rhs) -> bool
			{
				return lhs.getName() < rhs.getName();
			};
		auto compareGrades = [](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverage() > rhs.getAverage();
		};
		auto compareSubjectGrades = [&subject](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverageAt(subject) > rhs.getAverageAt(subject);
		};
		switch(key)
		{
			case ui::SortKey::EName:
				std::sort(students.begin(), students.end(), compareName);
				break;
			case ui::SortKey::EGrades:
				std::sort(students.begin(), students.end(), compareGrades);
				break;
			case ui::SortKey::ESubjectGrades:
				std::cout << "\nPlease enter subject:";
				subject = enterString();
				std::sort(students.begin(), students.end(), compareSubjectGrades);
				break;
			default:
				return;
		};

		for (auto i : students)
		{
			std::cout << "\n";
			showStudent(i);
			std::cout << "\n";
		}
	}

	void UserInterface::showStudent(const model::Student& student)
	{
		std::cout << "\n";
		std::cout << "[ Name : " << &student.getName()[0] << ", Age: " << student.getAge() << ", Gender: " << &student.getGender()[0] << ", Subjects and grades :\n";
		grades_t grades = student.getGrades();
		showGrades(grades);
		std::cout << " ]\n";
	}

	void UserInterface::showBestStudent()
	{
		model::Student st = controller_.getBestStudent();

		std::cout << "\n";
		showStudent(st);
		std::cout << "\n";
	}
	void UserInterface::showWorstStudent()
	{
		model::Student st = controller_.getWorstStudent();

		std::cout << "\n";
		showStudent(st);
		std::cout << "\n";
	}
	void UserInterface::showWorstStudentAtSubject()
	{
		std::cout << "\n";
		std::cout << "\nPlease enter subject:";
		bytes_t subject = enterString();
		model::Student st = controller_.getWorstStudentAt(subject);

		std::cout << "\n";
		showStudent(st);
		std::cout << "\n";
	}
	void UserInterface::showFailingStudents()
	{
		StudentsVec failingStudents = controller_.getFailingStudents();

		for (auto i : failingStudents)
		{
			std::cout << "\n";
			showStudent(i);
			std::cout << "\n";
		}
	}
	void UserInterface::showFailingStudentsAtSubject()
	{
		std::cout << "\n";
		std::cout << "\nPlease enter subject:";
		bytes_t subject = enterString();
		StudentsVec failingStudents = controller_.getFailingStudentsAt(subject);

		for (auto i : failingStudents)
		{
			std::cout << "\n";
			showStudent(i);
			std::cout << "\n";
		}
	}
}
#include <iostream>

#include "model/Student.h"
#include "ui/UserInterface.h"
#include "controller/StudentsController.h"

#include <vector>

// how to read and print text to the screen without using any char or string

int main()
{
/*	model::Student st;
	
	std::cout << "\nEnter name: ";
	bytes_t name;
	while(std::cin.peek() != '\n')
	{
		uint8_t ch;
		std::cin >> ch;
		name.push_back(ch);
	}
	std::cin.ignore();
	st.setName(name);
	
	std::cout << "\nEnter gender:";
	bytes_t gender;
	while(std::cin.peek() != '\n')
	{
		uint8_t ch;
		std::cin >> ch;
		gender.push_back(ch);
	}
	std::cin.ignore();
	st.setGender(gender);

	std::cout << "\nEnter age:";
	uint32_t age;
	std::cin >> age;
	std::cin.ignore();
	st.setAge(age);

	std::cout << "\nEnter subject:";
	bytes_t subject;
	while(std::cin.peek() != '\n')
	{
		uint8_t ch;
		std::cin >> ch;
		subject.push_back(ch);
	}
	std::cin.ignore();

	uint32_t numberOfGrades;
	std::cout <<"\nEnter number of grades:";
	std::cin >> numberOfGrades;

	std::vector<uint32_t> grades;
	for (uint32_t i = 0; i < numberOfGrades; i++)
	{
		std::cout << "\nEnter grade:";
		uint32_t grade;
		std::cin >> grade;
		grades.push_back(grade);
	}
	std::cin.ignore();
	grades_t gradesMap;
	gradesMap[subject] = grades;

	st.setGrades(gradesMap);

	std::cout << "\nThis is the data for student you entered:\n";
	std::cout << "Student ; name = " << &st.getName()[0] << ", gender = " << &st.getGender()[0] << ", age = " << st.getAge() << ", grades = \n";
	for (auto i : st.getGrades())
	{
		std::cout << "subject: " << &i.first[0] << ", grades: ";
		for (auto j : i.second)
		{
			std::cout << j << " ";
		}
	}*/

	controller::StudentsController controller;
	ui::UserInterface interface(controller);

	interface.start();

	return 0;
}

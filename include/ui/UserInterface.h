#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include "controller/StudentsController.h"
#include "model/Student.h"

namespace ui
{
	enum class SortKey
	{
		EName,
		EGrades,
		ESubjectGrades
	};

	class UserInterface
	{
	public:
		UserInterface(const controller::StudentsController& controller);
		~UserInterface() = default;

		void start();

	private:
		void showOptions();

		void addStudent();
		void showStudents();
		void showGradesOfStudent();
		void showBestStudent();
		void showBestStudentAtSubject();
		void showWorstStudent();
		void showWorstStudentAtSubject();
		void showFailingStudents();
		void showFailingStudentsAtSubject();
		void showSortedStudents(SortKey key);

		void showStudent(const model::Student& student);
		void showGrades(const grades_t& grades);

		bytes_t enterString();
		uint32_t enterInt(); 

		controller::StudentsController controller_;
	};
}

#endif
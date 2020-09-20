#ifndef _STUDENTS_CONTROLLER_H_
#define _STUDENTS_CONTROLLER_H_

#include <vector>
#include "model/Student.h"

using StudentsVec = std::vector<model::Student>;

namespace controller
{
	class StudentsController
	{
	public:
		StudentsController() = default;
		~StudentsController() = default;

		void setStudents(const StudentsVec& students);
		StudentsVec getStudents();

		void addStudent(const model::Student& student);
		model::Student getStudent(const bytes_t& name);

		model::Student getBestStudent();
		model::Student getBestStudentAt(const bytes_t& subject);

		model::Student getWorstStudent();
		model::Student getWorstStudentAt(const bytes_t& subject);

		StudentsVec getFailingStudents();
		StudentsVec getFailingStudentsAt(const bytes_t& subject);

	private:
		StudentsVec students_;
	};
}

#endif
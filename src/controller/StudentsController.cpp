#include "controller/StudentsController.h"

#include <algorithm>

namespace controller
{
	void StudentsController::setStudents(const StudentsVec& students)
	{
		students_ = students;
	}

	StudentsVec StudentsController::getStudents()
	{
		return students_;
	}

	void StudentsController::addStudent(const model::Student& student)
	{
		auto it = std::find_if(students_.begin(), students_.end(),
			[&student](const auto& stud) -> bool
			{
				return stud.getName() == student.getName();
			});
		if (it == students_.end())
		{
			students_.push_back(student);
		}
	}
	model::Student StudentsController::getStudent(const bytes_t& name)
	{
		auto it = std::find_if(students_.begin(), students_.end(),
			[&name](const auto& stud) -> bool
			{
				return stud.getName() == name;
			});
		if (it != students_.end())
		{
			return *it;
		}

		return model::Student();
	}

	model::Student StudentsController::getBestStudent()
	{
		auto localStudents = students_;

		auto compareAverage = [](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverage() > rhs.getAverage();
		};

		std::sort(localStudents.begin(), localStudents.end(), compareAverage);

		if (localStudents.empty())
			return model::Student();

		return localStudents.front();
	}

	model::Student StudentsController::getBestStudentAt(const bytes_t& subject)
	{
		auto localStudents = students_;

		auto compareAverage = [&subject](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverageAt(subject) > rhs.getAverageAt(subject);
		};

		std::sort(localStudents.begin(), localStudents.end(), compareAverage);

		if (localStudents.empty())
			return model::Student();

		return localStudents.front();
	}

	model::Student StudentsController::getWorstStudent()
	{
		auto localStudents = students_;

		auto compareAverage = [](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverage() < rhs.getAverage();
		};

		std::sort(localStudents.begin(), localStudents.end(), compareAverage);

		if (localStudents.empty())
			return model::Student();

		return localStudents.front();
	}

	model::Student StudentsController::getWorstStudentAt(const bytes_t& subject)
	{
		auto localStudents = students_;

		auto compareAverage = [&subject](const auto& lhs, const auto& rhs) -> bool
		{
			return lhs.getAverageAt(subject) < rhs.getAverageAt(subject);
		};

		std::sort(localStudents.begin(), localStudents.end(), compareAverage);

		if (localStudents.empty())
			return model::Student();

		return localStudents.front();
	}

	StudentsVec StudentsController::getFailingStudents()
	{
		StudentsVec students;
		auto localStudents = students_;

		std::for_each(localStudents.begin(), localStudents.end(),
			[&students](const auto& student) -> void
			{
				if (student.getAverage() < 5) // average lower than passing mark
				{
					students.push_back(student);
				}
			});

		return students;
	}

	StudentsVec StudentsController::getFailingStudentsAt(const bytes_t& subject)
	{
		StudentsVec students;
		auto localStudents = students_;

		std::for_each(localStudents.begin(), localStudents.end(),
			[&students, &subject](const auto& student) -> void
			{
				if (student.getAverageAt(subject) < 5) // average lower than passing mark
				{
					students.push_back(student);
				}
			});

		return students;
	}
}
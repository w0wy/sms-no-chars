#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdint.h>
#include <vector>
#include <map>

using bytes_t = std::vector<uint8_t>;
using grades_t = std::map<bytes_t, std::vector<uint32_t>>;

namespace model
{
	class Student
	{
	public:
		Student() = default;
		~Student() = default;

		void setAge(uint32_t age);
		void setName(const bytes_t& name);
		void setGender(const bytes_t& gender);
		void setGrades(const grades_t& grades);

		uint32_t getUid() const;
		uint32_t getAge() const;
		bytes_t getName() const;
		bytes_t getGender() const;
		grades_t getGrades() const;

		void addGrade(const bytes_t& name, uint32_t grade);
		void removeGrade(const bytes_t& name, uint32_t grade);

		uint32_t getAverageAt(const bytes_t& subject) const;
		uint32_t getAverage() const;

	private:
		uint32_t uid_;
		uint32_t age_;
		bytes_t name_;
		bytes_t gender_;
		grades_t grades_;
	};
}

#endif
#include "model/Student.h"

#include <algorithm>
#include <numeric>

namespace model
{
	void Student::setAge(uint32_t age)
	{
		age_ = age;
	}

	void Student::setName(const bytes_t& name)
	{
		name_ = name;
	}
	void Student::setGender(const bytes_t& gender)
	{
		gender_ = gender;
	}
	void Student::setGrades(const grades_t& grades)
	{
		grades_ = grades;
	}

	uint32_t Student::getUid() const
	{
		return uid_;
	}
	uint32_t Student::getAge() const
	{
		return age_;
	}
	bytes_t Student::getName() const
	{
		return name_;
	}
	bytes_t Student::getGender() const
	{
		return gender_;
	}
	grades_t Student::getGrades() const
	{
		return grades_;
	}

	void Student::addGrade(const bytes_t& name, uint32_t grade)
	{
		auto it = std::find_if(grades_.begin(), grades_.end(),
			[&name](const auto& elem) -> bool
			{
				return elem.first == name;
			});

		if (it != grades_.end())
		{
			it->second.push_back(grade);
		}
	}
	void Student::removeGrade(const bytes_t& name, uint32_t grade)
	{
		auto it = std::find_if(grades_.begin(), grades_.end(),
			[&name](const auto& elem) -> bool
			{
				return elem.first == name;
			});
		if (it != grades_.end())
		{
			auto vecIt = std::find(it->second.begin(), it->second.end(), grade);
			if (vecIt != it->second.end())
			{
				it->second.erase(vecIt);
			}
		}
	}

	uint32_t Student::getAverageAt(const bytes_t& subject) const
	{
		uint32_t average = 0;
		auto it = std::find_if(grades_.begin(), grades_.end(),
			[&subject](const auto& elem) -> bool
			{
				return elem.first == subject;
			});
		if (it != grades_.end())
		{
			average = std::accumulate(it->second.begin(), it->second.end(), 0);
			average = average / it->second.size();
		}

		return average;
	}

	uint32_t Student::getAverage() const
	{
		std::vector<uint32_t> averages;
		for (auto it : grades_)
		{
			uint32_t average = std::accumulate(it.second.begin(), it.second.end(), 0);
			average = average / it.second.size();
			averages.push_back(average);
		}

		uint32_t avg = std::accumulate(averages.begin(), averages.end(), 0);
		avg = avg / averages.size();
		return avg;
	}

}
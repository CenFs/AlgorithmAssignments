// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
template <typename Type>
Type random_in_range(Type start, Type end)
{
	auto range = end - start;
	++range;

	auto num = rand() % range;
	return static_cast<Type>(start + num);
}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(std::string name, int salary)
{
	Person* person = new Person;
	person->name = name;
	person->salary = salary;

	m_new_persons_unsorted_by_name.push_back(person);
	m_new_persons_unsorted_by_salary.push_back(person);

}

unsigned int Datastructure::size()
{
	return m_persons_sorted_by_name.size() + m_new_persons_unsorted_by_name.size();
}

void Datastructure::clear()
{
	m_new_persons_unsorted_by_salary.clear();
	m_new_persons_unsorted_by_name.clear();
	m_persons_sorted_by_salary.clear();
	m_persons_sorted_by_name.clear();
}

vector<Person *> Datastructure::personnel_alphabetically()
{
	merge_persons(m_persons_sorted_by_name, m_new_persons_unsorted_by_name, 1);

	return m_persons_sorted_by_name;
}

vector<Person *> Datastructure::personnel_salary_order()
{
	merge_persons(m_persons_sorted_by_salary, m_new_persons_unsorted_by_salary, 0);

	return m_persons_sorted_by_salary;
}

Person* Datastructure::min_salary()
{
	return nth_sorted_by_salary(0);
}

Person* Datastructure::max_salary()
{
	return nth_sorted_by_salary(size() - 1);
}

Person* Datastructure::median_salary()
{
	return nth_sorted_by_salary(size() / 2);
}

Person* Datastructure::first_quartile_salary()
{
	return nth_sorted_by_salary(size() / 4);
}

Person* Datastructure::third_quartile_salary()
{
	return nth_sorted_by_salary(size() * 3 / 4);
}

void Datastructure::merge_sort(vector<Person*> &persons, int start, int end, int flag) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(persons, start, mid, flag);
		merge_sort(persons, mid + 1, end, flag);
		merge(persons, start, mid, end, flag);
	}
}

bool Datastructure::compare(Person* p1, Person* p2, int flag) {
	if (flag == 0) {
		if (p1->salary <= p2->salary) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		if (p1->name <= p2->name) {
			return false;
		}
		else {
			return true;
		}
	}
}

void Datastructure::merge(vector<Person*> &persons, int start, int mid, int end, int flag) {
	vector<Person*> tmp;
	int i = start, j = mid + 1;
	while (i != mid + 1 && j != end + 1) {
		if (!compare(persons[i], persons[j], flag)) {
			tmp.push_back(persons[i++]);
		}
		else {
			tmp.push_back(persons[j++]);
		}
	}
	while (i != mid + 1) {
		tmp.push_back(persons[i++]);
	}
	while (j != end + 1) {
		tmp.push_back(persons[j++]);
	}
	for (int i = 0; i < tmp.size(); i++) {
		persons[start + i] = tmp[i];
	}
}


Person* Datastructure::nth_sorted_by_salary(int n) {
	merge_persons(m_persons_sorted_by_salary, m_new_persons_unsorted_by_salary, 0);

	return m_persons_sorted_by_salary[n];
}

void Datastructure::merge_persons(vector<Person*>& sorted_persons, vector<Person*>& unsorted_persons, int flag) {
	if (unsorted_persons.size() != 0) {
		int mid = sorted_persons.size() - 1;

		if (unsorted_persons.size() != 1) { 
			merge_sort(unsorted_persons, 0, unsorted_persons.size() - 1, flag);
			for (auto person : unsorted_persons) {
				sorted_persons.push_back(person);
			}
		}
		else {
			sorted_persons.push_back(unsorted_persons[0]); // for only one element
		}
		unsorted_persons.clear();
		merge(sorted_persons, 0, mid, sorted_persons.size() - 1, flag);
	}
}

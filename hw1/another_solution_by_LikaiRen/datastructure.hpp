// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

struct Person
{
	string name;
	int salary;
};

class Datastructure
{
public:
	Datastructure();
	~Datastructure();

	void add_person(string name, int salary);

	unsigned int size();
	void clear();

	vector<Person*> personnel_alphabetically();
	vector<Person*> personnel_salary_order();

	Person* min_salary();
	Person* max_salary();

	Person* median_salary();
	Person* first_quartile_salary();
	Person* third_quartile_salary();

private:
	vector<Person*> m_new_persons_unsorted_by_name;
	vector<Person*> m_new_persons_unsorted_by_salary;

	vector<Person*> m_persons_sorted_by_name;
	vector<Person*> m_persons_sorted_by_salary;

	void merge_persons(vector<Person*>& sorted_persons, vector<Person*>& unsorted_persons, int flag);

	void merge(vector<Person*>& persons, int start, int mid, int end, int flag); //flag=0->salary; flag=1->name;
	void merge_sort(vector<Person*>& persons, int start, int end, int flag);
	bool compare(Person* p1, Person* p2, int flag);	

	Person* nth_sorted_by_salary(int n);
};

#endif // DATASTRUCTURE_HPP

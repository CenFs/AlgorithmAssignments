// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

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
    // Add your implementation here
    vector<Person*> plist_;
    vector<Person*> plist_name_;
    Person *max_salary_;
    Person *min_salary_;
    // Person *median_salary_;
    // Person *first_quartile_salary_;
    // Person *third_quartile_salary_;
    bool sorted_a_;
    bool sorted_s_;
    // bool firstadd_;
};

#endif // DATASTRUCTURE_HPP

// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

using PersonID = string;
PersonID const NO_ID = "";

using Salary = int;
Salary const NO_SALARY = -1;


class Datastructure
{
public:
    Datastructure();
    ~Datastructure();

    void add_person(string name, PersonID id, string title, Salary salary);
    void remove_person(PersonID id);

    string get_name(PersonID id);
    string get_title(PersonID id);
    Salary get_salary(PersonID id);
    vector<PersonID> find_persons(string name);
    vector<PersonID> personnel_with_title(string title);

    void change_name(PersonID id, string new_name);
    void change_salary(PersonID id, Salary new_salary);

    void add_boss(PersonID id, PersonID bossid);

    unsigned int size();
    void clear();

    vector<PersonID> underlings(PersonID id);
    vector<PersonID> personnel_alphabetically();
    vector<PersonID> personnel_salary_order();

    PersonID find_ceo();
    PersonID nearest_common_boss(PersonID id1, PersonID id2);
    pair<unsigned int, unsigned int> higher_lower_ranks(PersonID id);

    PersonID min_salary();
    PersonID max_salary();

    PersonID median_salary();
    PersonID first_quartile_salary();
    PersonID third_quartile_salary();

    // void quick_sort(vector<Person*>& plist, int left, int right, bool sort_by_name);

private:
    // Add your implementation here
    struct Person {
        string name;
        PersonID id;
        string title;
        Salary salary;
        vector<Person*> children;
        Person* parent = NULL;
    };

    Person* pmax_salary_;
    Person* pmin_salary_;
    Person* p_;

    vector<Person*> vperson_;
    vector<Person*> vperson_name_;
    vector<PersonID> vpersonid_name_;
    vector<PersonID> vpersonid_salary_;

    bool sorted_name_;
    bool sorted_salary_;
    bool max_salary_removed_;
    bool min_salary_removed_;

    unordered_map<PersonID, Person*> m_;

    /*
    struct Node {
        Person p;
        vector<Node*> children; // if you wanna search "do i have this child", map/unordered_map is better.
        Node* parent;
    };*/
};

#endif // DATASTRUCTURE_HPP

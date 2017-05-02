// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
using namespace std;

using PersonID = string;
PersonID const NO_ID = "";

using Salary = int;
Salary const NO_SALARY = -1;

using Cost = int;
Cost const NO_COST = -1;

struct Person {
    string name;
    PersonID id;
    string title;
    Salary salary;
    vector<Person*> children;
    Person* parent = NULL;
};

struct AdjListNode {
    PersonID id;
    Cost cost;
    struct AdjListNode *next;
    friend bool operator< (AdjListNode a, AdjListNode b) {
        return a.cost > b.cost;
    }
};

struct AdjList {
    AdjListNode *head;
};

struct Graph {
    int vertices;
    int edges;
    // AdjList *array;
    unordered_map<PersonID, AdjList*> main_index;
};

struct DijkstraNode {
    PersonID id;
    Cost cost;
    Cost eachcost;
    friend bool operator< (DijkstraNode a, DijkstraNode b) {
        return a.cost > b.cost;
    }
};


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

    int count_all_children(Person* p);
    int nodes_of_higher_ranks(Person* top, int rank, int height);
    int nodes_of_lower_ranks(Person* top, int rank, int height);



    // After this are the new operations of hw3
    void add_friendship(PersonID id, PersonID friendid, Cost cost);
    void remove_friendship(PersonID id, PersonID friendid);
    vector<pair<PersonID, Cost>> get_friends(PersonID id);
    vector<pair<PersonID, PersonID>> all_friendships();

    bool check_boss_hierarchy();
    vector<pair<PersonID, Cost>> shortest_friendpath(PersonID fromid, PersonID toid);
    vector<pair<PersonID, Cost>> cheapest_friendpath(PersonID fromid, PersonID toid);
    pair<unsigned int, Cost> leave_cheapest_friendforest();

    bool equal_iter(auto curr_iter, auto next_iter);
    bool personid_exists(vector<pair<PersonID, PersonID>> v, pair<PersonID, PersonID> p);


private:
    // Add your implementation here
    Person* pmax_salary_;
    Person* pmin_salary_;
    Person* p_;

    vector<Person*> vperson_;
    vector<Person*> vperson_name_;
    unordered_map<PersonID, Person*> m_;

    bool sorted_name_;
    bool sorted_salary_;
    bool max_salary_removed_;
    bool min_salary_removed_;

    Graph* graph_;

};

#endif // DATASTRUCTURE_HPP

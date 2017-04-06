// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

#include <random>
using std::minstd_rand;
using std::uniform_int_distribution;

minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(string name, PersonID id, string title, Salary salary)
{

}

void Datastructure::remove_person(PersonID id)
{

}

string Datastructure::get_name(PersonID id)
{
    return ""; // Replace this with the actual implementation
}

string Datastructure::get_title(PersonID id)
{
    return ""; // Replace this with the actual implementation
}

Salary Datastructure::get_salary(PersonID id)
{
    return NO_SALARY; // Replace this with the actual implementation
}

vector<PersonID> Datastructure::find_persons(string name)
{
    return {}; // Replace this with the actual implementation
}

vector<PersonID> Datastructure::personnel_with_title(string title)
{
    return {}; // Replace this with the actual implementation
}

void Datastructure::change_name(PersonID id, string new_name)
{

}

void Datastructure::change_salary(PersonID id, Salary new_salary)
{

}

void Datastructure::add_boss(PersonID id, PersonID bossid)
{

}

unsigned int Datastructure::size()
{
    return 0; // Replace this with the actual implementation
}

void Datastructure::clear()
{

}

vector<PersonID> Datastructure::underlings(PersonID id)
{
    return {}; // Replace this with the actual implementation
}

vector<PersonID> Datastructure::personnel_alphabetically()
{
    return {}; // Replace this with the actual implementation
}

vector<PersonID> Datastructure::personnel_salary_order()
{
    return {}; // Replace this with the actual implementation
}

PersonID Datastructure::find_ceo()
{
    return NO_ID; // Replace this with the actual implementation
}

PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2)
{
    return NO_ID; // Replace this with the actual implementation, if any
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id)
{
    return {0,0}; // Replace this with the actual implementation, if any
}

PersonID Datastructure::min_salary()
{
    return NO_ID; // Replace this with the actual implementation
}

PersonID Datastructure::max_salary()
{
    return NO_ID; // Replace this with the actual implementation
}

PersonID Datastructure::median_salary()
{
    return NO_ID; // Replace this with the actual implementation
}

PersonID Datastructure::first_quartile_salary()
{
    return NO_ID; // Replace this with the actual implementation
}

PersonID Datastructure::third_quartile_salary()
{
    return NO_ID; // Replace this with the actual implementation
}

// After this are the new operations of hw3
// NOTE!!! Add all your new hw3 code here below these comments (to keep it
// separated from old hw2 code).
void Datastructure::add_friendship(PersonID id, PersonID friendid, Cost cost)
{

}

void Datastructure::remove_friendship(PersonID id, PersonID friendid)
{

}

vector<pair<PersonID, Cost>> Datastructure::get_friends(PersonID id)
{
    return {}; // Replace this with the actual implementation
}

vector<pair<PersonID, PersonID>> Datastructure::all_friendships()
{
    return {}; // Replace this with the actual implementation
}

vector<pair<PersonID, Cost> > Datastructure::shortest_friendpath(PersonID fromid, PersonID toid)
{
    return {}; // Replace this with the actual implementation
}

bool Datastructure::check_boss_hierarchy()
{
    return false; // Replace this with the actual implementation
}

vector<pair<PersonID, Cost>> Datastructure::cheapest_friendpath(PersonID fromid, PersonID toid)
{
    return {}; // Replace this with the actual implementation
}

pair<unsigned int, Cost> Datastructure::leave_cheapest_friendforest()
{
    return {}; // Replace this with the actual implementation
}

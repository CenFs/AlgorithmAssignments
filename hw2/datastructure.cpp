// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = rand() % range;
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

}

string Datastructure::get_title(PersonID id)
{

}

Salary Datastructure::get_salary(PersonID id)
{

}

vector<PersonID> Datastructure::find_persons(string name)
{

}

vector<PersonID> Datastructure::personnel_with_title(string title)
{

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

}

void Datastructure::clear()
{

}

vector<PersonID> Datastructure::underlings(PersonID id)
{

}

vector<PersonID> Datastructure::personnel_alphabetically()
{

}

vector<PersonID> Datastructure::personnel_salary_order()
{

}

PersonID Datastructure::find_ceo()
{

}

PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2)
{
    return NO_ID; // If you do not implement this, leave this return value as it is.
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id)
{
    return {0, 0}; // If you do not implement this, leave this return value as it is.
}

PersonID Datastructure::min_salary()
{

}

PersonID Datastructure::max_salary()
{

}

PersonID Datastructure::median_salary()
{

}

PersonID Datastructure::first_quartile_salary()
{

}

PersonID Datastructure::third_quartile_salary()
{

}

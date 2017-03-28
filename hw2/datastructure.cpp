// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
#include <stack>
using namespace std;

template <typename Type>
Type random_in_range(Type start, Type end) {
    auto range = end-start;
    ++range;

    auto num = rand() % range;
    return static_cast<Type>(start+num);
}


Datastructure::Datastructure() {
    sorted_name_ = false;
    sorted_salary_ = false;
    pmax_salary_ = new Person();
    pmin_salary_ = new Person();
    max_salary_removed_ = true;
    min_salary_removed_ = true;
}


Datastructure::~Datastructure() {
    clear();
    if (pmax_salary_)
        delete pmax_salary_;
    if (pmin_salary_)
        delete pmin_salary_;
    if (p_)
        delete p_;
}


void Datastructure::add_person(string name, PersonID id, string title, Salary salary) {
    p_ = new Person;
    p_->name = name;
    p_->id = id;
    p_->title = title;
    p_->salary = salary;
    vperson_.push_back(p_);
    sorted_salary_ = false;
    vperson_name_.push_back(p_);
    sorted_name_ = false;
    m_[id] = p_;

    if (vperson_.size() == 1) {
        pmin_salary_ = p_;
        pmax_salary_ = p_;
    } else {
        if ((pmin_salary_ -> salary) > (p_ -> salary)) pmin_salary_ = p_;
        if ((pmax_salary_ -> salary) < (p_ -> salary)) pmax_salary_ = p_;
    }
    max_salary_removed_ = false;
    min_salary_removed_ = false;

}


void Datastructure::remove_person(PersonID id) {
    /*vector<Person*> parent_children = m_[id]->parent->children;
    auto tmp = parent_children.begin();
    if (tmp != parent_children.end()) {
        tmp = parent_children.erase(find_if(parent_children.begin(), parent_children.end(), [id](const Person* p){return p->id == id;}));
        tmp++;
    }
    auto iter = m_[id]->children.begin();
    while (iter != m_[id]->children.end()) {
        (*iter)->parent = m_[id]->parent;
        parent_children.push_back((*iter));
        iter++;
    }*/

    m_.erase(id);
    vperson_.erase(remove_if(vperson_.begin(), vperson_.end(), [id](const Person* p){return p->id == id;}));
    if (sorted_salary_) {
        vpersonid_salary_.clear();
        auto iter = vperson_.begin();
        while (iter != vperson_.end()) {
            vpersonid_salary_.push_back((*iter)->id);
            iter++;
        }
    }
    vperson_name_.erase(remove_if(vperson_name_.begin(), vperson_name_.end(), [id](const Person* p){return p->id == id;}));
    if (sorted_name_) {
        vpersonid_name_.clear();
        auto iter = vperson_name_.begin();
        while (iter != vperson_name_.end()) {
            vpersonid_name_.push_back((*iter)->id);
            iter++;
        }
    }
    if (pmax_salary_->id == id) max_salary_removed_ = true;
    if (pmin_salary_->id == id) min_salary_removed_ = true;
}


string Datastructure::get_name(PersonID id) {
    return m_[id]->name;
}


string Datastructure::get_title(PersonID id) {
    return m_[id]->title;
}


Salary Datastructure::get_salary(PersonID id) {
    return m_[id]->salary;
}


vector<PersonID> Datastructure::find_persons(string name) {
    vector<Person*> vptmp;
    vector<PersonID> result;
    copy_if(vperson_.begin(), vperson_.end(), back_inserter(vptmp), [name](const Person* p){return p->name == name;});
    for (auto iter = vptmp.begin(); iter != vptmp.end(); iter++ ) {
        result.push_back((*iter)->id);
    }
    sort(result.begin(), result.end());
    return result;
}


vector<PersonID> Datastructure::personnel_with_title(string title) {
    vector<Person*> vptmp;
    vector<PersonID> result;
    copy_if(vperson_.begin(), vperson_.end(), back_inserter(vptmp), [title](const Person* p){return p->title == title;});
    for (auto iter = vptmp.begin(); iter != vptmp.end(); iter++ ) {
        result.push_back((*iter)->id);
    }
    sort(result.begin(), result.end());
    return result;
}


void Datastructure::change_name(PersonID id, string new_name) {
    m_[id]->name = new_name;
    sorted_name_ = false;
}


void Datastructure::change_salary(PersonID id, Salary new_salary) {

    if (pmax_salary_->id == m_[id]->id && m_[id]->salary < new_salary) {
        pmax_salary_ = m_[id];
        max_salary_removed_ = false;
    } else if (pmin_salary_->id == m_[id]->id && m_[id]->salary > new_salary) {
        pmin_salary_ = m_[id];
        min_salary_removed_ = false;
    } else {
        max_salary_removed_ = true;
        min_salary_removed_ = true;
    }

    m_[id]->salary = new_salary;
    sorted_salary_ = false;
}


void Datastructure::add_boss(PersonID id, PersonID bossid) {
    m_[id]->parent = m_[bossid];
    m_[bossid]->children.push_back(m_[id]);
}


unsigned int Datastructure::size() {
    return vperson_.size();
}


void Datastructure::clear() {
    vperson_.clear();
    vperson_name_.clear();
    vpersonid_name_.clear();
    vpersonid_salary_.clear();
    m_.clear();
}


vector<PersonID> Datastructure::underlings(PersonID id) {
    vector<PersonID> underlings;
    vector<Person*> children = m_[id]->children;
    //auto person = find_if(vperson_.begin(), vperson_.end(), [id](const Person* p){return p->id == id;});
    //vector<Person*> children = (*person)->children;

    for (auto iter = children.begin(); iter != children.end(); iter++) {
        underlings.push_back((*iter)->id);
    }
    sort(underlings.begin(), underlings.end());
    return underlings;
}


vector<PersonID> Datastructure::personnel_alphabetically() {
    if (!sorted_name_) {
        sort(vperson_name_.begin(), vperson_name_.end(), [](const Person* a, const Person* b){return a->name < b->name;});
        sorted_name_ = true;

        vpersonid_name_.clear();
        auto iter = vperson_name_.begin();
        while (iter != vperson_name_.end()) {
            vpersonid_name_.push_back((*iter)->id);
            iter++;
        }
    }
    return vpersonid_name_;
}


vector<PersonID> Datastructure::personnel_salary_order() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;

        vpersonid_salary_.clear();
        auto iter = vperson_.begin();
        while (iter != vperson_.end()) {
            vpersonid_salary_.push_back((*iter)->id);
            iter++;
        }
    }
    return vpersonid_salary_;
}


PersonID Datastructure::find_ceo() {
    vector<Person*> vptmp;
    copy_if(vperson_.begin(), vperson_.end(), back_inserter(vptmp), [](const Person* p){return p->parent == NULL;});
    if (vptmp.size() == 1) {
        return vptmp.at(0)->id;
    } else {
        return NO_ID;
    }
}


PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2) {
    PersonID ceo = find_ceo();
    Person* person1 = m_[id1];
    Person* person2 = m_[id2];
    if (person1->id == ceo || person2->id == ceo) {
        return ceo;
    }
    if (person1->id == person2->parent->id) {
        return person1->parent->id;
    } else if (person2->id == person1->parent->id) {
        return person2->parent->id;
    } else if (person1->parent->id == person2->parent->id) {
        return person1->parent->id;
    }

    stack<Person*> p1_parents;
    stack<Person*> p2_parents;
    while (person1->parent != NULL) {
        p1_parents.push(person1->parent);
        person1 = m_[person1->parent->id];
    }
    while (person2->parent != NULL) {
        p2_parents.push(person2->parent);
        person2 = m_[person2->parent->id];
    }
    Person* result = NULL;
    while (p1_parents.size() > 0 && p2_parents.size() > 0 && p1_parents.top() == p2_parents.top()) {
        result = p1_parents.top();
        p1_parents.pop();
        p2_parents.pop();
    }
    if (result != NULL) {
        return result->id;
    }
    return NO_ID;
}

int Datastructure::count_all_children(Person* p) {
    int count = 0;
    if (p->children.size() == 0) {
        return count;
    }
    count += p->children.size();
    auto iter = p->children.begin();
    while (iter != p->children.end()) {
        if ((*iter)->children.size() != 0)
            count += count_all_children((*iter));
        iter++;
    }
    return count;
}

int Datastructure::nodes_of_higher_ranks(Person* top, int rank, int height) {
    if (rank == 0) {
        return 0;
    } else if (rank == 1) {
        return 1;
    } else if (rank == 2) {
        return top->children.size() + 1;
    }

    int count = top->children.size();
    if (height == rank) {
        count++; // ceo
    }
    if (rank > 2 && height > rank - 1) {
        height--;
        auto iter = top->children.begin();
        while (iter != top->children.end()) {
            count += nodes_of_higher_ranks((*iter), rank, height);
            iter++;
        }
    }
    return count;
}

int Datastructure::nodes_of_lower_ranks(Person* top, int rank, int height) {
    if (rank == 0) {
        return count_all_children(top);
    }

    int count = 0;
    if (rank > 0 && height > 0) {
        height--;
        auto iter = top->children.begin();
        while (iter != top->children.end()) {
            if (height == 0) {
                count += count_all_children((*iter));
            } else {
                count += nodes_of_lower_ranks((*iter), rank, height);
            }
            iter++;
        }
    }
    return count;
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id) {
    PersonID ceoid = find_ceo();
    if (ceoid == NO_ID) {
        return {0, 0};
    }

    Person* ceo = m_[ceoid];
    Person* p = m_[id];

    int rank = 0;
    while (p->parent != NULL) {
        rank++;
        p = m_[p->parent->id];
    }
    return {nodes_of_higher_ranks(ceo, rank, rank), nodes_of_lower_ranks(ceo, rank, rank)};
}


PersonID Datastructure::min_salary() {
    if (min_salary_removed_) {
        if (!sorted_salary_) {
            sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
            sorted_salary_ = true;

            vpersonid_salary_.clear();
            auto iter = vperson_.begin();
            while (iter != vperson_.end()) {
                vpersonid_salary_.push_back((*iter)->id);
                iter++;
            }
        }
        pmin_salary_ = vperson_.at(0);
        min_salary_removed_ = false;
    }
    return pmin_salary_->id;
}


PersonID Datastructure::max_salary() {
    if (max_salary_removed_) {
        if (!sorted_salary_) {
            sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
            sorted_salary_ = true;

            vpersonid_salary_.clear();
            auto iter = vperson_.begin();
            while (iter != vperson_.end()) {
                vpersonid_salary_.push_back((*iter)->id);
                iter++;
            }
        }
        pmax_salary_ = vperson_.at(vperson_.size()-1);
        max_salary_removed_ = false;
    }
    return pmax_salary_->id;
}


PersonID Datastructure::median_salary() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;

        vpersonid_salary_.clear();
        auto iter = vperson_.begin();
        while (iter != vperson_.end()) {
            vpersonid_salary_.push_back((*iter)->id);
            iter++;
        }
    }
    return vperson_.at(vperson_.size() / 2)->id;
}


PersonID Datastructure::first_quartile_salary() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;

        vpersonid_salary_.clear();
        auto iter = vperson_.begin();
        while (iter != vperson_.end()) {
            vpersonid_salary_.push_back((*iter)->id);
            iter++;
        }
    }
    return vperson_.at(vperson_.size() / 4)->id;
}


PersonID Datastructure::third_quartile_salary() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;

        vpersonid_salary_.clear();
        auto iter = vperson_.begin();
        while (iter != vperson_.end()) {
            vpersonid_salary_.push_back((*iter)->id);
            iter++;
        }
    }
    return vperson_.at(vperson_.size() * 3 / 4)->id;
}

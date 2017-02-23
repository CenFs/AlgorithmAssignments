// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
template <typename Type>
Type random_in_range(Type start, Type end) {
    auto range = end-start;
    ++range;

    auto num = rand() % range;
    return static_cast<Type>(start+num);
}

void merge_sort(vector<Person*>& plist, int head, int tail, bool sort_by_name);
void merge(vector<Person*>& plist, int head, int mid, int tail, bool sort_by_name);
void quick_sort(vector<Person*>& plist, int left, int right, bool sort_by_name);


Datastructure::Datastructure() {
    plist_ = {};
    plist_name_ = {};
    sorted_a_ = false;
    sorted_s_ = false;
    max_salary_ = new Person();
    min_salary_ = new Person();
    // median_salary_ = new Person();
    // first_quartile_salary_ = new Person();
    // third_quartile_salary_ = new Person();
}

Datastructure::~Datastructure() {
    clear();
}

void Datastructure::add_person(std::string name, int salary) {
    Person *p = new Person();
    p -> name = name;
    p -> salary = salary;
    plist_.push_back(p);
    sorted_s_ = false;
    // plist_name_.push_back(p);
    sorted_a_ = false;
    if (plist_.size() == 1) {
        min_salary_ = p;
        max_salary_ = p;
    } else {
        if ((min_salary_ -> salary) > (p -> salary))    min_salary_ = p;
        if ((max_salary_ -> salary) < (p -> salary))    max_salary_ = p;
    }
    // cerr << "add person: " << p -> name << endl;
}

unsigned int Datastructure::size() {
    return int(plist_.size());
}

void Datastructure::clear() {
    plist_.clear();
    plist_name_.clear();
}

vector<Person *> Datastructure::personnel_alphabetically() {
    // cerr << "personnel_alphabetically()" << endl;
    if (!sorted_a_) {
        plist_name_ = plist_;
        quick_sort(plist_name_, 0, int(plist_name_.size())-1, true);
        // merge_sort(plist_, 0, int(plist_.size())-1, "name");
        sorted_a_ = true;
    }
    return plist_name_;
}

vector<Person *> Datastructure::personnel_salary_order() {
    // cerr << "personnel_salary_order()" << endl;
    quick_sort(plist_, 0, int(plist_.size())-1, false);
    // merge_sort(plist_, 0, int(plist_.size())-1, "salary");
    sorted_s_ = true;
    // max_salary_ = plist_.at(plist_.size()-1);
    // min_salary_ = plist_.at(0);
    // median_salary_ = plist_.at((plist_.size()) / 2);
    // first_quartile_salary_ = plist_.at((plist_.size()) / 4);
    // third_quartile_salary_ = plist_.at((plist_.size()) * 3 / 4);
    return plist_;
}

Person* Datastructure::min_salary() {
    // cerr << "min_salary()" << endl;
    // if (!sorted_s_) plist_ = personnel_salary_order();
    // else cerr << "sorted_s_ True" << endl;
    return min_salary_; // plist_.at(0);
}

Person* Datastructure::max_salary() {
    // cerr << "max_salary()" << endl;
    // if (!sorted_s_) plist_ = personnel_salary_order();
    // else cerr << "sorted_s_ True" << endl;
    return max_salary_; // plist_.at(plist_.size() - 1);
}

Person* Datastructure::median_salary() {
    // cerr << "median_salary()" << endl;
    if (!sorted_s_) plist_ = personnel_salary_order();
    // else cerr << "sorted_s_ True" << endl;
    return plist_.at(plist_.size() / 2); // median_salary_;
}

Person* Datastructure::first_quartile_salary() {
    // cerr << "first_quartile_salary()" << endl;
    if (!sorted_s_) plist_ = personnel_salary_order();
    // else cerr << "sorted_s_ True" << endl;
    return plist_.at(plist_.size() / 4); // first_quartile_salary_;
}

Person* Datastructure::third_quartile_salary() {
    // cerr << "third_quartile_salary()" << endl;
    if (!sorted_s_) plist_ = personnel_salary_order();
    // else cerr << "sorted_s_ True" << endl;
    return plist_.at(plist_.size() * 3 / 4); // third_quartile_salary_;
}



// quick sort
void quick_sort(vector<Person*>& plist, int left, int right, bool sort_by_name) {
    Person *ptmp = plist.at((left + right) / 2);
    int i = left, j = right;

    // cerr << "quick sort!" << endl;
    // partition
    if (sort_by_name/*sort_by.compare("name") == 0*/) {
        // cerr << "quick sort name" << endl;
        string pivot = ptmp -> name;
        while (i <= j) {
            while ((plist.at(i) -> name) < pivot) i++;
            while ((plist.at(j) -> name) > pivot) j--;
            if (i <= j) {
                ptmp = plist.at(i);
                plist.at(i) = plist.at(j);
                plist.at(j) = ptmp;
                i++;
                j--;
            }
        }
    } else /*if (sort_by.compare("salary") == 0)*/ {
        // cerr << "quick sort salary" << endl;
        int pivot = ptmp -> salary;
        while (i <= j) {
            while ((plist.at(i) -> salary) < pivot) i++;
            while ((plist.at(j) -> salary) > pivot) j--;
            if (i <= j) {
                ptmp = plist.at(i);
                plist.at(i) = plist.at(j);
                plist.at(j) = ptmp;
                i++;
                j--;
            }
        }
    } // else cerr << "quick sort NOT name NOT salary!!" << endl;

    // recursion
    if (left < j) quick_sort(plist, left, j, sort_by_name);
    if (i < right) quick_sort(plist, i, right, sort_by_name);
}



// merge sort
void merge_sort(vector<Person*>& plist, int head, int tail, bool sort_by_name) {
    if (head < tail) {
        int mid = (head + tail) / 2;
        merge_sort(plist, head, mid, sort_by_name);
        merge_sort(plist, mid + 1, tail, sort_by_name);
        merge(plist, head, mid, tail, sort_by_name);
    }
    return;
}

void merge(vector<Person*>& plist, int head, int mid, int tail, bool sort_by_name) {
    vector<Person*>plist_copy = plist;
    int i = head;
    int j = head;
    int k = mid + 1;
    if (sort_by_name/*sort_by.compare("name") == 0*/) {
        while (j <= mid && k <= tail) {
            if ((plist_copy.at(j)) -> name <= (plist_copy.at(k)) -> name) {
                plist.at(i) = plist_copy.at(j);
                j++;
            } else {
                plist.at(i) = plist_copy.at(k);
                k++;
            }
            i++;
        }
    } else /*if (sort_by.compare("salary") == 0)*/ {
        while (j <= mid && k <= tail) {
            if ((plist_copy.at(j)) -> salary <= (plist_copy.at(k)) -> salary) {
                plist.at(i) = plist_copy.at(j);
                j++;
            } else {
                plist.at(i) = plist_copy.at(k);
                k++;
            }
            i++;
        }
    } // else cerr << "merge sort NOT name NOT salary!!" << endl;
    if (j > mid)
        k = 0;
    else
        k = mid - tail;
    for (j = i; j <= tail; j++)
        plist.at(j) = plist_copy.at(j + k);
}



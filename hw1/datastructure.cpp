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

void merge_sort(vector<Person*>& plist, int head, int tail, string sort_by);
void merge(vector<Person*>& plist, int head, int mid, int tail, string sort_by);
void quick_sort(vector<Person*>& plist, int left, int right, string sort_by);



Datastructure::Datastructure() {
    plist_ = {};
    // sorted_a_ = false;
    sorted_s_ = false;
}

Datastructure::~Datastructure() {
    clear();
}

void Datastructure::add_person(std::string name, int salary) {
    Person *p = new Person();
    p -> name = name;
    p -> salary = salary;
    plist_.push_back(p);
    // sorted_a_ = false;
    sorted_s_ = false;
}

unsigned int Datastructure::size() {
    return int(plist_.size());
}

void Datastructure::clear() {
    plist_.clear();
}

vector<Person *> Datastructure::personnel_alphabetically() {
    vector<Person *> plist = plist_;
    // quick_sort(plist, 0, int(plist.size())-1, "name");
    merge_sort(plist, 0, int(plist.size())-1, "name");
    // sorted_a_ = true;
    return plist;
}

vector<Person *> Datastructure::personnel_salary_order() {
    // vector<Person *> plist = plist_;
    // quick_sort(plist_, 0, int(plist_.size())-1, "salary");
    merge_sort(plist_, 0, int(plist_.size())-1, "salary");
    sorted_s_ = true;
    return plist_;
}

Person* Datastructure::min_salary() {
    if (!sorted_s_) plist_ = personnel_salary_order();
    return plist_.at(0);
}

Person* Datastructure::max_salary() {
    if (!sorted_s_) plist_ = personnel_salary_order();
    return plist_.at(plist_.size()-1);
}

Person* Datastructure::median_salary() {
    if (!sorted_s_) plist_ = personnel_salary_order();
    return plist_.at((plist_.size()-1) / 2);
}

Person* Datastructure::first_quartile_salary() {
    if (!sorted_s_) plist_ = personnel_salary_order();
    return plist_.at((plist_.size()-1) / 4);
}

Person* Datastructure::third_quartile_salary() {
    if (!sorted_s_) plist_ = personnel_salary_order();
    return plist_.at((plist_.size()-1) * 3 / 4);
}



// quick sort
void quick_sort(vector<Person*>& plist, int left, int right, string sort_by) {
    Person *ptmp = new Person();
    int i = left, j = right;

    // partition
    if (sort_by.compare("name")) {
        string pivot = plist.at((left + right) / 2) -> name;
        while (i <= j) {
            while (plist.at(i) -> name < pivot) i++;
            while (plist.at(j) -> name > pivot) j--;
            if (i <= j) {
                ptmp = plist.at(i);
                plist.at(i) = plist.at(j);
                plist.at(j) = ptmp;
                i++;
                j--;
            }
        }
    }
    else if (sort_by.compare("salary")) {
        int pivot = plist.at((left + right) / 2) -> salary;
        while (i <= j) {
            while (plist.at(i) -> salary < pivot) i++;
            while (plist.at(j) -> salary > pivot) j--;
            if (i <= j) {
                ptmp = plist.at(i);
                plist.at(i) = plist.at(j);
                plist.at(j) = ptmp;
                i++;
                j--;
            }
        }
    }

    // recursion
    if (left < j) quick_sort(plist, left, j, sort_by);
    if (i < right) quick_sort(plist, i, right, sort_by);
}



// merge sort
void merge_sort(vector<Person*>& plist, int head, int tail, string sort_by) {
    if (head < tail) {
        int mid = (head + tail) / 2;
        merge_sort(plist, head, mid, sort_by);
        merge_sort(plist, mid + 1, tail, sort_by);
        merge(plist, head, mid, tail, sort_by);
    }
    return;
}

void merge(vector<Person*>& plist, int head, int mid, int tail, string sort_by) {
    vector<Person*>& plist_copy(plist);
    int i = head;
    int j = head;
    int k = mid + 1;
    if (sort_by.compare("name")) {
        while (j <= mid && k <= tail) {
            if (plist_copy.at(j) -> name <= plist_copy.at(k) -> name) {
                plist.at(i) = plist_copy.at(j);
                j++;
            } else {
                plist.at(i) = plist_copy.at(k);
                k++;
            }
        }
    } else if (sort_by.compare("salary")) {
        while (j <= mid && k <= tail) {
            if (plist_copy.at(j) -> salary <= plist_copy.at(k) -> salary) {
                plist.at(i) = plist_copy.at(j);
                j++;
            } else {
                plist.at(i) = plist_copy.at(k);
                k++;
            }
        }
    }
    if (j > mid)
        k = 0;
    else
        k = mid - tail;
    for (j = i; j <= tail; j++)
        plist.at(j) = plist_copy.at(j + k);
}


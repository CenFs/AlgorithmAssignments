// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

#include <stack>
#include <iostream>
#include <random>
#include <map>
#include <queue>
using namespace std;

#define INF 0xffff

minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

bool Datastructure::equal_iter(auto curr_iter, auto next_iter) {
    return (curr_iter->first == next_iter->first) && (curr_iter->second == next_iter->second);
}

bool Datastructure::personid_exists(vector<pair<PersonID, PersonID>> v, pair<PersonID, PersonID> p) {
    auto iter = find_if(v.begin(), v.end(), [p](const pair<PersonID, PersonID> p2){return (p.first == p2.first) && (p.second == p2.second);});
    if (iter != v.end()) return true;
    else return false;
}

Datastructure::Datastructure() {
    sorted_name_ = false;
    sorted_salary_ = false;
    pmax_salary_ = new Person();
    pmin_salary_ = new Person();
    max_salary_removed_ = true;
    min_salary_removed_ = true;

    graph_ = new Graph;
    graph_->edges = 0;
    graph_->vertices = 0;
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


    graph_->vertices++;
    graph_->main_index[id] = new AdjList;
    graph_->main_index[id]->head = NULL;
}


void Datastructure::remove_person(PersonID id) {
    if (m_.find(id) != m_.end()) {
        if (id == find_ceo()) {
            auto iter = m_[id]->children.begin();
            while (iter != m_[id]->children.end()) {
                (*iter)->parent = NULL;
                iter++;
            }
        } else {
            auto tmp = m_[id]->parent->children.begin();
            if (tmp != m_[id]->parent->children.end()) {
                tmp = m_[id]->parent->children.erase(remove_if(m_[id]->parent->children.begin(), m_[id]->parent->children.end(), [id](const Person* p){return p->id == id;}));
            }
            auto iter = m_[id]->children.begin();
            while (iter != m_[id]->children.end()) {
                (*iter)->parent = m_[id]->parent;
                m_[id]->parent->children.push_back((*iter));
                iter++;
            }
        }

        m_.erase(id);
        vperson_.erase(remove_if(vperson_.begin(), vperson_.end(), [id](const Person* p){return p->id == id;}));
        vperson_name_.erase(remove_if(vperson_name_.begin(), vperson_name_.end(), [id](const Person* p){return p->id == id;}));

        if (pmax_salary_->id == id) max_salary_removed_ = true;
        if (pmin_salary_->id == id) min_salary_removed_ = true;
    }
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
    m_.clear();
}


vector<PersonID> Datastructure::underlings(PersonID id) {
    vector<PersonID> underlings;
    vector<Person*> children = m_[id]->children;

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
    }
    vector<PersonID> vpersonid_name;
    auto iter = vperson_name_.begin();
    while (iter != vperson_name_.end()) {
        vpersonid_name.push_back((*iter)->id);
        iter++;
    }
    return vpersonid_name;
}


vector<PersonID> Datastructure::personnel_salary_order() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;
    }
    vector<PersonID> vpersonid_salary;
    auto iter = vperson_.begin();
    while (iter != vperson_.end()) {
        vpersonid_salary.push_back((*iter)->id);
        iter++;
    }
    return vpersonid_salary;
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
    Person* person1 = m_[id1];
    Person* person2 = m_[id2];

    if (m_.find(id1) == m_.end() || m_.find(id2) == m_.end() || person1->parent == NULL || person2->parent == NULL) {
        return NO_ID;
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
    if (rank > 2 && height > 2) {
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
    }
    return vperson_.at(vperson_.size() / 2)->id;
}

PersonID Datastructure::first_quartile_salary() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;
    }
    return vperson_.at(vperson_.size() / 4)->id;
}

PersonID Datastructure::third_quartile_salary() {
    if (!sorted_salary_) {
        sort(vperson_.begin(), vperson_.end(), [](const Person* a, const Person* b){return a->salary < b->salary;});
        sorted_salary_ = true;
    }
    return vperson_.at(vperson_.size() * 3 / 4)->id;
}









// After this are the new operations of hw3
// NOTE!!! Add all your new hw3 code here below these comments (to keep it
// separated from old hw2 code).
void Datastructure::add_friendship(PersonID id, PersonID friendid, Cost cost) {
    if (m_.find(id) != m_.end() && m_.find(friendid) != m_.end()) {
        bool friendship_exist = false;
        AdjListNode* node = graph_->main_index[id]->head;
        while (node) {
            if (friendid == node->id) {
                // Friendship exists, update the cost
                node->cost = cost;
                AdjListNode* node2 = graph_->main_index[friendid]->head;
                while (node2) {
                    if (id == node2->id) {
                        node2->cost = cost;
                        break;
                    }
                    node2 = node2->next;
                }
                friendship_exist = true;
                break;
            }
            node = node->next;
        }

        // If friendship doesnt exist, add new friendship
        // Else, do nothing
        if (!friendship_exist) {
            AdjListNode* newNode = new AdjListNode;
            newNode->id = friendid;
            newNode->cost = cost;
            newNode->next = graph_->main_index[id]->head;
            graph_->main_index[id]->head = newNode;

            newNode = new AdjListNode;
            newNode->id = id;
            newNode->cost = cost;
            newNode->next = graph_->main_index[friendid]->head;
            graph_->main_index[friendid]->head = newNode;

            graph_->edges++;
        }
    }
}

void Datastructure::remove_friendship(PersonID id, PersonID friendid) {
    // If people exist
    if (m_.find(id) != m_.end() && m_.find(friendid) != m_.end()) {
        // If friendship exists, remove it from [id] side
        // Else, do nothing
        bool friendship_deleted_id = false;
        AdjListNode* delNode = graph_->main_index[id]->head;
        if (friendid == delNode->id) {
            graph_->main_index[id]->head = delNode->next;
            delNode->next = NULL;
            friendship_deleted_id = true;
        } else {
            while (delNode->next) {
                if (friendid == delNode->next->id) {
                    AdjListNode* delNode_next = delNode->next;
                    delNode->next = delNode->next->next;
                    delNode_next->next = NULL;
                    friendship_deleted_id = true;
                    break;
                }
                delNode = delNode->next;
            }
        }

        // If [id] side has been removed, which means friendship exists, then remove [friendid] side
        // Else, do nothing
        if (friendship_deleted_id) {
            delNode = graph_->main_index[friendid]->head;
            if (id == delNode->id) {
                graph_->main_index[friendid]->head = delNode->next;
                delNode->next = NULL;
                graph_->edges--;
            } else {
                while (delNode->next) {
                    if (id == delNode->next->id) {
                        AdjListNode* delNode_next = delNode->next;
                        delNode->next = delNode->next->next;
                        delNode_next->next = NULL;
                        graph_->edges--;
                        break;
                    }
                    delNode = delNode->next;
                }
            }
        }
    }
}

vector<pair<PersonID, Cost>> Datastructure::get_friends(PersonID id) {
    // If the person exists
    if (m_.find(id) != m_.end()) {
        AdjListNode* node = graph_->main_index[id]->head;
        // If this person has no friendship
        if (node == NULL) return {};
        // Else, return all friendships in VECTOR (MAP is used to order the id)
        map<PersonID, Cost> m;
        vector<pair<PersonID, Cost>> v;
        while (node) {
            m[node->id] = node->cost;
            node = node->next;
        }
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            v.push_back((*iter));
        }
        return v;
    } else return {};
}

vector<pair<PersonID, PersonID>> Datastructure::all_friendships() {
    vector<pair<PersonID, PersonID>> v;
    multimap<PersonID, PersonID> mm;
    for (auto iter = graph_->main_index.begin(); iter != graph_->main_index.end(); iter++) {
        PersonID id = iter->first;
        AdjListNode* node = iter->second->head;
        while (node) {
            PersonID friendid = node->id;
            if (id < friendid) {
                mm.insert(pair<PersonID, PersonID>(id, friendid));
            } else {
                mm.insert(pair<PersonID, PersonID>(friendid, id));
            }
            node = node->next;
        }
    }

    auto iter = mm.begin();
    while (iter != mm.end()) {
        if (!personid_exists(v, (*iter)))
            v.push_back((*iter));
        iter++;
    }
    return v;
}



vector<pair<PersonID, Cost>> Datastructure::shortest_friendpath(PersonID fromid, PersonID toid) {
    if (m_.find(fromid) != m_.end() && m_.find(toid) != m_.end()) {
        vector<pair<PersonID, Cost>> vec;
        // int vertices = graph_->vertices;

        // Dijkstra
        map<PersonID, PersonID> parent;
        map<PersonID, bool> visited;
        map<PersonID, DijkstraNode> dist;
        priority_queue<DijkstraNode> q;

        for (auto iter = graph_->main_index.begin(); iter != graph_->main_index.end(); ++iter) {
            PersonID id = iter->first;
            dist[id].id = id;
            dist[id].cost = INF;
            parent[id] = NO_ID;
            visited[id] = false;
        }
        dist[fromid].cost = 0;
        q.push(dist[fromid]);
        while (!q.empty()) {
            DijkstraNode cd = q.top();
            q.pop();
            PersonID u = cd.id;
            // vec.push_back(make_pair(u, dist[u].eachcost));
            if (u == toid) break;
            if (visited[u]) continue;
            visited[u] = true;
            AdjListNode* p = graph_->main_index[u]->head;
            while (p) {
                PersonID v = p->id;
                if (!visited[v] && dist[v].cost > dist[u].cost + p->cost) {
                    dist[v].cost = dist[u].cost + p->cost;
                    dist[v].eachcost = p->cost;
                    parent[v] = u;
                    q.push(dist[v]);
                }
                p = p->next;
            }
        }

        stack<pair<PersonID, Cost>> stk;
        PersonID parentid = toid;
        while (parentid != fromid) {
            stk.push(make_pair(parentid, dist[parentid].eachcost));
            parentid = parent[parentid];
        }
        while (!stk.empty()) {
            vec.push_back(stk.top());
            stk.pop();
        }

        if (dist[toid].cost != INF) return vec;
        else return {}; // Shortest path doesnt exist

    } else return {};
}

bool Datastructure::check_boss_hierarchy() {
    return false; // Replace this with the actual implementation
}

vector<pair<PersonID, Cost>> Datastructure::cheapest_friendpath(PersonID fromid, PersonID toid) {
    return {}; // Replace this with the actual implementation
}

pair<unsigned int, Cost> Datastructure::leave_cheapest_friendforest() {
    return {}; // Replace this with the actual implementation
}

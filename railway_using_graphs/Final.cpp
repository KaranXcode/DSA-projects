#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
using namespace std;
class Parcel
{
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority)
    {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap
{
public:
    std::vector<Parcel *> heap;

    int parent(int i)
    {
        return (i - 1) / 2; // fill in this function
    }

    int left(int i)
    {
        return (2 * i + 1); // fill in this function
    }

    int right(int i)
    {
        return (2 * i + 2); // fill in this function
    }

    Parcel *get_max()
    {
        if (heap.size() > 0)
        {
            return heap[0];
        } // fill in this function
    }
    void max_heapify(int i)
    {
        int largest = i;
        int l = left(i);
        int r = right(i);
        if (heap[l] != NULL && heap[r] != NULL)
        {
            if (left(i) <= heap.size() && heap[l]->priority > heap[largest]->priority)
            {
                largest = l;
            }
            if (right(i) <= heap.size() && heap[r]->priority > heap[largest]->priority)
            {
                largest = r;
            }
            if (largest != i)
            {
                swap(heap[i], heap[largest]);
                max_heapify(largest);
            }
        }
        // function that maintains the max heap property
    }
    Parcel *extract_max()
    {

        Parcel *max = get_max();
        if (heap.size() > 0)
        {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            max_heapify(0);
        }
        return max;

        // function that returns the max element and removes it from the heap
    }
    void insert(Parcel *item)
    {
        heap.push_back(item);
        int size = heap.size() - 1;
        while (size > 0 && heap[size]->priority > heap[parent(size)]->priority)
        {
            swap(heap[parent(size)], heap[size]);
            size = parent(size);
        }
        // function that inserts item into the heap
    }

    bool is_empty()
    {
        return heap.empty();
    }
};

class FreightCar
{
public:
    int max_parcel_capacity;
    std::vector<Parcel *> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;

    FreightCar(int max_parcel_capacity)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel *parcel)
    {
        if (parcels.size() < max_parcel_capacity)

            parcels.push_back(parcel);
        else
            return; // load parcel
    }

    bool can_move()
    {
        if (parcels.size() == max_parcel_capacity)
        {
            return true;
            // if length of parcels is equal to max_parcel_capacity return true else return false
        }
        else
        {
            return false;
        }
    }

    void move(std::string destination)
    {
        // function that moves freight car to destination (link)
    }
};

class Vertex
{
public:
    std::string name;
    std::string colour;
    Vertex *parent;
    std::vector<FreightCar *> freight_cars;
    std::vector<Vertex *> neighbors;
    // trains_to_move is dict of destination and freight cars
    std::map<std::string, std::vector<FreightCar *>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap *> parcel_destination_heaps;
    std::vector<FreightCar *> sealed_freight_cars;
    std::vector<Parcel *> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        this->name = name;
        this->colour = "white";
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    Vertex *getparentPtr() const
    {
        return parent;
    }

    // Setter for rightptr
    void setparentPtr(Vertex *new_parentptr)
    {
        parent = new_parentptr;
    }
    void add_neighbor(Vertex *neighbor)
    {
        neighbors.push_back(neighbor); // add neighbor to neighbors vector
    }

    // add get neighbors function
    std::vector<Vertex *> get_neighbors()
    {
        return this->neighbors;
    }

    std::vector<Parcel *> get_all_current_parcels()
    {
        return all_parcels;
        // get all parcels from all destination heaps
    }

    void clean_unmoved_freight_cars()
    {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
        for (int i = freight_cars.size()-1; i >=0 ; i--)
        {
            if (freight_cars[i]->parcels.size() < freight_cars[i]->max_parcel_capacity)
            {
               for(auto &j:freight_cars[i]->parcels){
                   loadParcel(j);
               }
            }
            freight_cars.erase(freight_cars.begin() + i);
        }
    }

    void loadParcel(Parcel *parcel)
    {
        if (!parcel->delivered)
        {
            int t = 0;
            for (auto &i : parcel_destination_heaps)
            {
                if (i.first == parcel->destination)
                {
                    i.second->insert(parcel);
                    t = 1;
                    break;
                }
            }
            if (t == 0)
            {
                MaxHeap *obj = new MaxHeap();
                obj->insert(parcel);
                parcel_destination_heaps.emplace(parcel->destination, obj);
            }
        }
    }
    void loadFreightCars()
    {
        for (auto &i : this->parcel_destination_heaps)
        {
            if (i.second->heap.size() <= max_parcel_capacity)
            {
                FreightCar *freightcar = new FreightCar(i.second->heap.size());
                freightcar->current_location = this->name;
                freightcar->destination_city = i.first;
                freight_cars.push_back(freightcar);
                for (auto &parcel : i.second->heap)
                {

                    Parcel *j = i.second->extract_max();

                    freightcar->load_parcel(j);
                }
            }
            else
            {
                if ((i.second->heap.size() % max_parcel_capacity) == 0)
                {
                    int n = (i.second->heap.size() / max_parcel_capacity);
                    for (int j = 0; j < n; j++)
                    {
                        FreightCar *freightcar = new FreightCar(max_parcel_capacity);
                        freightcar->current_location = this->name;
                        freightcar->destination_city = i.first;
                        freight_cars.push_back(freightcar);
                        for (auto &parcel : i.second->heap)
                        {

                            if (freightcar->can_move())
                            {
                                break;
                            }
                            Parcel *j = i.second->extract_max();
                            freightcar->load_parcel(j);
                        }
                    }
                }
                else if ((i.second->heap.size() % max_parcel_capacity) != 0)
                {
                    int p = (i.second->heap.size() / max_parcel_capacity);
                    for (int m = 0; m < p + 1; m++)
                    {
                        FreightCar *freightcar = new FreightCar(max_parcel_capacity);
                        freightcar->current_location = this->name;
                        freightcar->destination_city = i.first;
                        freight_cars.push_back(freightcar);
                        for (auto &parcel : i.second->heap)
                        {
                            if (freightcar->can_move())
                            {
                                break;
                            }
                            Parcel *j = i.second->extract_max();
                            freightcar->load_parcel(j);
                        }
                    }
                }
            }
            // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        }
    }
    void print_parcels_in_heaps()
    {
        cout << this->parcel_destination_heaps.size() << endl;
        for (auto &i : this->parcel_destination_heaps)
        {
            for (auto &parcel : i.second->heap)
            {
                std::cout << "Parcel ID: " << parcel->parcel_id << "delivered: " << parcel->delivered << ", Parcel origin: " << parcel->origin << ", Parcel location: " << parcel->current_location << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
            }
        }
    }
    void print_parcels_in_freight_cars()
    {
        this->loadFreightCars();
        cout << freight_cars.size() << endl;
        for (auto &i : this->freight_cars)
        {
            cout << "parcels size  " << i->parcels.size() << endl;
            for (auto &parcel : i->parcels)
            {
                std::cout << "Parcel origin: " << parcel->origin << "  Parcel destination: " << parcel->destination << "  priority:" << parcel->priority << std::endl;
            }
        }
    }
};

class Graph
{

public:
    std::list<Vertex *> vertices;
    std::vector<std::pair<Vertex *, Vertex *>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        int flag1 = 0, flag2 = 0;
        Vertex *s;
        Vertex *d;
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                s = i;
            }
            if (i->name == destination)
            {
                d = i;
            }
        }
        edges.emplace_back(s, d);
        Vertex *result1, *result2;
        for (auto &i : this->vertices)
        {
            if (i->name == source)
            {
                flag1 = 1;
                result1 = i;
            }

            else if (i->name == destination)
            {
                flag2 = 1;
                result2 = i;
            }
        }

        if (flag1 == 0 && flag2 == 0)
        {
            Vertex *first = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            Vertex *firstneighbour = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(first);
            vertices.back()->add_neighbor(firstneighbour);
            vertices.push_back(firstneighbour);
            vertices.back()->add_neighbor(first);
        }
        else if (flag1 == 1 && flag2 == 0)
        {
            Vertex *newdest = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(newdest);
            vertices.back()->add_neighbor(result1);
            result1->add_neighbor(vertices.back());
        }
        else if (flag2 == 1 && flag1 == 0)
        {
            Vertex *newsource = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(newsource);
            vertices.back()->add_neighbor(result2);
            result2->add_neighbor(vertices.back());
        }
        else if (flag1 == 1 && flag2 == 1)
        {
            result1->add_neighbor(result2);
            result2->add_neighbor(result1);
        }

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
    }

    void print_graph()
    {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto &vertex : this->vertices)
        {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto &neighbor : vertex->neighbors)
            {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::string> bfs(std::string source, std::string destination)
    {
        for (auto &i : vertices)
        {
            i->colour = "white";
        }
        vector<string> shortest;
        Vertex *s;
        Vertex *d;
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                s = i;
            }
            if (i->name == destination)
            {
                d = i;
            }
        }
        for (auto &i : vertices)
        {
            i->setparentPtr(nullptr);
        }
        s->colour = "gray";
        queue<Vertex *> myque;
        myque.push(s);
        while (!myque.empty())
        {
            Vertex *u = myque.front();
            myque.pop();
            for (auto &v : u->neighbors)
            {
                if (v->colour == "white")
                {
                    v->colour = "grey";
                    v->setparentPtr(u);
                    myque.push(v);
                }
            }
            u->colour = "black";
        }
        while (d != NULL && d != s)
        {
            shortest.push_back(d->name);
            d = d->getparentPtr();
        }
        shortest.push_back(d->name);
        reverse(shortest.begin(), shortest.end());
        return shortest; // function to return path from source to destination using bfs
    }
    vector<string> path;
    vector<vector<string>> allpaths;
    int flag = 0;
    std::vector<std::string> dfs(std::string source, std::string destination, bool b = true)
    {
        if (b)
        {
            for (auto &i : vertices)
            {
                i->colour = "white";
            }
        }
        Vertex *s, *d;
        double p;

        for (auto &i : vertices)
        {
            if (i->name == source)
            {

                s = i;
            }
            if (i->name == destination)
            {

                d = i;
            }
            p++;
        }
        s->colour = "grey";
        path.push_back(source);
        if (source == destination)
        {

            allpaths.push_back(path);
            d->colour = "white";
            path.pop_back();
            return allpaths.front();
        }
        for (auto &v : s->neighbors)
        {
            if (v->colour == "white")
            {
                dfs(v->name, destination, false);
            }
        }
        path.pop_back();
        if (allpaths.empty())
        {
            return vector<string>();
        }
        else
        {
            return allpaths.front();
        }
        // function to return path from source to destination using dfs
    }

    void groupFreightCars()
    {
        

        for (auto &vertex : vertices)
        {
            vertex->loadFreightCars();
            for (auto &freight : vertex->freight_cars)
            {
                if (freight->parcels.size() == freight->max_parcel_capacity)
                {
                    freight->sealed = true;
                    freight->current_location = vertex->name;
                    vertex->sealed_freight_cars.push_back(freight);
                }
            }
          
            for (auto &frieghtcar : vertex->sealed_freight_cars)
            {
                int flag = 0;
                for (auto &k : vertex->trains_to_move)
                {
                    if (k.first == bfs(frieghtcar->current_location, frieghtcar->destination_city)[1])
                    {
                        flag = 1;
                        frieghtcar->next_link = k.first;
                        k.second.push_back(frieghtcar);
                        break;
                    }
                }
                if (flag == 0)
                {
                    
                    vector<FreightCar *> car;
                    frieghtcar->next_link = bfs(frieghtcar->current_location, frieghtcar->destination_city)[1];

                    car.push_back(frieghtcar);

                    vertex->trains_to_move.insert({frieghtcar->next_link, car});
                   
                }
            }

            vertex->sealed_freight_cars.clear();
            for (auto &trains : vertex->trains_to_move)
            {
                if (trains.second.size() < vertex->min_freight_cars_to_move)
                {
                    for (auto &k : trains.second)
                    {
                        vertex->sealed_freight_cars.push_back(k);
                    }
                    for (auto &k : trains.second)
                    {
                        trains.second.pop_back();
                    }
                }
            }
           
            for (auto &frieghtcar1 : vertex->sealed_freight_cars)
            {
          
                int flag = 0;
                for (auto &p : vertex->trains_to_move)
                {
                    if (p.first == dfs(frieghtcar1->current_location, frieghtcar1->destination_city)[1])
                    {
                       
                        flag = 1;
                        p.second.push_back(frieghtcar1);
                    }
                }

                if (flag == 0)
                {
                   
                    vector<FreightCar *> car1;
                    frieghtcar1->next_link = dfs(frieghtcar1->current_location, frieghtcar1->destination_city)[1];
                    car1.push_back(frieghtcar1);
                    vertex->trains_to_move.insert({frieghtcar1->next_link, car1});
                }
            }
           
            vertex->clean_unmoved_freight_cars();
        }

        // for every vertex, group freight cars by links
    }

    void moveTrains()
    {
        for (auto &vertex2 : vertices)
        {
            for (auto &eachtrain : vertex2->trains_to_move)
            {
                Vertex *previous = vertex2;
                if (eachtrain.second.size() >= vertex2->min_freight_cars_to_move)
                {
                    for (int i = previous->freight_cars.size() - 1; i >= 0; i--)
                    {
                        for (int j = 0; j < eachtrain.second.size(); j++)
                        {
                            if (previous->freight_cars[i] == eachtrain.second[j])
                            {
                                // for (int k=0; k < eachtrain.second[j]->parcels.size(); k++)
                                // {
                                //     previous->all_parcels.erase(previous->all_parcels.begin() + k);
                                //     k--;
                                // }
                                previous->freight_cars.erase(previous->freight_cars.begin() + i);
                            }
                        }
                    }
                    for (int i = previous->all_parcels.size() - 1; i >= 0; i--)
                    {
                        for (auto &j : eachtrain.second)
                        {
                            for (int k = 0; k < j->parcels.size(); k++)
                            {
                                if (previous->all_parcels[i] == j->parcels[k])
                                {
                                    previous->all_parcels.erase(previous->all_parcels.begin() + i);
                                }
                            }
                        }
                    }

                    for (auto &eachvertex : vertices)
                    {
                        if (eachtrain.first == eachvertex->name)
                        {
                            for (auto &i : eachtrain.second)
                            {
                                i->current_location = eachtrain.first;
                                eachvertex->freight_cars.push_back(i);
                                for (auto &j : i->parcels)
                                {
                                    eachvertex->all_parcels.push_back(j);
                                    if (j->destination == i->destination_city)
                                    {
                                        j->delivered = true;
                                    }
                                }
                            }
                        }
                    }
                    eachtrain.second.clear();
                }
            }
            // for every vertex, move freight cars to next link
        }
    }
};

class PRC
{
public:
    Graph graph;
    std::vector<FreightCar *> freight_cars;
    std::map<std::string, Parcel *> parcels;
    std::map<int, std::vector<Parcel *>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};
    }

    void create_graph(std::string graph_file_name)
    {
        ifstream input_file(graph_file_name);
        string line;
        while (getline(input_file, line))
        {
            int count = 0;
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    count++;
                }
            }
            string a[count + 1];
            int l = 0;
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    l++;
                }
                else
                {
                    if (line[i] != ',')
                    {
                        a[l] += line[i];
                    }
                }
            }
            graph.add_edge(a[0], a[1], min_freight_cars_to_move, max_parcel_capacity);
        }
        // read graph.txt file and create graph
    }

    void process_parcels(std::string parcels_file_name)
    {
        ifstream input_file(parcels_file_name);
        string line;
        while (getline(input_file, line))
        {
            int count = 0;
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    count++;
                }
            }
            string a[count + 1];
            int l = 0;
            int tim = 0;
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    l++;
                }
                else
                {
                    if (line[i] != ',')
                    {
                        a[l] += line[i];
                    }
                }
                tim++;
            }
            Parcel *parcel = new Parcel(stoi(a[0]), a[1], a[2], a[3], stoi(a[4]));
            parcels.insert({a[1], parcel});
            old_state = get_state();
        } // read parcels.txt file and create parcels
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel *> get_bookings(int time_tick, std::string vertex)
    {
        run_simulation(time_tick);
        for (auto &i : graph.vertices)
        {
            if (i->name == vertex)
            {
                return i->all_parcels;
            }
        }
    }

    std::map<std::string, std::string> get_state()
    {
        std::map<std::string, std::string> state;
        // from this.parcels
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *parcel = parcel_pair.second;
            state[parcel->parcel_id] = parcel->current_location;
        }
        return state;

      
    }

        void run_simulation(int run_till_time_tick = -1)
    {
        double pamda;

        new_state.clear();
        while (run_till_time_tick != 0 && this->time_tick <= this->max_time_tick)
        {
            if (run_till_time_tick > 0 && this->time_tick > run_till_time_tick)
            {
                break;
            }

            for (auto &parcel_pair : this->parcels)
            {
                Parcel *parcel = parcel_pair.second;
                if (parcel->time_tick == this->time_tick && !parcel->delivered)
                {
                    for (auto &vertex : this->graph.vertices)
                    {
                        if (vertex->name == parcel->origin)
                        {
                            vertex->loadParcel(parcel);
                            vertex->all_parcels.push_back(parcel);
                        }
                    }
                }
            }

            this->graph.groupFreightCars();
            this->graph.moveTrains();

            this->time_tick++;

            new_state = get_state();
            if (new_state == old_state)
            {
                break;
            }
            else
            {
                old_state = new_state;
            }
        }
    }

    bool convergence_check()
    {
        if (new_state.size() == 0)
        {
            return false;
        }
        int p = 0;
        for (auto &i : old_state)
        {
            if (old_state[i.first] != new_state[i.first])
            {
                p = 1;
                break;
            }
        }
        if (p == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
        old_state = new_state;
    }

    bool all_parcels_delivered()
    {
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *parcel = parcel_pair.second;
            if (!parcel->delivered)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels()
    {
        vector<string> ids;
        double baby;
        for (auto &i : graph.vertices)
        {
            baby++;
            for (auto &j : i->all_parcels)
            {
                if (!j->delivered)
                {
                    ids.push_back(j->parcel_id);
                }
            }
        }
        return ids;
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels()
    {
        vector<string> ids;
        for (auto &i : graph.vertices)
        {

            for (auto &j : i->all_parcels)
            {
                if (j->delivered)
                {
                    ids.push_back(j->parcel_id);
                }
            }
        }
        return ids;
       
    }

    
    std::vector<std::string> get_status_of_all_parcels(int t)
    {
        run_simulation(t);
        vector<string> status;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                string info = j->parcel_id + " " + j->current_location + " " + to_string(j->delivered) + "\n";
                status.push_back(info);
            }
        }
        
    }

    std::string get_status_of_parcel(std::string parcel_id, int t)
    {
        run_simulation(t);
        string status;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->parcel_id == parcel_id)
                    status = j->parcel_id + " " + j->current_location + " " + to_string(j->delivered);
            }
        }
        return status;
    }
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t)
    {
        run_simulation(t);
        vector<string> delivered;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->delivered == true)
                {
                    delivered.push_back(j->parcel_id);
                }
            }
        }
        return delivered;
    }
};
// int main()
// {

//     PRC prc = PRC(2, 2);
//     prc.create_graph("samples/4/graph.txt");
//     // prc.create_graph();
//     prc.process_parcels("samples/4/bookings.txt");
//     // prc.run_simulation();
//     // prc.graph.print_graph();
//     // std::vector<std::string> dfs_path = prc.graph.dfs("Rohtak", "Chennai");
//     // for(auto &i:dfs_path){
//     //     cout << i << endl;
//     // }
//     for (auto &i : prc.graph.vertices)
//     {
//         cout << i->name << endl;
//         i->print_parcels_in_heaps();
//         cout << endl;
//         cout << endl;
//     }
//     return 0;
// }
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop
{
private:
    std::string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(std::string name, MetroLine *metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(std::string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name)
{
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{

    MetroStop *stop = node;
    while (stop != nullptr)
    {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    MetroStop *stop = node;
    int count = 0;
    while (stop != NULL)
    {
        count++;
        stop = stop->getNextStop();
    }
    return count;
}

void MetroLine::populateLine(std::string filename)
{
    if (filename != "blue.txt" && filename != "green.txt" && filename != "orange.txt" && filename != "violet.txt" && filename != "red.txt" && filename != "magenta.txt" && filename != "yellow.txt")
    {
        return;
    }
    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        cerr << "Unable to open the file." << endl;
        return;
    }
    string line, out;
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
        string b[1];
        for (int i = 0; i < count; i++)
        {
            if (i != count - 1)
            {
                b[0] = b[0] + a[i] + " ";
            }
            else
            {
                b[0] = b[0] + a[i];
            }
        }
        b[1] = a[count];

        MetroStop *newstop = new MetroStop(b[0], this, stoi(b[1]));

        if (node == nullptr)
        {
            node = newstop;
        }
        else
        {

            MetroStop *temp = node;
            while (temp->getNextStop() != nullptr)
            {
                temp = temp->getNextStop();
            }
            temp->setNextStop(newstop);
            newstop->setPrevStop(temp);
        }

        // Read the file and populate the line
    }

    input_file.close();
}

// AVLNode class
class AVLNode
{
private:
    std::string stopName;
    std::vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(std::string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const
{
    return stopName;
}

const std::vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root;

public:
    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);

    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    AVLNode *rotateLeft(AVLNode *node);
    AVLNode *rotateRight(AVLNode *node);
    AVLNode *balance(AVLNode *node);
    int stringCompare(string s1, string s2);
    AVLNode *insert(AVLNode *node, MetroStop *metroStop);
    void populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(string stopName);
};

AVLNode *AVLTree::getRoot() const
{
    return root;
}

void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int lh = 0;
    int rh = 0;
    lh = height(node->getLeft()) + 1;
    rh = height(node->getRight()) + 1;
    return max(lh, rh);
}

int AVLTree::stringCompare(string s1, string s2)
{
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}
int AVLTree::balanceFactor(AVLNode *node)
{
    return height(node->getLeft()) - height(node->getRight());
}

AVLNode *AVLTree::rotateLeft(AVLNode *x)
{
    AVLNode *y = x->getRight();
    AVLNode *T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    if (T2 != nullptr)
    {
        T2->setParent(x);
    }
    if (x->getParent() != nullptr)
    {
        if (x->getParent()->getLeft() == x)
        {
            x->getParent()->setLeft(y);
        }
        else
        {
            x->getParent()->setRight(y);
        }
    }
    else
    {
        setRoot(y);
    }
    y->setParent(x->getParent());
    x->setParent(y);
    return y;
}
AVLNode *AVLTree::rotateRight(AVLNode *y)
{
    AVLNode *x = y->getLeft();
    AVLNode *T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    if (T2 != nullptr)
    {
        T2->setParent(y);
    }
    if (y->getParent() != nullptr)
    {
        if (y->getParent()->getLeft() == y)
        {
            y->getParent()->setLeft(x);
        }
        else
        {
            y->getParent()->setRight(x);
        }
    }
    else
    {
        setRoot(x);
    }
    x->setParent(y->getParent());
    y->setParent(x);
    return x;
}

AVLNode *AVLTree::balance(AVLNode *n)
{
    int bf = balanceFactor(n);
    if (bf > 1)
    {
        if (balanceFactor(n->getLeft()) < 0)
        {
            n->setLeft(rotateLeft(n->getLeft()));
        }
        return rotateRight(n);
    }
    if (bf < -1)
    {
        if (balanceFactor(n->getRight()) > 0)
        {
            n->setRight(rotateRight(n->getRight()));
        }
        return rotateLeft(n);
    }
    return n;
}

AVLNode *AVLTree::insert(AVLNode *node, MetroStop *metroStop)
{
    AVLNode *newnode = new AVLNode(metroStop->getStopName());
    if (node == NULL)
    {
        newnode->addMetroStop(metroStop);
        return newnode;
    }
    if (stringCompare(metroStop->getStopName(), node->getStopName()) < 0)
    {
        AVLNode *leftChild = insert(node->getLeft(), metroStop);
        if (leftChild->getParent() == nullptr)
        {
            leftChild->setParent(node);
            node->setLeft(leftChild);
        }
    }
    else if (stringCompare(metroStop->getStopName(), node->getStopName()) > 0)
    {
        AVLNode *RightChild = insert(node->getRight(), metroStop);
        if (RightChild->getParent() == nullptr)
        {
            RightChild->setParent(node);
            node->setRight(RightChild);
        }
    }
    return balance(node);
}
void AVLTree::populateTree(MetroLine *metroLine)
{
    MetroStop *temp = metroLine->getNode();
    if (getRoot()->getStops().size() == 0)
    {
        getRoot()->addMetroStop(temp);
        temp = temp->getNextStop();
    }

    AVLNode *node = getRoot();
    while (temp != NULL)
    {
        if (searchStop(temp->getStopName()) == nullptr)
        {
            node = insert(node, temp);
        }
        else
        {
            searchStop(temp->getStopName())->addMetroStop(temp);
        }
        temp = temp->getNextStop();
    }
}
void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;

    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode *AVLTree::searchStop(string stopName)
{

    AVLNode *head = this->getRoot();

    AVLNode *temp = head;

    while (temp != NULL && temp->getStopName() != stopName)
    {

        if (stringCompare(stopName, temp->getStopName()) < 0)
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }

    return temp;
}

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    Trip(MetroStop *metroStop, Trip *previousTrip);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip *> getTrips() const;

    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

std::queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop *> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop *stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

std::vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}
void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::printPath() const
{
    for (auto stop : stops)
    {
        
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree *getTree() const;
    const std::vector<MetroLine *> &getLines() const;
};

PathFinder::PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}

const std::vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    tree->setRoot(nullptr);
    for (auto line : lines)
    {
        if (tree->getRoot() == nullptr)
        {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
}

Path *PathFinder::findPath(std::string origin, std::string destination)
{
    int x = 0;
    Path *path=new Path() ;
    MetroStop *temp = getTree()->searchStop(origin)->getStops()[0];
    Exploration que;
    Trip *prev = NULL;
    while (temp!= NULL)
    {
        Trip *newtrip ;
        if (tree->searchStop(temp->getStopName())->getStops().size() == 1)
        {
            newtrip = new Trip(temp, prev); 
            prev = newtrip;
            if (temp->getStopName() == destination)
            {
                
                while (newtrip->getPrev()!=nullptr)
                {
                    path->addStop(newtrip->getNode());
                    x = newtrip->getNode()->getFare() - newtrip->getPrev()->getNode()->getFare();
                    path->setTotalFare(path->getTotalFare() + x);
                   
                   
                    newtrip = newtrip->getPrev();
                }
                path->addStop(newtrip->getNode());
                return path;
                
                 }
                
        }
        else
        {
         for (auto i : tree->searchStop(temp->getStopName())->getStops())
            {
                Trip *newtrip1 = new Trip(i, newtrip);
                que.enqueue(newtrip1);
            }
            Trip *current = que.getTrips().front();
            MetroStop *temp = current->getNode()->getNextStop();
            Trip* prev2 = current;
            Trip *prev3 = prev2;
            Trip *newtrip2;
            while (temp != NULL)
            {
                newtrip2 = new Trip(temp, prev2);
                prev2 = newtrip2;
                if(temp->getStopName()==destination){
                    while (newtrip2->getPrev() != nullptr)
                    {
                        x = newtrip->getNode()->getFare() - newtrip->getPrev()->getNode()->getFare();
                        path->addStop(newtrip2->getNode());
                        path->setTotalFare(path->getTotalFare() + x);
                        newtrip2 = newtrip2->getPrev();
                    }
                    path->addStop(newtrip2->getNode());
                    return path;
                }
                temp = temp->getNextStop();
            }
            
            if(temp==NULL){
                que.dequeue();
            }
            MetroStop *temp1 = current->getNode()->getPrevStop();
            Trip *newtrip3;
            while (temp1 != NULL )
            {
                newtrip3 = new Trip(temp1, prev3);
                prev3 = newtrip3;
                if(temp1->getStopName()==destination){
                    while (newtrip3->getPrev() != nullptr)
                    {
                        x = newtrip->getNode()->getFare() - newtrip->getPrev()->getNode()->getFare();
                        path->addStop(newtrip3->getNode());
                        path->setTotalFare(path->getTotalFare() + x);
                        newtrip3 = newtrip3->getPrev();
                    }
                    path->addStop(newtrip3->getNode());
                    return path;
                }
                temp1 = temp1->getNextStop();
            }
        }
        temp = temp->getNextStop();
    }
}
vector<MetroLine *> lines;
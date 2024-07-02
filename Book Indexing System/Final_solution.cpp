#include <bits/stdc++.h>
using namespace std;
vector<string> chapterlist;

class HybridNode
{
public:
    string key;              // Word
    string element;          // Chapter
    HybridNode *parent;      // Parent node
    HybridNode *left_child;  // Left child node
    HybridNode *right_child; // Right child node
    HybridNode *next_node;   // Next node in the linked list
    string color = "black";  // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};
class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts; // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val)
    {
        for (int i = 0; i < chapterlist.size(); i++)
        {
            pair<string, int> *a = new pair<string, int>(chapterlist[i].substr(0, chapterlist[i].size() - 4), 0);
            chapter_word_counts.push_back(*a);
        }
    }
    void setWord(string word_val)
    { // Set the word
        word = word_val;
    }

    string getWord()
    { // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    { // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};
vector<IndexEntry> index;
class RedBlackTree
{
private:
    HybridNode *root; // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode *getRoot()
    {
        return root; // Return the root node
    }

    void setRoot(HybridNode *node)
    {
        root = node; // Set the root node
    }
    int stringCompare(string s1, string s2)
    {

        char *c1 = new char[s1.length() + 1];
        strcpy(c1, s1.c_str());

        char *c2 = new char[s2.length() + 1];
        strcpy(c2, s2.c_str());

        int result = strcmp(c1, c2);
        return result;
    }
    void leftrotate(HybridNode *x)
    {
        HybridNode *y = x->right_child;
        x->right_child = y->left_child;
        if (y->left_child != NULL)
        {
            y->left_child->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->left_child)
        {
            x->parent->left_child = y;
        }
        else
        {
            x->parent->right_child = y;
        }
        y->left_child = x;
        x->parent = y;
    }
    void rightrotate(HybridNode *y)
    {
        HybridNode *x = y->left_child;
        y->left_child = x->right_child;
        if (x->right_child != NULL)
        {
            x->right_child->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == NULL)
        {
            root = x;
        }
        else if (y == y->parent->left_child)
        {
            y->parent->left_child = x;
        }
        else
        {
            y->parent->right_child = x;
        }
        x->right_child = y;
        y->parent = x;
    }
    HybridNode *successor(HybridNode *node)
    {
        if (node == nullptr)
        {
            return NULL;
        }

        if (node->right_child != nullptr)
        {
            node = node->right_child;
            while (node->left_child != nullptr)
            {
                node = node->left_child;
            }
            return node;
        }
        HybridNode *w = node->parent;
        while (w != nullptr && node == w->right_child)
        {
            node = w;
            w = w->parent;
        }
        return w;
    }

    void balancetree(HybridNode *v, HybridNode *parentofx)
    {
        if (v != NULL && v != root)
        {

            if ((v->parent->right_child == v && v->parent->left_child->color == "black") || (v->parent->left_child == v && v->parent->right_child->color == "black"))
            {

                if (parentofx->right_child == v && parentofx->left_child->color == "black" && ((parentofx->left_child->left_child != NULL && parentofx->left_child->left_child->color == "red" && parentofx->left_child->right_child == NULL) || (parentofx->left_child->left_child != NULL && parentofx->left_child->right_child != NULL && parentofx->left_child->left_child->color == "red" && parentofx->left_child->right_child->color == "red")))
                {

                    parentofx->left_child->color = parentofx->color;
                    parentofx->left_child->left_child->color = "black";
                    parentofx->color = "black";
                    rightrotate(parentofx);
                }
                else if (parentofx->right_child == v && parentofx->left_child->color == "black" && parentofx->left_child->right_child != NULL && parentofx->left_child->right_child->color == "red" && parentofx->left_child->left_child == NULL)
                {

                    parentofx->left_child->right_child->color = parentofx->color;
                    parentofx->color = "black";
                    leftrotate(parentofx->left_child);
                    rightrotate(parentofx);
                }
                else if (parentofx->left_child == v && parentofx->right_child->color == "black" && ((parentofx->right_child->right_child != NULL && parentofx->right_child->right_child->color == "red")))
                {

                    parentofx->right_child->color = parentofx->color;
                    parentofx->right_child->right_child->color = "black";

                    parentofx->color = "black";

                    leftrotate(parentofx);
                }
                else if (parentofx->left_child == v && parentofx->right_child->color == "black" && parentofx->right_child->left_child != NULL && parentofx->right_child->left_child->color == "red")
                {

                    parentofx->right_child->left_child->color = parentofx->color;
                    parentofx->color = "black";
                    rightrotate(parentofx->right_child);
                    leftrotate(parentofx);
                }
                else if (parentofx->left_child == v && parentofx->right_child->color == "black" && ((parentofx->right_child->right_child == NULL && parentofx->right_child->left_child == NULL) || (parentofx->right_child->right_child != NULL && parentofx->right_child->right_child->color == "black" && parentofx->right_child->left_child == NULL) || (parentofx->right_child->right_child == NULL && parentofx->right_child->left_child != NULL && parentofx->right_child->left_child->color == "black") || (parentofx->right_child->right_child != NULL && parentofx->right_child->left_child != NULL && parentofx->right_child->right_child->color == "black" && parentofx->right_child->left_child->color == "black")))
                {

                    parentofx->right_child->color = "red";
                    if (parentofx->color == "black")
                    {

                        balancetree(parentofx, parentofx->parent);
                    }
                    else
                    {

                        parentofx->color = "black";
                    }
                }
                else if (parentofx->right_child == v && parentofx->left_child->color == "black" && ((parentofx->left_child->right_child == NULL && parentofx->left_child->left_child == NULL) || (parentofx->left_child->right_child != NULL && parentofx->left_child->right_child->color == "black" && parentofx->left_child->left_child == NULL) || (parentofx->left_child->right_child == NULL && parentofx->left_child->left_child != NULL && parentofx->left_child->left_child->color == "black") || (parentofx->left_child->right_child != NULL && parentofx->left_child->left_child != NULL && parentofx->left_child->right_child->color == "black" && parentofx->left_child->left_child->color == "black")))
                {

                    parentofx->left_child->color = "red";
                    if (parentofx->color == "black")
                    {

                        balancetree(parentofx, parentofx->parent);
                    }
                    else
                    {

                        parentofx->color = "black";
                    }
                }
            }
            else if ((parentofx->right_child == v && parentofx->left_child->color == "red") || (parentofx->left_child == v && parentofx->right_child->color == "red"))
            {

                if ((parentofx->left_child == v && parentofx->right_child->color == "red"))
                {

                    parentofx->right_child->color = "black";
                    parentofx->color = "red";
                    leftrotate(parentofx);
                    balancetree(v, parentofx);
                }
                else if ((parentofx->right_child == v && parentofx->left_child->color == "red"))
                {

                    parentofx->left_child->color = "black";
                    parentofx->color = "red";
                    rightrotate(parentofx);
                    balancetree(v, parentofx);
                }
            }
        }
        else if (v == NULL)
        {

            if (parentofx->left_child == v && (parentofx->right_child == NULL || parentofx->right_child->color == "black") && ((parentofx->right_child->right_child == NULL && parentofx->right_child->left_child == NULL) || (parentofx->right_child->right_child != NULL && parentofx->right_child->right_child->color == "black" && parentofx->right_child->left_child == NULL) || (parentofx->right_child->right_child == NULL && parentofx->right_child->left_child != NULL && parentofx->right_child->left_child->color == "black") || (parentofx->right_child->right_child != NULL && parentofx->right_child->left_child != NULL && parentofx->right_child->right_child->color == "black" && parentofx->right_child->left_child->color == "black")))
            {

                parentofx->right_child->color = "red";
                if (parentofx->color == "black")
                {

                    balancetree(parentofx, parentofx->parent);
                    return;
                }
                else
                {

                    parentofx->color = "black";
                }
            }
            else if (parentofx->right_child == v && parentofx->left_child->color == "black" && ((parentofx->left_child->right_child == NULL && parentofx->left_child->left_child == NULL) || (parentofx->left_child->right_child != NULL && parentofx->left_child->right_child->color == "black" && parentofx->left_child->left_child == NULL) || (parentofx->left_child->right_child == NULL && parentofx->left_child->left_child != NULL && parentofx->left_child->left_child->color == "black") || (parentofx->left_child->right_child != NULL && parentofx->left_child->left_child != NULL && parentofx->left_child->right_child->color == "black" && parentofx->left_child->left_child->color == "black")))
            {

                parentofx->left_child->color = "red";
                if (parentofx->color == "black")
                {
                    balancetree(parentofx, parentofx->parent);
                }
                else
                {
                    parentofx->color = "black";
                }
            }
            else if ((parentofx->right_child == v && parentofx->left_child->color == "black") || (parentofx->left_child == v && parentofx->right_child->color == "black"))
            {

                if (parentofx->right_child == v && parentofx->left_child->color == "black" && ((parentofx->left_child->left_child != NULL && parentofx->left_child->left_child->color == "red" && parentofx->left_child->right_child == NULL) || (parentofx->left_child->left_child != NULL && parentofx->left_child->right_child != NULL && parentofx->left_child->left_child->color == "red" && parentofx->left_child->right_child->color == "red")))
                {

                    parentofx->left_child->color = parentofx->color;
                    parentofx->left_child->left_child->color = "black";
                    parentofx->color = "black";
                    rightrotate(parentofx);
                }
                else if (parentofx->right_child == v && parentofx->left_child->color == "black" && parentofx->left_child->right_child != NULL && parentofx->left_child->right_child->color == "red" && parentofx->left_child->left_child == NULL)
                {

                    parentofx->left_child->right_child->color = parentofx->color;
                    parentofx->color = "black";
                    leftrotate(parentofx->left_child);
                    rightrotate(parentofx);
                }
                else if (parentofx->left_child == v && parentofx->right_child->color == "black" && ((parentofx->right_child->right_child != NULL) && (parentofx->right_child->right_child->color == "red" && parentofx->right_child->left_child == NULL) || (parentofx->right_child->right_child != NULL) && (parentofx->right_child->left_child != NULL) && (parentofx->right_child->right_child->color == "red" && parentofx->right_child->left_child->color == "red")))
                {

                    parentofx->right_child->color = parentofx->color;
                    parentofx->right_child->right_child->color = "black";

                    parentofx->color = "black";

                    leftrotate(parentofx);
                }
                else if (parentofx->left_child == v && parentofx->right_child->color == "black" && parentofx->right_child->left_child != NULL && parentofx->right_child->left_child->color == "red" && parentofx->right_child->right_child == NULL)
                {

                    parentofx->right_child->left_child->color = parentofx->color;
                    parentofx->color = "black";
                    rightrotate(parentofx->right_child);
                    leftrotate(parentofx);
                }
            }
            else if ((parentofx->right_child == v && parentofx->left_child->color == "red") || (parentofx->left_child == v && parentofx->right_child->color == "red"))
            {

                if ((parentofx->left_child == v && parentofx->right_child->color == "red"))
                {

                    parentofx->right_child->color = "black";
                    parentofx->color = "red";
                    leftrotate(parentofx);
                    balancetree(v, parentofx);
                }
                else if ((parentofx->right_child == v && parentofx->left_child->color == "red"))
                {

                    parentofx->left_child->color = "black";
                    parentofx->color = "red";
                    rightrotate(parentofx);
                    balancetree(v, parentofx);
                }
            }
        }
        else if (v == root)
        {
            return;
        }
    }

    bool deleteNode(string key)
    {

        HybridNode *x = search(key);

        HybridNode *w, *v;
        if (x->left_child == NULL || x->right_child == NULL)
        {

            w = x;
        }
        else
        {
            w = successor(x);
        }
        if (w != x)
        {

            x->key = w->key;
            x->element = w->element;
        }
        if (w->left_child != NULL)
        {
            v = w->left_child;
        }
        else
        {
            v = w->right_child;
        }
        if (v != NULL)
        {
            v->parent = w->parent;
        }
        if (w->parent == NULL)
        {
            root = v;
        }
        else if (w->parent->left_child == w)
        {
            w->parent->left_child = v;
        }
        else
        {
            w->parent->right_child = v;
        }
        // if (w->parent->right_child->left_child)
        //

        if ((w->color == "red") || (w->color == "black" && v != NULL && v->color == "red"))
        {
            if (v != NULL)
            {

                v->color = "black";
            }
        }
        else
        {

            balancetree(v, w->parent);
        }
        // Implement Red-Black Tree deletion
    }

    void deleterepeated()
    {
        for (int i = 0; i < index.size(); i++)
        {
            int flag = 0;
            vector<pair<string, int>> vec1 = index[i].getChapterWordCounts();
            for (int j = 0; j < chapterlist.size(); j++)
            {

                if (vec1[j].second == 0)
                {
                    flag = 1;
                }
            }
            if (flag == 0)
            {

                deleteNode(index[i].getWord());
                index.erase(index.begin() + i);
                i--;
            }
        }
    }
    HybridNode *insert(string key, string element)
    {
        // IndexEntry* word;
        HybridNode *par = NULL;
        HybridNode *newnode = new HybridNode(key, element);
        HybridNode *temp = getRoot();

        while (temp != NULL)
        {

            par = temp;
            if (stringCompare(newnode->key, temp->key) < 0)
            {
                temp = temp->left_child;
            }
            else if (stringCompare(newnode->key, temp->key) > 0)
            {
                temp = temp->right_child;
            }

            else
            {

                for (int i = 0; i < index.size(); i++)
                {

                    if (key == index[i].getWord())
                    {

                        vector<pair<string, int>> vec = index[i].getChapterWordCounts();
                        for (int k = 0; k < chapterlist.size(); k++)
                        {
                            if (element == index[i].getChapterWordCounts()[k].first)
                            {
                                vec[k].second++;
                                index[i].setChapterWordCounts(vec);
                            }
                        }
                    }
                }
                temp = temp->left_child;
                return nullptr;
            }
        }
        newnode->parent = par;
        if (par == NULL)
        {
            root = newnode;
            IndexEntry *newword = new IndexEntry(newnode->key);
            vector<pair<string, int>> v = newword->getChapterWordCounts();
            for (int i = 0; i < chapterlist.size(); i++)
            {
                if (newnode->element == newword->getChapterWordCounts()[i].first)
                {
                    v[i].second++;
                    newword->setChapterWordCounts(v);
                    break;
                }
            }
            index.push_back(*newword);
        }
        else
        {
            if (stringCompare(newnode->key, par->key) < 0)
            {
                newnode->color = "red";
                par->left_child = newnode;
                IndexEntry *newword = new IndexEntry(newnode->key);
                vector<pair<string, int>> v = newword->getChapterWordCounts();
                for (int i = 0; i < chapterlist.size(); i++)
                {
                    if (newnode->element == newword->getChapterWordCounts()[i].first)
                    {
                        v[i].second++;
                        newword->setChapterWordCounts(v);
                        break;
                    }
                }
                index.push_back(*newword);
            }
            else if (stringCompare(newnode->key, par->key) > 0)
            {
                newnode->color = "red";
                par->right_child = newnode;
                IndexEntry *newword = new IndexEntry(newnode->key);
                vector<pair<string, int>> v = newword->getChapterWordCounts();
                for (int i = 0; i < chapterlist.size(); i++)
                {
                    if (newnode->element == newword->getChapterWordCounts()[i].first)
                    {
                        v[i].second++;
                        newword->setChapterWordCounts(v);
                        break;
                    }
                }
                index.push_back(*newword);
            }
        }
        HybridNode *made = newnode;
        while (par != NULL && par != getRoot())
        {
            if (par->color == "black")
            {
                return made;
            }
            else if (par->color == "red")
            {

                if (((par->parent->right_child == par) && (par->parent->left_child != nullptr && par->parent->left_child->color == "red")) || ((par->parent->left_child == par) && (par->parent->right_child != nullptr && par->parent->right_child->color == "red")))
                {

                    par->color = "black";
                    if (par->parent->right_child == par)
                    {
                        par->parent->left_child->color = "black";
                    }
                    else
                    {
                        par->parent->right_child->color = "black";
                    }
                    if (par->parent != root)
                        par->parent->color = "red";
                    par = par->parent->parent;
                    newnode = newnode->parent->parent;
                }
                else if (((par->parent->right_child == par) && (par->parent->left_child == nullptr || par->parent->left_child->color == "black")) || ((par->parent->left_child == par) && (par->parent->right_child == nullptr || par->parent->right_child->color == "black")))
                {
                    if ((par->parent->left_child == par) && (par->left_child == newnode))
                    {

                        swap(par->color, par->parent->color);
                        rightrotate(par->parent);
                        return made;
                    }
                    else if ((par->parent->left_child == par) && (par->right_child == newnode))
                    {

                        swap(par->right_child->color, par->parent->color);
                        leftrotate(par);
                        rightrotate(par->parent->parent);
                        return made;
                    }
                    else if ((par->parent->right_child == par) && (par->right_child == newnode))
                    {

                        swap(par->color, par->parent->color);
                        leftrotate(par->parent);
                        return made;
                    }
                    else if ((par->parent->right_child == par) && (par->left_child == newnode))
                    {
                        swap(par->left_child->color, par->parent->color);
                        rightrotate(par);
                        leftrotate(par->parent->parent);
                        return made;
                    }
                }
            }
        }
        return made;
    }
    vector<HybridNode *> traverseUp(HybridNode *node)
    {
        vector<HybridNode *> traverseup;
        HybridNode *temp = node;
        while (temp != NULL)
        {
            traverseup.push_back(temp);
            temp = temp->parent;
        }
        return traverseup;
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
    }

    vector<HybridNode *> traverseDown(HybridNode *node, string bit_sequence)
    {
        vector<HybridNode *> traversDown;
        traversDown.push_back(node);
        for (int j = 0; j < bit_sequence.size(); j++)
        {
            if (node == nullptr)
            {
                break;
            }
            if (bit_sequence[j] == '1')
            {
                node = node->left_child;
                traversDown.push_back(node);
            }
            else
            {
                node = node->right_child;
                traversDown.push_back(node);
            }
        }
        return traversDown;
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
    }
    vector<HybridNode *> preOrderTraversal(HybridNode *node, int depth)
    {
        vector<HybridNode *> result;

        if (node == nullptr)
        {
            return result;
        }
        result.push_back(node);
        vector<HybridNode *> leftSubtree = preOrderTraversal(node->left_child, depth + 1);
        result.insert(result.end(), leftSubtree.begin(), leftSubtree.end());
        vector<HybridNode *> rightSubtree = preOrderTraversal(node->right_child, depth + 1);
        result.insert(result.end(), rightSubtree.begin(), rightSubtree.end());

        return result;

        // Perform pre-order traversal staying within specified depth
    }
    HybridNode *search(string key)
    {
        HybridNode *temp = getRoot();
        while (temp != nullptr && temp->key != key)
        {
            if (stringCompare(key, temp->key) < 0)
            {
                temp = temp->left_child;
            }
            else
            {
                temp = temp->right_child;
            }
        }
        return temp;
        // Implement Red-Black Tree search
    }
    int blackheight(HybridNode *node)
    {
        HybridNode *temp = node;
        int p = 0;
        while (temp != nullptr)
        {
            if (temp->color == "black")
                p++;
            temp = temp->left_child;
        }
        return p;

        // Implement blackheight
    }
};

class Lexicon
{
private:
    RedBlackTree red_black_tree; // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names)
    {
        chapterlist = chapter_names;
        for (int j = 0; j < chapter_names.size(); j++)
        {
            ifstream input_file(chapter_names[j]);

            if (!input_file.is_open())
            {
                cerr << "Unable to open the file." << endl;
                return;
            }
            string line;
            getline(input_file, line);
            vector<string> words;
            string word;
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] >= 65 && line[i] <= 90)
                {
                    line[i] = line[i] + 32;
                }
                if (line[i] == ' ')
                {
                    words.push_back(word);
                    red_black_tree.insert(word, chapter_names[j].substr(0, chapter_names[j].size() - 4));
                    word = "";
                }
                else
                {
                    word += line[i];
                }
            }
            words.push_back(word);
            red_black_tree.insert(word, chapter_names[j].substr(0, word.size() - 4));
        }
        red_black_tree.deleterepeated();
    }
    vector<IndexEntry> buildIndex()

    {
        return index;
        // Build the index using the remaining words in the Red-Black Tree
    }
};

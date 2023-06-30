#include <iostream>

template <class T>
class Iterator;

template <class T>
class Container;

template <class T>
class Node;

template <class T>
class Iterator {
private:
    Node<T>* node;
public:
    Iterator() : node(nullptr) {}

    explicit Iterator(Node<T>* node) : node(node) {}

    Iterator(const Iterator<T>& it) : node(it.node) {}

    Iterator& operator = (Node<T>* _node) {
        node = _node;
        return *this;
    }

    bool operator == (const Iterator<T>& it) const {
        return it == *this;
    }

    bool operator != (const Iterator<T>& it) const {
        return it != *this;
    }

    Iterator<T>& operator ++ () {
        node = node->next;
        return *this;
    }

    T* operator * () {
        if (node != nullptr)
            return node->value;
        else
            return nullptr;
    }
};

template <class T>
class Node {
public:
    Node* next;
    T* value;

    friend class Container<T>;
    friend class Iterator<T>;

    explicit Node(T* _value) : value(_value), next(nullptr) {}

    Node() = default;
    ~Node() = default;

    void print() {
        std::cout << value->value << " ";
    }
};

template <class T>
class Container {
private:
    Node<T>* head;
    Node<T>* tail;

    Iterator<T> headIter;
    Iterator<T> tailIter;
public:
    explicit Container(T* value) {
        head = new Node<T>(value);
        tail = head;
        headIter = Iterator<T>(head);
        tailIter = Iterator<T>(tail);
    }

    ~Container() {
        Node<T>* currentNode = head;
        Node<T>* nextNode = head;

        while (nextNode != tail) {
            nextNode = nextNode->next;
            delete currentNode;
            currentNode = nextNode;
        }

        delete currentNode;
    }

    bool isEmpty() {
        return head == tail;
    }

    Iterator<T> begin() {
        return headIter;
    }

    Iterator<T> end() {
        return tailIter;
    }

    void add(T* value) {
        auto* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        headIter = Iterator<T>(head);
    }

    T remove() {
        auto* nodeToDelete = head;
        T value = nodeToDelete->value;

        head = nodeToDelete->next;
        headIter = iterator(head);

        delete nodeToDelete;

        return value;

    }

    Iterator<T> find(T& value) {
        auto iter = begin();
        while (*iter != nullptr) {
            if (*iter == &value) {
                return iter;
            }


            ++iter;
        }

        return tailIter;
    }

    int size() {
        int count = 0;

        auto iter = begin();
        while (*iter != nullptr) {
            count++;
            ++iter;
        }

        return count;
    }

    void print() {
        Iterator<T> iter = begin();
        while (*iter != nullptr) {
            std::cout << *iter;
            ++iter;
        }

        std::cout << std::endl;
    }

    void swap(Container<T>& x) {
        Container<T> y = x;
        x = this;
        this = y;
    }
};

class Wagon {
public:
    unsigned int tonsOfCargo;

    explicit Wagon() {
        tonsOfCargo = 0;
    }

    void transferCargo(Wagon target) {
        if (tonsOfCargo >= 100) {
            target.tonsOfCargo += 100;
            tonsOfCargo -= 100;
        }
    }

    void loadCargo(unsigned int cargo) {
        tonsOfCargo += cargo;
    }

    friend std::ostream& operator << (std::ostream& os, Wagon* carriage) {
        os << "| " << carriage->tonsOfCargo << " |-";
        return os;
    }
};

std::string buildRailroad(Container<Wagon>& train) {
    std::string railroad;
    for (Iterator<Wagon> it = train.begin(); *it != nullptr; ++it) {
        railroad += "=/=";
        for (int i = 0; i < std::to_string((*it)->tonsOfCargo).length(); i+=2) {
            railroad += "/=";
        }
        railroad += "/=/";
    }
    return railroad;
}

int main() {
    //train station with 4 wagons
    auto* wagon1 = new Wagon();
    auto* wagon2 = new Wagon();
    auto* wagon3 = new Wagon();
    auto* wagon4 = new Wagon();

    //attaching wagons to a train
    Container<Wagon> train(wagon1);
    train.add(wagon2);
    train.add(wagon3);
    train.add(wagon4);

    //print train
    train.print();

    //building railroad using size of each wagon
    std::cout << buildRailroad(train) << std::endl << std::endl;

    //loading train cargo
    for (Iterator<Wagon> iter = train.begin(); *iter != nullptr; ++iter) {
        (*iter)->loadCargo(100);
    }

    //find wagon3 and load 400 more cargo
    auto iter = train.find(*wagon3);
    (*iter)->loadCargo(400);

    //print train
    train.print();
    //building railroad using size of each wagon
    std::cout << buildRailroad(train) << std::endl << std::endl;

    return 0;
}

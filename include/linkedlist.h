#include <cstdlib>
#include <utility>
#include <iostream>

namespace edu {
    namespace vcccd {
        namespace vc {
            namespace csv15 {
                template<class T>
                class LinkedList {
                private:
                    struct Node {
                        Node(T data, Node *next) : _data(data), _next(next) {}
                        Node* _next;
                        T _data;
                    };
                public:
                    class iterator {
                    public:
                        iterator(Node *node) : _node(node) {}
                        iterator(const iterator &other) : _node(other._node) {}

                    public:
                        const T &operator*() { return _node->_data; }
                        const T &operator*() const { return _node->_data; }
                        iterator &operator++() { _node = _node->_next; return *this; }
                        iterator operator++(int) { iterator before(*this); _node = _node->_next; return before; }
                        bool operator==(const iterator &other) { return other._node == _node; }
                        bool operator!=(const iterator &other) { return !operator==(other); }
                        Node *node() { return _node; }
                    private:
                        Node *_node;
                    };

                public:
                    LinkedList() : _size(0), head(nullptr), tail(nullptr) {}
                    LinkedList(const LinkedList &other) : _size(0), head(nullptr), tail(nullptr) {
                        for (const T& val : other) {
                            push_front(val);
                        }
                    }

                    ~LinkedList() { clear(); } //destructor

                public:
                    bool empty() const { return _size == 0; }
                    T &front() { return head->_data; }
                    const T &front() const { return head->_data; }
                    T &back() { return tail->_data; }
                    const T &back() const { return tail->_data; }
                    size_t size() const { return _size; }

                public:
                    iterator begin() { return iterator(head); }
                    const iterator begin() const { return iterator(head); }
                    iterator end() { return iterator(nullptr); }
                    const iterator end() const { return iterator(nullptr); }

                public:
                    void clear() { //should delete everything
                        erase(head, tail);

                        std::cout << head->_data << " " << tail->_data << std::endl;
                        std::cout << " Done " << std::endl;
                    }
                    iterator insert(iterator where, const T &value) { //
                        where.node()->_next = new Node(value, where.node()->_next);
                        if (where.node() == tail) {
                            tail = where.node()->_next;
                        }

                        _size++;
                        printList(_size);
                        return where;
                    }
                    iterator erase(iterator where) { //erase 
                        Node *temp = head;
                        if (_size == 1) {
                            delete head;
                            head = tail = nullptr;
                            return where;
                        }
                        else if (where.node() == head) {

                            delete head;
                            head = temp->_next;
                            return where;
                        }
                        else if (where.node() == tail) {
                            temp = tail;
                            delete tail;
                            tail = temp->_next;
                            return where;
                        }
                        else {
                            for (auto curr = head; curr != where.node(); curr++) {
                                temp = curr;
                            }
                            delete temp;
                        }
                        _size--;
                        std::cout << "size is " << _size << std::endl;
                        printList(_size);
                        return where;

                    }
                    iterator erase(iterator first, iterator last) { //erase that includes everything 

                        for (auto curr = first; curr != last; curr++) {
                            erase(curr);
                        }
                        return first;
                    }
                    void push_back(const T &value) {
                        Node *newNode = new Node(value, nullptr);
                        if (tail == nullptr) {
                            head = tail = newNode;
                        }
                        else {
                            tail = tail->_next = newNode;
                        }
                        _size++;
                        std::cout << "Pushed " << value << " to back" << std::endl;
                        std::cout << "size is " << _size << std::endl;
                        printList(_size);
                    }
                    void pop_back() {
                        if (tail == nullptr) {
                            std::cout << "Nothing to pop!" << std::endl;
                            printList(_size);
                            return;
                        }
                        if (_size == 1) {
                            std::cout << "Popped " << tail->_data << " from back" << std::endl;
                            delete tail;
                            head = tail = nullptr;
                            _size--;
                            std::cout << "size is " << _size << std::endl;
                            return;
                        }
                        Node *current = head;
                        while (current->_next != tail) {
                            current = current->_next;
                        }
                        std::cout << "Popped " << tail->_data << " from back" << std::endl;
                        delete(tail);
                        current->_next = nullptr;
                        tail = current;
                        _size--;
                        std::cout << "size is " << _size << std::endl;
                        printList(_size);
                    }
                    void push_front(const T &value) {
                        Node *newNode = new Node(value, nullptr);
                        if (head == nullptr) {
                            head = newNode;
                            tail = newNode;
                        }
                        else {
                            newNode->_next = head; //copies the head to be next
                            head = newNode;
                        }
                        _size++;
                        std::cout << "Pushed " << value << " to front" << std::endl;
                        std::cout << "size is " << _size << std::endl;
                        printList(_size);
                    }
                    void pop_front() {

                        if (head == nullptr) {
                            std::cout << "Nothing to pop!" << std::endl;
                            std::cout << "size is " << _size << std::endl;
                            return;
                        }
                        if (_size == 1) {
                            std::cout << "Popped " << head->_data << " from front" << std::endl;
                            delete head;
                            head = tail = nullptr; //make head and tail to be null
                            _size--;
                            std::cout << "size is " << _size << std::endl;
                            return;
                        }
                        Node *temp = head; //coping the current head before deleting
                        head = temp->_next;//head is next
                        std::cout << "Popped " << temp->_data << " from front" << std::endl;
                        delete temp;
                        _size--;
                        std::cout << "size is " << _size << std::endl;
                        printList(_size);
                    }


                public:
                    void swap(LinkedList &other) { //take two nodes and swap them

                    }
                    void printList(size_t size) { //this prints out the entire list
                        Node *Temp = head;
                        std::cout << "LIST = { ";
                        for (int i = 0; i < size; ++i) {
                            std::cout << Temp->_data << ", ";
                            Temp = Temp->_next;
                        }
                        std::cout << "}\n" << std::endl;
                        delete(Temp);
                    }
                private:
                    Node *head;
                    Node *tail;
                    size_t _size;
                };
            }
        }
    }
}

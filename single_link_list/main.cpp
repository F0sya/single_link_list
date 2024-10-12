#include <iostream>
using namespace std;


template <typename T> class Element {
public:
    T value;
    Element* next;
    Element() : value(), next(nullptr) {}
    Element(T value) : value(value), next(nullptr) {}
    ~Element() = default;
};

template <typename T> class single_linked_list {
private:
    Element<T>* _head;
    Element<T>* _tail;
    int _size;

public:
    single_linked_list() : _head(nullptr), _tail(nullptr), _size(0) {}
    ~single_linked_list() {
        Element<T>* temp = _head;
        while (temp != nullptr) {
            temp = temp->next;
            delete _head;
            _head = temp;
        }
        _tail = nullptr;
    }

    void push_back(T value) {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr) {
            _head = temp;
            _tail = temp;
        }
        else {
            _tail->next = temp;
            _tail = temp;
        }
        _size++;
    }
    void push_front(T value) {
        Element<T>* temp = new Element<T>(value);
        if (_head == nullptr) {
            _head = temp;
            _tail = temp;
        }
        else {
            temp->next = _head;
            _head = temp;
        }
        _size++;
    }
    void pop_back() {
        if (_head == nullptr) {
            return;
        }
        else if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Element<T>* temp = _head;
            while (temp->next != _tail) {
                temp = temp->next;
            }
            delete _tail;
            _tail = temp;
            _tail->next = nullptr;
        }
        _size--;
    }
    void pop_front() {
        if (_head == nullptr) {
            return;
        }
        else if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Element<T>* temp = _head;
            _head = _head->next;
            delete temp;
        }
        _size--;
    }
    void insert(int index, T value) {
        if (index < 0 || index > _size) {
            return;
        }
        else if (index == 0) {
            push_front(value);
        }
        else if (index == _size) {
            push_back(value);
        }
        else {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            Element<T>* new_elem = new Element<T>(value);
            new_elem->next = temp->next;
            temp->next = new_elem;
            _size++;
        }
    }
    void remove_by_index(int index) {
        if (index < 0 || index >= _size) {
            return;
        }
        else if (index == 0) {
            pop_front();
        }
        else if (index == _size - 1) {
            pop_back();
        }
        else {
            Element<T>* temp = _head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            Element<T>* to_delete = temp->next;
            temp->next = temp->next->next;
            delete to_delete;
            _size--;
        }
    }
    void remove_by_value(T value) {
        Element<T>* temp = _head;
        int index = 0;
        while (temp != nullptr) {
            if (temp->value == value) {
                remove_by_index(index);
                return;
            }
            temp = temp->next;
            index++;
        }
    }

    void find_element(T value) {
        Element<T>* temp = _head;
        int index = -1;
        bool found = false;
        while (temp != nullptr) {
            index++;
            if (temp->value == value) {
                found = true;
                break;
            } 
            temp = temp->next;
        }
        (found == false) ? cout << "No references!" << endl : cout << "First reference of value [" << value << "] is found on: " << index << endl;
    }

    void find_element_and_change(T value, T changer) {
        Element<T>* temp = _head;
        int count = 0;
        while (temp != nullptr) {
            if (temp->value == value) {
                temp->value = changer;
                count++;
            }
            temp = temp->next;
        }
        (count == 0) ? cout << "No changes!" << endl : cout << "Amount of changed elements: " << count << endl;
    }
    void print() {
        Element<T>* temp = _head;
        while (temp != nullptr) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void dev_print() {
        int index = 0;
        Element<T>* temp = _head;
        while (temp != nullptr) {
            cout << "Element[" << index << "]: " << (long long)temp << endl;
            cout << "Value: " << temp->value << endl;
            cout << "Next element: " << (long long)temp->next << endl << endl;
            temp = temp->next;
            index++;
        }
        cout << endl;
    }
    int size() { return _size; }
};

int main() {
    single_linked_list<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(1);

    list.print();
    

    list.find_element(4);
    list.find_element_and_change(10, 2);

    list.print();
    return 0;

}
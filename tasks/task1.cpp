#include <iostream>
#include <vector>
#include <memory>
#include <tuple>
#include <string>
using namespace std;

// class enum
enum class ContainerType
{
    Generic,
    UniquePtr,
    SharedPtr
};

// Generic class
template <typename T>
class GenericContainer
{
private:
    vector<T> elements; // generic vector
public:
    // add an element
    void add(const T &element)
    {
        elements.push_back(element);
    }
    // return at given index
    T get(size_t index) const
    {
        if (index < elements.size())
        {
            return elements[index];
        }
        throw out_of_range("Index out of range");
    }
    //size
    constexpr size_t size() const// instead of int use size_t for objects sizes
    {
        return elements.size();
    }

    // print
    void print() 
    {
        for (const auto &elem : elements)
        {
            cout << *elem << " ";
        }
        cout << endl;
    }
};



// unique_ptr
template <typename T>
class GenericContainer<unique_ptr<T>>
{
private:
    vector<unique_ptr<T>> elements;

public:
    // add unique pointer
    void add(unique_ptr<T> element)
    {
        elements.push_back(move(element));
    }


    // move ownership at index
    unique_ptr<T> release(size_t index)
    {
        if (index < elements.size())
        {
            unique_ptr<T> releasedElement = move(elements[index]);
            elements.erase(elements.begin() + index);
            return releasedElement;
        }
        throw out_of_range("Index out of range");
    }


    // size
    constexpr size_t size() const
    {
        return elements.size();
    }


    // print container
    void print() const
    {
        for (const auto &elem : elements)
        {
            if (elem)
            {
                cout << *elem << " ";
            }
        }
        cout << endl;
    }
};



// shared_ptr
template <typename T>
class GenericContainer<shared_ptr<T>>
{
private:
    vector<shared_ptr<T>> elements;

public:
    //  add
    void add(const shared_ptr<T> &element)
    {
        elements.push_back(element);
    }
    //  size of the container
    constexpr size_t size() const
    {
        return elements.size();
    }
    // Prints all elements and their use counts in the container
    void print() const
    {
        for (const auto &elem : elements)
        {
            if (elem)
            {
                cout << *elem << " (use count: " << elem.use_count() << ") ";
            }
        }
        cout << endl;
    }
};


int main()
{
   
    GenericContainer<int> intContainer;
    intContainer.add(10);
    intContainer.add(20);
    cout << "Generic container (int): ";
    intContainer.print();

    // Using the container with unique_ptr
    GenericContainer<unique_ptr<int>> uniquePtrContainer;
    uniquePtrContainer.add(make_unique<int>(100));
    uniquePtrContainer.add(make_unique<int>(200));
    cout << "UniquePtr container before release: ";
    uniquePtrContainer.print();

    auto releasedElement = uniquePtrContainer.release(0); // release ownership at 0 index
    cout << "UniquePtr container after release: ";
    uniquePtrContainer.print();
    cout << "Released element: " << *releasedElement << endl;


    // Using the container with shared_ptr
    GenericContainer<shared_ptr<int>> sharedPtrContainer;
    sharedPtrContainer.add(make_shared<int>(300));
    sharedPtrContainer.add(make_shared<int>(400));

    cout << "SharedPtr container: ";
    sharedPtrContainer.print();

    // printing container size
    auto printSize = [](const auto &container)
    {
        cout << "Container size: " << container.size() << endl;
    };


    // call lambda
    printSize(intContainer);
    printSize(uniquePtrContainer);
    printSize(sharedPtrContainer);

    // Using tuples and structured bindings
    tuple<int, string, double> info = make_tuple(1, "example", 3.14);
    auto [id, name, value] = info;
    cout << "Tuple values - ID: " << id << ", Name: " << name << ", Value: " << value << endl;

    
    return 0;
}
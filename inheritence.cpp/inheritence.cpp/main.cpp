#include <iostream>
#include <string>

using namespace std;

// Abstract class
class Vehicle
{
public:
    virtual void print() = 0;
};

class Car : public Vehicle
{
public:
    void print()
    {
        cout << "CAR" << endl;
    }
    
};

int main()
{
    Vehicle * v1 = new Car;
    v1 -> print();
    return 0;
}

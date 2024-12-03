#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex dataMutex;
// parent class
class ClusterManager
{
    // properties
    double speed;
    double fuel;
    double temp;

public:
    // constructor
    ClusterManager(double speed, double fuel, double temp)
    {
        this->speed = speed;
        this->fuel = fuel;
        this->temp = temp;
    }

    // setters
    void setSpeed(double speed)
    {
        this->speed = speed;
    }

    void setFuel(double fuel)
    {
        this->fuel = fuel;
    }

    void setTemp(double temp)
    {
        this->temp = temp;
    }

    // getters
    double getSpeed()
    {
        return speed;
    }

    double getFuel()
    {
        return fuel;
    }
    double getTemp()
    {
        return temp;
    }

    // abstract method

    virtual void display()
    {
        cout << "Speed:" << speed << "km/h, Fuel Level:" << fuel << "%, Temperature:" << temp << "\u00B0C" << endl;
    }
};

// child classes

class Speed : public ClusterManager
{

public:
    Speed(double s, double f, double t) : ClusterManager(s, f, t) {}

    void display()
    {
        cout << "Speed:" << getSpeed() << "km/h" << endl;
    }
};

class Fuel : public ClusterManager
{

public:
    Fuel(double s, double f, double t) : ClusterManager(s, f, t) {}

    void display()
    {
        cout << "Fuel:" << getFuel() << "%" << endl;
    }
};

class Temp : public ClusterManager
{

public:
    Temp(double s, double f, double t) : ClusterManager(s, f, t) {}

    void display()
    {
        cout << "Speed:" << getTemp() << "\u00B0C" << endl;
    }
};

// displaying data and giving warning as well

void displayData(ClusterManager &data, bool &flag)
{
    while (flag)
    {
        {
            lock_guard<mutex> lock(dataMutex);
            cout << "--------Digital cluster--------" << endl;
            cout << endl;
            cout << "Speed:" << data.getSpeed() << "km/h" << endl;
            cout << "Fuel:" << data.getFuel() << "%" << endl;
            cout << "Temperature:" << data.getTemp() << "\u00B0C" << endl;
            if (data.getTemp() > 110)
            {
                cout << "WARNING!: Over Heating.." << endl;
            }
            if (data.getFuel() < 15)
            {
                cout << "WARNING!: Low Fuel.." << endl;
            }
        }
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// updating real time data
void updateData(ClusterManager &data, bool &flag)
{
    while (flag)
    {

        {
            lock_guard<mutex> lock(dataMutex);

            random_device rd;
            mt19937 gen(rd());
            // for speed
            uniform_real_distribution<double> distrSpeed(0.0f, 400.0); // 0 to maximum value for float point
                                                                       // for fuel
            uniform_real_distribution<double> distrFuel(0.0f, 100.0);
            // for temperature
            uniform_real_distribution<double> distrTemp(0.0f, 200.0);
            // update speed with generator
            data.setSpeed(distrSpeed(gen));
            data.setFuel(distrFuel(gen));
            data.setTemp(distrTemp(gen));
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main()
{

    ClusterManager data(0.0, 50, 0.0);
    bool flag = true; // means vehical is running

    // creating threads
    thread t1(displayData, ref(data), ref(flag));
    thread t2(updateData, ref(data), ref(flag));

    // runnig for 10 sec
    this_thread::sleep_for(chrono::seconds(10));
    flag = false;

    t1.join();
    t2.join();

    cout << "Vehical stoped after 10 seconds" << endl;
    return 0;
}
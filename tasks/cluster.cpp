#include <iostream>
#include <random>
#include <thread>
#include <mutex>

using namespace std;

class VehicalData
{
    double speed;
    double fuel;
    double temperature;

public:
    VehicalData() : speed(0), fuel(10), temperature(0)
    {
    }

    // setter
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
        temperature = temp;
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
        return temperature;
    }
};

mutex dataMutex;

void displayData(VehicalData &data, bool &flag)
{
    while (flag)
    {
        {
            lock_guard<mutex> lock(dataMutex);
            cout << "speed:" << data.getSpeed() << "km/h, fuel:" << data.getFuel() << "%, temperature:" << data.getTemp() << "\u00B0C" << endl;
            if (data.getTemp() > 100 || data.getFuel() < 10)
            {
                cout << "WARNING: high temperature or low fuel detected!" << endl;
            }
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void updateData(VehicalData &data, bool &flag)
{
    while (flag)
    {

        {
            lock_guard<mutex> lock(dataMutex);

            random_device rd;
            mt19937 gen(rd());
            // for speed
            uniform_real_distribution<double> distrSpeed(0.0f, 380.0); // 0 to maximum value for float point
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

    VehicalData data;
    bool flag = true; // means vehical is running
    // initial data
    cout << "Initail Data:" << endl;

    thread t1(displayData, ref(data), ref(flag));
    thread t2(updateData, ref(data), ref(flag));

    this_thread::sleep_for(chrono::seconds(10));
    flag = false;

    t1.join();
    t2.join();

    cout << "Vehical stoped" << endl;
    return 0;
}
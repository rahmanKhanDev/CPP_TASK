#include <iostream>
#include <mutex>
#include <vector>
#include <string>

using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void updateEngineTemp(float engineTemp) = 0;
    virtual void updateOilPressure(float oilPressure) = 0;
    virtual ~Observer() = default;
};

// Observer implementation class
class DiagnosticObserver : public Observer
{
private:
    string observerName;

public:
    DiagnosticObserver(string name)
    {
        observerName = name;
    }

    void updateEngineTemp(float engineTemp) override
    {
        cout << "Observer Name: " << observerName
             << " received Engine Temperature: " << engineTemp << endl;
    }

    void updateOilPressure(float oilPressure) override
    {
        cout << "Observer Name: " << observerName
             << " received Oil Pressure: " << oilPressure << endl;
    }
};

// Singleton class  Diagnostic system
class Diagnostic
{
private:
    float engineTemp;
    float oilPressure;

    static Diagnostic *diagnostic; // single instance
    static std::mutex mtx;
    vector<Observer *> observers; // observers

    Diagnostic() : engineTemp(0), oilPressure(0) {}

public:
    // delete dynamic meemory and copy objs
    Diagnostic(const Diagnostic &) = delete;
    Diagnostic &operator=(const Diagnostic &) = delete;

    // Add observer
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }

    // Notify all observers
    void notifyObservers()
    {
        for (Observer *observer : observers)
        {
            observer->updateEngineTemp(engineTemp);
            observer->updateOilPressure(oilPressure);
        }
    }

    // Setters and getters
    void setEngineTemp(float temp)
    {
        engineTemp = temp;
        notifyObservers(); // Notify after updating
    }

    float getEngineTemp() const
    {
        return engineTemp;
    }

    void setOilPressure(float pressure)
    {
        oilPressure = pressure;
        notifyObservers(); // Notify after updating
    }

    float getOilPressure() const
    {
        return oilPressure;
    }

    // Get the singleton instance
    static Diagnostic *getDiagnostic()
    {
        if (diagnostic == nullptr)
        {
            lock_guard<mutex> lock(mtx);
            if (diagnostic == nullptr)
            {
                diagnostic = new Diagnostic();
            }
        }
        return diagnostic;
    }
};

// Initialize static members with initial value
Diagnostic *Diagnostic::diagnostic = nullptr;
std::mutex Diagnostic::mtx;

// Main n
int main()
{
    //  singleton instance
    Diagnostic *diagnosticSystem = Diagnostic::getDiagnostic();

    // create observers
    DiagnosticObserver observer1("Display");
    DiagnosticObserver observer2("Logger");
    DiagnosticObserver observer3("Alert System");

    // observers added
    diagnosticSystem->addObserver(&observer1);
    diagnosticSystem->addObserver(&observer2);
    diagnosticSystem->addObserver(&observer3);

    // update  data and notify
    cout << "Updating engine temperature to 85.5..." << endl;
    diagnosticSystem->setEngineTemp(85.5);

    cout << "Updating oil pressure to 42.7..." << endl;
    diagnosticSystem->setOilPressure(42.7);

    return 0;
}

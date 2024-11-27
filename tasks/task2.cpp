#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
  using namespace std;
struct CarSensorData {
    double speed; // in km/h
    double fuelLevel; // in percentage
    double engineTemp; // in Celsius
    array<double, 4> tirePressure; 
};

// minimum threshold for tire pressure
double adjustTirePressure(double pressure) {
    return pressure < 30.0 ? 30.0 : pressure;
}


int main() {
    // Sample sensor data
    CarSensorData sensorData = {120.0, 80.0, 90.0, {28.0, 32.0, 27.5, 31.0}};
    
    // Adjust sensor data
    sensorData.speed = std::plus<double>()(sensorData.speed, 10.0);
    sensorData.fuelLevel = std::minus<double>()(sensorData.fuelLevel, 5.0);
    sensorData.engineTemp = std::plus<double>()(sensorData.engineTemp, 2.0);
    
    // Adjust tire pressures using std::transform and std::ptr_fun
    std::transform(
        sensorData.tirePressure.begin(),
        sensorData.tirePressure.end(),
        sensorData.tirePressure.begin(),
        adjustTirePressure
    );

    // Check if all tire pressures are above the safe threshold (30 PSI)
    bool tirePressureSafe = std::all_of(
        sensorData.tirePressure.begin(),
        sensorData.tirePressure.end(),
        [](double pressure) { return pressure > 30.0; }
    );

    // Display the formatted sensor data
    std::cout << std::fixed << std::setprecision(1);

    // Display speed with a fixed width of 10, right-aligned
    std::cout << "Speed: " << std::setw(10) << sensorData.speed << " km/h" << std::endl;

    // Display fuel level as percentage
    std::cout << "Fuel Level: " << std::setw(10) << sensorData.fuelLevel << "%" << std::endl;

    // Display engine temperature with 1 decimal place
    std::cout << "Engine Temp: " << std::setw(10) << sensorData.engineTemp << " °C" << std::endl;

    // Display tire pressures with each value formatted to 1 decimal place, separated by commas
    std::cout << "Tire Pressure: ";
    for (size_t i = 0; i < sensorData.tirePressure.size(); ++i) {
        std::cout << sensorData.tirePressure[i];
        if (i < sensorData.tirePressure.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << " PSI" << std::endl;

    // Display whether tire pressures are safe
    std::cout << "Tire Pressure Safe: " << std::boolalpha << tirePressureSafe << std::endl;

    return 0;
}

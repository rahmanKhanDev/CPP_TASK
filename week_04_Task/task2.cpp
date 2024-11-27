#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm> // for std::copy, std::find
#include <iterator>  // for std::ostream_iterator

using namespace std;

int main()
{
    // Step 1: Populate Containers
    vector<string> dynamicWidgets = {"Speedometer", "Tachometer", "FuelGauge", "Odometer"};
    set<string> staticWidgets = {"Logo", "WarningLights"};

    // Step 2: Use Iterators to Print Dynamic Widgets
    cout << "Dynamic Widgets:\n";
    for (auto it = dynamicWidgets.begin(); it != dynamicWidgets.end(); ++it)
    {
        cout << *it << '\n';
    }

    // Step 3: Check if a specific widget ("WarningLights") is in the std::set
    string targetStaticWidget = "WarningLights";
    auto staticWidgetIt = staticWidgets.find(targetStaticWidget);
    if (staticWidgetIt != staticWidgets.end())
    {
        cout << "\nFound static widget: " << *staticWidgetIt << '\n';
    }
    else
    {
        cout << "\nStatic widget " << targetStaticWidget << " not found.\n";
    }

    // Step 4: Combine both containers into a std::vector<std::string>
    vector<string> allWidgets;
    allWidgets.reserve(dynamicWidgets.size() + staticWidgets.size()); // Reserve space
    copy(dynamicWidgets.begin(), dynamicWidgets.end(), back_inserter(allWidgets));
    copy(staticWidgets.begin(), staticWidgets.end(), back_inserter(allWidgets));

    // Step 5: Use std::find to locate a specific widget in the combined container
    string targetWidget = "Tachometer";
    auto foundWidget = find(allWidgets.begin(), allWidgets.end(), targetWidget);

    // Step 6: Output Results
    cout << "\nCombined Widgets:\n";
    for (const auto &widget : allWidgets)
    {
        cout << widget << '\n';
    }

    if (foundWidget != allWidgets.end())
    {
        cout << "\nFound widget: " << *foundWidget << '\n';
    }
    else
    {
        cout << "\nWidget " << targetWidget << " not found.\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Define the Control structure
struct Control
{
    int id;       // Unique ID
    string type;  // "button" or "slider"
    string state; // "visible", "invisible", "disabled"

    // Overload equality operator for  equal
    bool operator==(const Control &other) const
    {
        return id == other.id && type == other.type && state == other.state;
    }
};

// Function to print details of a control
void printControl(const Control &control)
{
    cout << "ID: " << control.id
         << ", Type: " << control.type
         << ", State: " << control.state << '\n';
}

int main()
{
    // Initialize the container with sample controls (5 buttons, 5 sliders)
    vector<Control> controls = {
        {1, "button", "visible"}, {2, "button", "invisible"}, {3, "button", "disabled"}, {4, "button", "visible"}, {5, "button", "visible"}, {6, "slider", "disabled"}, {7, "slider", "visible"}, {8, "slider", "visible"}, {9, "slider", "invisible"}, {10, "slider", "disabled"}};

    // 1. Use std::for_each to iterate and print details of all controls
    cout << "All controls:\n";
    for_each(controls.begin(), controls.end(), printControl);

    // 2. Use std::find to find a control with a specific ID
    int searchID = 3;
    auto foundControl = find_if(controls.begin(), controls.end(),
                                [searchID](const Control &ctrl)
                                { return ctrl.id == searchID; });

    if (foundControl != controls.end())
    {
        cout << "\nControl with ID " << searchID << " found:\n";
        printControl(*foundControl);
    }
    else
    {
        cout << "\nControl with ID " << searchID << " not found.\n";
    }

    // 3. Use std::find_if to find the first invisible control
    auto invisibleControl = find_if(controls.begin(), controls.end(),
                                    [](const Control &ctrl)
                                    { return ctrl.state == "invisible"; });

    if (invisibleControl != controls.end())
    {
        cout << "\nFirst invisible control:\n";
        printControl(*invisibleControl);
    }
    else
    {
        cout << "\nNo invisible control found.\n";
    }

    // 4. Use std::adjacent_find to check for consecutive controls with the same state
    auto consecutiveSameState = adjacent_find(controls.begin(), controls.end(),
                                              [](const Control &a, const Control &b)
                                              { return a.state == b.state; });

    if (consecutiveSameState != controls.end())
    {
        cout << "\nConsecutive controls with the same state:\n";
        printControl(*consecutiveSameState);
        printControl(*(consecutiveSameState + 1));
    }
    else
    {
        cout << "\nNo consecutive controls with the same state found.\n";
    }

    // 5. Use std::count to count the number of visible controls
    int visibleCount = count_if(controls.begin(), controls.end(),
                                [](const Control &ctrl)
                                { return ctrl.state == "visible"; });
    cout << "\nNumber of visible controls: " << visibleCount << '\n';

    // 6. Use std::count_if to count sliders that are disabled
    int disabledSliders = count_if(controls.begin(), controls.end(),
                                   [](const Control &ctrl)
                                   { return ctrl.type == "slider" && ctrl.state == "disabled"; });
    std::cout << "Number of disabled sliders: " << disabledSliders << '\n';

    // 7. Use std::equal to compare two subranges of controls
    vector<Control> subrange1 = {{1, "button", "visible"}, {2, "button", "invisible"}};
    bool areSubrangesEqual = equal(subrange1.begin(), subrange1.end(), controls.begin());
    cout << "\nAre the subrange and beginning of controls equal? "
         << (areSubrangesEqual ? "Yes" : "No") << '\n';

    return 0;
}

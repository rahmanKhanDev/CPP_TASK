#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>   // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <iterator> // for std::back_inserter

using namespace std;
// Define the Control structure
struct Control
{
    int id;       // Unique ID
    string type;  // "button" or "slider"
    string state; // "visible", "invisible", "disabled"

    // Utility for displaying Control
    void print() const
    {
        cout << "ID: " << id << ", Type: " << type << ", State: " << state << '\n';
    }
};

int main()
{
    // Initialize Controls
    vector<Control> controls = {
        {1, "button", "visible"}, {2, "slider", "visible"}, {3, "button", "invisible"}, {4, "slider", "disabled"}, {5, "button", "visible"}, {6, "slider", "invisible"}, {7, "slider", "visible"}, {8, "button", "disabled"}, {9, "slider", "visible"}, {10, "button", "invisible"}};

    cout << "Original Controls:\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 1: Create a backup of the control list using std::copy
    vector<Control> backupControls;
    copy(controls.begin(), controls.end(), std::back_inserter(backupControls));

    // Step 2: Use std::fill to set all states to "disabled" temporarily
    fill(controls.begin(), controls.end(), Control{0, "unknown", "disabled"});
    cout << "\nAfter fill (all disabled):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 3: Use std::generate to assign random states ("visible", "invisible", "disabled")
    const string states[] = {"visible", "invisible", "disabled"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 2);

    generate(controls.begin(), controls.end(), [&gen, &dist, &states]()
             {
        static int id = 1;
        string type = (id % 2 == 0) ? "slider" : "button";
        return Control{id++, type, states[dist(gen)]}; });

    cout << "\nAfter generate (random states):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 4: Use std::transform to change the state of all sliders to "invisible"
    transform(controls.begin(), controls.end(), controls.begin(), [](Control &ctrl)
              {
        if (ctrl.type == "slider") ctrl.state = "invisible";
        return ctrl; });

    cout << "\nAfter transform (sliders invisible):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 5: Use std::replace to replace "disabled" with "enabled"
    replace_if(controls.begin(), controls.end(), [](const Control &ctrl)
               { return ctrl.state == "disabled"; }, Control{0, "unknown", "enabled"});

    cout << "\nAfter replace (disabled to enabled):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 6: Use std::remove_if to filter out invisible controls
    controls.erase(remove_if(controls.begin(), controls.end(), [](const Control &ctrl)
                             { return ctrl.state == "invisible"; }),
                   controls.end());

    cout << "\nAfter remove_if (remove invisible):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 7: Use reverse to reverse the control order
    reverse(controls.begin(), controls.end());
    cout << "\nAfter reverse:\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    // Step 8: Use std::partition to group visible controls together
    partition(controls.begin(), controls.end(), [](const Control &ctrl)
               { return ctrl.state == "visible"; });

    cout << "\nAfter partition (group visible):\n";
    for (const auto &ctrl : controls)
        ctrl.print();

    return 0;
}

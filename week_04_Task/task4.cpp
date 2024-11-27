#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

    // Comparison operator for sorting
    bool operator<(const Control &other) const
    {
        return id < other.id;
    }

    // Equality operator for set operations
    bool operator==(const Control &other) const
    {
        return id == other.id;
    }
};

int main()
{
    // Initialize two lists of controls
    vector<Control> controls1 = {
        {5, "button", "visible"}, {2, "slider", "disabled"}, {8, "button", "visible"}, {1, "slider", "invisible"}, {7, "button", "visible"}};

    vector<Control> controls2 = {
        {4, "button", "disabled"}, {3, "slider", "invisible"}, {6, "button", "visible"}, {2, "slider", "disabled"}, {9, "slider", "visible"}};

    cout << "Original List 1:\n";
    for (const auto &ctrl : controls1)
        ctrl.print();

    cout << "\nOriginal List 2:\n";
    for (const auto &ctrl : controls2)
        ctrl.print();

    // Step 1: Sorting using std::sort
    sort(controls1.begin(), controls1.end());
    sort(controls2.begin(), controls2.end());

    cout << "\nList 1 After Sorting:\n";
    for (const auto &ctrl : controls1)
        ctrl.print();

    cout << "\nList 2 After Sorting:\n";
    for (const auto &ctrl : controls2)
        ctrl.print();

    // Step 2: Stable sort using std::stable_sort (already sorted, just for demonstration)
    stable_sort(controls1.begin(), controls1.end());
    stable_sort(controls2.begin(), controls2.end());

    // Step 3: Binary Search using std::lower_bound and std::upper_bound
    int searchID = 2;
    auto lower = lower_bound(controls1.begin(), controls1.end(), Control{searchID, "", ""});
    auto upper = upper_bound(controls1.begin(), controls1.end(), Control{searchID, "", ""});

    if (lower != controls1.end() && lower->id == searchID)
    {
        cout << "\nControl Found with ID " << searchID << ":\n";
        lower->print();
    }
    else
    {
        cout << "\nControl with ID " << searchID << " not found.\n";
    }

    // Step 4: Merging two sorted lists using std::merge
    vector<Control> mergedControls;
    merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
          back_inserter(mergedControls));

    cout << "\nMerged List After std::merge:\n";
    for (const auto &ctrl : mergedControls)
        ctrl.print();

    // Step 5: Using std::inplace_merge on a single list
    vector<Control> inplaceMergeControls = {{1, "slider", "invisible"}, {3, "button", "visible"}, {2, "slider", "disabled"}, {4, "button", "disabled"}};
    sort(inplaceMergeControls.begin(), inplaceMergeControls.begin() + 2); // Sort the first half
    sort(inplaceMergeControls.begin() + 2, inplaceMergeControls.end());   // Sort the second half

    inplace_merge(inplaceMergeControls.begin(), inplaceMergeControls.begin() + 2, inplaceMergeControls.end());

    cout << "\nList After std::inplace_merge:\n";
    for (const auto &ctrl : inplaceMergeControls)
        ctrl.print();

    // Step 6: Set Operations using std::set_union and std::set_intersection
    vector<Control> setUnion, setIntersection;
    set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
              back_inserter(setUnion));
    set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
                     back_inserter(setIntersection));

    cout << "\nSet Union:\n";
    for (const auto &ctrl : setUnion)
        ctrl.print();

    cout << "\nSet Intersection:\n";
    for (const auto &ctrl : setIntersection)
        ctrl.print();

    return 0;
}

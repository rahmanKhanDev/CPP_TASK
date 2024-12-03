#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// struct
struct Control
{
    int id;       // unique id
    string type;  // button or slider
    string state; // visible, invisible,disabled

    // constructor
    Control(int bId, string bType, string bState) : id(bId), type(bType), state(bState) {}
    // display

    void displayControls()
    {
        cout << "Id:" << id << ", Type:" << type << ", State:" << state << endl;
    }

    // operator overloading to compare id
    bool compareById(const Control &control, int targetId)
    {
        return control.id == targetId;
    }
};

// main
int main()
{
    vector<Control> controls; // controls stored in vector

    // creating 10 sample controls
    Control control1(1001, "Button", "visible");
    Control control2(1002, "Slider", "visible");
    Control control3(1003, "Slider", "invisible");
    Control control4(1004, "Button", "visible");
    Control control5(1005, "Slider", "invisible");
    Control control6(1006, "Button", "visible");
    Control control7(1007, "Button", "visible");
    Control control8(1008, "Slider", "visible");
    Control control9(1009, "Button", "invisible");
    Control control10(1010, "Slider", "invisible");

    controls.push_back(control1);
    controls.push_back(control2);
    controls.push_back(control3);
    controls.push_back(control4);
    controls.push_back(control5);
    controls.push_back(control6);
    controls.push_back(control7);
    controls.push_back(control8);
    controls.push_back(control9);
    controls.push_back(control10);

    // stl algorithms
     
    // for_each for printing
    for_each(controls.begin(), controls.end(), [](Control control)
             { control.displayControls(); }); // call display on control obj
    // find(), find by id
    int controlId = 1004;
    auto controlById = find(controls.begin(), controls.end(), [controlId](const Control control)
                            { return control.id == controlId; });

    // check if cotrolById exist or not
    if (controlById == controls.end())
    {
        cout << "given id not found" << endl;
    }
}
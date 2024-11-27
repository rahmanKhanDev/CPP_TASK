#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// struct of way points
struct Waypoint
{
private:
    double latitude;

    double longitude;

    string description;

public:
    // parameterized constructor
    Waypoint(double latitude, double longitude, string description) : latitude(latitude), longitude(longitude), description(description)
    {
    }

    // ~Waypoint()
    // {
    //     cout << "waypoint destroyed:" << description << endl; // will be called when delete will happen in main like delete waypoint
    // }

    // getters
    double getLatitude()
    {
        return latitude;
    }

    double getLongitude()
    {
        return longitude;
    }

    string getDescription()
    {
        return description;
    }
};

class Navigation
{
private:
    vector<Waypoint> waypoints;

public:
    // push to the vector
    void addWaypoint(const Waypoint &waypoint)
    {
        waypoints.push_back(waypoint);
        cout << "Sucessfully added waypoint" << endl;
    }

    // remove waypoint based on index
    void removeWaypoint(size_t index)
    {
        if (index < waypoints.size())
        {
            Waypoint wayPointToBeDeleted = waypoints[index]; // store waypoint before deleteion

            waypoints.erase(waypoints.begin() + index); // 0+index
            cout << "sucessfully deleted waypoint:" << wayPointToBeDeleted.getDescription() << endl;
        }
        else
        {
            cout << "Error: Index out of bound" << endl;
        }
    }

    // clear waypoints
    void clearWaypoints()
    {
        if (!waypoints.empty())
        {
            waypoints.clear();
            cout << "Waypoint list cleared." << endl;
        }
        else
        {
            cout << "No waypoints to clear" << endl;
        }
    }

    // display in sequence al waypoints
    void displayWaypoints() const
    {
        if (!waypoints.empty())
        {
            int count = 0;
            for (Waypoint waypoint : waypoints)
            {
                count++;
                cout << "Waypoint " << count << " [lat: " << waypoint.getLatitude() << ", lon:" << waypoint.getLongitude() << "]- '" << waypoint.getDescription() << "'" << endl;
            }
        }
        else
        {
            cout << "No waypoints to show, please add some waypoints." << endl;
        }
    }
};

int main()
{
    double latitude;
    double longitude;
    string description;

    int size; // size for waypoints

    cout << "How many waypoints you want to enter:" << endl;
    cin >> size;

    Navigation navigation;
    // adding waypoints to navigation vector
    for (int i = 0; i < size; i++)
    {
        cout << "Enter " << i + 1 << " waypoint information-" << endl;
        cout << "Enter latitude:" << endl;
        cin >> latitude;
        cout << "Enter longitude:" << endl;
        cin >> longitude;
        cin.ignore(); // ignore spcaes left by cin in the next line
        cout << "Enter description:" << endl;
        getline(cin, description);

        Waypoint waypoint(latitude, longitude, description);
        navigation.addWaypoint(waypoint);
        cout << endl;
    }

    cout << "Before remove waypoints are:" << endl;
    navigation.displayWaypoints();
    cout << endl;

    if (size > 0) // checks if waypoints are present or not
    {
        navigation.removeWaypoint(0);
        cout << endl;
        cout << "After removal of waypoint, waypoints are:" << endl;
        cout << endl;
        navigation.displayWaypoints();
    }
    else
    {
        cout << "No waypoints to remove" << endl;
    }

    cout << "\n";
    navigation.clearWaypoints();

    navigation.displayWaypoints();
    return 0;
}

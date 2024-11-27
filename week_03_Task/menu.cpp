#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define the structure for the Menu Tree node
struct MenuNode
{
    string data;                 // Menu item name
    vector<MenuNode *> children; // Submenus (children)

    MenuNode(string itemData)
    {
        data = itemData;
    }

    // Add a submenu to the current menu item
    void addChild(MenuNode *child)
    {
        children.push_back(child);
    }
};

void displayMenu(MenuNode *menu, int level = 0)
{
    // cout << string(level * 4, ' ') << "== " << menu->data << " ==\n";
    cout << "== " << menu->data << " ==\n";
    if (menu->children.empty())
    {
        cout << "No submenus available.\n";
    }
    else
    {
        for (int i = 0; i < menu->children.size(); i++)
        {
            cout << i + 1 << ". " << menu->children[i]->data << endl;
        }
    }
}

// Function to handle navigation through the menu tree
void navigateMenu(MenuNode *menu)
{
    int choice;
    while (true)
    {
        displayMenu(menu); // Show current menu
        cout << "Choose an option (enter 0 to go back): ";
        cin >> choice;

        // Check if the user wants to go back to the previous menu
        if (choice == 0)
        {
            cout << "Going back...\n";
            break;
        }

        // Check if the choice is valid
        if (choice < 1 || choice > menu->children.size())
        {
            cout << "Invalid choice, please try again.\n";
        }
        else
        {
            // Navigate to the chosen submenu
            cout << "Navigating to " << menu->children[choice - 1]->data << "...\n";
            navigateMenu(menu->children[choice - 1]); // Recursively navigate deeper
        }
    }
}

int main()
{
    // Root Menu
    MenuNode *root = new MenuNode("Main Menu");

    // Submenus under "Main Menu"
    MenuNode *submenu1 = new MenuNode("Settings");
    MenuNode *submenu2 = new MenuNode("Media");

    // Adding submenus to root
    root->addChild(submenu1);
    root->addChild(submenu2);

    // Submenus under "Settings"
    MenuNode *submenu1_1 = new MenuNode("Display Settings");
    MenuNode *submenu1_2 = new MenuNode("Audio Settings");
    submenu1->addChild(submenu1_1);
    submenu1->addChild(submenu1_2);

    // Submenu under "Help"
    MenuNode *submenu2_1 = new MenuNode("Radio");
    MenuNode *submenu2_2 = new MenuNode("Bluetooth Audio");
    submenu2->addChild(submenu2_1);
    submenu2->addChild(submenu2_2);

    // Start navigating the menu
    cout << "Welcome to the Menu System!\n";
    navigateMenu(root);

    // Clean up dynamically allocated memory
    delete root;
    delete submenu1;
    delete submenu2;
    delete submenu1_1;
    delete submenu1_2;
    delete submenu2_1;

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct City {
    int index;
    string name;
};

vector<City> cities;
vector<vector<int>> roads;
vector<vector<double>> budgets;

// Find city index by name
int findCityIndex(const string& name) {
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == name) return i;
    }
    return -1;
}

// Add cities
void addCities(int n) {
    for (int i = 0; i < n; ++i) {
        string name;
        cout << "Enter the name of city " << cities.size() + 1 << ": ";
        cin >> ws;
        getline(cin, name);

        if (findCityIndex(name) != -1) {
            cout << "City already exists. Skipping...\n";
            continue;
        }

        cities.push_back({(int)cities.size() + 1, name});
        for (auto& row : roads) row.push_back(0);
        roads.push_back(vector<int>(cities.size(), 0));
        for (auto& row : budgets) row.push_back(0.0);
        budgets.push_back(vector<double>(cities.size(), 0.0));
    }
}

// Add road
void addRoad() {
    string c1, c2;
    cout << "Enter the name of the first city: "; cin >> ws; getline(cin, c1);
    cout << "Enter the name of the second city: "; getline(cin, c2);

    int i1 = findCityIndex(c1), i2 = findCityIndex(c2);
    if (i1 == -1 || i2 == -1 || i1 == i2) {
        cout << "Invalid city names.\n";
        return;
    }

    roads[i1][i2] = roads[i2][i1] = 1;
    cout << "Road added between " << c1 << " and " << c2 << "\n";
}

// Add budget
void addBudget() {
    string c1, c2;
    double b;
    cout << "Enter the name of the first city: "; cin >> ws; getline(cin, c1);
    cout << "Enter the name of the second city: "; getline(cin, c2);

    int i1 = findCityIndex(c1), i2 = findCityIndex(c2);
    if (i1 == -1 || i2 == -1 || !roads[i1][i2]) {
        cout << "No road exists between these cities.\n";
        return;
    }

    cout << "Enter the budget for the road (in Billion RWF): "; cin >> b;
    budgets[i1][i2] = budgets[i2][i1] = b;
    cout << "Budget added.\n";
}

// Edit city name
void editCity() {
    int idx;
    string newName;
    cout << "Enter the index of the city to edit: "; cin >> idx;
    if (idx < 1 || idx > cities.size()) {
        cout << "Invalid index.\n";
        return;
    }
    cout << "Enter new name for the city: "; cin >> ws; getline(cin, newName);
    cities[idx - 1].name = newName;
    cout << "City updated successfully.\n";
}

// Search city by index
void searchCity() {
    int idx;
    cout << "Enter the index of the city: "; cin >> idx;
    if (idx < 1 || idx > cities.size()) {
        cout << "City not found.\n";
        return;
    }
    cout << idx << ": " << cities[idx - 1].name << "\n";
}

// Display all cities
void displayCities() {
    for (const auto& city : cities) {
        cout << city.index << ": " << city.name << "\n";
    }
}

// Display roads adjacency matrix
void displayRoads() {
    cout << "Cities:\n";
    for (const auto& city : cities)
        cout << city.index << ": " << city.name << "\n";

    cout << "\nRoads Adjacency Matrix:\n";
    for (int i = 0; i < roads.size(); i++) {
        for (int j = 0; j < roads[i].size(); j++) {
            cout << roads[i][j];
        }
        cout << "\n";
    }
}

// Display all recorded data (cities + road + budget)
void displayAllData() {
    displayCities();
    cout << "\nRoads Adjacency Matrix:\n";
    for (auto& row : roads) {
        for (auto val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "\nBudget Adjacency Matrix (in Billion RWF):\n";
    for (auto& row : budgets) {
        for (auto val : row) cout << fixed << setprecision(1) << val << " ";
        cout << "\n";
    }
}

// Save to files
void saveToFiles() {
    ofstream cityFile("cities.txt"), roadFile("roads.txt");
    cityFile << "Index City Name\n";
    for (auto& city : cities)
        cityFile << city.index << "     " << city.name << "\n";
    cityFile.close();

    roadFile << "Nbr  Road                                Budget\n";
    int count = 1;
    for (int i = 0; i < roads.size(); i++) {
        for (int j = i + 1; j < roads[i].size(); j++) {
            if (roads[i][j]) {
                roadFile << count++ << ".   " << cities[i].name << "-" << cities[j].name
                         << setw(35 - cities[i].name.length() - cities[j].name.length())
                         << budgets[i][j] << "\n";
            }
        }
    }
    roadFile.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n"
             << "1. Add new city(ies)\n"
             << "2. Add roads between cities\n"
             << "3. Add budget for roads\n"
             << "4. Edit city\n"
             << "5. Search for a city using its index\n"
             << "6. Display cities\n"
             << "7. Display roads\n"
             << "8. Display recorded data on console\n"
             << "9. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int n;
                cout << "Enter the number of cities to add: ";
                cin >> n;
                addCities(n);
                break;
            }
            
            case 2: addRoad(); break;
            case 3: addBudget(); break;
            case 4: editCity(); break;
            case 5: searchCity(); break;
            case 6: displayCities(); break;
            case 7: displayRoads(); break;
            case 8: displayAllData(); break;
            case 9: saveToFiles(); cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}

#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

void setGoals(queue<string>& Activities);
void removeGoals(queue<string>& Activities);
void displayGoals(const queue<string>& Activities);
void saveToFile(const queue<string>& Activities, const string& filename);
void loadFromFile(queue<string>& Activities, const string& filename);

int main() {
    cout << "**** DAILY ACTIVITY TRACKER ****" << endl;
    string ch;
    const string filename = "Goal.txt";
    queue<string> activities;

    loadFromFile(activities, filename);

    while (true) {
        cout << "\nWhat do you want to do? (add, remove, review, exit): ";
        cin >> ch;
        cin.ignore(); // Flush newline after ch input

        if (ch == "add") {
            setGoals(activities);
        } else if (ch == "remove") {
            removeGoals(activities);
        } else if (ch == "review") {
            displayGoals(activities);
        } else if (ch == "exit") {
            saveToFile(activities, filename);
            break;
        } else {
            cout << "Invalid input." << endl;
        }
    }
    return 0;
}

void setGoals(queue<string>& Activities) {
    string work;
    string stopPoint;
    do {
        cout << "Enter Goal: ";
        getline(cin, work);
        if (!work.empty()) {
            Activities.push(work);
        }
        cout << "Stop? (yes to stop, anything else to continue): ";
        getline(cin, stopPoint);
    } while (stopPoint != "yes");
}

void removeGoals(queue<string>& Activities) {
    if (Activities.empty()) {
        cout << "No goals to remove." << endl;
        return;
    }
    int goals_to_delete = 0;
    cout << "Enter the number of goals to delete: ";
    cin >> goals_to_delete;
    cin.ignore();
    if (goals_to_delete > Activities.size()) {
        cout << "You entered more than the number of goals present." << endl;
        return;
    }
    for (int i = 0; i < goals_to_delete; i++) {
        cout << "Will remove: " << Activities.front() << endl;
        Activities.pop();
        cout << "Removed " << i + 1 << " task(s)" << endl;
    }
}

void displayGoals(const queue<string>& Activities) {
    queue<string> temp = Activities;
    int i = 1;
    if (temp.empty()) {
        cout << "No goals to display." << endl;
        return;
    }
    while (!temp.empty()) {
        cout << i << ". " << temp.front() << endl;
        temp.pop();
        i++;
    }
}

void saveToFile(const queue<string>& Activities, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }
    queue<string> temp = Activities;
    int i = 1;
    while (!temp.empty()) {
        file << i << ". " << temp.front() << endl;
        temp.pop();
        i++;
    }
    file.close();
}

void loadFromFile(queue<string>& Activities, const string& filename) {
    ifstream file(filename);
    string line;
    if (!file.is_open()) {
        cout << "No previous entries." << endl;
        return;
    }
    while (getline(file, line)) {
        // Remove any leading numbers and ". " sequences
        while (!line.empty() && isdigit(line[0])) {
            size_t pos = line.find(". ");
            if (pos != string::npos) {
                line = line.substr(pos + 2);
            } else {
                break;
            }
        }
        if (!line.empty()) {
            Activities.push(line);
        }
    }
}

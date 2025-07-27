#include <iostream>
#include <vector>
#include <string>
using namespace std;

void view_tasks(vector<string>& tasks);
void add_task(vector<string>& tasks);
void remove_task(vector<string>& tasks);



int main(){

    bool end_program = false;
    vector<string> tasks;
    cout << "Welcome to your To-Do List" << endl;

    while(!end_program){
        char user_input;
        cout << "What would you like to do? Type v to view tasks, a to add tasks, r to remove tasks, or e to exit: " << endl;
        cin >> user_input;
        cin.ignore();

        user_input = tolower(user_input);

        if(!(user_input == 'v') && !(user_input == 'a') && !(user_input == 'r') && !(user_input == 'e')){
            cout << "Invalid input! Please try again..." << endl;
            continue;
        }

        switch(user_input) {
            case 'v':
                cout << "Viewing tasks..." << endl;
                view_tasks(tasks);
                break;
            case 'a':
                cout << "Choosing to add a task..." << endl;
                add_task(tasks);
                break;
            case 'r':
                cout << "Choosing to remove a task..." << endl;
                remove_task(tasks);
                break;
            case 'e':
                cout << "Exiting program..." << endl;
                end_program = true;
                break;
        }

    }
    
    return 0;
}

void view_tasks(vector<string>& tasks){

    if(tasks.empty()){
        cout << "No tasks available." << endl;
        return;
    }

    cout << "Here are your tasks..." << endl;
    cout << "------------------------" << endl;

    for(int i = 0; i < tasks.size(); i++){
        cout << i + 1 << ". " << tasks[i] << endl;
    }

    return;

}

void add_task(vector<string>& tasks){
    string task;
    cout << "Enter a task to add: " << endl;
    getline(cin,task);
    tasks.push_back(task);
    cout << "Tasks added successfully!" << endl;
    return;

}

void remove_task(vector<string>& tasks){
    string task_number;

    if(tasks.empty()){
        cout << "Sorry, there are no tasks to remove!" << endl;
        return;
    }

    view_tasks(tasks);
    cout << "Enter what number task to remove: " << endl;
    getline(cin,task_number);

    if(stoi(task_number) > tasks.size()){
        cout << "Invalid task number!" << endl;
        return;
    } else {
        tasks.erase(tasks.begin() + ( stoi(task_number) - 1 ) );
        cout << "Task removed successfully!" << endl;
        return;
    }
    
} 




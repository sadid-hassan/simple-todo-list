/*
 * File: main_cli.cpp
 * Project: TodoListGUI
 * Author: Sadid Hassan
 * Description:
 *   Entry point for the To-Do List application. Initializes
 *   the application window and manages program flow.
 *
 * Created: July 2025
 * Updated: July 2025
 */



#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Command Characters
const char VIEW = 'v';
const char ADD = 'a';
const char REMOVE = 'r';
const char EXIT = 'e';


void view_tasks(vector<string>& tasks);
void add_task(vector<string>& tasks);
void remove_task(vector<string>& tasks);





/*
* @brief Handles the user menu for the To-Do List
*
* Continuously prompts the user for an action until they choose to exit.
* Valid actions include: view, add, remove.
*/
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
            case VIEW:
                cout << "Viewing tasks..." << endl;
                view_tasks(tasks);
                break;
            case ADD:
                cout << "Choosing to add a task..." << endl;
                add_task(tasks);
                break;
            case REMOVE:
                cout << "Choosing to remove a task..." << endl;
                remove_task(tasks);
                break;
            case EXIT:
                cout << "Exiting program..." << endl;
                end_program = true;
                break;
        }

    }
    
    return 0;
}



/*
* @brief Allows user to view the tasks in the To-Do List as a numbered list
*
* @param tasks Reference to the list of current tasks
*/ 
void view_tasks(vector<string>& tasks){

    if(tasks.empty()){
        cout << "No tasks available." << endl;
        return;
    }

    cout << "Here are your tasks..." << endl;
    cout << "------------------------" << endl;

    for(size_t i = 0; i < tasks.size(); i++){
        cout << i + 1 << ". " << tasks[i] << endl;
    }

    return;

}



/*
* @brief Adds a task to the To-Do List
*
* Prompts the user for a description and appends 
* the task to the vector
*
* @param tasks Reference to the list of current tasks
*/
void add_task(vector<string>& tasks){
    string task;
    cout << "Enter a task to add: " << endl;
    getline(cin,task);
    tasks.push_back(task);
    cout << "Tasks added successfully!" << endl;
    return;

}



/*
* @brief Removes a task from the To-Do List
*
* Prompts the user to select a number, 
* and removes that associated task from the list
*
* @param tasks Reference to the list of current tasks
*/
void remove_task(vector<string>& tasks){
    string task_number;

    if(tasks.empty()){
        cout << "Sorry, there are no tasks to remove!" << endl;
        return;
    }

    view_tasks(tasks);
    cout << "Enter what number task to remove: " << endl;
    getline(cin,task_number);

    int index;
    try{
        index = stoi(task_number);
    } catch (...){
        cout << "Invalid input!" << endl;
        return;
    }

    if(index < 1 || index > tasks.size()){
        cout << "Invalid task number!" << endl;
        return;
    } else {
        tasks.erase(tasks.begin() + ( index - 1 ) );
        cout << "Task removed successfully!" << endl;
        return;
    }
    
} 




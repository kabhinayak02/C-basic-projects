#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct todolist{
    int id;
    string task;
};

int Id;

void addTask(){
    // system("clear");
    todolist todo;
    cout << "Enter new task: " << endl;
    cin.get();
    getline(cin, todo.task);
    char save;
    cout << "save? (y/n): ";
    cin >> save;
    if(save == 'y' or save == 'Y'){
        Id++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n" << Id;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add more task? (y/n): ";
        cin >> more;
        if(more == 'y' or more == 'Y'){
            addTask();
        }
        else{
            // system("clear");
            cout << "Added successfully" << endl;
            return;
        }
    }
    // system("clear");
}

void showTask(){
    // system("clear");
    todolist todo;
    ifstream fin;
    fin.open("todo.txt");
    cout << "Task: " << endl;

    while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.task != ""){
            cout << todo.id << ": " << todo.task << endl;
        }
        else{
            cout << "\tEmpty" << endl;
        }

    }
    fin.close();

}

int searchTask(){
    // system("clear");
    int id;
    cout << "Enter the Task Id: ";
    cin >> id;
    todolist todo;
    ifstream fin("todo.txt");
    while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.id == id){
            // system("clear");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }
    // system("clear"); 
    cout << "Not Found" << endl;
    return 0;
}

void deleteTask(){
    // system("clear");
    int id = searchTask();
    if(id == 0){
        cout << "Not Found";
        return;
    }
    char del;
    cout << "\n\t Delete? (y/n): ";
    cin >> del;
    if(del == 'y' or del == 'Y'){
        todolist todo;
        ofstream temp;
        temp.open("temp.txt");
        ifstream fin;
        fin.open("todo.txt");
        int index = 1;
        while(!fin.eof()){
            fin >> todo.id;
            fin.ignore();
            getline(fin, todo.task);
            if(todo.id != id){
                temp << "\n" << index;
                temp << "\n" << todo.task;
                index++;
                Id--;

            }
        }
        fin.close();
        temp.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        // system("clear");
        cout << "\n\t Deleted Successfully! " << endl;
    }
    else{
        // system("clear");
        cout << "Not Found" << endl;
    }
}

void updateTask(){
    int id = searchTask(); // First, search for the task to update
    if(id == 0){
        cout << "Task not found" << endl;
        return;
    }

    char updateChoice;
    cout << "Do you want to update this task? (y/n): ";
    cin >> updateChoice;
    if(updateChoice != 'y' && updateChoice != 'Y') {
        cout << "Task not updated" << endl;
        return;
    }

    todolist todo;
    ifstream fin("todo.txt");
    ofstream temp("temp.txt");
    while(fin >> todo.id && getline(fin, todo.task)){
        if(todo.id == id){
            cout << "Enter new task: ";
            cin.ignore(); // Ignore the newline character in the buffer
            getline(cin, todo.task); // Get the new task from the user
        }
        temp << todo.id << "\n" << todo.task << "\n";
    }
    fin.close();
    temp.close();

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    cout << "Task updated successfully" << endl;
}


int main(){
    // system("clear");
    while(true){
        // banner();
        cout<<" 1. Add Task" << endl;
        cout<<" 2. Show Task" << endl;
        cout<<" 3. Search Task" << endl;
        cout<<" 4. Delete Task" << endl;
        cout<<" 5. Update Task" << endl;
        cout<<" 6. Exit the App" <<endl;

        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            showTask();
            break;
        case 3:
            searchTask();
            break;
        case 4:
            deleteTask();
            break;
        case 5:
            updateTask();
            break;
        case 6:
            return 0;
        default:
            cout<<"Enter Valid input";
            break;
        }
    }
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> 
using namespace std;

struct todolist
{
    int id;
    string task;
};

    int ID;

    void heading();
    void addTask();
    void showTask();
    int searchTask();
    void deleteTask();
    void updateTask();



int main (){
    system("cls");

    while (true)
    {
       heading();
        cout<<"\n\t1. Add Task";
        cout<<"\n\t2. Show Task";
        cout<<"\n\t3. Search Task";
        cout<<"\n\t4. Delete Task";
        cout<<"\n\t5. Update Task";

        int choice;
        cout<<"\n\tEnter Choice: ";
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
        
        default:
            break;
        }
     
    }
    return 0;
}

        void heading(){
            cout<<"_________________________________"<<endl;
            cout<<"\t     My Todo   "<<endl;
            cout<<"_________________________________"<<endl;
        }



        void addTask(){
            system("cls");
            heading();

            todolist todo;
            cout<<"Enter New Task(ID: " <<ID+1<< "): "<<endl;
            cin.get();
            getline(cin,todo.task);
            char save;
            cout<<"Do you want to save the task? (y/n):";
            cin>>save;
            if(save == 'y'){
                ID++;
                ofstream fout;   //writing something in file
                fout.open("todo.txt", ios::app);
                fout<<"\n"<<ID;
                fout<<"\n"<<todo.task;
                fout.close();

                char more;   //User want to add new task
                cout<<"Do you want to add more Task? (y/n):";
                cin>>more;

                if(more == 'y'){
                    addTask();
                }
                else{
                    system("cls");
                    cout<<"Added Succesfully!"<<endl;
                    return;
                }

            }
            system("cls");


        }

        void showTask(){
            system("cls");
            heading();

            todolist todo;
            ifstream fin;
            fin.open("todo.txt");
            cout<<"Task:"<<endl;

            while(!fin.eof()){
                    fin>>todo.id;
                    fin.ignore();
                    getline(fin, todo.task);

                    if(todo.task != ""){
                        cout<<"\t"<<todo.id<<":"<<todo.task<<endl;

                    }
                    else{
                        cout<<"\tEmpty!"<<endl;

                    }
            }
            fin.close();
            char exit;
            cout<<"Exit? (y/n):";
            cin>>exit;

            if(exit != 'y'){
                showTask();

            }
            system("cls");
        }


        int searchTask(){
            system("cls");
            heading();

            int id;
            cout<<"Enter the Task id:";
            cin>>id;
            todolist todo;
            ifstream fin("todo.txt");
            
            while(!fin.eof()){

                fin>>todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if(todo.id == id){
                    system("cls");
                    cout<<"Task: "<<endl;
                     cout<<"\t"<<todo.id<<":"<<todo.task<<endl;
                     return id;

                }
            }
            system("cls");
            cout<<"Not Found!"<<endl;
            return 0;
        }



        void deleteTask(){
            system("cls");
            int id = searchTask();
            if(id != 0){
                char del;
                cout<<"\\n\tDelete? (y/n):";
                cin>>del;

                if(del == 'y'){
                    todolist todo;
                    ofstream tempFile;
                    tempFile.open("temp.txt");
                    ifstream fin;
                    fin.open("todo.txt");
                    int index =1;
                    while(!fin.eof()){
                        fin>>todo.id;
                        fin.ignore();
                        getline(fin, todo.task);
                        if(todo.id != id){
                            tempFile << "\n"<<index;
                            tempFile<<"\n"<<todo.task;
                            index++;
                            ID--;
                        }

                    }
                    fin.close();
                    tempFile.close();
                    remove("todo.txt");
                    rename("temp.txt", "todo.txt");
                    system("cls");
                    cout<<"\n\tDeleted Succesfully!"<<endl;

                }
                else{
                    system("cls");
                    cout<<"Not Deleted!"<<endl;
                }
            }
        }


        void updateTask() {
    system("cls");
    int id = searchTask();  // Search for the task by ID
    if (id != 0) {
        todolist todo;
        char update;
        cout << "\n\tUpdate? (y/n): ";
        cin >> update;

        if (update == 'y') {
            string updatedTask;
            cin.ignore();  // Clear input buffer
            cout << "Enter updated task: ";
            getline(cin, updatedTask);

            ofstream tempFile;  // Temporary file for the updated content
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            while (!fin.eof()) {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id == id) {
                    tempFile << "\n" << todo.id;
                    tempFile << "\n" << updatedTask;  // Update the task with new input
                } else {
                    tempFile << "\n" << todo.id;
                    tempFile << "\n" << todo.task;  // Keep the task as is if not updated
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");           // Remove the original file
            rename("temp.txt", "todo.txt");  // Rename the temp file to the original file

            system("cls");
            cout << "\n\tUpdated Successfully!" << endl;
        } else {
            system("cls");
            cout << "Task not updated!" << endl;
        }
    }
}

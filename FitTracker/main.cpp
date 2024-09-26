#include<iostream>
#include<conio.h>
#include"sqlite/sqlite3.h"

using namespace std;

class create_user {
    string name;
    char gender;
    int age;
    float weight;
    float height;
    string username;
    string password;


    public :

    void registeruser() {
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter age: ";
        cin>>age;


        while(true) {
            cout<<"Enter sex";
            cin>>gender;
            if(gender=='m' || gender=='M'|| gender=='f'||gender=='F') {
                break;
            }
            else {
                cout<<"Sorry wrong gender!!"<<endl;
                cout<<"If u think this is your real gender please die"<<endl;
                cout<<"If u think there has been an error PLease enter again"<<endl;
            }
        }

        cout<<"Enter weight: ";
        cin>>weight;
        cout<<"Enter height: ";
        cin>>height;
        cout<<"Enter username";
        cin>>username;
        cout<<"Enter password";
        cin>>password;
        cout<<"User Created successfully!!"<<endl;
    }
    bool validateLogin(string username,string password){
        sqlite3 *db;
        int rc = sqlite3_open("fitness_database.db", &db);
        if (rc != SQLITE_OK) {
            cout<<"Can't open database"<<endl;
            return false;
        }
        const char *sql = "SELECT * FROM user WHERE username = ? AND password = ?";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            cout<<"Can't prepare statement"<< sqlite3_errmsg(db)<<endl;
            sqlite3_close(db);
            return false;
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, NULL);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, NULL);

        rc = sqlite3_step(stmt);

        if(rc == SQLITE_ROW) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return true;
        }
        else{
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return false;
        }
    }
    void displayuser(){
        cout<<name[0]<<endl;
        cout<<gender<<endl;
        cout<<age<<endl;
        cout<<weight<<endl;
        cout<<height<<endl;
    }

    void insert_into_database();
    void retreive_data(const string& username);

    };

void create_user::retreive_data(const string &username) {
    sqlite3 *db;
    int rc = sqlite3_open("fitness_database.db", &db);
    if(rc != SQLITE_OK) {
        cout<<"Can't open database"<<endl;
        sqlite3_close(db);
    }
    const char sql[] = "SELECT * FROM user WHERE username= ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(rc != SQLITE_OK) {
        cout<<"Can't prepare statement"<<endl;
        sqlite3_close(db);
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, NULL);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *namepointer = sqlite3_column_text(stmt, 0);
        string name = string(reinterpret_cast<const char*>(namepointer));
        const unsigned char *genderpointer = sqlite3_column_text(stmt, 1);
        string gender = string(reinterpret_cast<const char*>(genderpointer));
        int age = sqlite3_column_int(stmt, 2);
        auto weight = (float)sqlite3_column_double(stmt, 3);
        auto height= (float)sqlite3_column_double(stmt, 4);
        const unsigned char *usernamepointer = sqlite3_column_text(stmt, 5);
        string password = string(reinterpret_cast<const char*>(usernamepointer));
        const unsigned char *passwordpointer = sqlite3_column_text(stmt, 6);
        string username = string(reinterpret_cast<const char*>(passwordpointer));
    }
    cout<<"Name: "<<name<<endl;
    cout<<"Gender: "<<gender<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Weight: "<<weight<<endl;
    cout<<"Height: "<<height<<endl;
}
void create_user::insert_into_database() {

    int rc = sqlite3_initialize();
    if (rc != SQLITE_OK) {
        cout<<"sqlite3_initialize failed"<<endl;
        return;
    }
    else {
        cout<<"sqlite3_initialize success"<<endl;
    }

    sqlite3 *db;
    rc = sqlite3_open("fitness_database.db",&db);
    if(rc != SQLITE_OK) {
        cout<<"Can't open database"<<endl;
        sqlite3_close(db);
        return;
    }
    else {
        cout<<"Opened database successfully"<<endl;
    }


    const char *sql = "CREATE TABLE IF NOT EXISTS user (name TEXT , age INTEGER, gender TEXT, weight REAL, height REAL, username TEXT PRIMARY KEY, password TEXT)";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        cout<<"Can't create table"<<endl;
        sqlite3_close(db);
        return;
    }
    else {
        cout<<"Created table successfully"<<endl;
    }

    char str[256];
    sprintf(str,"INSERT INTO user (name, age, gender, weight, height, username, password) VALUES ('%s','%d','%c','%f','%f','%s','%s')",name.c_str(),age,gender,weight,height,username.c_str(),password.c_str());
    rc = sqlite3_exec(db, str, 0, 0, 0);
    if (rc != SQLITE_OK) {
        cout<<"Can't insert table"<<endl;
        sqlite3_close(db);
        return;
    }
    else {
        cout<<"Insert table successfully"<<endl;
    }
    sqlite3_close(db);
}


    int main() {
        string username,password; //using it in switch case 2nd block
        create_user user1;
        while (1){
            cout<<"-----------MENU------------"<<endl;
            cout<<"1. Create user"<<endl;
            cout<<"2.Login user"<<endl;
            cout<<"3. Exit"<<endl;

            cout<<"Enter your choice: ";
            int choice;
            cin>>choice;

            switch(choice) {
                case 1:
                    user1.registeruser();
                    user1.insert_into_database();
                break;
                case 2:
                    cout<<"Enter username";
                cin>>username;
                cout<<"Enter password";
                cin>>password;

                if(user1.validateLogin(username,password)){
                    cout << "Login Successfull";
                    user1.retreive_data(username);



                }
                else{
                    cout << "Invalid username or password";

                }

                break;
                default:
                    cout<<"Wrong option";
                break;
            }
        }
        getch();
    }

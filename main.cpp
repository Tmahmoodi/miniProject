#include<iostream>
#include<string>
#include<fstream>
#include "professor.h"
#include "student.h"
using namespace std;
//make a class for entering to the site to keep usernames and passwords in the private part of the class
class site
{
private:
    int log_in;
    string user, username, password, given_username, given_password;
public:
    //call panel function on the start object of the class to show a panel for sing up, sign in or exit from the site
    void panel()
    {
        //make a do_while loop so whenever the user sign out from its own panel, site's panel will show again
        do
        {
            cout<<"======================================================================="<<endl;
            cout <<"enter 1 for sign up.\nenter 2 for sign in.\nenter 3 to close the site:\n";
            cin >> log_in;
            cout<<"======================================================================="<<endl;
            switch (log_in)
            {
                //make a new account
                case 1:
                {
                    string check_user, check_pass;
                    bool check = true;
                    //opening a file in read mode to compare new username with old usernames and in write mode to
                    //write the new username and password in the file
                    fstream user_pass_professor;
                    user_pass_professor.open("professor_user_pass.txt", fstream::in|ios::app|fstream::out);
                    //exception handling to be sure that the file is open
                    if(!user_pass_professor.is_open())
                    {
                        cerr<<"there is a problem. please try again a few minutes later.\n";
                        return;
                    }
                    else
                    {
                        //make a while loop to be sure that the new username is not duplicated
                        while(check)
                        {
                            check = false;
                            cout<<"please enter your username: \n";
                            getline(cin>>ws, username);
                            //compare new username with old usernames from the beginning till the end of the file
                            while(!user_pass_professor.eof())
                            {
                                getline(user_pass_professor, check_user, '\n');
                                getline(user_pass_professor, check_pass, '\n');
                                if(check_user == username)
                                {
                                    cout<<"your username is already chosen by others. please try again.\n";
                                    check = true;
                                    //if the new username was duplicated, back to the beginning of the file and get the
                                    //username again and check it with old ones
                                    user_pass_professor.clear();
                                    user_pass_professor.seekg(0, ios::beg);
                                    break;
                                }
                            }
                        }
                    }
                    //go to the end of the file to add new username and password
                    user_pass_professor.clear();
                    user_pass_professor.seekp(ios::end);
                    cout<<"please enter your password: \n";
                    getline(cin>>ws, password);
                    //write new username and password in the file
                    user_pass_professor<<username<<"\n"<<password<<endl;
                    cout<<"welcome "<<username<<":) "<<endl;
                    //close the opened file
                    user_pass_professor.close();
                    //make an object of the professor class and call a function on it to show the designed panel for professors
                    professor ob;
                    ob.professor_panel(username);
                    break;
                }
                    //login to the site with a created account
                case 2:
                {
                    string saved_user, saved_password;
                    bool find = false;
                    cout<<"please enter 'p' if you are professor and enter 's' if you are student:\n";
                    cin>>user;
                    if(user == "p")
                    {
                        while (!find)
                        {
                            //open the file in read mode to find the given username and password
                            ifstream user_pass_professor;
                            user_pass_professor.open("professor_user_pass.txt", fstream::in);
                            //exception handling to be sure that the file is open
                            if(!user_pass_professor.is_open())
                            {
                                cerr<<"there is a problem. please try again a few minutes later.\n";
                                return;
                            }
                            else
                            {
                                cout<<"please enter your username: \n";
                                getline(cin>>ws, given_username);
                                cout<<"please enter your password: \n";
                                getline(cin>>ws, given_password);
                                //searching for the given username and password from the beginning till the end of the file
                                while (!user_pass_professor.eof())
                                {
                                    getline(user_pass_professor, saved_user);
                                    getline(user_pass_professor, saved_password);
                                    if(saved_user == given_username)
                                    {
                                        if(saved_password == given_password)
                                        {
                                            cout<<"welcome "<<given_username<<":) "<<endl;
                                            find = true;
                                            //make an object of the professor class and call a function on it
                                            //to show the designed panel for professors
                                            professor ob;
                                            //give the username of professor to the function with reference to avoid make
                                            //unnecessary copy of it
                                            ob.professor_panel(given_username);
                                            break;
                                        }
                                    }
                                }
                                if(!find)
                                {
                                    cout<<"your username or password is incorrect. please try again.\n";
                                }
                                //close the opened file
                                user_pass_professor.close();
                            }
                        }
                    }
                    else if(user == "s")
                    {
                        while(!find)
                        {
                            ifstream students;
                            students.open("student_user_pass.txt", fstream::in);
                            if(students.is_open())
                            {
                                cout<<"please enter your username: \n";
                                getline(cin>>ws, given_username);
                                cout<<"please enter your password: \n";
                                getline(cin>>ws, given_password);
                                //searching for the given username and password from the beginning till the end of the file
                                while (!students.eof())
                                {
                                    getline(students, saved_user);
                                    if(saved_user == ("student's username: " + given_username))
                                    {
                                        getline(students, saved_password);
                                        if(saved_password == ("password: " + given_password))
                                        {
                                            cout<<"welcome "<<given_username<<":)\n";
                                            find = true;
                                            //make an object of the student class and call a function on it
                                            //to show the designed panel for students
                                            student ob;
                                            //give the username of student to the function with reference to avoid make
                                            //unnecessary copy of it
                                            ob.student_panel(given_username);
                                            break;
                                        }
                                    }
                                }
                                //use a boolean to be sure that the given username and password was found
                                if(!find)
                                {
                                    cout<<"your username or password is incorrect. please try again.\n";
                                }
                                //close the opened file
                                students.close();
                            }
                                //exception handling to be sure that the file is open
                            else
                            {
                                cerr<<"there is a problem. please try again a few minutes later.\n";
                                return;
                            }
                        }
                    }
                    break;
                }
                    //log out
                case 3:
                {
                    cout<<"thanks for choosing our site :)\n";
                    break;
                }
            }
        }while(log_in != 3);
    }
};
int main()
{
    //make an object of the site class and call a function on it to enter to the site
    site start;
    start.panel();
    return 0;
}
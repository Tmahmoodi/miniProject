#include<iostream>
#include<string>
#include<fstream>
#include "professor.h"
#include "student.h"
using namespace std;
class site
{
private:
    int log_in;
    string user, username, password, given_username, given_password;
public:
    void panel()
    {
        do
        {
            cout<<"======================================================================="<<endl;
            cout <<"enter 1 for sign up.\nenter 2 for sign in.\nenter 3 to close the site:\n";
            cin >> log_in;
            cout<<"======================================================================="<<endl;
            switch (log_in)
            {
                case 1:
                {
                    string check_user, check_pass;
                    bool check = true;
                    while(check)
                    {
                        check = false;
                        cout<<"please enter your username: \n";
                        getline(cin>>ws, username);
                        fstream user_pass_professor;
                        user_pass_professor.open("professor_user_pass.txt", fstream::in|ios::app|fstream::out);
                        if(!user_pass_professor.is_open())
                        {
                            cout<<"there is a problem. please try again a few minutes later.\n";
                            check = false;
                        }
                        else
                        {
                            while(!user_pass_professor.eof())
                            {
                                getline(user_pass_professor, check_user, '\n');
                                getline(user_pass_professor, check_pass, '\n');
                                if(check_user == username)
                                {
                                    cout<<"your username is already chosen by others. please try again.\n";
                                    check = true;
                                    break;
                                }
                            }
                            user_pass_professor.close();
                        }
                    }
                    fstream user_pass_professor("professor_user_pass.txt", ios::out|ios::app);
                    if(!user_pass_professor)
                    {
                        cout<<"there is a problem. please make a try a few minutes later.\n";
                    }
                    else
                    {
                        cout<<"please enter your password: \n";
                        getline(cin>>ws, password);
                        user_pass_professor<<username<<"\n"<<password<<endl;
                        cout<<"welcome "<<username<<":) "<<endl;
                        professor ob;
                        ob.professor_panel(username);
                    }
                    break;
                }
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
                            fstream user_pass_professor;
                            user_pass_professor.open("professor_user_pass.txt", fstream::in|fstream::out);
                            if(!user_pass_professor.is_open())
                            {
                                cout<<"there is a problem. please try again a few minutes later.\n";
                                find = true;
                            }
                            else
                            {
                                cout<<"please enter your username: \n";
                                getline(cin>>ws, given_username);
                                cout<<"please enter your password: \n";
                                getline(cin>>ws, given_password);
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
                                            professor ob;
                                            ob.professor_panel(given_username);
                                            break;
                                        }
                                    }
                                }
                                if(!find)
                                {
                                    cout<<"your username or password is incorrect. please try again.\n";
                                }
                                user_pass_professor.close();
                            }
                        }
                    }
                    else if(user == "s")
                    {
                        while(!find)
                        {
                            fstream students;
                            students.open("student_user_pass.txt", fstream::in|fstream::out);
                            if(students.is_open())
                            {
                                cout<<"please enter your username: \n";
                                getline(cin>>ws, given_username);
                                cout<<"please enter your password: \n";
                                getline(cin>>ws, given_password);
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
                                            student ob;
                                            ob.student_panel();
                                            break;
                                        }
                                    }
                                }
                                if(!find)
                                {
                                    cout<<"your username or password is incorrect. please try again.\n";
                                }
                                students.close();
                            }
                            else
                            {
                                cout<<"there is a problem. please try again a few minutes later.\n";
                                find = true;
                            }
                        }
                    }
                    break;
                }
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
    site start;
    start.panel();
    return 0;
}
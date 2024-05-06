#ifndef MINI_PROJECT_PROFESSOR_H
#define MINI_PROJECT_PROFESSOR_H
#include <string>
#include<sstream>
using namespace std;
class exam
{
private:
    int num_questions;
    string type_question, question, name_of_exam, option;
    double time_question, time_exam = 0;
    float grade_question;
public:
    void make_test(string given_professor_user)
    {
        fstream exams("exams.txt", fstream::out|ios::app);
        if(!exams)
        {
            cout<<"there is a problem. please try again a few minutes later.";
        }
        else
        {
            exams<<"professor's name: "<<given_professor_user<<endl;
            cout<<"what is your exam name?\n";
            getline(cin>>ws, name_of_exam);
            exams<<"exam's name: "<<name_of_exam<<endl;
            cout<<"how many questions do you want to make?\n";
            cin>>num_questions;
            cout<<"whenever we ask about the type of your question, write 't' to design test question or write 'd' to make descriptive question.\n";
            for (int i = 0; i < num_questions; ++i)
            {
                cout<<"type of your question: \n";
                cin>>type_question;
                exams<<"type of question: "<<type_question<<endl;
                cout<<"question number "<<i+1<<": "<<endl;
                getline(cin>>ws, question);
                exams<<"question number "<<i+1<<": "<<question<<endl;
                if(type_question == "t")
                {
                    cout<<"a) ";
                    getline(cin>>ws, option);
                    exams<<"a) "<<option<<endl;
                    cout<<"b) ";
                    getline(cin>>ws, option);
                    exams<<"b) "<<option<<endl;
                    cout<<"c) ";
                    getline(cin>>ws, option);
                    exams<<"c) "<<option<<endl;
                    cout<<"d) ";
                    getline(cin>>ws, option);
                    exams<<"d) "<<option<<endl;
                    cout<<"please choose the correct answer:\n";
                    cin>>option;
                    exams<<"correct answer: "<<option<<endl;
                }
                cout<<"grade of this question:\n";
                cin>>grade_question;
                exams<<"grade this question: "<<grade_question<<endl;
                exams<<"---------------------------------------------------------------------"<<endl;
                cout<<"time of your question (based on minutes):\n";
                cin>>time_question;
                time_exam += time_question;
            }
        }
        exams<<"time of exam: "<<time_exam<<endl;
        exams<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        exams.close();
    }
};
class List
{
private:
    string list_name, user_st, pass_st, compare,professor_user, saved_list_name, line, searched_line;
    int num_st;
    bool check_name_list = true;
    stringstream saver_file;
public:
    void make_list(string given_professor_user)
    {
        fstream students;
        students.open("student_user_pass.txt", fstream::out|ios::app|fstream::in);
        if(students.is_open())
        {
            cout<<"the name of your list is better to have your lesson's name + your school or university's name + your name + year\n";
            do
            {
                check_name_list = false;
                cout<<"what is your list name?\n";
                getline(cin>>ws, list_name);
                while(!students.eof())
                {
                    getline(students, compare);
                    if(compare == "list's name: " + list_name)
                    {
                        check_name_list = true;
                        cout<<"your name list was chosen already. please choose another name.\n";
                        break;
                    }
                }
                students.close();
            } while(check_name_list);
            students.open("student_user_pass.txt", fstream::out|ios::app);
            if(students.is_open())
            {
                students<<"professor's name: "<<given_professor_user<<endl<<"list's name: "<<list_name<<endl;
                cout<<"how many students do you want to add?\n";
                cin>>num_st;
                for (int i = 0; i < num_st; ++i)
                {
                    cout<<"student's username: "<<"\n";
                    getline(cin>>ws, user_st);
                    cout<<"password: "<<"\n";
                    getline(cin>>ws, pass_st);
                    students<<"student's username: "<<user_st<<endl<<"password: "<<pass_st<<endl;
                }
                students<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                students.close();
            }
            else
            {
                cout<<"there is a problem. please try again a few minutes later.\n";
            }
        }
        else
        {
            cout<<"there is a problem. please try again a few minutes later.\n";
        }
    }
    void add_to_list()
    {
        cout<<"which list do you want to add your new student(s) to?\n";
        getline(cin>>ws, list_name);
        fstream students;
        students.open("student_user_pass.txt", fstream::in|fstream::out);
        if(!students.is_open())
        {
            cout<<"there is a problem. please try again a few minutes later.\n";
        }
        else
        {
            while(getline(students, line))
            {
                saver_file<<line<<endl;
            }
            students.close();
            searched_line = "list's name: " + list_name;
            searched_line.append("\n");
            size_t location = saver_file.str().find(searched_line);
            if(location == string::npos)
            {
                cout<<"can't find your list.\n";
            }
            else
            {
                string keeper = saver_file.str().substr(0, location);
                cout<<"how many students do you want to add?\n";
                cin>>num_st;
                keeper.append("list's name: "+ list_name +"\n");
                for (int i = 0; i < num_st; ++i)
                {
                    cout<<"student's username: "<<"\n";
                    getline(cin>>ws, user_st);
                    cout<<"password: "<<"\n";
                    getline(cin>>ws, pass_st);
                    keeper.append("student's username: " + user_st + '\n');
                    keeper.append("password: " + pass_st + '\n');
                }
                keeper.append(saver_file.str().substr(location + searched_line.length()));
                students.open("student_user_pass.txt", fstream::out);
                if(!students.is_open())
                {
                    cout<<"there is a problem. please try again a few minutes later.\n";
                }
                else
                {
                    students<<keeper;
                    cout<<"new students added successfully.\n";
                    students.close();
                }
            }
        }
    }
};
class professor
{
private:
    int professor_management, num_list;
    string show;
    bool find = false;
public:
    void professor_panel(string given_professor_user)
    {
        do
        {
            cout<<"======================================================================="<<endl;
            cout<<"panel:\nenter 1 to see your designed exams.\nenter 2 to make a new exam.\nenter 3 to manage your list.\nenter 4 to exit: \n";
            cin>>professor_management;
            cout<<"======================================================================="<<endl;
            switch(professor_management)
            {
                case 1:
                {
                    string professor_user;
                    fstream exams;
                    exams.open("exams.txt", fstream::out|ios::app|fstream::in);
                    if(!exams.is_open())
                    {
                        cout<<"there is a problem. please try again a few minutes later.";
                    }
                    while(!exams.eof())
                    {
                        getline(exams, professor_user);
                        if(professor_user == ("professor's name: " + given_professor_user))
                        {
                            find = true;
                            do
                            {
                                getline(exams, show);
                                if(show != ("type of question: d") && show != ("type of question: t"))
                                    cout<<show<<endl;
                            }while(show != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                        }
                    }
                    if(!find)
                    {
                        cout<<"you don't have any designed exam.\n";
                    }
                    exams.close();
                    break;
                }
                case 2:
                {
                    exam ob;
                    ob.make_test(given_professor_user);
                    break;
                }
                case 3:
                {
                    cout<<"enter 1 if you want to see your lists.\nenter 2 if you want to add a new list.\nenter 3 if you want to add new students.\n";
                    cin>>num_list;
                    cout<<"======================================================================="<<endl;
                    if(num_list == 1)
                    {
                        bool find_list = false;
                        string professor_user, user_st, pass_st, list_name;
                        fstream students;
                        students.open("student_user_pass.txt", fstream::out|ios::app|fstream::in);
                        if(!students.is_open())
                        {
                            cout<<"there is a problem. please try again a few minutes later.";
                        }
                        else
                        {
                            while(!students.eof())
                            {
                                getline(students, professor_user);
                                if(professor_user == ("professor's name: " + given_professor_user))
                                {
                                    find_list = true;
                                    getline(students,list_name);
                                    cout<<list_name<<endl;
                                    do
                                    {
                                        getline(students, user_st);
                                        if((user_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") && (pass_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"))
                                        {
                                            getline(students, pass_st);
                                            cout<<user_st<<endl<<pass_st<<endl;
                                        }
                                    }while((user_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") && (pass_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
                                }
                            }
                            students.close();
                            if(!find_list)
                            {
                                cout<<"you don't have any list.\n";
                            }
                        }
                    }
                    else if(num_list == 2)
                    {
                        List ob;
                        ob.make_list(given_professor_user);
                    }
                    else if(num_list == 3)
                    {
                        List ob;
                        ob.add_to_list();
                    }
                    break;
                }
                case 4:
                {
                    cout<<"have a great day :)"<<endl;
                    break;
                }
            }
        }while(professor_management != 4);
    }
};
#endif
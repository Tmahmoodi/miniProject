#ifndef MINI_PROJECT_PROFESSOR_H
#define MINI_PROJECT_PROFESSOR_H
#include<string>
#include<fstream>
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
    void designed_exams(const string &given_professor_user);
    void make_test(const string &given_professor_user);
};
void exam::designed_exams(const string &given_professor_user)
{
    string professor_user, line;
    bool find = false;
    fstream exams;
    exams.open("exams.txt", fstream::out|ios::app|fstream::in);
    if(!exams.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
    }
    while(!exams.eof())
    {
        getline(exams, professor_user);
        if(professor_user == ("professor's name: " + given_professor_user))
        {
            find = true;
            do
            {
                getline(exams, line);
                if(line != ("type of question: d") && line != ("type of question: t"))
                    cout<<line<<endl;
            }while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }
        else if(professor_user.empty())
        {
            break;
        }
        else
        {
            while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
            {
                getline(exams, line);
            }
        }
    }
    if(!find)
    {
        cout<<"you don't have any designed exam.\n";
    }
    exams.close();
}
void exam::make_test(const string &given_professor_user)
{
    bool check = true;
    string line;
    fstream name_exam;
    name_exam.open("exam's name.txt", fstream::in|fstream::out|ios::app);
    if(!name_exam.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
    }
    else
    {
        do
        {
            cout<<"what is your exam name?\n(your exam name is better to have complete info like your lesson's name, your school or university's name and the year.)\n";
            getline(cin>>ws, name_of_exam);
            while(!name_exam.eof())
            {
                getline(name_exam,line);
                if(line == "exam's name: " + name_of_exam)
                {
                    check = false;
                    cout<<"the name of your exam was chosen. please try another one.\n";
                    break;
                }
            }
            name_exam.clear();
            name_exam.seekp(ios::beg);
        }while(!check);
        name_exam.seekp(ios::end);
        name_exam<<"exam's name: "<<name_of_exam<<endl;
        name_exam.close();
        fstream exams("exams.txt", fstream::out|ios::app);
        if(exams)
        {
            exams<<"professor's name: "<<given_professor_user<<endl;
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
                exams<<"grade this question: "<<endl<<grade_question<<endl;
                exams<<"---------------------------------------------------------------------"<<endl;
                cout<<"time of your question (based on minutes):\n";
                cin>>time_question;
                time_exam += time_question;
            }
            exams<<"time of exam: "<<endl<<time_exam<<endl;
            exams<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            exams.close();
        }
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.";
            return;
        }
    }
}
class List
{
private:
    string list_name, user_st, pass_st, compare,professor_user, saved_list_name, line, searched_line;
    int num_st;
    stringstream saver_file;
public:
    void show(const string &given_professor_user);
    void make_list(const string &given_professor_user);
    void add_to_list(const string &given_professor_user);
};
void List::show(const string &given_professor_user)
{
    bool find_list = false;
    fstream students;
    students.open("student_user_pass.txt", fstream::out|ios::app|fstream::in);
    if(!students.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
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
                    else
                    {
                        cout<<user_st<<endl;
                    }
                }while((user_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~") && (pass_st != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
            }
            else if(professor_user.empty())
            {
                break;
            }
            else
            {
                while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    getline(students, line);
            }
        }
        students.close();
        if(!find_list)
        {
            cout<<"you don't have any list.\n";
        }
        cout<<"======================================================================="<<endl;
    }
}
void List::make_list(const string &given_professor_user)
{
    fstream students;
    students.open("student_user_pass.txt", fstream::out|ios::app|fstream::in);
    if(students.is_open())
    {
        cout<<"what is your list name?\n";
        getline(cin>>ws, list_name);
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
        cout<<"======================================================================="<<endl;
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
void List::add_to_list(const string &given_professor_user)
{
    cout << "which list do you want to add your new student(s) to?\n";
    getline(cin >> ws, list_name);
    ifstream students;
    students.open("student_user_pass.txt", ios::in);
    if (!students.is_open())
    {
        cerr << "there is a problem. please try again a few minutes later.\n";
        return;
    }
    else
    {
        while (getline(students, line))
        {
            saver_file << line << endl;
        }
    }
    students.close();
    ofstream change;
    change.open("student_user_pass.txt", ios::out);
    if(change.is_open())
    {
        while(!saver_file.eof())
        {
            getline(saver_file, line);
            if(line == "professor's name: " + given_professor_user)
            {
                getline(saver_file, line);
                if(line == "list's name: " + list_name)
                {
                    while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(saver_file, line);
                    }
                    saver_file.seekg(-(long long)(line.length() + 1), ios::cur);
                    change<<saver_file.str().substr(0, saver_file.tellg());
                    cout << "how many students do you want to add?\n";
                    cin >> num_st;
                    stringstream add;
                    for (int i = 0; i < num_st; ++i)
                    {
                        cout << "student's username: \n";
                        getline(cin >> ws, user_st);
                        cout << "password: \n";
                        getline(cin >> ws, pass_st);
                        add<<"student's username: "<<user_st<<endl;
                        add<<"password: "<<pass_st<<endl;
                    }
                    change<<add.str();
                    change<<saver_file.str().substr(saver_file.tellg());
                    cout << "new student(s) added successfully.\n";
                    cout<<"======================================================================="<<endl;
                    change.close();
                    break;
                }
                else if(line.empty())
                {
                    break;
                }
                else
                {
                    while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(saver_file, line);
                    }
                }
            }
            else if(line.empty())
            {
                break;
            }
            else
            {
                while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(saver_file, line);
                }
            }
        }
    }
    else
    {
        cerr << "there is a problem. please try again a few minutes later.\n";
        return;
    }
}
class professor
{
private:
    int professor_management, num_list;
protected:
    void share_exam(const string &given_professor_user);
    void check_exams(const string &given_professor_user);
    void ranking();
    void limitation(const string &given_professor_user);
public:
    void professor_panel(const string &given_professor_user);
};
void professor::professor_panel(const string &given_professor_user)
{
    do
    {
        cout<<"======================================================================="<<endl;
        cout<<"panel:\nenter 1 to see your designed exams.\nenter 2 to make a new exam.\n"
              "enter 3 to manage your list.\nenter 4 to share a specific exam with a list of your students.\n"
              "enter 5 to check the answered exams of your students.\n"
              "enter 6 to see your students' performances in an exam.\n"
              "enter 7 to close the site for doing a specific exam for your students or closing an exam on history.\nenter 8 to exit:\n";
        cin>>professor_management;
        cout<<"======================================================================="<<endl;
        switch(professor_management)
        {
            case 1:
            {
                exam ob;
                ob.designed_exams(given_professor_user);
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
                do
                {
                    cout<<"enter 1 if you want to see your lists.\nenter 2 if you want to add a new list.\n"
                          "enter 3 if you want to add new student(s).\nenter 4 to exit from list's management.\n";
                    cin>>num_list;
                    cout<<"======================================================================="<<endl;
                    if(num_list == 1)
                    {
                        List ob;
                        ob.show(given_professor_user);
                    }
                    else if(num_list == 2)
                    {
                        List ob;
                        ob.make_list(given_professor_user);
                    }
                    else if(num_list == 3)
                    {
                        List ob;
                        ob.add_to_list(given_professor_user);
                    }
                }while(num_list != 4);
                break;
            }
            case 4:
            {
                share_exam(given_professor_user);
                break;
            }
            case 5:
            {
                check_exams(given_professor_user);
                break;
            }
            case 6:
            {
                ranking();
                break;
            }
            case 7:
            {
                limitation(given_professor_user);
                break;
            }
            case 8:
            {
                cout<<"have a great day :)"<<endl;
                break;
            }
        }
    }while(professor_management != 8);
}
void professor::share_exam(const string &given_professor_user)
{
    string name_of_exam, name_of_list, line1, line2;
    stringstream saver_exam, saver_list;
    bool find_exam = false, find_list = false, check = false;
    cout<<"please enter the exam name witch you want to share:\n";
    getline(cin>>ws, name_of_exam);
    cout<<"please enter the name of your list witch you want to share the exam with:\n";
    getline(cin>>ws, name_of_list);
    fstream students;
    students.open("student_user_pass.txt", fstream::in);
    if(students.is_open())
    {
        while(!students.eof())
        {
            getline(students, line1);
            if(!line1.empty())
            {
                getline(students, line2);
                if((line1 == ("professor's name: " + given_professor_user)) && (line2 == ("list's name: " + name_of_list)))
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(students, line1);
                        getline(students, line2);
                        if(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                            saver_list<<line1<<endl;
                    }
                    find_list = true;
                    break;
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(students, line1);
                    }
                }
            }
            else
                break;
        }
        if(!find_list)
        {
            cout<<"sorry, we can't find your chosen list.\n";
        }
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    students.close();
    fstream exams;
    exams.open("exams.txt", fstream::in|fstream::out|ios::app);
    if(exams.is_open())
    {
        if(find_list)
        {
            while(!exams.eof())
            {
                getline(exams, line1);
                if(!line1.empty())
                {
                    getline(exams, line2);
                    if(line1 == ("professor's name: " + given_professor_user) && line2 == ("exam's name: " + name_of_exam))
                    {
                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        {
                            getline(exams, line1);
                            if(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                saver_exam<<line1<<endl;
                            else
                                saver_exam<<line1;
                        }
                        find_exam = true;
                        break;
                    }
                    else
                    {
                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        {
                            getline(exams, line1);
                        }
                    }
                }
                else
                    break;
            }
        }
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    exams.close();
    if(find_exam)
    {
        fstream shared_exam("shared_exams.txt", fstream::out|ios::app|fstream::in);
        if(shared_exam)
        {
            while(!saver_list.eof())
            {
                check = false;
                shared_exam.seekg(0, ios::beg);
                getline(saver_list, line1);
                if(!line1.empty())
                {
                    while(getline(shared_exam, line2))
                    {
                        if(line2 == "professor's name: " + given_professor_user)
                        {
                            getline(shared_exam, line2);
                            getline(shared_exam, line2);
                            if(line2 == line1)
                            {
                                getline(shared_exam, line2);
                                getline(shared_exam, line2);
                                if(line2 == "exam's name: " + name_of_exam)
                                {
                                    check = true;
                                    break;
                                }
                            }
                        }
                        else if(line2.empty())
                        {
                            break;
                        }
                        else
                        {
                            while(line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                            {
                                getline(shared_exam, line2);
                            }
                        }
                    }
                    if(!check)
                    {
                        shared_exam.clear();
                        shared_exam.seekg(ios::end);
                        shared_exam<<"professor's name: "<<given_professor_user<<"\ncheck: no"<<endl<<line1<<endl<<"show exam is: open\n"<<"exam's name: "<<name_of_exam<<endl<<"situation: not answered.\n";
                        while(!saver_exam.eof())
                        {
                            getline(saver_exam, line1);
                            shared_exam<<line1<<endl;
                        }
                        saver_exam.clear();
                        saver_exam.seekg(0, std::ios::beg);
                    }
                }
                else
                    break;
            }
            cout<<"shared successfully completed.\n";
        }
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.\n";
            return;
        }
    }
    else if(find_list && !find_exam)
    {
        cout<<"sorry we can't find your chosen exam.\n";
    }
}
void professor::check_exams(const string &given_professor_user)
{
    string name_list, line1, line2, reaction, exam_name, line3, add = "check: yes";
    float grade_exam, grade_st, grade;
    bool find_list = false, checked = false, check = true;
    stringstream saver_users, saver_exams;
    cout<<"please enter the name of your student's list:\n";
    getline(cin>>ws, name_list);
    ifstream students;
    students.open("student_user_pass.txt", ios::in);
    if(students.is_open())
    {
        while (getline(students, line1))
        {
            if(line1 == "professor's name: " + given_professor_user)
            {
                getline(students, line1);
                if(line1 == "list's name: " + name_list)
                {
                    while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(students, line1);
                        if(line1.at(0) == 's')
                            saver_users<<line1<<endl;
                    }
                    find_list = true;
                    break;
                }
            }
            else if(line1.empty())
            {
                break;
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    getline(students, line1);
            }
        }
        students.close();
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    if(find_list)
    {
        ifstream checking("shared_exams.txt", ios::in);
        ofstream checked_exams("checked_exams.txt", ios::out|ios::app);
        ofstream grades("grades.txt", ios::out|ios::app);
        if(checking.is_open(), checked_exams.is_open(), grades.is_open())
        {
            while(getline(checking, line1))
            {
                saver_exams<<line1<<endl;
            }
            checking.close();
            while (!saver_users.eof())
            {
                getline(saver_users, line2);
                if(check)
                {
                    saver_exams.clear();
                    saver_exams.seekg(0, ios::beg);
                    stringstream saver_checked_exam, keeper;
                    while (!saver_exams.eof())
                    {
                        getline(saver_exams, line1);
                        if(line1.empty())
                        {
                            break;
                        }
                        else
                        {
                            if(line1 == "professor's name: " + given_professor_user)
                            {
                                getline(saver_exams, line3);
                                if(line3 == "check: no")
                                {
                                    getline(saver_exams, line1);
                                    if(line1 == line2)
                                    {
                                        checked = true;
                                        saver_exams.seekg(-(long)(line1.length() + line3.length() + 2), ios::cur);
                                        keeper<<saver_exams.str().substr(0, saver_exams.tellg())<<add<<endl;
                                        getline(saver_exams, line1);
                                        keeper<<saver_exams.str().substr(saver_exams.tellg());
                                        grade_st = grade_exam = 0;
                                        saver_checked_exam<<"professor's name: "<<given_professor_user<<endl;
                                        for (int i = 0; i < 3; ++i)
                                        {
                                            getline(saver_exams, line1);
                                            saver_checked_exam<<line1<<endl;
                                            cout<<line1<<endl;
                                        }
                                        exam_name = line1;
                                        while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                        {
                                            getline(saver_exams, line1);
                                            if(line1 == "type of question: d")
                                            {
                                                for (int i = 0; i < 2; ++i)
                                                {
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                }
                                                if(line1 == "answer: ")
                                                {
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    cout<<"reaction: \n";
                                                    getline(cin>>ws, reaction);
                                                    saver_checked_exam<<"reaction: "<<reaction<<endl;
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    grade_exam += stof(line1);
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    cin>>grade;
                                                    grade_st += grade;
                                                    saver_checked_exam<<grade<<endl;
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                }
                                                else
                                                {
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    grade_exam += stof(line1);
                                                    saver_checked_exam<<"grade of the student: "<<endl<<0<<endl;
                                                    cout<<"grade of the student: "<<endl<<0<<endl;
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                }
                                            }
                                            else if(line1 == "type of question: t")
                                            {
                                                for (int i = 0; i < 6; ++i)
                                                {
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                }
                                                if(line1.at(0) == 's')
                                                {
                                                    char st_answer = line1.at(18);
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                    char right_answer = line1.at(16);
                                                    cout<<"reaction: \n";
                                                    getline(cin>>ws, reaction);
                                                    saver_checked_exam<<"reaction: "<<reaction<<endl;
                                                    if(right_answer == st_answer)
                                                    {
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                        grade = stof(line1);
                                                        grade_exam += grade;
                                                        grade_st += grade;
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl<<grade<<endl;
                                                        saver_checked_exam<<grade<<endl;
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                    }
                                                    else
                                                    {
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                        grade = 0;
                                                        grade_exam += stof(line1);
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl<<grade<<endl;
                                                        saver_checked_exam<<grade<<endl;
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                    }
                                                }
                                                else
                                                {
                                                    for (int i = 0; i < 2; ++i)
                                                    {
                                                        getline(saver_exams, line1);
                                                        saver_checked_exam<<line1<<endl;
                                                        cout<<line1<<endl;
                                                    }
                                                    grade_exam += stof(line1);
                                                    saver_checked_exam<<"grade of the student: "<<endl<<0<<endl;
                                                    cout<<"grade of the student: "<<endl<<0<<endl;
                                                    getline(saver_exams, line1);
                                                    saver_checked_exam<<line1<<endl;
                                                    cout<<line1<<endl;
                                                }
                                            }
                                        }
                                        ofstream save("shared_exams.txt", ios::out);
                                        if(save)
                                        {
                                            save<<keeper.str().substr(0);
                                            saver_exams.str("");
                                            saver_exams<<keeper.str().substr(0);
                                            saver_checked_exam<<"grade: "<<grade_st<<"/"<<grade_exam<<endl;
                                            checked_exams<<saver_checked_exam.str().substr(0)<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                                            grades<<exam_name<<endl<<line2<<endl<<"grade: "<<grade_st<<"/"<<grade_exam<<endl;
                                            cout<<"do you want to check another exam?\n1)yes 2)no\n";
                                            cin>>reaction;
                                            if(reaction == "2")
                                                check = false;
                                            save.close();
                                            break;
                                        }
                                        else
                                        {
                                            cerr<<"there is a problem, please try again later.\n";
                                            return;
                                        }
                                    }
                                    else if(line1.empty())
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                        {
                                            getline(saver_exams, line1);
                                        }
                                    }
                                }
                                else if(line3.empty())
                                {
                                    break;
                                }
                                else
                                {
                                    while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                    {
                                        getline(saver_exams, line1);
                                    }
                                }
                            }
                            else if(line1.empty())
                            {
                                break;
                            }
                            else
                            {
                                while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                {
                                    getline(saver_exams, line1);
                                }
                            }
                        }
                    }
                }
                else
                {
                    checked_exams.close();
                    grades.close();
                    break;
                }
            }
        }
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.\n";
            return;
        }
    }
    else
    {
        cout<<"sorry we can't find your chosen list.\n";
    }
    if(!checked)
    {
        cout<<"you don't have any unchecked exam.\n";
    }
}
void professor::ranking()
{
    string exam_name, line1;
    stringstream saver_names, saver_grades;
    string *names;
    float *grades, exam_grade;
    int counter = 0;
    ifstream sort;
    sort.open("grades.txt", ios::in);
    if(sort.is_open())
    {
        cout<<"In which exam do you want to see the ranking of students?\n";
        getline(cin>>ws, exam_name);
        while(getline(sort, line1))
        {
            if(line1 == "exam's name: " + exam_name)
            {
                ++counter;
                getline(sort, line1);
                saver_names<<line1<<endl;
                getline(sort, line1);
                saver_grades<<line1<<endl;
            }
        }
        if(saver_names.rdbuf()->in_avail() != 0)
        {
            names = new string [counter];
            grades = new float [counter];
            for (int i = 0; i < counter; ++i)
            {
                getline(saver_names, line1);
                names[i] = line1;
                getline(saver_grades, line1);
                grades[i] = stof(line1.substr(7));
            }
            size_t location = line1.find('/');
            exam_grade = stof(line1.substr(location + 1));
            for (int i = 1; i < counter; ++i)
            {
                for (int j = 0; j < i; ++j)
                {
                    if(grades[j] > grades[i])
                    {
                        float temp1 = grades[j];
                        grades[j] = grades[i];
                        grades[i] = temp1;
                        string temp2 = names[j];
                        names[j] = names[i];
                        names[i] = temp2;
                    }
                }
            }
            cout<<"ranking of students for "<<exam_name<<" exam with the total score of "<<exam_grade<<":\n";
            for (int i = 0; i < counter; ++i)
            {
                cout<<names[i]<<endl<<"grade: "<<grades[i]<<endl;
            }
            delete [] names;
            delete [] grades;
            names = nullptr;
            grades = nullptr;
        }
        else
        {
            cout<<"we can't find any students witch done your chosen exam.\n";
        }
        sort.close();
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
void professor::limitation(const string &given_professor_user)
{
    stringstream saver_list, change, keeper;
    bool find = false, make_change = false, do_once = false;
    int option;
    string exam_name, list_name, line1, line2, add = "show exam is: close";
    cout<<"enter 1 to close the site for doing an exam for a list of your student.\n"
          "enter 2 to give the permission of seeing an exam on the panel of a list of your students.\n"
          "enter 3 to close on both.\n";
    cin>>option;
    cout<<"please enter the exam's name:\n";
    getline(cin>>ws, exam_name);
    cout<<"please enter the list's name:\n";
    getline(cin>>ws, list_name);
    ifstream list;
    list.open("student_user_pass.txt", fstream::in);
    if(list.is_open())
    {
        while(getline(list, line1))
        {
            if(line1 == "professor's name: " + given_professor_user)
            {
                getline(list, line1);
                if(line1 == "list's name: " + list_name)
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(list, line1);
                        if(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        {
                            saver_list<<line1<<endl;
                            getline(list, line1);
                        }
                    }
                    find = true;
                    break;
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        getline(list, line1);
                }
            }
            else if(line1.empty())
            {
                break;
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    getline(list, line1);
            }
        }
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    if(find)
    {
        if((option == 1) || (option == 3))
        {
            fstream time_out("shared_exams.txt", fstream::in|fstream::out);
            if (time_out)
            {
                while (getline(time_out, line2))
                {
                    change << line2 << endl;
                }
                time_out.clear();
                time_out.seekp(0, ios::beg);
                while (!saver_list.eof())
                {
                    make_change = false;
                    getline(saver_list, line1);
                    if (!line1.empty())
                    {
                        while (!change.eof())
                        {
                            getline(change, line2);
                            if (line2 == "professor's name: " + given_professor_user)
                            {
                                getline(change, line2);
                                getline(change, line2);
                                if (line2 == line1)
                                {
                                    getline(change, line1);
                                    getline(change, line2);
                                    if (line2 == "exam's name: " + exam_name)
                                    {
                                        change.seekg(-(long) (line1.length() + line2.length() + 2), ios::cur);
                                        keeper << change.str().substr(0, change.tellg()) << add << endl;
                                        getline(change, line2);
                                        keeper << change.str().substr(change.tellg());
                                        make_change = true;
                                        break;
                                    }
                                    else if (line2.empty())
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        while (line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                            getline(change, line2);
                                    }
                                }
                                else if (line2.empty())
                                {
                                    break;
                                }
                                else
                                {
                                    while (line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                        getline(change, line2);
                                }
                            }
                            else if (line2.empty())
                            {
                                break;
                            }
                            else
                            {
                                while (line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                    getline(change, line2);
                            }
                        }
                        if(make_change)
                        {
                            do_once = true;
                            time_out.seekp(0, ios::beg);
                            time_out.write(keeper.str().c_str(), (long)keeper.str().length());
                            change.str("");
                            change << keeper.str();
                        }
                        keeper.str("");
                    }
                    else
                        break;
                }
            }
            else
            {
                cerr << "there is a problem. please try again a few minutes later.\n";
                return;
            }
        }
        saver_list.clear();
        saver_list.seekg(0, ios::beg);
        change.str("");
        if((option == 2) || (option == 3))
        {
            fstream limit("checked_exams.txt", fstream::in|fstream::out);
            if(limit)
            {
                while(getline(limit, line2))
                {
                    change<<line2<<endl;
                }
                limit.clear();
                limit.seekg(0, ios::beg);
                while(!saver_list.eof())
                {
                    make_change = false;
                    getline(saver_list, line1);
                    if(!line1.empty())
                    {
                        while(!change.eof())
                        {
                            getline(change, line2);
                            if(line2 == "professor's name: " + given_professor_user)
                            {
                                getline(change, line2);
                                if(line2 == line1)
                                {
                                    getline(change, line1);
                                    getline(change, line2);
                                    if(line2 == "exam's name: " + exam_name)
                                    {
                                        change.seekg(-(long)(line1.length() + line2.length() + 2), ios::cur);
                                        keeper<<change.str().substr(0, change.tellg())<<add<<endl;
                                        getline(change, line2);
                                        keeper<<change.str().substr(change.tellg());
                                        make_change = true;
                                        break;
                                    }
                                    else if(line2.empty())
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        while(line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                            getline(change, line2);
                                    }
                                }
                                else if(line2.empty())
                                {
                                    break;
                                }
                                else
                                {
                                    while(line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                        getline(change, line2);
                                }
                            }
                            else if(line2.empty())
                            {
                                break;
                            }
                            else
                            {
                                while(line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                    getline(change, line2);
                            }
                        }
                        if(make_change)
                        {
                            do_once = true;
                            limit.seekp(0, ios::beg);
                            limit.write(keeper.str().c_str(), (long)keeper.str().length());
                            change.str("");
                            change<<keeper.str();
                        }
                        keeper.str("");
                    }
                    else
                        break;
                }
            }
            else
            {
                cerr<<"there is a problem. please try again a few minutes later.\n";
                return;
            }
        }
        if(do_once)
            cout<<"closing successfully done.\n";
    }
    else
        cout<<"sorry, we can't find your chosen list.\n";
}
#endif
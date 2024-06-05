#ifndef MINI_PROJECT_PROFESSOR_H
#define MINI_PROJECT_PROFESSOR_H
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
//creat an exam class to keep data members related to exams in private part and functions in protected part
class exam
{
private:
    int num_questions;
    string type_question, question, name_of_exam, option;
    double time_question, time_exam;
    float grade_question;
protected:
    void designed_exams(const string &given_professor_user);
    void make_test(const string &given_professor_user);
};
//a function to search in designed exams and show user designed exams by user if available
void exam::designed_exams(const string &given_professor_user)
{
    string professor_user, line;
    bool find = false;
    //open the designed exams file in read mode to find designed exams by professor
    //and in write mode because if there isn't any designed exam, it can cause of an error in opening the file
    fstream exams;
    exams.open("exams.txt", fstream::out|ios::app|fstream::in);
    //exception handling to be sure that the file is open
    if(!exams.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
    }
    //read the designed exam file from the beginning till the end to find the designed exams by the professor
    while(!exams.eof())
    {
        getline(exams, professor_user);
        if(professor_user == ("professor's name: " + given_professor_user))
        {
            //if an exam find witch was designed by the professor, boolean will be true
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
    //show a message to the professor if searching the file is over and can't find any designing exam by the professor
    if(!find)
    {
        cout<<"you don't have any designed exam.\n";
    }
    exams.close();
}
//a function for designing exams
void exam::make_test(const string &given_professor_user)
{
    time_exam = 0;
    bool check = true;
    string line;
    //open file in read mode to be sure that the exam's name is not duplicated and save the new exam's name in file
    fstream name_exam;
    name_exam.open("exam's name.txt", fstream::in|fstream::out|ios::app);
    //exception handling to be sure that the file is open
    if(!name_exam.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
    }
    else
    {
        //give the exam name and read the exam's name file from the beginning till the end to make sure that the
        //exam;s name is unique
        do
        {
            check = true;
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
            //if the name was duplicated, get the position back to the beginning of the file and compare the new name
            //with names from the beginning
            name_exam.clear();
            name_exam.seekp(ios::beg);
        }while(!check);
        name_exam.seekp(ios::end);
        name_exam<<"exam's name: "<<name_of_exam<<endl;
        //closing the file witch saved the exam's names
        name_exam.close();
        //open the file witch saved the designed exams on it on write mode
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
            //exception handling to be sure that the file is open
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.";
            return;
        }
    }
}
//creat a list class to keep data members related to lists in private part and functions in protected part
class List
{
private:
    string list_name, user_st, pass_st, compare,professor_user, saved_list_name, line, searched_line;
    int num_st;
public:
    void show(const string &given_professor_user);
    void make_list(const string &given_professor_user);
    void add_to_list(const string &given_professor_user);
};
//a function for showing created list by professor
void List::show(const string &given_professor_user)
{
    bool find_list = false;
    fstream students;
    //open a file in read mode to find lists witch created by professor
    //and in write mode to avoid receiving an error about opening the file
    students.open("student_user_pass.txt", fstream::out|ios::app|fstream::in);
    //exception handling to be sure that the file is open
    if(!students.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.";
        return;
    }
    else
    {
        //read the file from the beginning till the end to find designed list by professor
        while(!students.eof())
        {
            getline(students, professor_user);
            if(professor_user == ("professor's name: " + given_professor_user))
            {
                //if there was any list in file witch created by professor, the boolean will be true
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
        //show a message to the professor if searching in the file overed and there isn't any list witch created by professor
        if(!find_list)
        {
            cout<<"you don't have any list.\n";
        }
        cout<<"======================================================================="<<endl;
    }
}
//a function to creat new lists
void List::make_list(const string &given_professor_user)
{
    bool find_name;
    //open the file in write mode to add new list to our file
    //and in read mode to avoid making duplicated usernames
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
            //put the position of reading from file to read from the beginning if the username was duplicated
            students.clear();
            students.seekg(0, ios::beg);
            //make a do_while loop to avoid making duplicated usernames for students
            do
            {
                find_name = false;
                cout<<"student's username: "<<"\n";
                getline(cin>>ws, user_st);
                cout<<"password: "<<"\n";
                getline(cin>>ws, pass_st);
                while(!students.eof())
                {
                    getline(students, line);
                    if(!line.empty())
                    {
                        if(line == "student's username: " + user_st)
                        {
                            getline(students, line);
                            if(line != "password: " + pass_st)
                            {
                                cout<<"the username of your student was chosen. please choose another one.\n";
                                find_name = true;
                                break;
                            }
                        }
                    }
                    else
                        break;
                }
            }while(find_name);
            //get back the position of writing in file to write in the end of file
            students.clear();
            students.seekp(ios::end);
            students<<"student's username: "<<user_st<<endl<<"password: "<<pass_st<<endl;
        }
        //get back the position of writing in file to write in the end of file
        students.clear();
        students.seekp(ios::end);
        students<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        students.close();
        cout<<"======================================================================="<<endl;
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
//a function to add new students to a designed list
void List::add_to_list(const string &given_professor_user)
{
    stringstream saver_file;
    bool find_list = false, find_name;
    cout << "which list do you want to add your new student(s) to?\n";
    getline(cin >> ws, list_name);
    //open the file in read mode to read line by line from it
    ifstream students;
    students.open("student_user_pass.txt", ios::in);
    //exception handling to be sure that the file is open
    if (!students.is_open())
    {
        cerr << "there is a problem. please try again a few minutes later.\n";
        return;
    }
    else
    {
        //read line by line from our file and save them in a stringstream
        while (getline(students, line))
        {
            saver_file << line << endl;
            if(line == "list's name: " + list_name)
                find_list = true;
        }
    }
    //close the file in read mode
    students.close();
    //if list's name found while we were reading files, the boolean will be true and user can add new students to file
    if(find_list)
    {
        //declare a stringstream to keep changes content in it
        stringstream add;
        //open the file in write mode to add new students to our file
        fstream change;
        change.open("student_user_pass.txt", fstream::out|fstream::in);
        if(change.is_open())
        {
            //read from the beginning till the end of the file to find the list's name
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
                        //go back a line to add new students before the separator
                        saver_file.seekg(-(long long)(line.length() + 1), ios::cur);
                        add<<saver_file.str().substr(0, saver_file.tellg());
                        cout << "how many students do you want to add?\n";
                        cin >> num_st;
                        for (int i = 0; i < num_st; ++i)
                        {
                            //get back the position of reading from file to read from the beginning if the username was duplicated
                            change.clear();
                            change.seekg(0, ios::beg);
                            //make a do_while loop to avoid making duplicated usernames for students
                            do
                            {
                                find_name = false;
                                cout << "student's username: \n";
                                getline(cin >> ws, user_st);
                                cout << "password: \n";
                                getline(cin >> ws, pass_st);
                                while(!change.eof())
                                {
                                    getline(change, line);
                                    if(line == "student's username: " + user_st)
                                    {
                                        getline(change, line);
                                        if(line != "password: " + pass_st)
                                        {
                                            cout<<"the username of your student was chosen. please choose another one.\n";
                                            find_name = true;
                                            break;
                                        }
                                    }
                                }
                            }while(find_name);
                            add<<"student's username: "<<user_st<<endl;
                            add<<"password: "<<pass_st<<endl;
                        }
                        add<<saver_file.str().substr(saver_file.tellg());
                        //get back the position of writing in file to write in the end of the file
                        change.clear();
                        change.seekp(0, ios::beg);
                        change<<add.str();
                        cout << "new student(s) added successfully.\n";
                        cout<<"======================================================================="<<endl;
                        change.close();
                        break;
                    }
                    else if(line.empty())
                    {
                        break;
                    }
                        //if the line wasn't equal to our chosen line, it will pass all the lines till it get to separation line
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
                    //if the line wasn't equal to our chosen line, it will pass all the lines till it get to separator line
                else
                {
                    while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(saver_file, line);
                    }
                }
            }
        }
            //exception handling to be sure that the file is open
        else
        {
            cerr << "there is a problem. please try again a few minutes later.\n";
            return;
        }
    }
    else
        cout<<"sorry, we can't find your chosen list.\n======================================================================="<<endl;;
}
//create a class for professor to keep data members in private part and function members in protected part
//this class inherits from exam and list class
class professor: public exam, public List
{
private:
    int professor_management, num_list;
    //declare the signature of functions in the class to avoid make them inline
protected:
    void share_exam(const string &given_professor_user);
    void check_exams(const string &given_professor_user);
    void answer_protests();
    void ranking();
    void limitation(const string &given_professor_user);
public:
    void professor_panel(const string &given_professor_user);
};
//creat a function for showing the panel of the professors
void professor::professor_panel(const string &given_professor_user)
{
    //make a do_while loop for showing the panel until the user wants to log out
    do
    {
        cout<<"======================================================================="<<endl;
        cout<<"panel:\nenter 1 to see your designed exams.\nenter 2 to make a new exam.\n"
              "enter 3 to manage your list.\nenter 4 to share a specific exam with a list of your students.\n"
              "enter 5 to check the answered exams of your students.\nenter 6 to see your student's protest.\n"
              "enter 7 to see your students' performances in an exam.\n"
              "enter 8 to close the site for doing a specific exam for your students or closing an exam on history.\nenter 9 to exit:\n";
        cin>>professor_management;
        cout<<"======================================================================="<<endl;
        switch(professor_management)
        {
            case 1:
            {
                //call a function in exam class to  find designed exam(s) and show them
                designed_exams(given_professor_user);
                break;
            }
            case 2:
            {
                //call a function in exam class to design a new exam and save it on a file
                make_test(given_professor_user);
                break;
            }
            case 3:
            {
                //make a do_while loop to handle related things to the lists
                do
                {
                    cout<<"enter 1 if you want to see your lists.\nenter 2 if you want to add a new list.\n"
                          "enter 3 if you want to add new student(s).\nenter 4 to exit from list's management.\n";
                    cin>>num_list;
                    cout<<"======================================================================="<<endl;
                    if(num_list == 1)
                    {
                        //call a function in list class to show lists witch designed by professor
                        show(given_professor_user);
                    }
                    else if(num_list == 2)
                    {
                        //call a function in list class to make a new list
                        make_list(given_professor_user);
                    }
                    else if(num_list == 3)
                    {
                        //call a function in list class to add new students to a designed list
                        add_to_list(given_professor_user);
                    }
                }while(num_list != 4);
                break;
            }
            case 4:
            {
                //call a function to share a designed exam by professor to a list of professor's students
                share_exam(given_professor_user);
                break;
            }
            case 5:
            {
                //call a function to correct exams
                check_exams(given_professor_user);
                break;
            }
            case 6:
            {
                //call a function to answer the protest of students
                answer_protests();
                break;
            }
            case 7:
            {
                //call a function to rank students in an exam
                ranking();
                break;
            }
            case 8:
            {
                //call a function to limit the access of students for doing an exam or for showing an exam in their panel
                limitation(given_professor_user);
                break;
            }
            case 9:
            {
                cout<<"have a great day :)"<<endl;
                break;
            }
        }
    }while(professor_management != 9);
}
//call a function to share a specific exam with a list of professor's students
void professor::share_exam(const string &given_professor_user)
{
    string name_of_exam, name_of_list, line1, line2;
    stringstream saver_exam, saver_list;
    bool find_exam = false, find_list = false, check = false;
    cout<<"please enter the exam name witch you want to share:\n";
    getline(cin>>ws, name_of_exam);
    cout<<"please enter the name of your list witch you want to share the exam with:\n";
    getline(cin>>ws, name_of_list);
    //open the file in read mode to save student's usernames in a stringstream
    ifstream students;
    students.open("student_user_pass.txt", ios::in);
    if(students.is_open())
    {
        //read the file line by line to find the list's name
        while(!students.eof())
        {
            getline(students, line1);
            if(!line1.empty())
            {
                getline(students, line2);
                //if the professor's user was the same in the file and the list name in the next line was same too,
                //it will save the student's usernames in a stringstream and the related boolean (find_list) will be true
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
            //if the boolean stayed false and can't find list's name in the file, it will show a message to professor
            cout<<"sorry, we can't find your chosen list.\n";
        }
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    students.close();
    //open the file in read mode to save the chosen exam in a stringstream
    ifstream exams;
    exams.open("exams.txt", ios::in);
    if(exams.is_open())
    {
        //check if the list's name was found, do the rest commands
        if(find_list)
        {
            //read from the first till the end of the file to find the exam's name
            while(!exams.eof())
            {
                getline(exams, line1);
                if(!line1.empty())
                {
                    getline(exams, line2);
                    //if the name of the professor was the same in the file and the exam's name was the same
                    //with the exam's name in file, it will save the exam in a stringstream
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
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    exams.close();
    //check if the exam's name was found, do the rest commands
    if(find_exam)
    {
        //open the file in read mode to avoid sharing one exam twice for a student and in write mode
        //to add an exam in the file for students
        fstream shared_exam("shared_exams.txt", fstream::out|ios::app|fstream::in);
        if(shared_exam)
        {
            //read saved student's username in the stringstream line by line from the beginning till the end
            while(!saver_list.eof())
            {
                check = false;
                //put the position of reading from file at the beginning of the file
                shared_exam.seekg(0, ios::beg);
                getline(saver_list, line1);
                if(!line1.empty())
                {
                    //check if the exam is already saved for a student, avoid saving it again for him/her
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
                    //if the boolean (check) is false, it means that the exam wasn't shared for the student and share it
                    if(!check)
                    {
                        //put the position of writing in a file in the end of the file
                        shared_exam.clear();
                        shared_exam.seekg(ios::end);
                        shared_exam<<"professor's name: "<<given_professor_user<<"\ncheck: no"<<endl<<line1<<endl<<"show exam is: open\n"<<"exam's name: "<<name_of_exam<<endl;
                        while(!saver_exam.eof())
                        {
                            getline(saver_exam, line1);
                            shared_exam<<line1<<endl;
                        }
                        //put the position of reading from file at the beginning of the file
                        saver_exam.clear();
                        saver_exam.seekg(0, std::ios::beg);
                    }
                }
                else
                    break;
            }
            cout<<"shared successfully completed.\n";
        }
            //exception handling to be sure that the file is open
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.\n";
            return;
        }
    }
    else if(find_list && !find_exam)
    {
        //show a message to professor if there isn't any exam with given name in the file
        cout<<"sorry we can't find your chosen exam.\n";
    }
}
//a function to correct the exams
void professor::check_exams(const string &given_professor_user)
{
    string name_list, line1, line2, reaction, exam_name, line3, add = "check: yes";
    float grade_exam, grade_st, grade;
    bool find_list = false, checked = false, check = true;
    stringstream saver_users, saver_exams;
    cout<<"please enter the name of your student's list:\n";
    getline(cin>>ws, name_list);
    //open the file in read mode to find the list's name
    ifstream students;
    students.open("student_user_pass.txt", ios::in);
    if(students.is_open())
    {
        //read the file line by line to find the list's name
        while (getline(students, line1))
        {
            //if the professor's username was the same with the file and list's name was the same too,
            //it will save the usernames in a stringstream
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
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    if(find_list)
    {
        //open the shared exams file in read mode to correct the exams
        ifstream done_exams("done_exams.txt", ios::in);
        //open the checked_exams file in write mode to add checked exams in it
        ofstream checked_exams("checked_exams.txt", ios::out|ios::app);
        //open the grades file in write mode to add grades in it
        ofstream grades("grades.txt", ios::out|ios::app);
        if(done_exams.is_open(), checked_exams.is_open(), grades.is_open())
        {
            //save the content of the file in a stringstream
            while(getline(done_exams, line1))
            {
                saver_exams<<line1<<endl;
            }
            done_exams.close();
            //find students' usernames in saver_exams stringstream
            //with the help of reading line by line from saver_users stringstream
            while (!saver_users.eof())
            {
                getline(saver_users, line2);
                //with check boolean we help the professor to decide if the professor wants to check another exam or not
                if(check)
                {
                    //put the position of saver_exams at the beginning to search in file from the beginning for each student to find
                    //her/him exam
                    saver_exams.clear();
                    saver_exams.seekg(0, ios::beg);
                    stringstream saver_checked_exam, keeper;
                    //read the saver_exams from the beginning till the end to find the exam of the student
                    while (!saver_exams.eof())
                    {
                        getline(saver_exams, line1);
                        if(!line1.empty())
                        {
                            //if the professor name was the same with the professor name in the stringstream
                            //and the professor doesn't check the exam previously, it will show the exam for checking it
                            if(line1 == "professor's name: " + given_professor_user)
                            {
                                getline(saver_exams, line3);
                                if(line3 == "check: no")
                                {
                                    getline(saver_exams, line1);
                                    if(line1 == line2)
                                    {
                                        //this boolean will be true if there is any exam for checking
                                        checked = true;
                                        //go back to line and put the position before the line (check: no) to change this line to
                                        //(check: yes)
                                        saver_exams.seekg(-(long)(line1.length() + line3.length() + 2), ios::cur);
                                        //save the content of saver_exams before the line (check: no) in a helper stringstream
                                        //named keeper and add a new line with the new content
                                        keeper<<saver_exams.str().substr(0, saver_exams.tellg())<<add<<endl;
                                        getline(saver_exams, line1);
                                        //save the rest content of saver_exams (after the changed line) in the keeper
                                        keeper<<saver_exams.str().substr(saver_exams.tellg());
                                        grade_st = grade_exam = 0;
                                        //save the checked exams in a stringstream named saver_checked_exam
                                        saver_checked_exam<<"professor's name: "<<given_professor_user<<endl;
                                        for (int i = 0; i < 3; ++i)
                                        {
                                            getline(saver_exams, line1);
                                            saver_checked_exam<<line1<<endl;
                                            cout<<line1<<endl;
                                        }
                                        exam_name = line1;
                                        //make a while loop to check the exam
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
                                        ofstream save("done_exams.txt", ios::out);
                                        if(save)
                                        {
                                            //update the content of shared_exams file
                                            save<<keeper.str().substr(0);
                                            //update the content of saver_exams stringstreame
                                            saver_exams.str("");
                                            saver_exams<<keeper.str().substr(0);
                                            saver_checked_exam<<"grade: "<<grade_st<<"/"<<grade_exam<<endl;
                                            //save the checked exams in the file
                                            checked_exams<<saver_checked_exam.str().substr(0)<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                                            //save the grades in a file
                                            grades<<exam_name<<endl<<line2<<endl<<"grade: "<<grade_st<<"/"<<grade_exam<<endl;
                                            cout<<"do you want to check another exam?\n1)yes 2)no\n";
                                            cin>>reaction;
                                            //based on the reaction, the boolean will be true or false. if the
                                            //boolean be false, no more exam show for checking
                                            if(reaction == "2")
                                                check = false;
                                            save.close();
                                            break;
                                        }
                                            //exception handling to be sure that the file is open
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
            //exception handling to be sure that the file is open
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
    //if the boolean be false, it will tell the professor that there isn't any exam to be checked
    if(!checked)
    {
        cout<<"you don't have any unchecked exam.\n";
    }
}
//a function to answer the protest of students
void professor::answer_protests()
{
    string name_of_exam, line1, line2, protest_answer, student_name, add = "answered: yes";
    bool find_protest = false, change = false;
    int option = 1;
    stringstream exam_pro, saver_answers, keeper;
    cout<<"please enter the exam name witch you want to see student's protests on:\n";
    getline(cin>>ws, name_of_exam);
    //open file in read mode to save its content in a stringsteam and in write mode
    //to add new content and change the old content
    fstream exam_protest("protest.txt",fstream::in|fstream::out);
    if (exam_protest)
    {
        while(getline(exam_protest, line1))
        {
            exam_pro<<line1<<endl;
        }
        exam_protest.clear();
        exam_protest.seekp(0, ios::beg);
        while (!exam_pro.eof())
        {
            change = false;
            getline(exam_pro, line1);
            if(!line1.empty() && option == 1)
            {
                //if the exam's name found in stringstream and the protest wasn't check before,
                //the line (answered: no) will update to (answered: yes) and professor can answer
                //the student's protest
                if(line1 == "exam's name: " + name_of_exam)
                {
                    getline(exam_pro, line2);
                    if(line2 == "answered: no")
                    {
                        //if any changing happened in stringstream, the boolean will be true to update the content of the file
                        change = true;
                        find_protest = true;
                        //go back a line, before the line (answered: no) and save the content
                        //before it in a helper stringstream named keeper
                        exam_pro.seekg(-(long)(line2.length() + 1), ios::cur);
                        //add the line (answered: yes) after the old content saved in exam_pro stringstream in keeper
                        keeper<<exam_pro.str().substr(0, exam_pro.tellg())<<add<<endl;
                        getline(exam_pro, line2);
                        //save the rest content of exam_pro in keeper
                        keeper<<exam_pro.str().substr(exam_pro.tellg());
                        getline(exam_pro, line2);
                        cout<<line2<<endl;
                        getline(exam_pro, line2);
                        student_name = line2;
                        cout<<line2<<endl;
                        getline(exam_pro, line2);
                        cout<<line2<<endl;
                        getline(exam_pro, line2);
                        cout<<line2<<endl;
                        getline(exam_pro, line2);
                        cout<<"please enter answer to "<<student_name<<" protest: \n";
                        getline(cin>>ws, protest_answer);
                        saver_answers<<line1<<endl<<"answer of "<<student_name<<": "<<endl<<"professor's answer: "<<protest_answer<<endl<<line2<<endl;
                    }
                    else
                    {
                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                            getline(exam_pro, line1);
                    }
                    if(change)
                    {
                        //update the content of the file
                        exam_protest.seekp(0, ios::beg);
                        exam_protest.write(keeper.str().c_str(), (long)keeper.str().length());
                        //make the keeper clean
                        keeper.str("");
                        cout<<"do you want to check another protest?\n1)yes 2)no";
                        cin>>option;
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        getline(exam_pro, line1);
                }
            }
            else
                break;
        }
        //if there aren't any unanswered protest in file, this boolean help us to show it by a message to professor
        //and if there was any protest it will help us to open the file and write answers on it
        if(!find_protest)
            cout<<"there isn't any protest for your chosen exam.\n";
        else
        {
            //open the file in write mode to add the answer of the professor to the protest(s)
            ofstream pro_answer("protest_answer.txt" , fstream::out|ios::app);
            if(pro_answer)
            {
                pro_answer<<saver_answers.str();
            }
            else
            {
                cerr<<"there is a problem. please try again a few minutes later.\n";
                return;
            }
        }
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
//call a function to rank students based on an exam
void professor::ranking()
{
    string exam_name, line1;
    stringstream saver_names, saver_grades;
    //declare two pointers for saving grades and names related to an exam after reading the file
    string *names;
    float *grades, exam_grade;
    //declare a counter for counting the numbers of students which participate in an exam
    //and declare the length of pointers
    int counter = 0;
    //open the file in read mode to save the names and grades of an exam in two stringstreams
    ifstream sort;
    sort.open("grades.txt", ios::in);
    if(sort.is_open())
    {
        cout<<"In which exam do you want to see the ranking of students?\n";
        getline(cin>>ws, exam_name);
        //read the file line by line and saved the students' usernames and their passwords in two separate stringstreams
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
        //check if the stringstream is not empty, do the rest commands
        if(saver_names.rdbuf()->in_avail() != 0)
        {
            //use new for making array of length counter
            names = new string [counter];
            grades = new float [counter];
            //save the names and grades in related arrays
            for (int i = 0; i < counter; ++i)
            {
                getline(saver_names, line1);
                names[i] = line1;
                getline(saver_grades, line1);
                grades[i] = stof(line1.substr(7));
            }
            size_t location = line1.find('/');
            exam_grade = stof(line1.substr(location + 1));
            //use selection sort to sort the students which participate in the chosen exam in ascending order
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
            //print the arrays
            cout<<"ranking of students for "<<exam_name<<" exam with the total score of "<<exam_grade<<":\n";
            for (int i = 0; i < counter; ++i)
            {
                cout<<names[i]<<endl<<"grade: "<<grades[i]<<endl;
            }
            //delete the arrays
            delete [] names;
            delete [] grades;
            names = nullptr;
            grades = nullptr;
        }
            //print a message for professor if the stringstream was empty
        else
        {
            cout<<"we can't find any students witch done your chosen exam.\n";
        }
        sort.close();
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
//call a function to limit the access of students on doing en exam or watching an exam
void professor::limitation(const string &given_professor_user)
{
    stringstream saver_list, change, keeper;
    bool find = false, make_change = false, do_once = false, find_name;
    int option;
    string exam_name, list_name, line1, line2, line3, line4, line5, professor_name, add = "show exam is: close";
    cout<<"enter 1 to close the site for doing an exam for a list of your student.\n"
          "enter 2 to give the permission of seeing an exam on the panel of a list of your students.\n"
          "enter 3 to close on both.\n";
    cin>>option;
    cout<<"please enter the exam's name:\n";
    getline(cin>>ws, exam_name);
    cout<<"please enter the list's name:\n";
    getline(cin>>ws, list_name);
    //open the file in read mode to save the students' usernames in a stringstream
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
                    //if the list's name found, the boolean will be true
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
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    //if the boolean be true means that the chosen list, found and the rest commands will be executed
    if(find)
    {
        if((option == 1) || (option == 3))
        {
            stringstream saver_names;
            //open the file in read mode to save the content in a stringstream and
            //in write mode to update its content
            fstream time_out("shared_exams.txt", fstream::in|fstream::out);
            fstream done_exams("done_exams.txt", fstream::out|fstream::in|ios::app);
            while(!done_exams.eof())
            {
                getline(done_exams, line1);
                if(!line1.empty() && line1 == "professor's name: " + given_professor_user)
                {
                    getline(done_exams, line1);
                    getline(done_exams, line1);
                    saver_names<<line1<<endl;
                }
            }
            //put the position at the end of stringstream for writing in it
            done_exams.clear();
            done_exams.seekp(ios::end);
            if (time_out)
            {
                //save the content of file in a stringstream
                while (getline(time_out, line2))
                {
                    change << line2 << endl;
                }
                //put the position at the beginning of the file
                time_out.clear();
                time_out.seekp(0, ios::beg);
                while (!saver_list.eof())
                {
                    find_name = false;
                    //use a boolean to understand if any changes happened
                    make_change = false;
                    getline(saver_list, line1);
                    if (!line1.empty())
                    {
                        //start from the beginning of the stringstream to find the professor's username and given exam's name
                        while (!change.eof())
                        {
                            getline(change, professor_name);
                            if (professor_name == "professor's name: " + given_professor_user)
                            {
                                getline(change, line3);
                                getline(change, line2);
                                if (line2 == line1)
                                {
                                    getline(change, line4);
                                    getline(change, line5);
                                    if (line5 == "exam's name: " + exam_name)
                                    {
                                        //update the content of change and shared_exams.txt using a helper stringstream named keeper
                                        //get the position back a line to change (show exam is: open) to (show exam is: close)
                                        change.seekg(-(long) (line4.length() + line5.length() + 2), ios::cur);
                                        //save the content before (show exam is: open) and add (show exam is: close)
                                        keeper << change.str().substr(0, change.tellg()) << add << endl;
                                        getline(change, line4);
                                        //save the content after (show exam is: open)
                                        keeper << change.str().substr(change.tellg());
                                        make_change = true;
                                        while(!saver_names.eof())
                                        {
                                            getline(saver_names, line4);
                                            if(line4 == line2)
                                            {
                                                find_name = true;
                                                break;
                                            }
                                        }
                                        if(!find_name)
                                        {
                                            done_exams<<professor_name<<endl<<line3<<endl<<line1<<endl<<"show exam is: open"<<endl;
                                            while (line2 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                            {
                                                getline(change, line2);
                                                done_exams<<line2<<endl;
                                            }
                                        }
                                        break;
                                    }
                                    else if (line4.empty())
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
                            else if (professor_name.empty())
                            {
                                break;
                            }
                            else
                            {
                                while (professor_name != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                    getline(change, professor_name);
                            }
                        }
                        //if the make_change boolean becomes true, the content of change and the file will update
                        if(make_change)
                        {
                            do_once = true;
                            //put the position of writing in the file at the beginning
                            time_out.seekp(0, ios::beg);
                            //update the content of the file and change stringstream
                            time_out.write(keeper.str().c_str(), (long)keeper.str().length());
                            change.str("");
                            change << keeper.str();
                            //put the position of reading from stringstream at the beginning of it
                            //to check the new username with saved usernames in file
                            saver_names.clear();
                            saver_names.seekg(0, ios::beg);
                        }
                        //clear the content of the file
                        keeper.str("");
                    }
                    else
                        break;
                }
            }
                //exception handling to be sure that the file is open
            else
            {
                cerr << "there is a problem. please try again a few minutes later.\n";
                return;
            }
            //closing two files
            time_out.close();
            done_exams.close();
        }
        if((option == 2) || (option == 3))
        {
            //put the position of saver_list at the beginning of the stringstream
            saver_list.clear();
            saver_list.seekg(0, ios::beg);
            //clear the content of stringstream
            change.str("");
            //open the file in read mode to save the content of file in a stringstream
            //and in write mode to update the content of file
            fstream limit_in_checked("checked_exams.txt", fstream::in|fstream::out);
            if(limit_in_checked)
            {
                //save the content of the file in a stringstream
                while(getline(limit_in_checked, line2))
                {
                    change<<line2<<endl;
                }
                //put the position of reading from file at the beginning
                limit_in_checked.clear();
                limit_in_checked.seekg(0, ios::beg);
                while(!saver_list.eof())
                {
                    make_change = false;
                    getline(saver_list, line1);
                    if(!line1.empty())
                    {
                        //start from the beginning of the stringstream to find the professor's username and given exam's name
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
                                        //update the content of change and shared_exams.txt using a helper stringstream named keeper
                                        //get the position back a line to change (show exam is: open) to (show exam is: close)
                                        change.seekg(-(long)(line1.length() + line2.length() + 2), ios::cur);
                                        //save the content before (show exam is: open) and add (show exam is: close)
                                        keeper<<change.str().substr(0, change.tellg())<<add<<endl;
                                        getline(change, line2);
                                        //save the content after (show exam is: open)
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
                        //if the make_change boolean become true, the content of change and the file will update
                        if(make_change)
                        {
                            do_once = true;
                            //put the position of writing in the file at the beginning
                            limit_in_checked.seekp(0, ios::beg);
                            //update the content of the file and change stringstream
                            limit_in_checked.write(keeper.str().c_str(), (long)keeper.str().length());
                            change.str("");
                            change<<keeper.str();
                        }
                        //clear the content of the file
                        keeper.str("");
                    }
                    else
                        break;
                }
            }
                //exception handling to be sure that the file is open
            else
            {
                cerr<<"there is a problem. please try again a few minutes later.\n";
                return;
            }
            //put the position of saver_list at the beginning of the stringstream
            saver_list.clear();
            saver_list.seekg(0, ios::beg);
            //clear the content of stringstream
            change.str("");
            change.clear();
            change.seekp(0, ios::beg);
            //open the file in read mode to save the content of file in a stringstream
            //and in write mode to update the content of file
            fstream limit_in_done("done_exams.txt", fstream::in|fstream::out);
            if(limit_in_done)
            {
                //save the content of the file in a stringstream
                while(getline(limit_in_done, line2))
                {
                    change<<line2<<endl;
                }
                //put the position of reading from file at the beginning
                limit_in_done.clear();
                limit_in_done.seekg(0, ios::beg);
                change.clear();
                change.seekg(0, ios::beg);
                while(!saver_list.eof())
                {
                    make_change = false;
                    getline(saver_list, line1);
                    if(!line1.empty())
                    {
                        //start from the beginning of the stringstream to find the professor's username and given exam's name
                        while(!change.eof())
                        {
                            getline(change, line2);
                            if(line2 == "professor's name: " + given_professor_user)
                            {
                                getline(change, line2);
                                getline(change, line2);
                                if(line2 == line1)
                                {
                                    getline(change, line1);
                                    getline(change, line2);
                                    if(line2 == "exam's name: " + exam_name)
                                    {
                                        //update the content of change and shared_exams.txt using a helper stringstream named keeper
                                        //get the position back a line to change (show exam is: open) to (show exam is: close)
                                        change.seekg(-(long)(line1.length() + line2.length() + 2), ios::cur);
                                        //save the content before (show exam is: open) and add (show exam is: close)
                                        keeper<<change.str().substr(0, change.tellg())<<add<<endl;
                                        getline(change, line2);
                                        //save the content after (show exam is: open)
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
                        //if the make_change boolean become true, the content of change and the file will update
                        if(make_change)
                        {
                            do_once = true;
                            //put the position of writing in the file at the beginning
                            limit_in_done.seekp(0, ios::beg);
                            //update the content of the file and change stringstream
                            limit_in_done.write(keeper.str().c_str(), (long)keeper.str().length());
                            change.str("");
                            change<<keeper.str();
                        }
                        //clear the content of the file
                        keeper.str("");
                    }
                    else
                        break;
                }
            }
                //exception handling to be sure that the file is open
            else
            {
                cerr<<"there is a problem. please try again a few minutes later.\n";
                return;
            }
        }
        //if the boolean (do_once) is true, it means that closing is done at least one time
        if(do_once)
            cout<<"closing successfully done.\n";
    }
    else
        cout<<"sorry, we can't find your chosen list.\n";
}
#endif
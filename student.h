#ifndef MINIPROJECT_STUDENT_H
#define MINIPROJECT_STUDENT_H
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
using namespace std;
class student
{
private:
    int student_management;
    string answer;
    double time;
protected:
    void do_exam(const string &given_username);
    void show_exams(const string &given_username);
    void show_grades(const string &given_username);
    void protest_exam(const string &given_username);
    void protest_result(const string &given_username);
public:
    void student_panel(const string &given_username);
};
void student::student_panel(const string &given_username)
{
    do
    {
        cout<<"======================================================================="<<endl;
        cout<<"enter 1 to do your active exams.\nenter 2 to see your grades.\n"
              "enter 3 to protest your score.\nenter 4 to see the result of your protests.\n"
              "enter 5 to see the exam which you have done.\nenter 6 to exit.\n";
        cin>>student_management;
        cout<<"======================================================================="<<endl;
        switch (student_management)
        {
            case 1:
            {
                do_exam(given_username);
                break;
            }
            case 2:
            {
                show_grades(given_username);
                break;
            }
            case 3:
            {
                protest_exam(given_username);
                break;
            }
            case 4:
            {
                protest_result(given_username);
                break;
            }
            case 5:
            {
                show_exams(given_username);
                break;
            }
            case 6:
            {
                cout<<"have a great day :)"<<endl;
                break;
            }
        }
    }while(student_management != 6);
}
void student::do_exam(const string &given_username)
{
    string line1, line2, exam_name, professor_name;
    stringstream keeper, saver_file;
    bool find_name = false, find_exam = false, check_name = false;
    cout<<"your exam's name:\n";
    getline(cin>>ws ,exam_name);
    ifstream shared_exam;
    shared_exam.open("shared_exams.txt", fstream::in);
    if(shared_exam.is_open())
    {
        while(getline(shared_exam, line1))
        {
            saver_file<<line1<<endl;
        }
        shared_exam.close();
        while(!saver_file.eof())
        {
            getline(saver_file,line1);
            professor_name = line1;
            getline(saver_file,line1);
            getline(saver_file,line1);
            if(line1 == "student's username: " + given_username)
            {
                find_name = true;
                getline(saver_file,line1);
                if(line1 == "show exam is: open")
                {
                    getline(saver_file,line1);
                    if(line1 == "exam's name: " + exam_name)
                    {
                        find_exam = true;
                        fstream exams;
                        exams.open("exams.txt" , fstream::in);
                        if (exams.is_open())
                        {
                            while(!exams.eof())
                            {
                                getline(exams, line1);
                                if(!line1.empty())
                                {
                                    getline(exams, line2);
                                    if(line1 == professor_name && line2 == "exam's name: " + exam_name)
                                    {
                                        while(line1 != "time of exam: ")
                                        {
                                            getline(exams, line1);
                                        }
                                        if(line1 == "time of exam: ")
                                        {
                                            getline(exams, line1);
                                            time = stod(line1)*60;
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                                            getline(exams, line1);
                                    }
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
                        getline(saver_file,line1);
                        if(line1 == "situation: not answered.")
                        {
                            saver_file.seekg((long)(-line1.length()-1), ios::cur);
                            ofstream add1("shared_exams.txt", fstream::out);
                            if(add1.is_open())
                            {
                                add1<<saver_file.str().substr(0, saver_file.tellg());
                                add1.close();
                                getline(saver_file,line1);
                                keeper << "situation: answered.\n";
                                auto start_time = std::chrono::high_resolution_clock::now();
                                do
                                {
                                    auto time_keeper = std::chrono::high_resolution_clock::now() - start_time;
                                    double time_manager = std::chrono::duration<double>(time_keeper).count();
                                    if(time_manager < time)
                                    {
                                        getline(saver_file, line1);
                                        if(line1 == "type of question: d")
                                        {
                                            keeper<<(line1 + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n' + "answer: " + '\n');
                                            cout<<line1<<endl<<"answer: "<<endl;
                                            getline(cin>>ws, answer);
                                            keeper<<(answer + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n' + "grade of the student: " + '\n');
                                        }
                                        else if(line1 == "type of question: t")
                                        {
                                            keeper<<(line1 + '\n');
                                            for (int i = 0; i < 5; ++i)
                                            {
                                                getline(saver_file, line1);
                                                cout<<line1<<endl;
                                                keeper<<(line1 + '\n');
                                            }
                                            cout<<"correct answer is:\n";
                                            cin>>answer;
                                            getline(saver_file, line1);
                                            keeper<<("student's answer: " + answer + '\n' + line1 + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n' + "grade of the student: " + '\n');
                                        }
                                        else
                                        {
                                            keeper<<(line1 + '\n');
                                        }
                                    }
                                    else
                                    {
                                        cout<<"time out.\n";
                                        break;
                                    }
                                } while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                                cout<<"exam finished.\n";
                                ofstream add2("shared_exams.txt", fstream::out|ios::app);
                                if(!add2)
                                {
                                    cerr<<"there is a problem. please try again a few minutes later.\n";
                                    return;
                                }
                                else
                                {
                                    add2<<keeper.str();
                                    add2<<saver_file.str().substr(saver_file.tellg());
                                }
                                add2.close();
                                break;
                            }
                            else
                            {
                                cerr<<"there is a problem. please try again a few minutes later.\n";
                                return;
                            }
                        }
                        else
                        {
                            cout<<"you have already answered to this exam.\n";
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
                        {
                            getline(saver_file,line1);
                        }
                    }
                }
                else if(line1.empty())
                {
                    break;
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(saver_file,line1);
                    }
                }
            }
            else if(line1.empty())
            {
                break;
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(saver_file,line1);
                }
            }
        }
        if(!find_name)
        {
            cout<<"sorry we can't find your name in list.\n";
            check_name = true;
        }
        if(!find_exam && !check_name)
        {
            cout<<"sorry we can't find your chosen exam.\n";
        }
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
}
void student::show_grades(const string &given_username)
{
    bool find = false;
    string line1, line2;
    fstream showing;
    showing.open("grades.txt", fstream::in|ios::app|fstream::out);
    if(showing.is_open())
    {
        while(getline(showing, line2))
        {
            getline(showing, line1);
            if(line1 == "student's username: " + given_username)
            {
                find = true;
                cout<<line2<<endl<<line1<<endl;
                getline(showing, line1);
                cout<<line1<<endl;
            }
            else
                getline(showing, line1);
        }
        showing.close();
        if(!find)
        {
            cout<<"can't find any result.\n";
        }
    }
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
}
void student::show_exams(const string &given_username)
{
    string line1, line2, line3, line4;
    stringstream exams, showed;
    bool find = false, present = true, find_st = false, not_show = false;
    fstream showing_with_grades("checked_exams.txt", fstream::out|ios::app|fstream::in);
    if(showing_with_grades)
    {
        while(getline(showing_with_grades, line1))
        {
            getline(showing_with_grades, line2);
            if(line2 == "student's username: " + given_username)
            {
                getline(showing_with_grades, line3);
                if(line3 == "show exam is: open")
                {
                    cout<<line1<<endl<<line2<<endl;
                    getline(showing_with_grades, line1);
                    exams<<line1;
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(showing_with_grades, line1);
                        cout<<line1<<endl;
                    }
                }
                else
                {
                    getline(showing_with_grades, line1);
                    cout<<"the permission of seeing the exam with name "<<line1.substr(13)<<" is token.\n";
                    showed<<line1<<endl;
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(showing_with_grades, line1);
                    }
                }
            }
            else if(line1.empty())
            {
                break;
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(showing_with_grades, line1);
                }
            }
        }
        showing_with_grades.close();
    }
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
    ifstream showing;
    showing.open("shared_exams.txt", ios::in);
    if(showing.is_open())
    {
        while(getline(showing, line1))
        {
            find_st = find = not_show = false;
            present = true;
            if(!line1.empty())
            {
                for (int i = 0; i < 2; ++i)
                {
                    getline(showing, line2);
                }
                if(line2 == "student's username: " + given_username)
                {
                    find_st = true;
                    getline(showing, line3);
                    if(line3 == "show exam is: open")
                    {
                        getline(showing, line3);
                        while (!exams.eof())
                        {
                            getline(exams, line4);
                            if(line3 == line4)
                            {
                                find = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        not_show = true;
                        getline(showing, line3);
                        while(!showed.eof())
                        {
                            getline(showed, line4);
                            if(line4 == line3)
                            {
                                present = false;
                                break;
                            }
                        }
                        if(present)
                        {
                            cout<<"the permission of seeing the exam with name "<<line3.substr(13)<<" is token.\n";
                        }
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        getline(showing, line1);
                }
            }
            else
                break;
            if(!find && find_st && !not_show)
            {
                cout<<line1<<endl<<line2<<endl<<line3<<endl;
                getline(showing, line1);
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(showing, line1);
                    if(line1 != "type of question: d" && line1 != "type of question: t" && line1 != "correct answer: a" && line1 != "correct answer: b" && line1 != "correct answer: c" && line1 != "correct answer: d")
                        cout<<line1<<endl;
                }
            }
            else if(line1.empty())
            {
                break;
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(showing, line1);
                }
            }
            exams.clear();
            exams.seekg(0, ios::beg);
            showed.clear();
            showed.seekg(0, ios::beg);
        }
    }
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
}
void student::protest_exam(const string &given_username)
{
    string exam_name, line1, protest_detail;
    bool find_student = false, find_exam = false, find_protest = false;
    cout<<"your exam's name witch you want to protest on:\n";
    getline(cin>>ws ,exam_name);
    fstream examine;
    examine.open("protest.txt", fstream::in|fstream::out|ios::app);
    if(examine.is_open())
    {
        while(!examine.eof())
        {
            getline(examine, line1);
            if(!line1.empty())
            {
                if(line1 == "exam's name: " + exam_name)
                {
                    getline(examine, line1);
                    getline(examine, line1);
                    getline(examine, line1);
                    if(line1 == given_username)
                    {
                        find_protest = true;
                        break;
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        getline(examine, line1);
                }
            }
            else
                break;
        }
        examine.close();
    }
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
    if(find_protest)
    {
        cout<<"you have already protested in this exam and you can't do it again.\n";
    }
    else
    {
        ifstream protest;
        protest.open("grades.txt",ios::in);
        if(protest.is_open())
        {
            while (getline(protest, line1))
            {
                if(line1 == "exam's name: " + exam_name)
                {
                    getline(protest, line1);
                    if(line1 == "student's username: " + given_username)
                    {
                        getline(protest, line1);
                        cout<<"your garde of "<<exam_name<<" exam is: "<<line1.substr(7)<<endl;
                        find_student = true;
                        break;
                    }
                    find_exam = true;
                }

            }
            protest.close();
        }
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.\n";
            return;
        }
        if (!find_exam)
        {
            cout<<"sorry we can't find your exam in checked exams list.\n";
        }
        if (find_student)
        {
            fstream protest_exam;
            protest_exam.open("protest.txt", fstream::out|ios::app|fstream::in);
            if(protest_exam.is_open())
            {
                std::chrono::system_clock::time_point protest_time;
                protest_time = std::chrono::system_clock::now();
                std::time_t timestamp = std::chrono::system_clock::to_time_t(protest_time);
                std::tm* time_info = std::localtime(&timestamp);
                char buffer[80];
                std::strftime(buffer,80,"%Y-%m-%d %H:%M:%S" , time_info);
                cout<<"please enter your protest:\n";
                getline(cin>>ws, protest_detail);
                protest_exam<<"exam's name: "<<exam_name<<endl<<"answered: no\nstudent's username: \n"<<given_username<<endl<<"protest detail: "<<protest_detail<<endl;
                protest_exam<<"time protest: "<<buffer<<endl;
                protest_exam<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                cout<<"protest saved successfully.\n";
            }
            else
            {
                cerr<<"there is a problem. please make a try a few minutes later.\n";
                return;
            }
            protest_exam.close();
        }
        else
        {
            cout<<"sorry we can't find your name in grades list.\n";
        }
    }
}
void student::protest_result(const string &given_username)
{
    string exam_name, line1, line2, line3;
    bool check_answer = false;
    cout<<"your exam's name witch you want to see result of protest:\n";
    getline(cin>>ws ,exam_name);
    fstream pro_result;
    pro_result.open("protest_answer.txt",fstream::in|fstream::out|ios::app);
    if (pro_result.is_open())
    {
        while (!pro_result.eof())
        {
            getline(pro_result,line1);
            if (!line1.empty())
            {
                if(line1 == "exam's name: " + exam_name)
                {
                    getline(pro_result,line2);
                    if(line2 == "answer of " + given_username + ": ")
                    {
                        getline(pro_result,line2);
                        cout<<line2<<endl;
                        getline(pro_result,line2);
                        check_answer = true;
                    }
                    else
                    {
                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                            getline(pro_result,line1);
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        getline(pro_result,line1);
                }
            }
        }
    }
    else
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    if(!check_answer)
    {
        cout<<"no result found.\n";
    }
}
#endif //MINIPROJECT_STUDENT_H
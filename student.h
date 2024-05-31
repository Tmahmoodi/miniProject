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
    string line , searched_line, answer;
    stringstream saver_file;
    double time;
public:
    void do_exam(string given_username);
    void student_panel(string given_username)
    {
        do
        {
            cout<<"======================================================================="<<endl;
            cout<<"enter 1 to do your active exams.\nenter 2 to see your grades.\nenter 3 to protest your score.\nenter 4 to see the result of your protests.\nenter 5 to exit.\n";
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
                    break;
                }
                case 3:
                {
                    break;
                }
                case 4:
                {
                    break;
                }
                case 5:
                {
                    cout<<"have a great day :)"<<endl;
                    break;
                }
            }
        }while(student_management != 5);
    }
};
void student::do_exam(string given_username)
{
    string line1, line2, exam_name;
    stringstream keeper;
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
            if(line1 == "show exam is: open")
            {
                getline(saver_file,line2);
                if(line2 == "student's username: " + given_username)
                {
                    find_name = true;
                    getline(saver_file,line1);
                    string professor_name = line1;
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
                            }
                        }
                        else
                        {
                            cout<<"there is a problem. please try again a few minutes later.\n";
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
                                            keeper<<(line1 + '\n' + "grade of the student: " + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n');
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
                                            keeper<<(line1 + '\n' + "grade of the student: " + '\n');
                                            getline(saver_file, line1);
                                            keeper<<(line1 + '\n');
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
                                    cout<<"there is a problem. please try again a few minutes later.\n";
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
                                cout<<"there is a problem. please try again a few minutes later.\n";
                            }
                        }
                        else
                        {
                            cout<<"you have already answered to this exam.\n";
                            break;
                        }
                    }
                    else
                    {
                        while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        {
                            if(line1 == "")
                                break;
                            else
                                getline(saver_file,line1);
                        }
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        if(line1 == "")
                            break;
                        else
                            getline(saver_file,line1);
                    }
                }
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    if(line1 == "")
                        break;
                    else
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
        cout<<"there is a problem. please try again a few minutes later.\n";
    }
}
#endif //MINIPROJECT_STUDENT_H
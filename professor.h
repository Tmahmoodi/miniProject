#ifndef MINI_PROJECT_PROFESSOR_H
#define MINI_PROJECT_PROFESSOR_H
#include<string>
#include "student.h"
using namespace std;
class exam
{
private:
    string *question, *type_of_questions, *options_keeper, *helper_with_options, *right_answers, *helper_of_write_answers, *name_of_exams, *helper_with_exams_names;
    string show_options [4] = {"a)","b)","c)","d)"};
    int number_of_exams = 0, number_of_questions, number_of_options = 0, test_options_in_output = 4,size_of_write_answers = 0;
    bool options = false, first_exam = true;
    double whole_time = 0, *time_of_question;
public:
    void make_test()
    {
        string type_of_question;
        number_of_exams += 1;
        for(int i = 0; i < number_of_exams; ++i)
        {
            if(first_exam)
            {
                name_of_exams = new string [(number_of_exams + 1)];
                cout<<"your exam name: \n";
                getline(cin>>ws, name_of_exams [0]);
            }
            else
            {
                helper_with_exams_names = new string [(number_of_exams + 1)];
                for(int i = 0; i < (number_of_exams-1); ++i)
                {
                    helper_with_exams_names[i] = name_of_exams[i];
                }
                delete [] name_of_exams;
                name_of_exams = nullptr;
                cout<<"your exam name: \n";
                getline(cin>>ws, helper_of_write_answers[(number_of_exams-1)]);
                name_of_exams = new string [(number_of_exams + 1)];
                for(int i = 0; i < (number_of_exams-1); ++i)
                {
                    name_of_exams[i] = helper_with_exams_names[i];
                }
                delete [] helper_with_exams_names;
                helper_with_exams_names = nullptr;
            }
            first_exam = false;
        }
        cout<<"how many questions do you want to make?\n";
        cin>>number_of_questions;
        question = new string [(number_of_questions+1)];
        type_of_questions = new string [(number_of_questions+1)];
        time_of_question = new double [number_of_questions];
        cout<<"whenever we ask about the type of your question, write 't' to design test question or write 'd' to make descriptive question.\n";
        for(int i = 0; i < number_of_questions; ++i)
        {
            cout<<"type of question number "<< (i+1)<<": \n";
            cin>>type_of_question;
            if(type_of_question == "d")
            {
                cout<<"your question:\n ";
                getline(cin>>ws, question[i]);
                type_of_questions[i] = type_of_question;
            }
            else if(type_of_question == "t")
            {
                if(!options)
                {
                    number_of_options += 4;
                    size_of_write_answers += 1;
                    options_keeper = new string [(number_of_options+1)];
                    right_answers = new string [(size_of_write_answers+1)];
                }
                else
                {
                    helper_with_options = new string [(number_of_options+1)];
                    for(int i = 0; i < number_of_options; ++i)
                    {
                        helper_with_options [i] = options_keeper[i];
                    }
                    delete [] options_keeper;
                    options_keeper = nullptr;
                    number_of_options += 4;
                    options_keeper = new string [(number_of_options+1)];
                    for(int i = 0; i < (number_of_options - 4); ++i)
                    {
                        options_keeper[i] = helper_with_options [i];
                    }
                    delete [] helper_with_options;
                    helper_with_options = nullptr;
                    helper_of_write_answers = new string [(size_of_write_answers+1)];
                    for(int i = 0; i < size_of_write_answers; ++i)
                    {
                        helper_of_write_answers [i] = right_answers[i];
                    }
                    delete [] right_answers;
                    right_answers = nullptr;
                    size_of_write_answers += 1;
                    right_answers = new string [(size_of_write_answers+1)];
                    for(int i = 0; i < (size_of_write_answers - 1); ++i)
                    {
                        right_answers[i] = helper_of_write_answers [i];
                    }
                    delete [] helper_of_write_answers;
                    helper_of_write_answers = nullptr;
                }
                cout<<"your question:\n ";
                getline(cin>>ws, question[i]);
                cout<<"a) ";
                getline(cin>>ws,options_keeper [(number_of_options - 4)]);
                cout<<"b) ";
                getline(cin>>ws,options_keeper [(number_of_options - 3)]);
                cout<<"c) ";
                getline(cin>>ws,options_keeper [(number_of_options - 2)]);
                cout<<"d) ";
                getline(cin>>ws,options_keeper [(number_of_options - 1)]);
                cout<<"please enter which option is true: \n";
                cin>>right_answers[(size_of_write_answers - 1)];
                type_of_questions[i] = type_of_question;
                options = true;
            }
            cout<<"please enter the time of your question (based on minutes): \n";
            cin>>time_of_question[i];
            whole_time += time_of_question[i];
            if(i != (number_of_questions)-1)
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
    }
    void show_exams()
    {
        int j = 0, t = 0, f=0;
        cout<<"name of your exam: "<<name_of_exams[f]<<endl;
        f+=1;
        for(int i = 0; i < number_of_questions; ++i)
        {
            int y = 0;
            cout<<"question number "<<(i+1)<<": "<<question[i]<<endl;
            if(type_of_questions[i] == "t")
            {
                for(int k = j ; k < test_options_in_output; ++k)
                {
                    cout<<show_options[y]<<options_keeper[k]<<"  ";
                    y+=1;
                }
                cout<<endl<<"right answer of your test is: "<<right_answers[t]<<endl;
                t+=1;
                test_options_in_output += 4;
                j+=4;
            }
            cout<<"time of your question: "<<time_of_question[i]<<endl;
            if(i != (number_of_questions)-1)
                cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        }
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"time of your exam: "<<whole_time<<" min"<<endl;
        test_options_in_output = 4;
    }
};
class list
{
private:
    student *list_students, *helper_list_students;
    int num_st, keeper;
public:
    void make_list(int number_of_students, bool first_list)
    {
        list_students = new student [number_of_students];
        num_st = number_of_students;
        for (int i = 0; i < number_of_students; ++i)
        {
            student ob;
            list_students[i] = ob;
            list_students[i].set();
        }
    }
    void add_student(int added_st)
    {
        helper_list_students = new student [num_st];
        for (int i = 0; i < num_st; ++i)
        {
            helper_list_students[i] = list_students[i];
        }
        delete [] list_students;
        list_students = nullptr;
        keeper = num_st;
        num_st+=added_st;
        list_students = new student [num_st];
        for (int i = 0; i < (num_st-added_st); ++i)
        {
            list_students[i] = helper_list_students[i];
        }
        delete [] helper_list_students;
        helper_list_students = nullptr;
        for (int i = keeper; i < num_st; ++i)
        {
            student ob;
            list_students[i]=ob;
            list_students[i].set();
        }
    }
    void show()
    {
        int number_student = 1;
        for (int i = 0; i < num_st; ++i)
        {
            list_students[i].show(number_student);
            ++number_student;
        }
    }
};
class professor
{
private:
    int professor_management, number_of_added_student, number_of_students, number_of_exams = 0,number_list = 0, num_lists;
    bool designed_exam = false, full_exam_array = false, first_list = true, first_student_list = true;
    exam *designed_exams, *helper;
    list *main_list, *helper_list;
public:
    void professor_panel()
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
                    if(!designed_exam)
                    {
                        cout<<"you don't have any designed exam. please design one and then try again.\n";
                    }
                    else
                    {
                        for(int i = 0; i < number_of_exams; ++i)
                        {
                            cout<<"exam number "<<i+1<<": "<<endl;
                            designed_exams[i].show_exams();
                            if(i != (number_of_exams)-1)
                                cout<<"======================================================================="<<endl;
                        }
                    }
                    break;
                }
                case 2:
                {
                    exam new_one;
                    number_of_exams += 1;
                    if(!full_exam_array)
                    {
                        designed_exams = new exam [number_of_exams];
                        designed_exams [(number_of_exams-1)] = new_one;
                        designed_exams [(number_of_exams-1)].make_test();
                        designed_exam = true;
                    }
                    else
                    {
                        helper = new exam [number_of_exams];
                        for(int i = 0; i < (number_of_exams-1); ++i)
                        {
                            helper[i] = designed_exams [i];
                        }
                        delete [] designed_exams;
                        designed_exams = nullptr;
                        designed_exams = new exam [number_of_exams];
                        for(int i = 0; i < (number_of_exams-1); ++i)
                        {
                            designed_exams [i] = helper[i];
                        }
                        designed_exams [(number_of_exams - 1)] = new_one;
                        delete [] helper;
                        helper = nullptr;
                        designed_exams [(number_of_exams - 1)].make_test();
                    }
                    full_exam_array = true;
                    break;
                }
                case 3:
                {
                    int num_list;
                    cout<<"enter 1 if you want to see your lists.\nenter 2 if you want to add a new list.\nenter 3 if you want to add new students.\n";
                    cin>>num_list;
                    if(num_list == 1)
                    {
                        if(first_list)
                        {
                            cout<<"there isn't any list. please make a list first.\n";
                        }
                        else
                        {
                            for (int i = 0; i < number_list; ++i)
                            {
                                cout<<"list number "<<(i+1)<<" : \n";
                                main_list[i].show();
                                if(i != (number_list)-1)
                                    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                            }
                        }
                    }
                    else if(num_list == 2)
                    {
                        if(first_list)
                        {
                            cout<<"how many students do you want to add?";
                            cin>>number_of_students;
                            ++number_list;
                            list ob;
                            main_list = new list [number_list];
                            main_list[0] = ob;
                            main_list[0].make_list(number_of_students, first_list);
                        }
                        else
                        {
                            ++number_list;
                            list ob;
                            helper_list = new list [number_list];
                            for(int i = 0; i < (number_list-1); ++i)
                            {
                                helper_list [i] = main_list[i];
                            }
                            delete [] main_list;
                            main_list = nullptr;
                            cout<<"how many students do you want to add? \n";
                            cin>>number_of_students;
                            main_list = new list [number_list];
                            helper_list[(number_list-1)] = ob;
                            for(int i = 0; i < number_list; ++i)
                            {
                                main_list[i] = helper_list [i];
                            }
                            delete [] helper_list;
                            helper_list = nullptr;
                            main_list[(number_list-1)].make_list(number_of_students, first_list);
                        }
                        first_list = false;
                    }
                    else if(num_list == 3)
                    {
                        int num_add_lists;
                        cout<<"which list do you want to add your students?";
                        cin>>num_add_lists;
                        cout<<"how many students do you want to add?";
                        cin>>number_of_added_student;
                        main_list[(num_add_lists-1)].add_student(number_of_added_student);
                    }
                    break;
                }
                case 4:
                {
                    cout<<"have a great day :)\n";
                    cout<<"======================================================================="<<endl;
                    break;
                }
            }
        }while(professor_management != 4);
    }
};
#endif
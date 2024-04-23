#ifndef MINI_PROJECT_PROFESSOR_H
#define MINI_PROJECT_PROFESSOR_H
#include<string>
using namespace std;
class exam
{
private:
    string *question, *type_of_questions, *options_keeper, *helper_with_options, *write_answers, *helper_of_write_answers;
    int number_of_questions, number_of_options = 0, size_of_write_answers = 0;
    bool options = false;
public:
    void make_test()
    {
        string type_of_question;
        cout<<"how many questions do you want to make?";
        cin>>number_of_questions;
        question = new string [number_of_questions];
        type_of_questions = new string [number_of_questions];
        cout<<"whenever we ask about the type of your question, write 't' to design test question or write 'd' to make descriptive question.\n";
        for(int i = 0; i < number_of_questions; ++i)
        {
            cout<<"type of question number "<< (i+1)<<": ";
            cin>>type_of_question;
            if(type_of_question == "d")
            {
                cout<<"your question:\n ";
                getline(cin>>ws, question[i]);
                type_of_questions[i] = type_of_question;
                cout<<"-------------------------------------------------------"<<endl;
            }
            else if(type_of_question == "t")
            {
                if(!options)
                {
                    number_of_options += 4;
                    size_of_write_answers += 1;
                    options_keeper = new string [number_of_options];
                    write_answers = new string [size_of_write_answers];
                }
                else
                {
                    helper_with_options = new string [number_of_options];
                    for(int i = 0; i < number_of_options; ++i)
                    {
                        helper_with_options [i] = options_keeper[i];
                    }
                    delete [] options_keeper;
                    options_keeper = nullptr;
                    number_of_options += 4;
                    options_keeper = new string [number_of_options];
                    for(int i = 0; i < (number_of_options - 4); ++i)
                    {
                        options_keeper[i] = helper_with_options [i];
                    }
                    delete [] helper_with_options;
                    helper_with_options = nullptr;
                    helper_of_write_answers = new string [size_of_write_answers];
                    for(int i = 0; i < size_of_write_answers; ++i)
                    {
                        helper_of_write_answers [i] = write_answers[i];
                    }
                    delete [] write_answers;
                    write_answers = nullptr;
                    size_of_write_answers += 1;
                    write_answers = new string [size_of_write_answers];
                    for(int i = 0; i < (size_of_write_answers - 1); ++i)
                    {
                        write_answers[i] = helper_of_write_answers [i];
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
                cout<<"please enter which option is true: ";
                cin>>write_answers[(size_of_write_answers - 1)];
                type_of_questions[i] = type_of_question;
                cout<<"-------------------------------------------------------"<<endl;
                options = true;
            }
        }
    }
};
class professor
{
private:
    int professor_management, number_of_exams = 0;
    bool full_exam_array = false;
    exam *designed_exams, *helper;
public:
    void professor_panel()
    {
        do
        {
            cout<<"==================================================="<<endl;
            cout<<"panel:\nenter 1 to see your designed exams.\nenter 2 to make a new exam.\nenter 3 to add your student\nenter 4 to exit: ";
            cin>>professor_management;
            cout<<"==================================================="<<endl;
            switch(professor_management)
            {
                case 2:
                {
                    exam new_one;
                    number_of_exams += 1;
                    if(!full_exam_array)
                    {
                        designed_exams = new exam [number_of_exams];
                        designed_exams [(number_of_exams-1)] = new_one;
                        designed_exams [(number_of_exams-1)].make_test();
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
                case 4:
                {
                    cout<<"have a great day :)\n";
                    cout<<"==================================================="<<endl;
                    break;
                }
            }
        }while(professor_management != 4);
    }
};
#endif

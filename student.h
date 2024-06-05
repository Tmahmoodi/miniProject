#ifndef MINIPROJECT_STUDENT_H
#define MINIPROJECT_STUDENT_H
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
using namespace std;
//create student class to keep data members related to student in private part and functions in protected part
class student
{
private:
    int student_management;
    string answer, line;
    double time;
protected:
    //declare the prototype of functions in class to avoid make them inline
    void do_exam(const string &given_username);
    void show_exams(const string &given_username);
    void show_grades(const string &given_username);
    void protest_exam(const string &given_username);
    void protest_result(const string &given_username);
public:
    void student_panel(const string &given_username);
};
//create a function to show students panel ,so she can select what to do
void student::student_panel(const string &given_username)
{
    //make do_while loop for showing the panel until the user want to log out
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
                //call a function in student class to allows the user to choose one of the active exams and do the exam
                do_exam(given_username);
                break;
            }
            case 2:
            {
                //call a function in student class to allows the user to see the grade of the chosen exam
                show_grades(given_username);
                break;
            }
            case 3:
            {
                //call a function in student class to allows the user protest on chosen exam after seeing the exams' grades
                protest_exam(given_username);
                break;
            }
            case 4:
            {
                //call a function in student class to allows the user to see the result of the protest
                protest_result(given_username);
                break;
            }
            case 5:
            {
                //call a function in student class to allows the user to see exams witch done
                // and checked by the professor( with grades and professors reaction).
                show_exams(given_username);
                break;
            }
            case 6:
            {
                //to exit the student panel
                cout<<"have a great day :)"<<endl;
                break;
            }
        }
    }while(student_management != 6);
}
//Create a function to allows the student see the exam questions designed and activated by the professor
//and answer them in the time specified by the professor.
void student::do_exam(const string &given_username)
{
    string line1, line2, line3, line4, line5, chosen_exam;
    stringstream keeper, saver_file, exams_name, done;
    bool find_exam = false, do_exam = false;
    ifstream shared_exam;
    //open a file in read mode to find student username and her/his matching exams
    shared_exam.open("shared_exams.txt", fstream::in);
    //open a file in read mode to save done exams name in stringstream
    //and in write mood to clear it then write new stringstream in the file
    fstream done_exams("done_exams.txt", fstream::in|fstream::out|ios::app);
    //exception handling to be sure that the file is open
    if(!shared_exam.is_open() || !done_exams.is_open())
    {
        cerr<<"there is a problem. please try again a few minutes later.\n";
        return;
    }
    while(!done_exams.eof())
    {
        getline(done_exams, line);
        if(!line.empty())
        {
            getline(done_exams, line);
            getline(done_exams, line);
            if(line == "student's username: " + given_username)
            {
                getline(done_exams, line);
                getline(done_exams, line);
                done << line << endl;
                while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(done_exams, line);
                }
            }
            else
            {
                while(line != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(done_exams, line);
                }
            }
        }
    }
    while(getline(shared_exam, line1))
    {
        find_exam = false;
        done.clear();
        done.seekg(0, ios::beg);
        //looking for student chosen exam in shared exams and if founded "find_exam" boolean is true.
        if(!line1.empty())
        {
            getline(shared_exam, line2);
            getline(shared_exam, line3);
            if(line3 == "student's username: " + given_username)
            {
                getline(shared_exam, line4);
                getline(shared_exam, line5);
                while(!done.eof())
                {
                    getline(done, line);
                    if(line5 == line)
                    {
                        find_exam = true;
                        break;
                    }
                }
                if(!find_exam)
                {
                    saver_file<<line1<<endl<<line2<<endl<<line3<<endl<<line4<<endl<<line5<<endl;
                    exams_name<<line5<<endl;
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(shared_exam, line1);
                        saver_file<<line1<<endl;
                    }
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(shared_exam, line1);
                    }
                }
            }
            else
            {
                while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                {
                    getline(shared_exam, line1);
                }
            }
        }
    }
    //check if the stringstream is not empty, do the rest commands
    if(exams_name.rdbuf()->in_avail() != 0)
    {
        //show to student his/her active exams and get from student his/her chosen exam
        while(!exams_name.eof())
        {
            getline(exams_name, line1);
            cout<<line1<<endl;
        }
        cout<<"please enter the name of the exam which you want to do:\n";
        getline(cin>>ws, chosen_exam);
        fstream exams;
        //open a file in read mode to get time of exam that student choose to do
        exams.open("exams.txt" , fstream::in);
        //exception handling to be sure that the file is open
        if (exams.is_open())
        {
            while(!exams.eof())
            {
                getline(exams, line1);
                if(!line1.empty())
                {
                    //get the time which belong to chosen exam and student's professor
                    getline(exams, line2);
                    if(line2 == "exam's name: " + chosen_exam)
                    {
                        //read line by line till found time of this special exam
                        //and when found it we covert string to double and covert minute to second
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
            //exception handling to be sure that the file is open
        else
        {
            cerr<<"there is a problem. please try again a few minutes later.\n";
            return;
        }
        while(getline(saver_file, line1))
        {
            if(!line1.empty())
            {
                getline(saver_file, line2);
                getline(saver_file, line3);
                getline(saver_file, line4);
                getline(saver_file, line5);
                if(line5 == "exam's name: " + chosen_exam)
                {
                    do_exam = true;
                    //save this lines in keeper stringstream if exam name is match
                    //and get the time of system when the exam is start
                    keeper<<line1<<endl<<line2<<endl<<line3<<endl<<line4<<endl<<line5<<endl;
                    auto start_time = std::chrono::high_resolution_clock::now();
                    do
                    {
                        //We count and check the elapsed time from the start of the exam until
                        // the time it reaches the end of the time that professor has specified
                        auto time_keeper = std::chrono::high_resolution_clock::now() - start_time;
                        double time_manager = std::chrono::duration<double>(time_keeper).count();
                        if(time_manager < time)
                        {
                            //show questions and get the answer from student and save answers in keeper stringstream
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
                    if(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        while (line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                        {
                            getline(saver_file, line1);
                            keeper<<(line1 + '\n');
                        }
                    }
                    break;
                }
                else
                {
                    while(line1 != "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                    {
                        getline(saver_file, line1);
                    }
                }
            }
        }
        if(!do_exam)
        {
            cout<<"sorry, we can't find your chosen exam.\n";
        }
        else
        {
            //write students username with his/her answers in done_exams file
            done_exams.clear();
            done_exams.seekp(ios::end);
            done_exams<<keeper.str();
        }
    }
    else
        cout<<"there isn't any active exam for doing.\n";
}
//Create a function to allows the student see the grades of exam
void student::show_grades(const string &given_username)
{
    bool find = false;
    string line1, line2;
    fstream showing;
    //open a file in read mode to show student grades
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
        //use a boolean to declare if there was any grade for the student or not
        //if the boolean stayed false, it means that the there wasn't any grade for the student
        if(!find)
        {
            cout<<"can't find any result.\n";
        }
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
}
//Create a function to allows the student see the history of his/her exams
void student::show_exams(const string &given_username)
{
    string line1, line2, line3, line4;
    stringstream exams, showed;
    bool find = false, present = true, find_st = false, not_show = false;
    //open a file in read mode to save exam with grades in stringstream
    // and check if student has permission to see the history or not
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
                    //saving the name of exam in a stringstream
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
                    //saving the name of exam in a stringstream
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
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
    ifstream showing;
    //open a file in read mood to check show exam is open or not
    showing.open("done_exams.txt", ios::in);
    //exception handling to be sure that the file is open
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
                                //this boolean helps to notice if the exam had shown once or not
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
                                //this boolean helps to find out whether the exam view closed message was displayed or not
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
            //with booleans help, we can notice if we can show exam in the output or not
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
            //put the position of stringstreams which saved the exams' names at the beginning for comparing with the rest exams
            //related to the student
            exams.clear();
            exams.seekg(0, ios::beg);
            showed.clear();
            showed.seekg(0, ios::beg);
        }
    }
        //exception handling to be sure that the file is open
    else
    {
        cerr<<"there is a problem, please try again later.\n";
        return;
    }
}
//Create a function to allows the student protest in his/her grades and send it to professor
void student::protest_exam(const string &given_username)
{
    string exam_name, line1, protest_detail;
    bool find_student = false, find_exam = false, find_protest = false;
    cout<<"your exam's name witch you want to protest on:\n";
    getline(cin>>ws ,exam_name);
    fstream examine;
    //creat a file in write mood to save protest in it and read mood for professor to check
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
    //use this boolean to find out if the student had already protested on an exam or not
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
                        //show student grade of the exam
                        getline(protest, line1);
                        cout<<"your garde of "<<exam_name<<" exam is: "<<line1.substr(7)<<endl;
                        find_student = true;
                        break;
                    }
                }
                find_exam = true;
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
                //get the time and date of protest and save it in file with detail of protest
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
//Create a function to allows the student to see the result of protest in his/her grades
void student::protest_result(const string &given_username)
{
    string exam_name, line1, line2, line3;
    bool check_answer = false;
    cout<<"your exam's name witch you want to see result of protest:\n";
    getline(cin>>ws ,exam_name);
    fstream pro_result;
    //open a file to reed protest result
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
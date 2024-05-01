#ifndef MINIPROJECT_STUDENT_H
#define MINIPROJECT_STUDENT_H
#include<string>
#include<iomanip>
using namespace std;
class student
{
private:
    string StudentUsername;
    string StudentPassword;
public:
    void set()
    {
        cout<<"please enter username of your student: \n";
        getline(cin>>ws, StudentUsername);
        cout<<"please enter password of your student: \n";
        getline(cin>>ws, StudentPassword);
    }
    void show(int number_student)
    {
        cout<<"student number: "<<number_student<<setw(15)<<"username: "<<StudentUsername<<"\n"<<setw(32)<<"password: "<<StudentPassword<<endl;
        ++number_student;
    }
};
#endif //MINIPROJECT_STUDENT_H
#ifndef MINIPROJECT_STUDENT_H
#define MINIPROJECT_STUDENT_H
#include<string>
using namespace std;
class student
{
private:
    int student_management;
public:
    void student_panel()
    {
        cout<<"======================================================================="<<endl;
        cout<<"enter 1 to do your exam.\nenter 2 to see your grade.\nenter 3 to exit.\n";
        cin>>student_management;
        cout<<"======================================================================="<<endl;
        switch (student_management)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                cout<<"have a great day :)"<<endl;
                break;
            }
        }
    }
};
#endif //MINIPROJECT_STUDENT_H
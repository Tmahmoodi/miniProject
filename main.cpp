#include<iostream>
#include<string>
#include "enter.h"
#include "professor.h"
using namespace std;
int main()
{
    int member_counter = 0 , log_in;
    bool check_first_one = true;
    professor *list1, *helper_list;
    string site_chekker;
    do
    {
        cout<<"do you want to close the site? (if you say yes, all the history will be deleted)\nenter yes or no:";
        cin>>site_chekker;
        if(site_chekker != "yes")
        {
            cout << "enter 1 for sign up.\nenter 2 for sign in: ";
            cin >> log_in;
            if (log_in == 1)
            {
                ++member_counter;
                professor ob;
                if (check_first_one)
                {
                    list1 = new professor[member_counter];
                    list1[(member_counter-1)] = ob;
                }
                else
                {
                    helper_list = new professor[member_counter];
                    for (int i = 0; i < (member_counter - 1); ++i)
                    {
                        helper_list[i] = list1[i];
                    }
                    helper_list[(member_counter - 1)] = ob;
                    delete[] list1;
                    list1 = nullptr;
                    list1 = new professor[member_counter];
                    for (int i = 0; i < member_counter; ++i)
                    {
                        list1[i] = helper_list[i];
                    }
                    delete[] helper_list;
                    helper_list = nullptr;
                }
                check_first_one = false;
            }
            int keeper = make_an_account(log_in);
            list1[keeper].professor_panel();
        }
    }while(site_chekker == "no");
    return 0;
}
#include <iostream>
#include <string>
#include "professor.h"

using namespace std;

class site
{
private:
    int member_counter = 0 , log_in, members = 0;
    bool check_first_one = true;
    professor *list1, *helper_list;
    string site_checker, *username1, *password1, *username2, *password2, *given_username, *given_password;
public:
    void list()
    {
        do
        {
            cout<<"do you want to close the site? (if you say yes, all the history will be deleted)\nenter yes or no:\n";
            cin>>site_checker;
            if(site_checker != "yes")
            {
                cout << "enter 1 for sign up.\nenter 2 for sign in: \n";
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
        }while(site_checker == "no");
    }
    int check_account()
    {
        bool check = false;
        int keeper = -1;
        given_username = new string [1];
        given_password = new string [1];
        cout<<"please enter your username: \n";
        getline (cin>>ws, given_username[0]);
        cout<<"please enter your password: \n";
        getline (cin>>ws, given_password[0]);
        for (int i = 0; i < members; i++)
        {
            if(given_username[0] == username1[i])
            {
                if(given_password[0] == password1[i])
                {
                    cout<<"welcome "<<given_username[0]<<" :)"<<endl;
                    check = true;
                    keeper = i;
                    delete [] given_username;
                    delete [] given_password;
                    given_username = nullptr;
                    given_password = nullptr;
                    break;
                }
            }
        }
        if(!check)
        {
            cout<<"your username or password is incorrect. please try again.\n";
        }
        return keeper;
    }
    int make_an_account(int log_in)
    {
        bool check_username = false;
        switch(log_in)
        {
            case 1:
            {
                members += 1;
                if (members == 1)
                {
                    username1 = new string[(members+1)];
                    password1 = new string[(members+1)];
                    cout << "please enter your username: \n";
                    getline(cin >> ws, username1[0]);
                    cout << "please enter your password: \n";
                    getline(cin >> ws, password1[0]);
                }
                else
                {
                    username2 = new string[(members+1)];
                    password2 = new string[(members+1)];
                    for (int i = 0; i < (members - 1); ++i)
                    {
                        username2[i] = username1[i];
                        password2[i] = password1[i];
                    }
                    cout << "please enter your username: \n";
                    while (!check_username)
                    {
                        check_username = true;
                        getline(cin >> ws, username2[(members - 1)]);
                        for (int i = 0; i < (members - 1); ++i)
                        {
                            if (username1[i] == username2[(members - 1)])
                            {
                                cout << "user name was chosen by others, please try an other username: \n";
                                check_username = false;
                            }
                        }
                    }
                    cout << "please enter your password: \n";
                    getline(cin >> ws, password2[(members - 1)]);
                    delete[] username1;
                    delete[] password1;
                    username1 = nullptr;
                    password1 = nullptr;
                    username1 = new string[(members+1)];
                    password1 = new string[(members+1)];
                    for (int i = 0; i < members; ++i)
                    {
                        username1[i] = username2[i];
                        password1[i] = password2[i];
                    }
                    delete[] username2;
                    delete[] password2;
                    username2 = nullptr;
                    password2 = nullptr;
                }
                return (members-1);
                break;
            }
            case 2:
            {
                int saver = check_account();
                while(saver == -1)
                {
                    saver = check_account();
                }
                return saver;
                break;
            }
        }
    }
};
int main()
{
    site start;
    start.list();
    return 0;
}
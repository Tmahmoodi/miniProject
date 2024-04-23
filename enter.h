#ifndef MINIPROJECT2_ENTER_H
#define MINIPROJECT2_ENTER_H
#include<string>

using namespace std;

string *username1, *password1, *username2, *password2, *given_username, *given_password;
int members = 0;

void make_an_account(int log_in)
{

    bool check_username = false;
    bool check = false;
    switch(log_in)
    {
        case 1:
            members += 1;
            if(members == 1)
            {
                username1 = new string [members+1];
                password1 = new string [members+1];
                cout<<"please enter your username: ";
                getline(cin>>ws, username1[0]);
                cout<<"please enter your password: ";
                getline(cin>>ws, password1[0]);
            }
            else
            {
                username2 = new string [members];
                password2 = new string [members];
                for (int i = 0; i < (members-1); ++i)
                {
                    username2[i] = username1[i];
                    password2[i] = password1[i];
                }
                cout<<"please enter your username: ";
                while(!check_username)
                {
                    check_username = true;
                    getline(cin>>ws, username2[(members - 1)]);
                    for(int i = 0; i < (members-1); ++i)
                    {
                        if(username1[i] == username2[(members - 1)])
                        {
                            cout<<"user name was chosen by others, please try an other username: ";
                            check_username = false;
                        }
                    }
                }
                cout<<"please enter your password: ";
                getline(cin>>ws, password2[(members - 1)]);
                delete [] username1;
                delete [] password1;
                username1 = nullptr;
                password1 = nullptr;
                username1 = new string [members];
                password1 = new string [members];
                for (int i = 0; i < members; ++i)
                {
                    username1[i] = username2[i];
                    password1[i] = password2[i];
                }
                delete [] username2;
                delete [] password2;
                username2 = nullptr;
                password2 = nullptr;
            }
            break;
        case 2:
        {
            given_username = new string [1];
            given_password = new string [1];
            cout<<"please enter your username: ";
            getline (cin>>ws, given_username[0]);
            cout<<"please enter your password: ";
            getline (cin>>ws, given_password[0]);
            for (int i = 0; i <= members; i++)
            {
                if(given_username[0] == username1[i])
                {
                    if(given_password[0] == password1[i])
                    {
                        cout<<"welcome\n";
                        check = true;
                        delete [] given_username;
                        delete [] given_password;
                        break;
                    }
                }
            }
            if(!check)
            {
                cout<<"your username or password is incorrect. please try again\n";
                make_an_account(log_in);
            }
            break;
        }

    }
}

#endif

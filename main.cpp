#include<iostream>
#include<string>
#include "enter.h"

using namespace std;

int main()
{
    int log_in;
    string site;
    do
    {
        cout<<"do you want to close the site? (if you say yes, all the history will be deleted)\nenter yes or no: ";
        cin>>site;
        if(site != "yes") {
            cout << "enter 1 for sign up.\nenter 2 for sign in: ";
            cin >> log_in;
            make_an_account(log_in);
        }
    }while(site == "no");
    return 0;
    }
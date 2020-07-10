/*************************************************************************
  @FileName: MyString.cpp
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Thu 18 Jun 2020 10:25:45 PM CST
 ************************************************************************/
#include "MyString.h"

#include <my_head.h>
#include <iostream>

MyString::MyString(const char * str)
{
    if(str)
    {
        myString_ = new char[strlen(str) + 1];
        strcpy(myString_, str);
    }
    else
    {
        myString_ = new char[1];
        *myString_ = '\0';
    }
}

MyString::MyString(const MyString & str)
{
    myString_ = new char[strlen(str.myString_) + 1];
    strcpy(myString_, str.myString_);
}

MyString & MyString::operator=(const MyString & str)
{
    if(this == &str)
        return  * this;

    delete [] myString_;
    myString_ = new char[strlen(str.myString_) + 1];
    strcpy(myString_, str.myString_);
    return * this;
}

int main()
{
    MyString myStr1("int");
    cout << myStr1.get_c_str() << endl;
    MyString str2(myStr1);
    cout << str2.get_c_str() << endl;
    MyString str3 = myStr1;
    cout << str3.get_c_str() << endl;


    std::cout << "Hello world" << std::endl;
    return 0;
}


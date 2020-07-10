/*************************************************************************
  @FileName: MyString.h
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Thu 18 Jun 2020 10:22:23 PM CST
 ************************************************************************/
#ifndef __MY_STRING_H__
#define __MY_STRING_H__


class MyString
{
public:
    MyString(const char * str);
    MyString(const MyString & str);
    MyString & operator=(const MyString & str);

    char * get_c_str() const { return myString_; }
    ~MyString() {}

private:
    char * myString_;

};

#endif //end of __MY_STRING_H__

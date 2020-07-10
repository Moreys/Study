#!/usr/bin/env python
# coding=utf-8
counter = 100
miles = 1000.0
mane = "morey"

print(counter)
print(miles)
print(mane)

print("可以使用连续等于a = b = c = 1")
a = b = c = 1
print(a)
print(b)
print(c)
'''
不可变数据三个：number数字  string字符串   tuple元组
可变数据三个：list列表    dictionary字典    set集合

'''



'''
number:
    int  float   bool complex复数
    除法的时候  / 返回一个浮点数   //返回一个整数
'''
print("number")




'''
string:
    + 号表示字符串连接   * 表示字符串复制    *x 表示复制的次数
    \ 表示转义特殊字符   如果不想让\发生转义  可以在开头加入r

'''
print("string")
str="moreys"

print("输出字符:",str);
print("输出第一个到倒数第二个的所有字符str[0:-1]:",str[0:-1]);
print("输出第一个字符str[0]:",str[0]);
print("输出第二个到第五个字符str[2:5]:",str[2:5]);
print("输出输出第三个以后的字符str[2:]:",str[2:]);
print("输出字符串两次str * 2:",str * 2);
print("连接字符串str + '你好':",str + "你好");

print("hellomorey 使用反斜杠+n转义特殊字符\n",'hello\nmorey');
print("r'hellomorey'在字符串前面添加一个r，表示原始字符串，不会发生转义\n",'hello\nmorey');





'''
list:
    使用最频繁的数据类型
    [] 
    变量[头下标:尾下标]
    + 表示连接    * 表示复制
'''
print("List")
list = ['abc', 789, 2.24, 'morey', 70.2]
timylist = [123, "morey"]
print("输出整个列表:list\n", list)
print("输出第一个元素:list[0]\n",list[0])
print("输出2到3个元素:list[1:3]\n",list[1:3])
print("输出2后面所有的元素:list[2:]\n",list[2:])
print("输出两次列表 tinmylist * 2\n", timylist * 2)
print("连接列表 list + timylist\n", list + timylist)




'''

'''






















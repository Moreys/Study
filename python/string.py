#!/usr/bin/env python
# coding=utf-8
print("python字符串形式")
word = '字符串'
sentence = "这是一个句子"
paragraph = """这是一个
可以自由组合多行
再加一行也OK
"""
print(word, sentence, paragraph)


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

print("等等用户输入") #\n\n显示两个空行
input("\n\n按下enter建后退出")



print("同一行显示多条语句，import sys; x = 'morey', sys.stdout.write(x + '')")
import sys; x = 'morey'; sys.stdout.write(x + '\n')


x = "a"
y = "b"
print("还上输出:print(x)")
print(x)
print("还上输出:print(y)")
print(y)
print("不换行输出print(x, end=" "")
print("不换行输出print(y, end=" "")
print(x, end=" ");
print(y, end=" ");





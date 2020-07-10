#!/usr/bin/env python
# coding=utf-8

a = "Hello"
b = "Python"

print("a + b 输出结果:", a + b)
print("a * 2 输出结果:", a * 2)
print("a[1]  输出结果:", a[1])
print("a[1:4]  输出结果:", a[1:4])




if("H" in a):
    print("H 在变量 a 中")
else:
    print("H 不在变量 a 中")

if("M" not in a):
    print("M 不在变量 a 中")
else:
    print("M 在变量中")

print(r'\n')
print(R'\n')


print("格式化输出")
print("我叫 %s 今年 %d 岁！" % ('小明', 10))


def dn():
    dgt = []
    num = []
    c = 0
    for c in range(2 ** 16):
        ch = chr(c)
        if ch.isdigit():dgt.append(ch)
        if ch.isnumeric():num.append(ch)
    print('digits:', dgt)
    print('numeric:', num)

dn()





print("字符串转换为列表")
var = "菜鸟教程"
list=[]
list=[i for i in var]
print(list)


print("列表转字符串 使用join")
var1 = ",".join(list)
print(var1)

print("字符串转为元组，使用tuple镜像")
tup = tuple(var)
print(tup)

























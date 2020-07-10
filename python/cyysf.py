#!/usr/bin/env python
# coding=utf-8
a = 10
b = 20
list = [1, 2, 3, 4, 5, 6]

if(a in list):
    print("1 变量a 在给定的列表中 list中")
else:
    print("1 变量a 不在给定的列表中 list中")


if(b not in list):
    print("2- 变量不在给定的列表中list 中")
else:
    print("2- 变量在给定的列表中list 中")

# 修改a的值
a = 2
if(a in list):
    print("3 -变量  a 在给定的列表list中")
else:
    print("3 -变量  a 不在给定的列表list中")


print("身份运算符")
a = 20
b = 20
if(a is b):
    print("1 a和b有相同的标识")
else:
    print("2 a和b没有相同的标识")

if(id(a) == id(b)):
    print("2 a和b有相同的标识")
else:
    print("2 a和b没有相同的标识")


b = 30
if(a is b):
    print("3 a和b有相同的标识")
else:
    print("3 a和b没有相同的标识")

if(a is not b):
    print("4 a和b没有相同的标识")
else:
    print("4 a和b有相同的标识")


print("and的优先级很高")

x = True
y = False
x = False
if x or y and z:
    print("yes")
else:
    print("no")


'''
is  是判断两个变量是否引用同一个内存地址
== 判断两个变量是否相等
'''


'''
print("引用a b 的情况")
a = 1000
b = 1000
list1 = [a,3,5]
list2 = [b,4,5]
print(list1[0] is list2[0])
tuple1 = (a, 3, 5)
tuple2 = (b, 3, 5)
print(tuple1[0] is tuple2[0])
dict1 = {6:a, 2:3, 4:5}
dict2 = {1:b, 2:4, 3:7}
print(dict1[6] is dict2[1])
'''


print("不引用a b 的情况")
print("直接使用数字来测试，列表 字典不受值大小的影响，返回ture  元组则受256值范围的影响超出范围则改变地址，返回false")
list1 = [1000,3,5]
list2 = [1000,4,5]
print(list1[0] is list2[0])
tuple1 = (1000, 3, 5)
tuple2 = (1000, 3, 5)
print(tuple1[0] is tuple2[0])
dict1 = {6:1000, 2:3, 4:5}
dict2 = {1:1000, 2:4, 3:7}
print(dict1[6] is dict2[1])
















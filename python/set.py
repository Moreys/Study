#!/usr/bin/env python
# coding=utf-8
sites = {'Google', 'Taobao', 'Morey', 'FaceBook', 'Zhihu', 'Baidu'}

print(sites) #输出集合


if 'Morey' in sites:
    print("Morey在集合中")
else:
    print("Morey不在集合中")

a = set('abracadafk')
b = set('aldreadfj')

print(a)
print(a - b)
print(a | b)
print(a & b)
print(a ^ b)

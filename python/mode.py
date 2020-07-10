#!/usr/bin/env python
# coding=utf-8
'''

import sys
print("===================Python import mode===============")
print("命令行参数:")
for i in sys.argv:
    print(i)
print("\n python 路径为:", sys.path);

from sys import argv,path #导入特定的成员
print("======python from import=======")
print("path:", path) #因为已经导入path成员，所有此处引用时不需要加入sys.path
'''

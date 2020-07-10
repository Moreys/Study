#!/usr/bin/env python
# coding=utf-8
'''
生成器：
    是一个返回迭代器的函数，只能用于迭代操作，
    调用生成器运行的过程中，每次遇到yield时函数会暂停并保存当前所有的运行信息
    返回yield的值，并在下一次执行next() 方法时从当前位置继续运行
    调用一个生成器函数返回的是一个迭代器对象
'''

import sys

def fibonacci(n):
    a, b, counter = 0, 1, 0
    while True:
        if(counter > n):
            return
        yield a
        a, b = b, a + b
        counter += 1

f = fibonacci(10)

while True:
    try:
        print(next(f), end=" ")
    except StopIteration:
        sys.exit()

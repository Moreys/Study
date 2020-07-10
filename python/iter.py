#!/usr/bin/env python
# coding=utf-8
list = [1, 2, 3, 4]
it = iter(list)
print(next(it))
print(next(it))

for x in it:
    print(x, end=",")
print("会记住之前的位置，而不是从头开始,这里是从3 开始")

import sys
list = [1, 2, 3, 4]
it = iter(list)
while True:
    try:
        print(next(it))
    except StopIteration:
        sys.exit()


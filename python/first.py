#!/usr/bin/env python
# coding=utf-8
a, b = 0, 1
while b < 1000:
    print(b, end=',')
    a, b = b, a + b

#!/usr/bin/env python
# coding=utf-8
class MyNumber:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        if self.a <= 20:
            x = self.a
            self.a += 1
            return x
        else:
            raise StopIteration #用于标识迭代的完成防止出现无限循环的情况

myclass = MyNumber()
myiter = iter(myclass)

for x in myiter:
    print(x)

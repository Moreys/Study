#!/usr/bin/env python
# coding=utf-8
'''

#普通函数调用
#def reverseWords(input)
    inputWords = input.split("")
    inputWords = inputWords[-1::-1]
    output = ' '.join(inputWords)
    return output
#相当于man函数
if __name__ == "__man__":
    input = "I like morey"
    rw = reverseWords(input)
    print(rw)

'''

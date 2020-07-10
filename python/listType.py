#!/usr/bin/env python
# coding=utf-8
list = ["google", "morey", 1997, 2000]
print("元素列表", list)
del  list[2]
print("删除第三个元素", list)

print("列表的操作,其实和C++的list差不都一样")
print("求长度len(list)", len(list))
#print("最大值max(list)", max(list))//不一样的还不能比较
#print("最小值min(list)", min(list))





print("遍历list")
for x in list:
    print(x)

print("list拼接")
list2 = ["hehe", "nihi", 111]
list += list2
print(list)
print("拼接的过程是自动放在后面")





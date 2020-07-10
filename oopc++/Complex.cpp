/*************************************************************************
  @FileName: Complex.cpp
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Thu 18 Jun 2020 07:12:24 PM CST
 ************************************************************************/
#include <my_head.h>
#include "Complex.h"
#include <iostream>


int main()
{
    const Complex c1(1, 2);
    cout << c1.getImag() << " " << c1.getReal() << endl;


    Complex c2(3, 1);
    c2.setImag(4);
    c2.setReal(4);
    
    std::cout << "Hello world" << std::endl;
    return 0;
}


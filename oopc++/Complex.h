/*************************************************************************
  @FileName: Complex.h
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Thu 18 Jun 2020 07:07:45 PM CST
 ************************************************************************/
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

class Complex
{
public:
    Complex(double r = 0, double i = 0)
        : re_(r)
        , im_(i)
    {}

    ~Complex() {}

#if 1
    double getReal() const { return re_; }
    double getImag() const { return im_; }

    void setReal(double r)  { re_ = r; }
    void setImag(double i)  { im_ = i; }
#endif

#if 0 //如果外面使用的是  const Complex(1, 2) 的方式申请对象，那么就会编译不通过
    double getReal()  { return re_; }
    double getImag()  { return im_; }
#endif


private:
    double re_;
    double im_;

};

#endif//end of __COMPLEX_H__

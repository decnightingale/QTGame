#include <iostream>
using namespace std;

class Complex {
public: 
double real, imag;
Complex(int i) { //����ת�����캯��
cout << "IntConstructor called" << endl;
real = i; imag = 0; 
}
Complex(double r, double i) { real = r; imag = i; }
Complex(const Complex& v)
{
real=v.real;
imag=v.imag;
cout<<"copy called"<<endl;
}
};
int main (){
Complex c1(7, 8);
Complex c2 = 12;
c1 = 9; // 9���Զ�ת����һ����ʱComplex����
cout << c1.real << "," << c1.imag << endl;
return 0;
}

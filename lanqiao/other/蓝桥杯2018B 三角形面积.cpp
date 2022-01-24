// 蓝桥杯2018B 三角形面积
/*
	思路：
	海伦公式
	sqrt(p*(p-a)*(p-b)*(p-c)) 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	double x1 = 2.3, x2 = 6.4, x3 = 5.1;
	double y1 = 2.5, y2 = 3.1, y3 = 7.2;
	
	double a = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
	double b = sqrt((x3-x1)*(x3-x1) + (y3-y1)*(y3-y1));
	double c = sqrt((x2-x3)*(x2-x3) + (y2-y3)*(y2-y3));
	
	double p = 0.5*(a + b + c);
	
	cout << a << " " << b << " " << c << endl;	
	cout << sqrt(p*(p-a)*(p-b)*(p-c)) << endl;
	
	return 0;
}

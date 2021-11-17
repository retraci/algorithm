// POJ 1017 Packets
/*
	思路：贪心

*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int s1, s2, s3, s4, s5, s6;
	int n = 0;
	while(~scanf("%d%d%d%d%d%d", &s1, &s2, &s3, &s4, &s5, &s6) && (s1+s2+s3+s4+s5+s6)) {
		n = s6;

		n += s5;
		s1 = max(0, s1-11*s5);

		n += s4;
		if(s2 >= 5*s4) {
			s2 -= 5*s4;
		} else {
			s1 = max(0, s1-4*(5*s4-s2));
			s2 = 0;
		}

		n += (s3+3)/4;
		if((s3 %= 4) && (s1 > 0 || s2 > 0)) {
			if(s2 >= 7-2*s3) {				// 如果剩余空间 s2 放不完
				s2 -= 7-2*s3;
				s1 = max(0, s1-(8-s3));
			} else {
				s1 = max(0, s1-(36-9*s3-4*s2));
				s2 = 0;
			}
		}

		n += (s2+8) / 9;
		if((s2 %= 9) && s1 > 0) {
			s1 = max(0, s1-(36-4*s2));
		}

		n += (s1+35) / 36;

		cout << n << endl;
	}

	return 0;
}

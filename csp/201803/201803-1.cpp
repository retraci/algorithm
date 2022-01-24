// 201803-1
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int sum = 0;
	
	int temp, last = -1;
	while(cin >> temp) {
		if(temp == 0) {
			cout << sum << endl;
			break;
		} 
		
		if(temp == 1) {
			last = 1;
			sum += last;
		} else {
			if(last == -1 || last == 1) {
				last = 2;
				sum += last;
			} else {
				last += 2;
				sum += last;
			}
		}		
	}
	
	return 0; 
}

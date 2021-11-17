// POJ 2348 Euclid's Game
/*
	思路：
	如果 2*a > b 没得选
	如果 2*a < b 必胜
	
	推导 2*a < b 必胜
	1.将 b 减少至刚好大于 a ，此时为没得选状态，若 b-(x-1)a 为必输态，则原状态为必胜态
	2.将 b 减少至刚好小于 a，此时由于该状态由 b-(x-1)a 推导而来，
	所以如果 b-(x-1)a 为必胜态，b-xa 为必输态，原状态为必胜态 
*/ 

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
	int a, b;
	while(cin >> a >> b && a && b) {
		bool flag = true;
		while(true) {
			if(a > b) swap(a, b);
			
			if(b % a == 0) break;
			if(a < b-a) break;
			
			b -= a;
			flag = !flag;
		}
		
		if(flag) {
			printf("Stan wins\n");
		} else {
			printf("Ollie wins\n");
		}
	}
	
	return 0;
}

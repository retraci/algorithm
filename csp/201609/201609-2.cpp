// 201609-2 火车购票
/*
	思路：
	模拟 
*/

#include <iostream>
#include <algorithm>

using namespace std;

int seats[20];

int main() {
	int n;
	cin >> n;
	
	int num;
	while(n--) {
		cin >> num;
		
		int flag = 0;
		for(int i = 0; i < 20; i++) {
			if(seats[i]+num <= 5) {
				int idx = i*5+seats[i]+1;
				
				for(int i = 0; i < num; i++) {
					if(i != num-1)
						cout << idx++ << " ";
					else 
						cout << idx++ << endl;
				}
				
				seats[i] += num;
				flag = 1;
				break;
			}
		}
		
		if(flag) continue;
		for(int i = 0; i<20 && num>0; i++) {
			if(seats[i] < 5) {
				int idx = i*5+seats[i]+1;
				
				int leaf = 5-seats[i];
				for(int i = 0; i < leaf; i++) {
					if(num != 1) {
						cout << idx++ << " ";
					} else {
						cout << idx++ << endl;
					}
					seats[i]++;
					num--;
					if(num == 0) break;
				}
			}
		}
	}
	
	return 0;
}

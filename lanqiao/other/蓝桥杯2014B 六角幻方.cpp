// 蓝桥杯2014B 六角幻方 
/*
	思路：
	dfs 全排列 
*/

#include <bits/stdc++.h>
#pragma optimize(2)

using namespace std;

int a[20] = {15,13,1,2,3,4,5,6,7,8,9,10,11,12,14,16,17,18,19};
vector<int> ls[15];

void print() {
	cout << endl;
	for(int i = 0; i < 19; i++) {
		printf("%d ", a[i]);
	}
	cout << endl;
}

bool check() {
	//print();
	int sum = 0;
	for(int i = 0; i < 15; i++) {
		int temp = 0;
		for(int j = 0; j < ls[i].size(); j++) {
			temp += a[ls[i][j]]; 
		}
		if(sum == 0) sum = temp;
		if(sum != 38) return false;
		if(sum != temp) return false;
	}
	
	return true;
}

void dfs(int x) {
	//print();
	if(x == 19) {
		if(check()) {
			printf("%d %d %d %d %d\n", a[7], a[8], a[9], a[10], a[11]);
		}
		return;
	}
	
	if(x == 7) {
		int temp1 = 0;
		for(int j = 0; j < ls[0].size(); j++) {
			temp1 += a[ls[0][j]]; 
		}
		if(temp1 != 38) return;
		
		int temp2 = 0;
		for(int j = 0; j < ls[1].size(); j++) {
			temp2 += a[ls[1][j]]; 
		}
		
		if(temp1 != temp2) return;
	} else if(x == 12) {
		int temp1 = 0;
		for(int j = 0; j < ls[0].size(); j++) {
			temp1 += a[ls[0][j]]; 
		}
		if(temp1 != 38) return;
		
		int temp2 = 0;
		for(int j = 0; j < ls[2].size(); j++) {
			temp2 += a[ls[2][j]]; 
		}
		
		int temp3 = 0;
		for(int j = 0; j < ls[5].size(); j++) {
			temp3 += a[ls[5][j]]; 
		}
		
		if(temp1 != temp2 || temp1 != temp3) return;
	} else if(x == 16) {
		int temp1 = 0;
		for(int j = 0; j < ls[0].size(); j++) {
			temp1 += a[ls[0][j]]; 
		}
		if(temp1 != 38) return;
		
		int temp2 = 0;
		for(int j = 0; j < ls[3].size(); j++) {
			temp2 += a[ls[3][j]]; 
		}
		
		int temp3 = 0;
		for(int j = 0; j < ls[6].size(); j++) {
			temp3 += a[ls[6][j]]; 
		}
		
		if(temp1 != temp2 || temp1 != temp3) return;
	}
	
	for(int i = x; i < 19; i++) {
		swap(a[x], a[i]);
		dfs(x+1);
		swap(a[x], a[i]);
	}
}

int main() {
	ls[0].push_back(0); ls[0].push_back(1); ls[0].push_back(2); 
	ls[1].push_back(3); ls[1].push_back(4); ls[1].push_back(5); ls[1].push_back(6); 
	ls[2].push_back(7); ls[2].push_back(8); ls[2].push_back(9); ls[2].push_back(10); ls[2].push_back(11);
	ls[3].push_back(12); ls[3].push_back(13); ls[3].push_back(14); ls[3].push_back(15);
	ls[4].push_back(16); ls[4].push_back(17); ls[4].push_back(18); 
	
	ls[5].push_back(0); ls[5].push_back(3); ls[5].push_back(7); 
	ls[6].push_back(1); ls[6].push_back(4); ls[6].push_back(8); ls[6].push_back(12);
	ls[7].push_back(2); ls[7].push_back(5); ls[7].push_back(9); ls[7].push_back(13); ls[7].push_back(16);
	ls[8].push_back(6); ls[8].push_back(10); ls[8].push_back(14); ls[8].push_back(17);
	ls[9].push_back(11); ls[9].push_back(15); ls[9].push_back(18); 
	
	ls[10].push_back(7); ls[10].push_back(12); ls[10].push_back(16); 
	ls[11].push_back(3); ls[11].push_back(8); ls[11].push_back(13); ls[11].push_back(17);
	ls[12].push_back(0); ls[12].push_back(4); ls[12].push_back(9); ls[12].push_back(14); ls[12].push_back(18);
	ls[13].push_back(1); ls[13].push_back(5); ls[13].push_back(10); ls[13].push_back(15);
	ls[14].push_back(2); ls[14].push_back(6); ls[14].push_back(11); 
	
//	for(int i = 0; i < 15; i++) {
//		for(int j = 0; j < ls[i].size(); j++) {
//			printf("%d ", ls[i][j]);
//		}
//		cout << endl;
//	}
	
	dfs(2);
	
	return 0;
} 

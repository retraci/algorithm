// 201903-2
/*
	思路：
	模拟
	
	node：
	减法把数字变负数 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	stack<int> nums;
	stack<char> op;
	string str;
	
	for(int i = 0; i < n; i++) {
		cin >> str;
		
		while(!nums.empty()) nums.pop();
		while(!op.empty()) op.pop();
		for(int j = 0; j < str.size(); j++) {
			if(isdigit(str[j])) {
				nums.push(str[j]-'0');
			} else {
				if(str[j] == '+') {
					op.push(str[j]);
				} else if(str[j] == '-') {
					op.push(str[j]);
					nums.push(-1*(str[j+1]-'0'));
					j++;
				} else if(str[j] == 'x') {
					int temp = nums.top(); nums.pop();
					nums.push(temp*(str[j+1]-'0'));
					j++;
				} else if(str[j] == '/') {
					int temp = nums.top(); nums.pop();
					nums.push(temp/(str[j+1]-'0'));
					j++; 
				}
			}
		}
		while(!op.empty()) {
			op.pop();
			int temp2 = nums.top(); nums.pop();
			int temp1 = nums.top(); nums.pop();
			nums.push(temp1+temp2);
		}
		if(nums.top() == 24) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	
	return 0;
} 

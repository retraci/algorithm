// 201903-4
/*
	
*/

/*
3 2
R1 S1
S0 R0
R1 S1
R0 S0
R1 R1 R1 R1 S1 S1 S1 S1
S0 S0 S0 S0 R0 R0 R0 R0

2 3
R1 S1
R2 S0 R0 S2
S1 R1
R1 
R2 S0 R0
S1 R1
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int op, num;
	Node(string& s) {
		if(s[0] == 'S') op = 1;
		else op = 0; 
		
		num = 0;
		for(int i = 1; i < s.size(); i++) {
			num = num*10+(s[i]-'0');
		}
	}
};

int n;
vector<queue<Node> > v;

void solve() {
	int flag = 1;
	
	while(flag) {
		flag =  0;
		for(int i = 0; i < n; i++) {
			if(v[i].empty()) continue;
			Node n1 = v[i].front();
			if(v[n1.num].empty()) break;
			Node n2 = v[n1.num].front();
			
			if(n2.num != i) continue;
			if(n2.op+n1.op != 1) continue;
			v[i].pop(); v[n1.num].pop();
			flag = 1;
		}
	}
	
	int ans = 0;
	for(int i = 0; i < n; i++) {
		if(!v[i].empty()) {
			ans = 1;
			break;
		}
	}
	cout << ans << endl;
}

int main() {
	int T;
	cin >> T >> n;
	
	string str;
	stringstream ss;
	queue<Node> temp;
	getchar();
	while(T--) {
		v.clear();
				
		for(int i = 0; i < n; i++) {
			ss.clear();
			getline(cin, str);
			ss << str;
			
			while(!temp.empty()) temp.pop();
			while(ss >> str) {
				temp.push(Node(str));
			}
			v.push_back(temp);			
		}
		
		solve();
	}
	
	return 0;
}

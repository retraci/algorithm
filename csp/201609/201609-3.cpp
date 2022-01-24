// 	201609-3 炉石传说
/*
	思路：
	模拟 
	
	node:
	vector.insert(it, val)
	vector.erase(it) 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

struct per {
	int att, heal;
	per(int a_, int h_) {
		att = a_, heal = h_;
	}
};

int n;
vector<per> A, B;

void print() {
	if(A[0].heal <= 0) {
		cout << -1 << endl;
	} else if(B[0].heal <= 0) {
		cout << 1 << endl;
	} else {
		cout << 0 << endl;
	}

	cout << A[0].heal << endl;
	cout << A.size()-1;
	for(int i = 1; i < A.size(); i++) {
		cout << " " << A[i].heal;
	}
	cout << endl;

	cout << B[0].heal << endl;
	cout << B.size()-1;
	for(int i = 1; i < B.size(); i++) {
		cout << " " << B[i].heal;
	}
	cout << endl;
}

int main() {
	cin >> n;

	A.push_back(per(0, 30));
	B.push_back(per(0, 30));
	string op;
	int a, b, c;
	int now = 1;
	while(n--) {
		cin >> op;
		if(op == "end") {
			now = -now;
			continue;
		}

		if(op == "summon") {
			scanf("%d%d%d", &a, &b, &c);

			if(now == 1) {
				A.insert(A.begin()+a, per(b, c));
			} else {
				B.insert(B.begin()+a, per(b, c));
			}
		} else if(op == "attack") {
			scanf("%d%d", &a, &b);

			if(now == 1) {
				A[a].heal -= B[b].att;
				B[b].heal -= A[a].att;

				if(a==0 && A[a].heal <= 0) {
					print();
					exit(0);
				}
				if(b==0 && B[b].heal <= 0) {
					print();
					exit(0);
				}
				if(A[a].heal <= 0) A.erase(A.begin()+a);
				if(B[b].heal <= 0) B.erase(B.begin()+b);
			} else {
				cout << B[a].heal << endl;
				B[a].heal -= A[b].att;
				A[b].heal -= B[a].att;

				if(a==0 && B[a].heal <= 0) {
					print();
					exit(0);
				}
				if(b==0 && A[b].heal <= 0) {
					print();
					exit(0);
				}
				if(B[a].heal <= 0) B.erase(B.begin()+a);
				if(A[b].heal <= 0) A.erase(A.begin()+b);
			}
		}
	}
	print();

	return 0;
}

#include<bits/stdc++.h>
using namespace std;
int big[30] , small[30] ;

int yay , whoops ;
const int M = 2e5 + 10 ;
bool vis[M] ;

int main () {
	string s ;
	cin >> s ;
	for (int i = 0 ; i < s.size () ; i ++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			big[s[i]-'A'] ++ ;
		}
		else 
			small[s[i]-'a'] ++ ;
	}
	cin >> s ;
	for (int i = 0 ; i < s.size () ; i ++) {
		if(s[i] >= 'A' && s[i] <= 'Z') {
			if (big[s[i]-'A']) {
				vis[i] = 1 ;
				big[s[i]-'A'] -- ;
				yay ++ ;
			}
		}
		else {
			if (small[s[i]-'a']) {
				vis[i] = 1 ;
				small[s[i]-'a'] -- ;
				yay ++ ;
			}
		}
	}
	for (int i = 0 ; i < s.size () ; i ++) {
		if (!vis[i]) {
			int id ;
			if (s[i] >= 'A' && s[i] <= 'Z') {
				id = s[i]-'A' ;
			}
			else id = s[i]-'a' ;
			if (big[id]) {
				big[id] -- ;
				whoops ++ ;
			}
			else if (small[id]) {
				small[id] -- ;
				whoops ++ ;
			}
		}
	}
	cout << yay << " " << whoops << endl ;
	return 0 ;
}

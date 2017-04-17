#include<bits/stdc++.h>
using namespace std;

const int M = 1000+10;
const int inf = 0x3f3f3f3f;
struct AC {
	int go[M][26], fail[M], end[M];
	int o, rt;
	char a[4] = {'A', 'G', 'C', 'T'};
	int b[128];
	int dp[M][M];

	int NewNode () {
		for (int i=0; i<4; i++)  {
			go[o][i] = -1;
		}
		end[o] = 0;
		return o++;
	}

	void Init () {
		for (int i=0; i<4; i++) {
			b[a[i]] = i;
		}
		o = 0;
		rt = NewNode();
	}

	void Ins (char *s) {
		int now = rt;
		for (; *s; s++) {
			if (go[now][b[*s]] == -1)
				go[now][b[*s]] = NewNode();
			now = go[now][b[*s]];
		}
		end[now] = 1;
	}

	void GetFail () {
		queue<int> q;	
		for (int i=0; i<4; i++) {
			if (go[rt][i] == -1) {
				go[rt][i] = rt;
			} else {
				fail[go[rt][i]] = rt;
				q.push (go[rt][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i=0; i<4; i++) {
				if (go[now][i] == -1) {
					go[now][i] = go[fail[now]][i];
				} else {
					fail[go[now][i]] = go[fail[now]][i];
					end[go[now][i]] |= end[go[fail[now]][i]];
					q.push (go[now][i]);
				}
			}
		}
	}

	void Solve (int CASE, char *s) {
		int lens = strlen(s+1);
		for (int i=0; i<1+lens; i++) {
			for (int j=0; j<o; j++) {
				dp[i][j] = inf;
			}
		}
		dp[0][rt] = 0;
		for (int i=1; i<1+lens; i++) {
			for (int j=0; j<o; j++) {
				if (dp[i-1][j] == inf) continue;
				for (int t=0; t<4; t++) {
					if (end[go[j][t]]) continue;
					dp[i][go[j][t]] = min(dp[i][go[j][t]],
							dp[i-1][j] + (a[t] != s[i]));
				}
			}
		}
		int minn = inf;
		for (int i=0; i<o; i++) {
			minn = min(minn, dp[lens][i]);
		}
		printf ("Case %d: %d\n", CASE, minn==inf?-1:minn);
	}
} ac;
char s[M];
int n;
 
int main () {
	int CASE=0;
	while (~scanf ("%d", &n) && n) {
		ac.Init();
		for (int i=0; i<n; i++) {
			scanf ("%s", s);
			ac.Ins(s);
		}
		ac.GetFail();
		scanf ("%s", s+1);
		ac.Solve(++CASE, s);
	}
	return 0;
}

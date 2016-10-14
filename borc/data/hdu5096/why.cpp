#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>  
#include <map>  
#include <string>  
#include <set>  
#include <cstdlib>  
#include <algorithm>  
using namespace std;  
  
#define mnx 20002  
#define N 3020  
#define E 1000200  
#define inf 0x3f3f3f3f  
#define ls (p[i].ch[0])  
#define rs (p[i].ch[1])  
#define md ((ll + rr) >> 1)  
const int M = 10000000;  
  
  
  
bool acc[mnx][11];  
int pen[mnx][11]; // 未提交时候的罚时  
int lst[mnx];  
int cnt[mnx]; // 总罚时  
int lstacc[mnx];  
  
int n, k;  
  
struct ff {  
    bool operator()(const int &a, const int &b) const{  
        if(lstacc[a] == -1 && lstacc[b] == -1) return a < b;  
        if(lstacc[a] == -1 || lstacc[b] == -1) return lstacc[b] == -1;  
        return lstacc[a] < lstacc[b];  
    }  
};  
struct node {  
    int ch[2], r, s, v, cnt;  
    set<int, ff> vv;  
    node() {}  
    void setIt(int v, int id) {  
        this -> v = v;  
        vv.clear();  
        vv.insert(id);  
        ch[0] = ch[1] = 0, r = rand(), s = 1;  
        cnt = 1;  
    }  
}p[mnx * 22];  
int sz;  
int creat(int v, int id) {  
    ++ sz;  
    p[sz].setIt(v, id);  
    return sz;  
}  
int cmp(int i, int v) {  
    if(p[i].v == v) return -1;  
    return v < p[i].v? 0: 1;  
}  
void mt(int i) {  
    p[i].s = p[i].cnt;  
    if(ls) p[i].s += p[ls].s;  
    if(rs) p[i].s += p[rs].s;  
}  
void rt(int &i, int d) {  
    int k = p[i].ch[d^1];  
    p[i].ch[d^1] = p[k].ch[d];  
    p[k].ch[d] = i;  
    mt(i), mt(k);  
    i = k;  
}  
void ins(int &i, int id, int v) {  
    if(!i) {  
        i = creat(v, id);  
        return;  
    }  
    int d = cmp(i, v);  
    if(d == -1) {  
        p[i].cnt ++, p[i].s++;  
        p[i].vv.insert(id);  
        return;  
    }  
    ins(p[i].ch[d], id, v);  
    if(p[p[i].ch[d]].r > p[i].r)  
        rt(i, d ^ 1);  
    mt(i);  
}  
set<int, ff>::iterator it;  
void Remove(int &i, int id, int v) {  
    int d = cmp(i, v);  
    if(d == -1) {  
        if(p[i].cnt > 1) {  
            p[i].cnt--, p[i].s--;  
            p[i].vv.erase(id);  
            return;  
        }  
        if(!ls) i = rs;  
        else if(!rs) i = ls;  
        else {  
            int d2 = p[ls].r > p[rs].r? 1: 0;  
            rt(i, d2);  
            Remove(p[i].ch[d2], id, v);  
        }  
    }  
    else Remove(p[i].ch[d], id, v);  
    if(i) mt(i);  
}  
int kth(int i, int k) {  
    if(!i) return -1;  
    int d = k - p[ls].s;  
    if(d <= 0) return kth(ls, k);  
    if(d <= p[i].cnt) {  
        if(d != 1) return -1;  
        return *(p[i].vv.begin());  
    }  
    return kth(rs, d - p[i].cnt);  
}  
int ran(int i, int id, int v) {  
    int d = cmp(i, v);  
    int c = 0;  
    if(ls) c += p[ls].s;  
    if(d == -1) return c + 1;  
    if(d == 0) return ran(ls, id, v);  
    return c + p[i].cnt + ran(rs, id, v);  
}  
int readint() {  
    char c;  
    while((c = getchar()) && !(c >= '0' && c <= '9'));  
    int ret = c - '0';  
    while((c = getchar()) && c >= '0' && c <= '9')  
        ret = ret * 10 + c - '0';  
    return ret;  
}  
char readc() {  
    char c;  
    while((c = getchar()) && !isalpha(c));  
    return c;  
}  
int main() {  
	freopen ("read.txt", "r", stdin);
    while(scanf("%d%d", &n, &k) != EOF) {  
        int kk = 0;  
        memset(pen, 0, sizeof pen);  
        memset(lst, -1, sizeof lst);  
        memset(cnt, 0, sizeof cnt);  
        memset(acc, 0, sizeof acc);  
        memset(lstacc, -1, sizeof lstacc);  
        int root = 0;  
        char op[20];  
        sz = 0;  
        for(int i = 0; i < n; ++i) {  
            ins(root, i, 0);  
        }  
        while(scanf("%s", op) && op[0] != 'C') {  
            ++kk;  
            if(op[0] == 'S') {  
                int t, team, res;  
                int id;  
                t = readint();  
                team = readint();  
                id = readc() - 'A';  
                res = readint();  
				//printf ("S %d:%d:%c:%d\n",t,team,id+'A',res);
                if(lst[team] != -1 && t - lst[team] < 5) continue;  
                if(acc[team][id]) continue;  
                if(res == 0) {  
                    pen[team][id] += 20;  
                    lst[team] = t;  
                    continue;  
                }  
                printf("[%d][%c]\n", team, (char)id + 'A');  
                Remove(root, team, cnt[team]);  
                cnt[team] += pen[team][id];  
                cnt[team] += t;  
                acc[team][id] = 1;  
                cnt[team] -= M;  
                lst[team] = t;  
                lstacc[team] = kk;  
                ins(root, team, cnt[team]);  
                continue;  
            }  
            int team;  
            if(op[0] == 'R') {  
                scanf("%d", &team);  
				//printf ("R %d\n", team);
                printf("%d\n", ran(root, team, cnt[team]));  
                continue;  
            }  
            int k;  
            scanf("%d", &k);  
			//printf ("T %d\n", k);
            printf("%d\n", kth(root, k));  
        }  
        scanf("%s", op);  
        puts("");  
    }  
    return 0;  
}  




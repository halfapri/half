#include <bits/stdc++.h>
using LL = long long ;
#define ALL(v) (v).begin(),(v).end()

struct San : std::vector<double> {
    void done() {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
    }

    int get(double x) {
        return std::lower_bound(begin(),end(),x) - begin();
    }
} ss;

struct Event {
    double p,l,r;
    int sig;

    bool operator < (const Event &rhs) const {
        if (p != rhs.p) return p < rhs.p;
        return sig > rhs.sig;
    }
};

struct SegmentTree {
    double t[2000 + 5 << 2][3];
    int tag[2000 + 5 << 2];

    void build(int l,int r,int rt) {
        t[rt][1] = t[rt][2] = 0.;
        t[rt][0] = ss[r + 1] - ss[l];
        tag[rt] = 0;
        if (l == r) return ;
        int mid = l + r >> 1;
        build(l,mid,rt << 1);
        build(mid + 1,r,rt << 1 | 1);
    }

    void up(int l,int r,int rt) {
        if (tag[rt] >= 2) {
            t[rt][2] = ss[r + 1] - ss[l];
            t[rt][1] = t[rt][0] = 0.;
        } else if (tag[rt] == 1) {
            if (l == r) {
                t[rt][1] = ss[r + 1] - ss[l];
                t[rt][0] = t[rt][2] = 0.;
            } else {
                t[rt][2] = t[rt << 1][1] + t[rt << 1][2] + t[rt << 1 | 1][1] + t[rt << 1 | 1][2];
                t[rt][1] = t[rt << 1][0] + t[rt << 1 | 1][0];
                t[rt][0] = 0.;
            }
        } else {
            if (l == r) {
                t[rt][0] = ss[r + 1] - ss[l];
                t[rt][1] = t[rt][2] = 0.;
            } else {
                for (int c = 0; c <= 2; ++ c) {
                    t[rt][c] = t[rt << 1][c] + t[rt << 1 | 1][c];
                }
            }
        }
    }

    void modify(int L,int R,int dt,int l,int r,int rt) {
        if (r < L || R < l) return ;
        if (L <= l && r <= R) {
            tag[rt] += dt;
            up(l,r,rt);
            return ;
        }
        int mid = l + r >> 1;
        modify(L,R,dt,l,mid,rt << 1);
        modify(L,R,dt,mid + 1,r,rt << 1 | 1);
        up(l,r,rt);
    }
} sgt;

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        int n;
        scanf("%d",&n);
        ss.clear();
        std::vector<Event> events;
        for (int i = 0; i < n; ++ i) {
            double a,b,c,d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            ss.push_back(b);
            ss.push_back(d);
            events.push_back(Event{a,b,d,1});
            events.push_back(Event{c,b,d,-1});
        }
        ss.push_back(100000. + 1);
        ss.done();
        std::sort(ALL(events));
        sgt.build(0,ss.size() - 2,1);
        double answer = 0;
        double pre = 0;
        for (auto e : events) {
            answer += sgt.t[1][2] * (e.p - pre);
            sgt.modify(ss.get(e.l),ss.get(e.r) - 1,e.sig,0,ss.size() - 2,1);
            pre = e.p;
        }
        printf("%.2f\n",answer + 1e-8);
    }
}

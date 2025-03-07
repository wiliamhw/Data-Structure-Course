#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define mod 31011
using namespace std;

vector<pair<int, pair<int, int>>> edge;
int M[105][105], p[105];
int n, m;

int findr(int x) {
    if (p[x]<0)
        return x;
    return p[x] = findr(p[x]);
}

long long det(vector<pair<int, int>> &es) {
    vector<int> hash;
    for (int i = 0; i < es.size(); i++) {
        hash.push_back(es[i].first);
        hash.push_back(es[i].second);
    }
    sort(hash.begin(), hash.end());
    hash.erase(unique(hash.begin(), hash.end()), hash.end());
    int n= hash.size();
    n--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = 0;
        }
    }
    for (int i = 0; i < es.size(); i++) {
        int u = lower_bound(hash.begin(), hash.end(), es[i].first) - hash.begin();
        int v = lower_bound(hash.begin(), hash.end(), es[i].second) - hash.begin();
        M[u][u]++;
        M[v][v]++;
        M[u][v]--;
        M[v][u]--;
    }
    long long ans = 1LL;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (M[j][i]) {
                ans *= -1;
                long long t = M[i][i] / M[j][i];
                for (int k = i; k < n; k++) {
                    M[i][k] = (M[i][k] - M[j][k] * t) % mod;
                    M[i][k] ^= M[j][k];
                    M[j][k] ^= M[i][k];
                    M[i][k] ^= M[j][k];
                }
            }
        }
        if(M[i][i] == 0) {
          return 0;
        }
        else ans = (ans * M[i][i]) % mod;
    }
    return (ans % mod + mod) % mod;
}

int main() {
    while (~scanf("%d %d",&n,&m)) {
        edge.clear();
        memset(p, -1, sizeof(p));
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d",&u,&v,&w);
            u--;
            v--;
            edge.push_back(make_pair(w, make_pair(u, v)));
        }
        long long ans = 1LL;
        sort(edge.begin(), edge.end());
        int l, r = 0;
        while(r < edge.size()) {
            l = r++;
            while(r < edge.size() && edge[r].first == edge[l].first)
                r++;
            for(int i = l; i < r; i++) {
                int &u=edge[i].second.first;
                int &v=edge[i].second.second;
                u = findr(u);
                v = findr(v);
            }
            for(int i = l; i < r; i++) {
              int u = edge[i].second.first;
              int v = edge[i].second.second;
              u = findr(u);
              v = findr(v);
              if(u != v)
                p[u] = v;
            }
            for(int i = 0; i < n; i++) {
                if(p[i] < 0) {
                    vector<pair<int,int> >es;
                    for(int j = l; j < r; j++)
                    {
                        int u = edge[j].second.first;
                        int v = edge[j].second.second;
                        if(findr(u) == i && findr(v) == i)
                        es.push_back(make_pair(u,v));
                    }
                    ans = (ans * det(es)) % mod;
                }
            }
        }
        int cot = 0;
        for (int i = 0; i < n; i++) {
            if (p[i] < 0) 
                cot++;
        }
        if (cot > 1) {
            puts("0");
            continue;
        }
        printf("%lld\n",(ans % mod + mod) % mod);
    }
}
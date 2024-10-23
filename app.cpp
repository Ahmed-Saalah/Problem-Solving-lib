#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DSU
{
    vector<int> parent , sz;
    vector<int> min_val, max_val;
    int max_size , component;

    DSU(int n)
    {
         parent = sz = min_val = max_val = vector<int>(n + 1);
        for(int i = 1 ; i <= n ; i++) {
            parent[i] = i;
            sz[i] = 1;
            //min_val[i] = max_val[i] = i; // Initialize min and max values 
        }
        
        max_size = 1 , component = n;
    }

    int find(int x)
    {
        if(parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    void uni(int x , int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return;
        if(sz[y] > sz[x])
            swap(x , y);
        parent[y] = x;
        sz[x] += sz[y];
        max_size = max(max_size , sz[x]);
        component--;
        min_val[x] = min(min_val[x], min_val[y]);
        max_val[x] = max(max_val[x] , max_val[y]);
    }



};

const int N = 1e5 + 5;
vector<int> g[N];
vector<int> depth(N , 0);

void dfs(int v , int p) 
{
    for(auto &u : g[v]) {
        if(u == p) continue;
        depth[u] = 1 + depth[v];
        dfs(u , v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n , m;
    cin >> n >> m;
    DSU dsu(n);
    vector<pair<long long , pair<int , int>>> MST;
    long long total_weight = 0;
    for(int i = 0; i < m ; i++)
    {
        int u , v;
        long long w;
        cin >> u >> v >> w;
        MST.push_back({w , {u , v}});
    }
    sort(MST.begin() , MST.end());
    for(int i = 0; i < m; i++)
    {
        int u = MST[i].second.first;
        int v = MST[i].second.second;
        long long w = MST[i].first;
        if(dsu.find(u) == dsu.find(v)) continue;
        dsu.uni(u , v);
        total_weight += w;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    //1- lowest amount that has to be spent to link all the cities
    cout << total_weight << '\n';

    //2- largest direct distance between two cities after building the roads

    // find max depth
    dfs(1 , -1);
    
    int node = max_element(depth.begin() , depth.end()) - depth.begin();
   
    // diameter
    depth[node] = 0;
    dfs(node , -1);

    cout << *max_element(depth.begin() , depth.end());
    
}
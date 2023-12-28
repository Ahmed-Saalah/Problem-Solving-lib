#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> parent , sz;
    int max_size , component;

    DSU(int n)
    {
        parent = sz = vector<int>(n + 1);
        for(int i = 1 ; i <= n ; i++)
            parent[i] = i , sz[i] = 1;  
        
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
    }


};


void solve()
{
    int n;
    cin >> n;
    DSU dsu(n);
    vector<pair<int , int>> removed , added;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        if (dsu.find(u) == dsu.find(v))
            removed.push_back({u,v});
        else dsu.uni(u,v);
    }

    for(int u = 1; u <= n ; u++)
    {
        for (int v = u + 1; v <= n;v++)
        {
            if(dsu.find(u) == dsu.find(v)) continue; 

            // edge should be added
            // because u and v are part of different connected components
            added.push_back({u , v});
            dsu.uni(u,v); // so that we are not introducing extra redundant edges
        }
    }

    cout<<added.size()<<'\n';
    for (int i = 0 ;i < added.size(); i++)
        cout<<removed[i].first<<" "<<removed[i].second<<" "<<added[i].first<<" "<<added[i].second<<'\n';
}


int main() 
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);cout.tie(NULL);
    solve();
    return 0;
}
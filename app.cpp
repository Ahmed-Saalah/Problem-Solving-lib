#include <bits/stdc++.h>
using namespace std;

template <class T> struct fenwick {
    int n;
    vector<T> a, bit;

    fenwick() {}

    fenwick(int _n) : n(_n + 1), a(n + 1), bit(n + 1) {} 

    void add(int i, T x) {
        a[i] += x;
        for (++i; i <= n; i += i & -i) bit[i] += x;
    }

    void set(int i, T val) {
        add(i, val - a[i]);
    }

    T query(int i) {
        T sum = 0;
        for (++i; i >= 1; i -= i & -i) sum += bit[i];
        return sum;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    fenwick<int> fen(n);
    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
        fen.add(i , a[i]);
    }
    cout << fen.query(1 , 3);
  
}
int main() 
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
        cout << '\n';
    }
    return 0; 
} 

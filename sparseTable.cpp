#include <iostream>
#include <vector>
#define ll long long
using namespace std;

struct SPARSETABLE
{
    vector<vector<int>> sp;
    
    int merge(int a , int b) 
    {
        return max(a , b);
    }

    void build(const vector<int>& A)
    {
        int n = A.size();
        sp = vector<vector<int>>(__lg(n) + 1 , vector<int>(n));
        sp[0] = A;
        
        for(int mask = 1 ; (1 << mask) <= n ; mask++)
        {
            for(int i = 0 ; i + (1 << mask) <= n ; i++)
            {
                 sp[mask][i] = merge(
                    sp[mask - 1][i] ,
                    sp[mask - 1][i + (1 << (mask - 1))]
                );
            }
        }
    }

    int query(int l , int r) 
    {
        int mask = __lg(r - l + 1);
        return merge(
            sp[mask][l] ,
            sp[mask][r - (1 << mask) + 1]
        );
    }

    int querylg(int l , int r) 
    {
        int res = 0;
        int len = r - l + 1;
        for(int mask = 0 ; l <= r ; mask++)
        {
            if(len >> mask & 1) {
                res = merge(sp[mask][l] , res);
                l += 1 << mask;
            }
        }

        return res;
    }
};



void solve()
{
    int n , m , q;
    cin >> n >> m;
    vector<int> A(m);
    for(auto &a : A)
        cin >> a;
    cin >> q;    

    SPARSETABLE sparseTable;
    sparseTable.build(A);
    
    while(q--)
    {
        int SX , SY , EX , EY , K;
        cin >> SX >> SY >> EX >> EY >> K;
        SY-- , EY--;
        if(SY > EY) {
            swap(SY , EY);
            swap(SX , EX);
        }

        int maxUpPoint = SX + (n - SX) / K * K;
        int MaxBlocked = sparseTable.query(SY , EY);

        if((SX - EX) % K != 0 || (SY - EY) % K != 0) 
        {
            cout << "NO\n";
            continue;
        }
      
        if(maxUpPoint > MaxBlocked)
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);cout.tie(NULL);

    int t;
    t = 1;
    // cin >> t;
    while(t--)
        solve();

    return 0;
}


#include <bits/stdc++.h>
#define ll long long
using namespace std;

/*
To find if exist subset from range L to R the ANDING == K
*/
class sparse_table // 1 index
{
private:
    ll n;
    vector<ll> v, LOG;
    vector<vector<ll>> dp;

    ll merge(ll a, ll b)
    {
        // min , max , gcd , lcm , sum
        return a & b; 
    }

    void preCount()
    {
        for (ll i = 2; i <= n; i++)
        {
            LOG[i] = LOG[i >> 1] + 1;
        }
    }

    void build()
    {
        for (ll i = 0; i < n; i++)
        {
            dp[i][0] = v[i];
        }
        for (ll mask = 1; (1 << mask) <= n; mask++)
        {
            for (ll i = 0; i + (1 << mask) <= n; i++)
            {
                dp[i][mask] = merge(dp[i][mask - 1], dp[i + (1 << (mask - 1))][mask - 1]);
            }
        }
    }

public:
    sparse_table(vector<ll> v)
    {
        this->v = v;
        n = v.size();
        LOG.assign(n + 1, 0);
        dp.assign(n + 1, vector<ll>(22, 0));
        preCount();
        build();
    }

    ll query(ll l, ll r)
    {
        ll mask = LOG[r - l + 1];
        return merge(dp[l][mask], dp[r - (1 << mask) + 1][mask]);
    }
};

void solve()
{
    ll n, k, q;
    cin >> n >> k >> q;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
        if ((v[i] & k) != k)
            v[i] = LLONG_MAX;
    }

    sparse_table st(v);
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        if (st.query(--l, --r) == k)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false),
    cout.tie(NULL), cin.tie(NULL);

    solve();

    return 0;
}
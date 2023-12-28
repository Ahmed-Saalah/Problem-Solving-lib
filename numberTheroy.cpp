#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;
#define ll long long
#define ld long double
#define pqg priority_queue<int,vector<int>, greater<int>>
#define pqgp priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>
#define all(x) x.begin(),x.end()
#define allr(v) ((v).rbegin()),((v).rend())
#define UniqueSort(v) sort(all(v));v.erase(unique(all(v)),v.end()) 
#define show(v) for(int i=0;i<v.size();i++)cout<<v[i]<<' ';cout<<endl;
#define see(x) cout<< #x << " = " << x << endl;
#define fx fixed<<setprecision
#define pi 3.141592653589793238462643383279502884197
#define MOD 1000000007
#define oo INT_MAX
#define OO LLONG_MAX
#define test_case int t;cin>>t;while(t--)
#define flash ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL)
const int dx[8]={0, 0, 1, -1, 1, -1, -1, 1};
const int dy[8]={1, -1, 0, 0, 1, -1, 1, -1}; 
char di[] = {'R', 'L', 'D', 'U'};
const unsigned ll N = 2e6 + 10;
/*
Don't be lazy in thinking
Think twice, code once
 * Think of different approaches to tackle a problem: write them down.
 * Think of different views of the problem. don't look from only one side.
 * don't get stuck in one approach.
 * common mistakes: - over_flow
 *                  - out_of_bound index
 *                  - infinite loop
 *                  - corner cases
 *                  - double counting.
 *
 * leeeeeSSSSSGOOOOOO ♡
*/
ll mul(ll a ,ll b, ll m)
{
   return ((a%m)*(b%m))%m;
}
ll gcd(ll x, ll y)
{
    return(!y) ? x : gcd(y, x%y);
}
ll lcm(ll x, ll y)
{
    return((x / gcd(x, y))*y);
}
bool isprime(ll n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i+=6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
ll fastPower(ll base , ll exp , ll m)
{
    ll res = 1;
    while(exp > 0)
    {
        if(exp & 1)
            res = (base % m * res % m) % m;
        base = (base % m * base % m) % m;
        exp /= 2;
    }
    return res;
}

ll fastpowerRec(ll a , ll b) {
    if(!b) return 1;
    ll ret = fastpowerRec(a, b / 2);
    return (b & 1 ? (((ret*ret)%MOD)*a) %MOD : ret * ret % MOD);
}

void primeFactors(ll n)
{
    vector<ll>primes;
    for(ll i = 2 ; i * i <= n ; i++)
    {
        if(n % i == 0) {
            primes.push_back(i);
            while(n % i == 0)
                n /= i;
        }
    }
    if(n > 1)
        primes.push_back(n);
}

bool prime[N + 2];
vector<int>primes;
void sieve()
{   // O(N log log N)
    memset(prime , true , sizeof(prime));
    prime[2] = true;
    for(int p = 2; p <= N ; p++) {
        if(prime[p]) {
            primes.push_back(p);
            for(int i = p * 2 ; i <= N ; i += p)
                prime[i] = false;
        }
    }
}

bool composite[N];
void linear_sieve()
{
    composite[0] = composite[1] = 1;
    for(int i = 2; i < N ; i++)
    {
        if(!composite[i]) primes.push_back(i);
        for(int j =0 ;j < primes.size() && i * primes[j] < N ; j++)
        {
            composite[i * primes[j]] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

int spf[N]; // smallest prime factor
void sieveSPF()
{
    for(int i = 1; i <= N ; i++)
        spf[i] = i; 
    for(int p = 2; p < N ; p++) {
        if(spf[p] == p) {
            for(int i = p * 2 ; i <= N ; i += p)
                if(spf[i] == i) // without this condition get the greatest prime factor
                    spf[i] = p;
        }
    }
    
}

map<ll,int>factorization;
void factorizeSPF(int x)
{
    /*
    Note : call sieve SPf function
    This function count prime factor for number X frequency in the map factorization
    map.first = primeFactor, map.second = frequency
    */
    while(x > 1)
    {
        factorization[spf[x]]++;
        x /= spf[x];
    }
    if(x > 1) 
        factorization[x]++;
}

void factorize(ll x)
{
    for(auto p : primes) {
        if(p * p > x)
            break;
        while(x % p == 0) {
            factorization[p]++;
            x /= p;
        }
    }
    if(x != 1) 
        factorization[x]++;
}

vector<pair<ll , ll>> vFactorization;
vector<int> divisors;
void getDivisorsBack(int index , ll divisor)
{
    // Get divisor form prime factor using Backtrack
    // q root time
    if(index == vFactorization.size()) {
        divisors.push_back(divisor);
        return;
    }
    for(int i = 0 ; i <= vFactorization[index].second; i++) {
        getDivisorsBack(index + 1 , divisor);
        divisor = divisor * 1LL * vFactorization[index].first;
    }
}

vector<int> getDivisors(int n)
{
    vector<int>ret;
    for(int i = 1; i * i <= n ; i++) {
        if(n % i == 0){
            ret.push_back(i);
            if(i != n/i)
                ret.push_back(n/i);
        }
    }
    return ret;
}

void update() 
{
    factorization.clear();
    divisors.clear();
    vFactorization.clear();
}

void solve() 
{
    
 
}
int main() 
{
    flash;
    test_case{ solve(); }
    // solve(); 
    return 0; // ♡ ♡ ♡
} 
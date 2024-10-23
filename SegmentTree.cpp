#include <bits/stdc++.h>
using namespace std;
const unsigned int N = 1e5 + 5;

struct Node
{
    long long mn;
    Node() 
    {
        mn = 1e18;
    }

    Node(int val) 
    {
        mn = val;
    }

    void change(int x) 
    {
        mn = x;
    }
};

struct segTree
{
    int tree_size;
    vector<Node> segData;

    segTree(int n) 
    {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        segData.assign(tree_size * 2 , Node());   
    }

    Node merge(Node &lf , Node &ri) 
    {
        Node ans = Node();
        ans.mn = min(lf.mn , ri.mn);
        return ans;
    }

    void init(vector<int>& arr , int ni , int lx , int rx)
    {
        if(rx - lx == 1)
        {
            if(lx < arr.size())
                segData[ni] = Node(arr[lx]); 
            return;
        }

        int mid = (lx + rx) / 2;
        init(arr , 2 * ni + 1 , lx , mid);
        init(arr , 2 * ni + 2 , mid , rx);

        segData[ni] = merge(segData[2 * ni + 1] , segData[2 * ni + 2]);

    }

    void init(vector<int>& arr)
    {
        init(arr , 0 , 0 , tree_size);
    }

    void set(int idx , int val , int ni , int lx , int rx) // 0 index , R not included
    {
        if(rx - lx == 1) {
            segData[ni].change(val);
            return;
        }

        long long mid = (lx + rx) / 2;
        if(idx < mid) {
            set(idx , val , 2 * ni + 1 , lx , mid);
        }
        else { 
            set(idx , val , 2 * ni + 2 , mid , rx);
        }

        segData[ni] = merge(segData[2 * ni + 1] , segData[2 * ni + 2]);
    }

    void set(int idx , int val) 
    {
        set(idx , val , 0 , 0 , tree_size);
    }

    Node get(int l , int r , int ni , int lx , int rx) // 0 index , R not included
    {
        if(lx >= l && rx <= r)
            return segData[ni];

        if(lx >= r || rx <= l)
            return Node(); // Invalid value

        int mid = (lx + rx) / 2;
        Node lf = get(l , r , 2 * ni + 1 , lx , mid);
        Node ri = get(l , r , 2 * ni + 2 , mid , rx);

        return merge(lf , ri);

    }

    long long get(int l , int r) 
    {
        return get(l , r , 0 , 0 , tree_size).mn;
    } 

};



void solve()
{
    int n , q;
    cin >> n >> q;
    vector<int> a(n);

    for(int i = 0 ; i < n; i++) {
        cin >> a[i];
    }
    
    segTree st = segTree(n);
    st.init(a);
 
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1) {
            int idx , val;
            cin >> idx >> val;
            st.set(idx , val);
        }
        else {
            int l , r;
            cin >> l >> r;
            cout << st.get(l , r) << endl;
        }
    }
    

}
int main() 
{
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
        cout << '\n';
    }
    return 0; 
} 


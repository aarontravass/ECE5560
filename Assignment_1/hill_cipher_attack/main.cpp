#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int
#define forn(i,n)for(ll i=0;i<(n);i++)
#define forn_rev(i,n)for(ll i=(n)-1;i>=0;i--)
#define for1n(i,n) for(ll i=1;i<=(n);i++)
#define print2D(arr) forn(i,arr.size()) { forn(j,arr[0].size()) { cout<<arr[i][j]<<" "; } cout<<endl;}
#define vec2D vector<vector<ll>>
using namespace std;

vec2D getCofactor(vec2D mat, vec2D temp, ll p, ll q, ll n)
{
    ll i = 0, j = 0;
    forn(row,n)
    {
        forn(col,n)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return temp;
}

ll determinantOfMatrix(vec2D mat, ll n,ll len)
{
    ll D = 0;
    if (n == 1)
        return mat[0][0];

    vec2D temp(len,vector<ll>(len));
    ll sign = 1;
    forn(f,n)
    {
        temp=getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1, len);
        sign = -sign;
    }
    return D;
}


vec2D convertStrToSQMat(string s)
{
    ll sz=ceil(sqrt(s.length()));
    vec2D mat(sz,vector<ll>(sz,0));
    ll cnt=0;
    forn(i,sz) forn(j,sz) mat[i][j]=(s[(cnt++)%s.length()]-'A');
    return mat;
}

ll add(ll a,ll b)
{
    return (a+b)%26;
}
ll mul(ll a,ll b)
{
    return (a*b)%26;
}

vec2D matMul(vec2D a,vec2D b)
{
    vec2D ans(a.size(),vector<ll>(b[0].size(),0));
    forn(i,a.size())
    {
        forn(j,b[0].size())
        {
            forn(k,b.size())
            {
                ans[i][j]=add(ans[i][j],mul(a[i][k],b[k][j]));
            }
        }
    }
    return ans;
}

vec2D plainToMat(string plaintext)
{
    vec2D ans(plaintext.size(),vector<ll>(1,0));
    forn(i,plaintext.size()) ans[i][0]=plaintext[i]-'A';
    return ans;
}
string matToString(vec2D m)
{
    string ans="";
    forn(i,m.size()) forn(j,m[0].size()) ans+=char(m[i][j]+65);
    return ans;
}

ll findInDet(ll det)
{
    forn(i,det) if(mul(det,i)==1)
        return i;
    return -1;
}
vec2D mulMatbyNum(vec2D mat,ll num)
{
    forn(i,mat.size())
    forn(j,mat[0].size())
    {
        while(mat[i][j]<0)
            mat[i][j]+=26;
        mat[i][j]=mul(mat[i][j],num);

    }

    return mat;
}

vec2D adjoint(vec2D A)
{
    vec2D adj(A.size(),vector<ll>(A.size(),0));
    vec2D temp(A.size(),vector<ll>(A.size(),0));
    if (A[0].size() == 1)
    {
        adj[0][0] = 1;
        return adj;
    }
    ll sign = 1;
    forn(i,A[0].size())
    {
        forn(j,A[0].size())
        {
            temp=getCofactor(A, temp, i, j, A[0].size());
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinantOfMatrix(temp, A[0].size()-1,A[0].size()));
        }
    }
    return adj;
}

vec2D inverse(vec2D adj,ll det)
{
    return mulMatbyNum(adj,findInDet(det));
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

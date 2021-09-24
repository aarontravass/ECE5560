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


vec2D convertStrToSQMat(string s,ll n)
{
    vec2D mat(n,vector<ll>(n,0));
    ll cnt=0;
    forn(i,n) forn(j,n) mat[i][j]=(s[(cnt++)%s.length()]-'A');
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
    for1n(i,25) if(mul(det,i)==1)
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

string preprocess(string s){
    string ans="";
    forn(i,s.size()){
        ll temp=(s[i]-'A');
        if(temp<=25 && temp>=0) ans+=s[i];
    }
    return ans;
}

int main()
{
    ll n;
    string key,plaintext;
    cout<<"Enter a key and plain text string separated by new lines (All upper case alphabets)"<<endl;
    cin>>key>>plaintext;
    cout<<"Now enter the size of a square matrix. Ex 2 for 2X2, 3 for 3X3"<<endl;
    cin>>n;
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
    plaintext=preprocess(plaintext);
    key=preprocess(key);
    if(n*n<key.size()){
        cout<<"The key length should be less than "<<n*n<<endl;
        return 0;
    }
    ll added_chars=0;
    while(1)
    {
        if(plaintext.size()%n!=0)
        {
            plaintext+='X';
            added_chars++;
        }
        else
            break;
    }

    vector<vector<ll>> mat=convertStrToSQMat(key,n);
    ll det=(determinantOfMatrix(mat,mat.size(),mat.size()));
    while(det<0) det+=26;
    if(det==0)
    {
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    if(det%2==0 || det%13==0){
        cout<<"The key is invalid"<<endl;
        return 0;
    }
    if(findInDet(det)<0){
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    string full_enc="",full_dec="";
    for(ll l=0; l<plaintext.size(); l+=n)
    {
        string s="";
        for(ll j=l; j<l+n; j++)
            s+=plaintext[j];
        vec2D plainMat=plainToMat(s);
        vec2D ans=matMul(mat,plainMat);
        full_enc+=matToString(ans);
        vec2D inv=inverse(adjoint(mat),det);
        vec2D dec=matMul(inv,ans);
        full_dec+=matToString(dec);
    }
    string final_enc="",final_dec="";
    forn(i,full_dec.size()-added_chars) final_dec+=full_dec[i];
    cout<<"Encrypted string is - "<<full_enc<<endl;
    cout<<"Decrypted string is - "<<final_dec<<endl;






    return 0;
}

#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int
#define forn(i,n)for(ll i=0;i<(n);i++)
#define forn_rev(i,n)for(ll i=(n)-1;i>=0;i--)
#define for1n(i,n) for(ll i=1;i<=(n);i++)
#define print2D(arr) forn(i,arr.size()) { forn(j,arr[0].size()) { cout<<arr[i][j]<<" "; } cout<<endl;}
#define vec2D vector<vector<ll>>
#define lapsed(t2,t1) chrono::duration_cast<chrono::microseconds>(t2-t1).count()
#define time Clock::now()
typedef std::chrono::high_resolution_clock Clock;

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

vec2D fetchMatFromStrAndSz(string s, int n){
    vec2D mat(n,vector<ll>(n,0));
    int cnt=0;
    forn(i,n) forn(j,n) mat[i][j]=s[cnt++]-'A';
    return mat;
}

bool matEqual(vec2D a,vec2D b){
    forn(i,a.size()) forn(j,a.size()) if(a[i][j]!=b[i][j]) return false;
    return true;
}

pair<bool,string> subset(string s,int i, int j){
    if(j>=s.size()){
        return make_pair(false,"");
    }
    string ans="";
    for(int itr=i;itr<=j;itr++) ans+=s[itr];
    return make_pair(true,ans);
}

bool testKey(vec2D key,string ciphertext,string plaintext,int n){
    for(int i=0;i<plaintext.size();i+=n*n){
        pair<bool,string> cipherSub=subset(ciphertext,i,i+n*n);
        if(!cipherSub.first) return true;
        pair<bool,string> plainSub=subset(plaintext,i,i+n*n);
        if(!plainSub.first) return true;
        vec2D plain=fetchMatFromStrAndSz(plainSub.second,n);
        vec2D cipher=fetchMatFromStrAndSz(cipherSub.second,n);
        vec2D new_ciph=matMul(plain,key);
        if(!matEqual(new_ciph,cipher)) return false;
    }
    return true;
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
    ios_base::sync_with_stdio(0);
    string ciphertext,plaintext;
    ll n;
    cout<<"Enter a plain text, cipher text and the matrix size, separated by new lines"<<endl;
    cin>>ciphertext>>plaintext>>n;
    auto t1=time;
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
    plaintext=preprocess(plaintext);
    ciphertext=preprocess(ciphertext);
    if(n*n>ciphertext.size()){
        cout<<"Cipher text must have size of at least "<<n*n<<" chars"<<endl;
        return 0;
    }
    if(n*n>plaintext.size()){
        cout<<"Plain text must have size of at least "<<n*n<<" chars"<<endl;
        return 0;
    }
    vec2D plain=fetchMatFromStrAndSz(plaintext,n);
    vec2D cipher=fetchMatFromStrAndSz(ciphertext,n);
    ll plain_det=(determinantOfMatrix(plain,n,n));
    while(plain_det<0) plain_det+=26;
    if(plain_det==0)
    {
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    if(plain_det%2==0 || plain_det%13==0){
        cout<<"The key is invalid"<<endl;
        return 0;
    }
    if(findInDet(plain_det)<0){
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    vec2D inv_plain=inverse(adjoint(plain),plain_det);
    vec2D key=matMul(inv_plain,cipher);
    if(testKey(key,ciphertext,plaintext,n)){
        cout<<"The key is - "<<matToString(key)<<endl;
    }
    else cout<<"A key could not be found!"<<endl;
    auto t2=time;
    cout<<endl<<"Time lapsed: "<<lapsed(t2,t1)<<" micro seconds"<<endl;


    return 0;
}

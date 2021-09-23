#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int
#define forn(i,n)for(ll i=0;i<(n);i++)
#define forn_rev(i,n)for(ll i=(n)-1;i>=0;i--)
#define for1n(i,n) for(ll i=1;i<=(n);i++)
#define print2D(arr) forn(i,arr.size()) forn(j,arr[0].size()) cout<<arr[i][j]<<" "; cout<<endl;
#define vec2D vector<vector<int>>
using namespace std;

void getCofactor(vector<vector<int>> &mat, vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;
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
}

int determinantOfMatrix(vector<vector<int>> mat, int n,int len)
{
    int D = 0;
    if (n == 1)
        return mat[0][0];

    vector<vector<int>> temp(len,vector<int>(len));

    int sign = 1;
    forn(f,n)
    {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1, len);
        sign = -sign;
    }
    return D;
}

bool isInvertible(vector<vector<int>> mat, int n)
{
    if (determinantOfMatrix(mat, n,2) != 0)
        return true;
    else
        return false;
}

vector<vector<int>> convertStrToSQMat(string s)
{
    int sz=ceil(sqrt(s.length()));
    vector<vector<int>> mat(sz,vector<int>(sz,0));
    int cnt=0;
    forn(i,sz) forn(j,sz) mat[i][j]=(s[(cnt++)%s.length()]-'A');
    return mat;
}

int add(int a,int b){
    return (a+b)%26;
}
int mul(int a,int b){
    return (a*b)%26;
}

vec2D matMul(vec2D a,vec2D b){
    vec2D ans(a.size(),vector<int>(b[0].size(),0));
    forn(i,a.size()){
        forn(j,b[0].size()){
            forn(k,b.size()){
                ans[i][j]=add(ans[i][j],mul(a[i][k],b[k][j]));
            }
        }
    }
    return ans;
}

vec2D plainToMat(string plaintext){
    vec2D ans(plaintext.size(),vector<int>(1,0));
    forn(i,plaintext.size()) ans[i][0]=plaintext[i]-'A';
    return ans;
}
string matToString(vec2D m){
    string ans="";
    forn(i,m.size()) forn(j,m[0].size()) ans+=char(m[i][j]+65);
    return ans;
}
int main()
{
    int n;
    string key,plaintext;
    cin>>key>>plaintext;
    int sz=ceil(sqrt(key.length()));
    if(sz!=plaintext.size()) {
        cout<<"Input a plaintext with valid length"<<endl;
        return 0;
    }
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
    vector<vector<int>> mat=convertStrToSQMat(key);
    if(!isInvertible(mat,mat.size())){
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    vec2D plainMat=plainToMat(plaintext);
    vec2D ans=matMul(mat,plainMat);
    cout<<"Encrypted string is - "<<matToString(ans)<<endl;





    return 0;
}

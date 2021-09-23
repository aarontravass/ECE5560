#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int
#define forn(i,n)for(ll i=0;i<(n);i++)
#define forn_rev(i,n)for(ll i=(n)-1;i>=0;i--)
#define for1n(i,n) for(ll i=1;i<=(n);i++)
#define print2D(arr) forn(i,arr.size()) { forn(j,arr[0].size()) { cout<<arr[i][j]<<" "; } cout<<endl;}
#define vec2D vector<vector<int>>
using namespace std;

vec2D getCofactor(vec2D mat, vec2D temp, int p, int q, int n)
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
    return temp;
}

int determinantOfMatrix(vec2D mat, int n,int len)
{
    int D = 0;
    if (n == 1)
        return mat[0][0];

    vec2D temp(len,vector<int>(len));
    int sign = 1;
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
    int sz=ceil(sqrt(s.length()));
    vec2D mat(sz,vector<int>(sz,0));
    int cnt=0;
    forn(i,sz) forn(j,sz) mat[i][j]=(s[(cnt++)%s.length()]-'A');
    return mat;
}

int add(int a,int b)
{
    return (a+b)%26;
}
int mul(int a,int b)
{
    return (a*b)%26;
}

vec2D matMul(vec2D a,vec2D b)
{
    vec2D ans(a.size(),vector<int>(b[0].size(),0));
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
    vec2D ans(plaintext.size(),vector<int>(1,0));
    forn(i,plaintext.size()) ans[i][0]=plaintext[i]-'A';
    return ans;
}
string matToString(vec2D m)
{
    string ans="";
    forn(i,m.size()) forn(j,m[0].size()) ans+=char(m[i][j]+65);
    return ans;
}

int findInDet(int det)
{
    forn(i,det) if(mul(det,i)==1)
        return i;
    return -1;
}
vec2D mulMatbyNum(vec2D mat,int num)
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
    vec2D adj(A.size(),vector<int>(A.size(),0));
    vec2D temp(A.size(),vector<int>(A.size(),0));
    if (A[0].size() == 1)
    {
        adj[0][0] = 1;
        return adj;
    }
    int sign = 1;
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

vec2D inverse(vec2D adj,int det)
{
    return mulMatbyNum(adj,findInDet(det));
}
int main()
{
    int n;
    string key,plaintext;
    cin>>key>>plaintext;
    int sz=ceil(sqrt(key.length()));
    int added_chars=0;
    while(1)
    {
        if(plaintext.size()%sz!=0)
        {
            plaintext+='x';
            added_chars++;
        }
        else
            break;
    }
    cout<<plaintext<<endl;
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);
    vector<vector<int>> mat=convertStrToSQMat(key);
    int det=determinantOfMatrix(mat,mat.size(),mat.size());

    if(det==0)
    {
        cout<<"The key is not invertible"<<endl;
        return 0;
    }
    string full_enc="",full_dec="";
    for(int l=0; l<plaintext.size(); l+=sz)
    {
        cout<<l<<endl;
        string s="";
        for(int j=l; j<l+sz; j++)
            s+=plaintext[j];
        vec2D plainMat=plainToMat(s);
        vec2D ans=matMul(mat,plainMat);
        full_enc+=matToString(ans);
        vec2D inv=inverse(adjoint(mat),det);
        vec2D dec=matMul(inv,ans);
        full_dec+=matToString(dec);
    }
    cout<<"Encrypted string is - "<<full_enc<<endl;
    string final_dec="";
    forn(i,full_dec.size()-added_chars) final_dec+=full_dec[i];
    cout<<"Decrypted string is - "<<final_dec<<endl;






    return 0;
}

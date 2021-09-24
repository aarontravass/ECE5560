#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int

using namespace std;

ll power(ll x, ull y, ll p)
{
    ll res = 1;
    x = x % p;

    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}


ll millerTest(ll d, ll n)
{
    srand(time(0));
    ll a = 2 + rand() % (n - 4);
    ll x = power(a, d, n);
    if (x == 1  || x == n-1)
        return 0;
    while (d != n-1)
    {
        ll y = (x * x) % n;
        d *= 2;

        if (y == 1)
            return __gcd(x-1,n);
        x=y;
        if (x == n-1)
            return 0;
    }


    return 1;
}


pair<ll,bool> isPrime(ll n, ll k)
{

    if (n <= 1)
        return make_pair(1,false);
    if(n == 4)
        return make_pair(2,false);
    if (n <= 3)
        return make_pair(0,true);

    ll d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    for (ll i = 0; i < k; i++){
        ll w=millerTest(d, n);
        if (w>0) return make_pair(w,false);
    }

    return make_pair(0,true);
}

ll findDivisor(ll n){
    if(n%2==0) return 2;
    for(ll i=3;i*i<=n;i+=2){
        if(n%i==0) return i;
    }
}
int main()
{


    ll n;
    float e;
    cout<<"Enter a number and the error margin separated by a new line"<<endl;
    cin>>n>>e;
    ll no_rounds=ceil(log10(e/100.0)/log10(0.25));
    pair<ll,bool> ans=isPrime(n, no_rounds);
    if(ans.second) cout<<"TRUE"<<endl;
    else cout<<"FALSE. Witness is "<<ans.first<<".\nOne of the divisor of this number is "<<findDivisor(n)<<endl;

    return 0;
}

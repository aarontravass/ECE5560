#include <bits/stdc++.h>

using namespace std;

int power(int x, unsigned int y, int p)
{
    int res = 1;
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


int millerTest(int d, int n)
{
    srand(time(0));
    int a = 2 + rand() % (n - 4);
    int x = power(a, d, n);
    if (x == 1  || x == n-1)
        return 0;
    while (d != n-1)
    {
        int y = (x * x) % n;
        d *= 2;

        if (y == 1)
            return __gcd(x-1,n);
        x=y;
        if (x == n-1)
            return 0;
    }


    return 1;
}


pair<int,bool> isPrime(int n, int k)
{

    if (n <= 1)
        return make_pair(1,false);
    if(n == 4)
        return make_pair(2,false);
    if (n <= 3)
        return make_pair(0,true);

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    for (int i = 0; i < k; i++){
        int w=millerTest(d, n);
        if (w>0) return make_pair(w,false);
    }

    return make_pair(0,true);
}

int main()
{


    int n;
    float e;
    cin>>n>>e;
    int no_rounds=ceil(log10(e/100.0)/log10(0.25));
    cout<<"No of rounds: "<<no_rounds<<endl;
    pair<int,bool> ans=isPrime(n, no_rounds);
    if(ans.second) cout<<"TRUE"<<endl;
    else cout<<"FALSE. Witness is "<<ans.first<<endl;

    return 0;
}

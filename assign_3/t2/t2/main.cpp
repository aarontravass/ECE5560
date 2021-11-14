#include <bits/stdc++.h>
#define ll long long int
#define ld long double
#define ull unsigned long long int
#define KEYSIZE 16
using namespace std;

int main()
{
    int i;

    ll mid_timer=1523986729;
    ll start_t = mid_timer - (2*60*60);
    ll end_t = mid_timer + (2*60*60);
    cout<<start_t<<endl<<end_t<<endl;
    string keys="";
    for (ll t=start_t; t<=end_t; t++)
    {
        string key="";
        srand (t);
        for (i = 0; i< KEYSIZE; i++)
        {
            char temp[KEYSIZE];
            sprintf(temp,"%.2x", (unsigned char)rand()%256);
            key+= temp;

        }
        keys=keys+key+"\n";
    }
    fstream keysFile;
    keysFile.open("keys.txt", ios::out);
    keysFile<<keys;
    keysFile.close();

    return 0;
}

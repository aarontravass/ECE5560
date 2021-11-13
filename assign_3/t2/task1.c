//
//  task1.c
//
//
//  Created by Angelos Stavrou
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEYSIZE 16

int main(void)
{
    int i;
    char key[KEYSIZE];
    printf("%lld\n", (long long) time(NULL));
int mid_timer=1523986729;
    int start_t = mid_timer - (2);
    int end_t = mid_timer + (2);
    for (int t=start_t; t<=end_t; t++)
    {

        srand (t);
        for (i = 0; i< KEYSIZE; i++)
        {
            key[i] = rand()%256;
            printf("%.2x", (unsigned char)key[i]);
        }
        printf("\n");
    }
    printf("%");
    return 0;
}

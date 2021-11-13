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
  //srand (0);      // This is where srand() is called using time

  for (i = 0; i< KEYSIZE; i++){
     key[i] = rand()%256;
     printf("%.2x", (unsigned char)key[i]);
  }
  printf("\n");
  return 0;
}

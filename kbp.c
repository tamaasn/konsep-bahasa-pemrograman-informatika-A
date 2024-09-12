#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define total_penghuni 5

char penghuni[total_penghuni][8]={"Akmal","Sani","Pratama","Akmal1","Sani1"};
struct Kamar{
  char penghuni[8];
  uint8_t index;
};

struct Kamar kamar[total_penghuni];

int main(){
  srand(time(NULL));
  int iteration_total;
  printf("Total iterasi : ");
  scanf("%d",&iteration_total);
  for(int i=0;i<total_penghuni;i++){
    strncpy(kamar[i].penghuni,penghuni[i],sizeof(kamar[i].penghuni));
    kamar[i].index = i+1;
  }
  printf("Kamar dan penghuni\n");
  for(int i=0;i<total_penghuni;i++){
    printf("Kamar %d memiliki penghuni %s\n",kamar[i].index,kamar[i].penghuni);
  }
  printf("==========\n");
  for(int i=0;i<iteration_total;i++){
    printf("Kamar setelah iterasi ke-%d\n",i+1);
    for(int j = 0;j< total_penghuni;j++){
      char penghuni_temp[8];
      uint8_t random_index = rand()%total_penghuni;
      strncpy(penghuni_temp,kamar[j].penghuni,8);
      memset(kamar[j].penghuni,0,sizeof(kamar[j].penghuni));
      strncpy(kamar[j].penghuni,kamar[random_index].penghuni,8);
      memset(kamar[random_index].penghuni,0,sizeof(kamar[random_index].penghuni));
      strncpy(kamar[random_index].penghuni,penghuni_temp,8);
    }
    for(int k=0;k<total_penghuni;k++){
      printf("Kamar %d memiliki penghuni %s yang berada di alamat %p\n",kamar[k].index,kamar[k].penghuni,(struct Kamar*)&kamar[k]);
    }
    printf("====================\n");
  }
}

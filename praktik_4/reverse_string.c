#include <stdio.h>
#include <stdlib.h>

int get_length(char text[] , int len){
  int total=0;
  for(int i=0;i<len && text[i] != '\0';i++){
    total++;
  }
  //printf("total : %d\n",total);
  return total;
}

char *reverse(char text[] , int len){
  char *result = (char*)malloc(sizeof(char) * len);
  for(int i=0;i<len;i++){
    result[i] = text[(len-1)-i];
    result[(len-1)-i] = text[i];
  }

  return result;
}

int main(){
  char nama[] = "Muhammad Akmal Sani Pratama\0";
  char nim[] = "23106050036\0";
  char asal[] = "Banguntapan, Bantul, Yogyakarta\0";
  char *result1 = reverse(nama,get_length(nama,sizeof(nama)));
  char *result2 = reverse(nim,get_length(nim,sizeof(nim)));
  char *result3 = reverse(asal,get_length(asal,sizeof(asal)));
  printf("Sebelum : %s\nSesudah : %s\n============\n",nama,result1);
  printf("Sebelum : %s\nSesudah : %s\n============\n",nim,result2);
  printf("Sebelum : %s\nSesudah : %s\n============\n",asal,result3);

  free(result1);
  free(result2);
  free(result3);
  return 0;
}

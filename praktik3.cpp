#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Barang{
  unsigned int id;
  unsigned int harga;
  unsigned int satuan;
  char nama[50];
};

unsigned int id=0;
const char *text_satuan[] = {"Ampul","Strip","PCS"};

void clear_buffer(){
  int ch;
  while(ch=getchar() != '\n' && ch != EOF);
}

void isi_data(struct Barang **barang,struct Barang temp,int index){
  *barang = (struct Barang*)realloc(*barang,sizeof(struct Barang)*index);
  (*barang)[index-1].id=temp.id;
  (*barang)[index-1].harga=temp.harga;
  (*barang)[index-1].satuan=temp.satuan;
  strncpy((*barang)[index-1].nama,temp.nama,sizeof((*barang)[index-1].nama));
}

struct Barang *buat_node(){
  struct Barang *barang = (struct Barang*)malloc(sizeof(struct Barang*)*0);
  return barang;
}

struct Barang input_data(){
  clear_buffer();
  unsigned int harga=4,satuan=4;
  char nama[50];

  printf("Masukkan nama : ");
  fgets(nama,sizeof(nama),stdin);
  if (nama[strlen(nama)-1] != '\n'){
    clear_buffer();
  }
  nama[strlen(nama)-1] = '\0';

  printf("Masukkan harga : ");
  scanf("%d",&harga);
  
  while(satuan > 3){
    printf("1. Ampul\n2. Strip\n3. PCS");
    printf("Masukkan satuan : ");
    scanf("%d",&satuan);
  }

  id++;
  struct Barang temp = {
    .id = id,
    .harga=harga,
    .satuan=satuan,
  };
  strncpy(temp.nama,nama,sizeof(temp.nama));
  return temp;
}

void cetak_barang(struct Barang *barang){
  for(int i=0;i<id;i++){
    printf("[%d]. %s | %d | %s |\n",i+1,barang[i].nama,barang[i].harga,text_satuan[barang[i].satuan]);
  }
}

int main(){
  struct Barang *barang = buat_node();
  int total_harga=0;

  unsigned int pilihan=0;
  while(pilihan < 4){
    printf("Total harga = %d\n",total_harga);
    printf("======================\n");
    printf("1. Input data\n2. Pilih barang\n3. Beli\n4. Keluar\n"); 
    printf("Pilih : ");
    scanf("%d",&pilihan);
    switch(pilihan){
      case 1: {
          struct Barang temp = input_data();
          isi_data(&barang,temp,id);
        }break;
      case 2: {
          cetak_barang(barang);
          int pilih=0;
          while(pilih > id || pilih < 1){
            printf("\nPilih : ");
            scanf("%d",&pilih);
          }
          total_harga += barang[pilih-1].harga;
        }break;
      case 3: {
          int input_harga;
          printf("Total uang : ");
          scanf("%d",&input_harga);
          int kembalian=input_harga-total_harga;
          if (kembalian < 0){
            printf("Uang kurang!!\n");
            break;
          }
          printf("Kembalian : %d\n",kembalian);
          total_harga=0;
        }break;
      case 4: {
          pilihan=5;
        }break;
      default:
        break;
    }
  }   
  free(barang);
  return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    printf("[INFO] Satuan?\n");
    printf("1. Ampul\n2. Strip\n3. PCS\n");
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
  printf("[INFO] Daftar barang\n");
  for(int i=0;i<id;i++){
    printf("[%d]. %s | %d | %s |\n",i+1,barang[i].nama,barang[i].harga,text_satuan[barang[i].satuan]);
  }
  printf("[%d]. Batal\n", id+1);
}

int main(){
  struct Barang *barang = buat_node();
  struct Barang temp;
  FILE *file = fopen("data.bin","rb");
  if (file == NULL){
    printf("Gagal membaca bin file\n");
  }
  printf("File size : %ld/%ld\n",sizeof(file),sizeof(struct Barang));
  while(fread(&temp,sizeof(struct Barang),1,file) == 1){
    printf("Loading bin file...\n");
    id++;
    printf("Nama : %s\n",temp.nama);
    isi_data(&barang,temp,id);
  }
  fclose(file);
  printf("Done\n");
  int total_harga=0;

  unsigned int pilihan=0;
  while(pilihan < 4){
    #ifdef _WIN32
    system("cls");
    #elif _WIN64
    system("cls");
    #else
    system("clear");
    #endif

    printf("\tTotal harga = %d\n",total_harga);
    printf("Sunny Corp\n\n");
    printf("======================\n");
    printf("1. Input data\n2. Pilih barang\n3. Beli\n4. Simpan ke .bin\n5. Keluar\n"); 
    printf("Pilih : ");
    scanf("%d",&pilihan);
    switch(pilihan){
      case 1: {
          temp = input_data();
          isi_data(&barang,temp,id);
        }break;
      case 2: {
          cetak_barang(barang);
          int pilih=0;
          while(pilih > id || pilih < 1){
            printf("\nPilih : ");
            scanf("%d",&pilih);
            if (pilih == id+1){ break; }
          }
          total_harga += barang[pilih-1].harga;
        }break;
      case 3: {
          int input_harga;
          printf("Total uang : ");
          scanf("%d",&input_harga);
          int kembalian=input_harga-total_harga;
          if (kembalian < 0){
            printf("[ERROR] Uang kurang!!\n");
            printf("[INFO] Enter untuk lanjut!\n");
            getchar();
            getchar();
            break;
          }
          printf("[INFO] Kembalian : %d\n",kembalian);
          printf("[INFO] Enter untuk lanjut!\n");
          getchar();
          getchar();
          total_harga=0;
        }break;
      case 4: {
            size_t count = id;
            printf("Count : %ld\n",count);
            file = fopen("data.bin","wb");
            if (file == NULL){
              printf("Gagal lihat file!\n");
              break;
            }

            for(int i=0;i<count;i++){
              size_t written = fwrite(&barang[i],sizeof(struct Barang),1,file);
              if (written != 1){
                printf("Gagal menyimpan file\n");
                break;
              }
              printf("Data sukses disimpan!!\n");
            }
            fclose(file);
          }
          break;
      case 5: {
          pilihan=5;
        }break;
      default:
        break;
    }
  }   
  free(barang);
  return 0;
}



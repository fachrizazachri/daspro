#include <stdio.h>

int cariKodeBarang(char kodeBarang[10]){
    return 0;
}

void tambahBarang() {
    char kodeBarang[16];
    char namaBarang[64];
    int hargaBarang;
    int stokBarang;
    int pengingatStok;
    while(1){
        printf("Masukkan kode barang               : ");
        gets(kodeBarang);
        if(kodeBarang[0] == '\0' || kodeBarang[0] == ' '){
            printf("[ERROR] Kode barang tidak valid. Silakan masukkan kode barang yang valid.\n");
            continue;
        }
        else{
            if(cariKodeBarang(kodeBarang) == 1){
                printf("[ERROR] Kode barang harus berbeda. Silakan masukkan kode barang yang belum pernah dipakai.\n");
                continue;
            }
            break;
        }
    }
    while(1){
        printf("Masukkan nama barang               : ");
        gets(namaBarang);
        if(namaBarang[0] == '\0' || namaBarang[0] == ' '){
            printf("[ERROR] Nama barang tidak valid. Silakan masukkan nama barang yang valid.\n");
            continue;
        }
        break;
    }
    while(1){
        printf("Masukkan harga barang (hanya angka): Rp");
        scanf("%d", &hargaBarang);
        if(hargaBarang < 0){
            printf("[ERROR] Harga tidak boleh negatif!\n");
            continue;
        }
        break;
    }
    while(1){
        printf("Masukkan stok barang               : ");
        scanf("%d", &stokBarang);
        if(stokBarang < 0){
            printf("[ERROR] Stok tidak boleh negatif!\n");
            continue;
        }
        break;
    }
    while(1){
        printf("Stok saat pengingat akan muncul    : ");
        scanf("%d", &pengingatStok);
        if(pengingatStok < 0){
            printf("[ERROR] Pengingat stok tidak boleh negatif!\n");
            continue;
        }
        break;
    }
    printf("Kode barang: %s\nNama barang: %s\nHarga barang: %d\nStok barang: %d\nPengingat stok: %d", kodeBarang, namaBarang, hargaBarang, stokBarang, pengingatStok);
}


int main() {
    tambahBarang();
}
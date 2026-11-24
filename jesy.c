#include <stdio.h>

int main() {
    char kode[100][20];
    char nama[100][50];
    int harga[100];
    int stok[100];
    int minimum[100];

    int jumlah_barang = 0;
    int pilihan;
    int ditemukan;
    int sama;
    int index;
    char kode_cari[20];

do {
    printf("\n===== MENU DATA ALAT TULIS =====\n");
    printf("1. Tampilkan Seluruh Barang\n");
    printf("2. Cari Barang Berdasarkan Kode\n");
    printf("0. Keluar\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    switch (pilihan) {

    case 1:
    printf("\n========== DAFTAR ALAT TULIS ==========\n");

    if (jumlah_barang == 0) 
    {
    printf("Belum ada data barang.\n");
    } else 
    {
    printf("%-10s %-20s %-12s %-8s %-10s\n","Kode", "Nama", "Harga", "Stok", "Minimum");

    for (int i = 0; i < jumlah_barang; i++) 
    {
    printf("%-10s %-20s Rp%-10d %-8d %-10d\n",
            kode[i], nama[i], harga[i], stok[i], minimum[i]);
    }
    }
    
    break;

    case 2:
    printf("\n===== CARI BARANG BERDASARKAN KODE =====\n");
    printf("Masukkan kode barang: ");
    scanf("%19s", kode_cari);

    ditemukan = 0;

    for (int i = 0; i < jumlah_barang; i++) 
    {
        sama = 1;

    for (int j = 0; kode[i][j] != '\0' ||kode_cari[j] != '\0'; j++) 
    {

    if (kode[i][j] != kode_cari[j]) 
    {
    sama = 0;
    
    
    break;
    }
    }

    if (sama == 1) 
    {
    index = i;
    ditemukan = 1;
    
    break;
    }
    }


    if (ditemukan == 1) 
    {
    printf("\n===== DATA BARANG DITEMUKAN =====\n");
    printf("Kode Barang  : %s\n", kode[index]);
    printf("Nama Barang  : %s\n", nama[index]);
    printf("Harga Satuan : Rp%d\n", harga[index]);
    printf("Stok         : %d\n", stok[index]);
    printf("Batas Minimum: %d\n", minimum[index]);

    if (stok[index] < minimum[index]) 
    {
        printf("Status       : STOK MENIPIS!\n");
    } else 
    {
        printf("Status       : Stok Aman\n");
    }

    } else 
    {
        printf("\n[INFO] Barang tidak ditemukan!\n");
    }
                
    break;

    case 0:
        printf("\nProgram selesai.\n");
        break;

    default:
        printf("\nPilihan tidak tersedia!\n");
    }

    } while (pilihan != 0);

    return 0;
}

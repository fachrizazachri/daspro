
#include <stdio.h>

int main() {
    int pilihan;

    do {
        printf("\n============================================\n");
        printf("     SISTEM PENGELOLAAN PERSEDIAAN\n");
        printf("             ALAT TULIS KAMPUS\n");
        printf("============================================\n");

        printf("\n                 MENU UTAMA\n\n");

        printf("1. Tambah Data Alat Tulis\n");
        printf("2. Lihat Daftar Alat Tulis\n");
        printf("3. Tambah Stok Persediaan Barang\n");
        printf("4. Lihat Jumlah Stok Barang\n");
        printf("5. Lihat Barang dengan Stok Terbanyak\n");
        printf("6. Keluar dari Program\n");

        printf("--------------------------------------------\n");
        printf("Masukkan pilihan menu [1-6]: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\nMenu Data Alat Tulis\n");
                break;

            case 2:
                printf("\nMenu Penambahan Stok\n");
                break;

            case 3:
                printf("\nMenu Daftar Alat Tulis\n");
                break;

            case 4:
                printf("\nMenu Stok Barang\n");
                break;

            case 5:
                printf("\nMenu Barang Dengan Stok Terbanyak\n");
                break;
            
            case 6:
                printf("\nTerima kasih telah menggunakan program!\n");
                break;

            default:
                printf("\nPilihan tidak valid! Silakan coba lagi.\n");
        }

    } while (pilihan != 6);

    return 0;
}


#include <stdio.h>

int main() {
    int pilihan;

    do {
        printf("\n============================================\n");
        printf("     SISTEM PENGELOLAAN PERSEDIAAN\n");
        printf("             ALAT TULIS KAMPUS\n");
        printf("============================================\n");

        printf("\n                 MENU UTAMA\n\n");

        printf("1. Tambah Data Alat Tulis Baru\n");
        printf("2. Tampilkan Seluruh Daftar Alat Tulis\n");
        printf("3. Tambah Stok Barang\n");
        printf("4. Kurangi Stok Barang\n");
        printf("5. Cari Barang Berdasarkan Kode\n");
        printf("6. Tampilkan Barang Stok Terbanyak & Tersedikit\n");
        printf("7. Tampilkan Peringatan Stok di Bawah Batas Minimum\n");
        printf("8. Hitung Total Nilai Persediaan\n");
        printf("0. Keluar\n");

        printf("--------------------------------------------\n");
        printf("Masukkan pilihan menu [1-8]: ");
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

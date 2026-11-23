#include <stdio.h>

typedef struct {
    char kode[20];
    char nama[50];
    int harga, stok, batasMinimum;
} Barang;

void analisisStok(Barang barang[], int jumlah) {
    if (jumlah == 0) {
        printf("Belum ada barang yang terdaftar.\n");
        return;
    }

    Barang *p = barang;
    int max = p->stok, min = p->stok;

    for (int i = 1; i < jumlah; i++) {
        if ((p + i)->stok > max)
            max = (p + i)->stok;

        if ((p + i)->stok < min)
            min = (p + i)->stok;
    }

    printf("\n=== BARANG DENGAN STOK TERBANYAK ===\n");

    for (int i = 0; i < jumlah; i++) {
        if ((p + i)->stok == max) {
            printf("Kode  : %s\n", (p + i)->kode);
            printf("Nama  : %s\n", (p + i)->nama);
            printf("Stok  : %d\n", (p + i)->stok);
        }
    }

    printf("\n=== BARANG DENGAN STOK TERSEDIKIT ===\n");

    for (int i = 0; i < jumlah; i++) {
        if ((p + i)->stok == min) {
            printf("Kode  : %s\n", (p + i)->kode);
            printf("Nama  : %s\n", (p + i)->nama);
            printf("Stok  : %d\n", (p + i)->stok);
        }
    }
}

int main() {
    Barang daftarBarang[] = {
        {"B001", "Buku", 5000, 20, 5},
        {"P001", "Pulpen", 3000, 50, 10},
        {"S001", "Pensil", 2000, 10, 5}
    };

    int jumlahBarang = 3;

    analisisStok(daftarBarang, jumlahBarang);

    return 0;
}
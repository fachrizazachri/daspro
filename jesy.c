#include <stdio.h>

// 1. MENAMPILKAN SELURUH DAFTAR
void tampilBarang(char kode[][20], char nama[][50],
                  int harga[], int stok[], int minimum[], int jumlah)
{
    if (jumlah == 0)
    {
        printf("\nBelum ada data barang!\n");
        return;
    }

    printf("\n====================================\n");
    printf("       DAFTAR PERSEDIAAN ATK\n");
    printf("====================================\n");

    printf("Kode\tNama\t\tHarga\tStok\tMinimum\n");

    for (int i = 0; i < jumlah; i++)
    {
        printf("%s\t%-12s\t%d\t%d\t%d\n",
               kode[i], nama[i], harga[i], stok[i], minimum[i]);
    }
}


// 2. MENCARI BARANG BERDASARKAN KODE
int cariBarang(char kode[][20], int jumlah, char kode_cari[])
{
    printf("\n====================================\n");
    printf("          PENCARIAN BARANG\n");
    printf("====================================\n");

    for (int i = 0; i < jumlah; i++)
    {
        int sama = 1;
        int j = 0;

        while (kode_cari[j] != '\0' || kode[i][j] != '\0')
        {
            if (kode_cari[j] != kode[i][j])
            {
                sama = 0;
                break;
            }

            j++;
        }

        if (sama == 1)
        {
            return i;
        }
    }

    return -1;
}


// 3. MENAMPILKAN DETAIL BARANG
void tampilDetailBarang(char kode[][20], char nama[][50],
                        int harga[], int stok[], int minimum[], int index)
{
    printf("\n====================================\n");
    printf("            DETAIL BARANG\n");
    printf("====================================\n");

    printf("Kode          : %s\n", kode[index]);
    printf("Nama          : %s\n", nama[index]);
    printf("Harga         : Rp%d\n", harga[index]);
    printf("Stok          : %d\n", stok[index]);
    printf("Batas Minimum : %d\n", minimum[index]);

    printf("====================================\n");
}

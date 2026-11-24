#include <stdio.h>

// 1. MENAMPILKAN SELURUH DAFTAR
void tampilBarang(char kode[][20], char nama[][50], int harga[], int stok[], int minimum[],int jumlah)
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
            barang[i].kode,
            barang[i].nama,
            barang[i].harga,
            barang[i].stok,
            barang[i].minimum);
    }
}


// 2. MENCARI BARANG BERDASARKAN KODE

int cariBarang(struct Barang barang[], int jumlah, char kode[]) 
{

    printf("\n====================================\n");
    printf("          PENCARIAN BARANG\n");
    printf("====================================\n");

    for (int i = 0; i < jumlah; i++) 
    {

        int sama = 1;
        int j = 0;

        while (kode[j] != '\0' || barang[i].kode[j] != '\0') 
        {

            if (kode[j] != barang[i].kode[j]) 
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
void tampilDetailBarang(struct Barang barang[], int index) 
{

    printf("\n====================================\n");
    printf("            DETAIL BARANG\n");
    printf("====================================\n");

    printf("Kode          : %s\n", barang[index].kode);
    printf("Nama          : %s\n", barang[index].nama);
    printf("Harga         : Rp%d\n", barang[index].harga);
    printf("Stok          : %d\n", barang[index].stok);
    printf("Batas Minimum : %d\n", barang[index].minimum);

    printf("====================================\n");
}

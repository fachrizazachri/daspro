printf("%-10s %-20s %-12s %-8s %-10s\n","Kode", "Nama", "Harga", "Stok", "Minimum");

    for (int i = 0; i < jumlah_barang; i++) 
    {
    printf("%-10s %-20s Rp%-10d %-8d %-10d\n",
            kode[i], nama[i], harga[i], stok[i], minimum[i]);
    }

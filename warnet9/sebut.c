#include <stdio.h>
#include <string.h>

// ------------ ARRAY DATA ------------
char ruangan[3][20] = {"Reguler", "VIP", "Premium"};
int status[3] = {1, 1, 1}; // 1 = tersedia, 0 = dipakai
int hargaPerJam[3] = {5000, 10000, 15000};

// Paket berbeda setiap ruangan
char paket[2][20] = {"Paket Hemat", "Paket Pro"};
int hargaPaket[3][2] = {
    {10000, 20000}, // Reguler
    {15000, 30000}, // VIP
    {20000, 40000}  // Premium
};

// ------------ FUNCTION ------------
void simpanFile(char nama[], char ruang[], char paket[], int total);
int hitungBiaya(int pilihRuang, int jam, int pilihPaket);
void tampilkanTabel();
void menu();

int main()
{
    menu();
    return 0;
}

void simpanFile(char nama[], char ruang[], char paket[], int total)
{
    FILE *f = fopen("transaksi.txt", "a");
    fprintf(f, "Nama: %s | Ruangan: %s | Paket: %s | Total: %d\n",
            nama, ruang, paket, total);
    fclose(f);
}

int hitungBiaya(int pilihRuang, int jam, int pilihPaket)
{
    int total = hargaPerJam[pilihRuang] * jam;

    if (jam >= 3)
    {
        total -= 5000; // diskon
    }

    // Paket berbeda tiap ruangan
    if (pilihPaket != -1)
    {
        total += hargaPaket[pilihRuang][pilihPaket];
    }

    return total;
}

void tampilkanTabel()
{
    printf("\n=== Daftar Ruangan & Paket ===\n");

    for (int i = 0; i < 3; i++)
    {
        printf("\n%d. %s - Harga per jam: %d\n", i + 1, ruangan[i], hargaPerJam[i]);
        printf("   Paket:\n");
        for (int j = 0; j < 2; j++)
        {
            printf("     - %s : %d\n", paket[j], hargaPaket[i][j]);
        }
    }
}

void menu()
{
    int pilih, pilihRuang, jam, pilihPaket;
    char nama[50];

    printf("\n========= MENU WARNET =========\n");
    printf("1. Lihat Ruangan\n");
    printf("2. Sewa Ruangan\n");
    printf("3. Keluar\n");
    printf("Pilih: ");
    scanf("%d", &pilih);

    if (pilih == 1)
    {
        tampilkanTabel();
        menu();
    }

    else if (pilih == 2)
    {
        printf("\nMasukkan Nama Penyewa: ");
        scanf(" %[^\n]", nama);

        printf("\nPilih Ruangan:\n");
        for (int i = 0; i < 3; i++)
        {
            printf("%d. %s %s\n", i + 1, ruangan[i], status[i] ? "(Tersedia)" : "(Dipakai)");
        }
        printf("Pilih: ");
        scanf("%d", &pilihRuang);
        pilihRuang--;

        if (status[pilihRuang] == 0)
        {
            printf("\nRuangan tidak tersedia!\n");
            menu();
            return;
        }

        printf("\nLama Sewa (jam): ");
        scanf("%d", &jam);

        printf("\nPilih Paket (atau -1 untuk tidak memakai):\n");
        printf("1. %s (%d)\n", paket[0], hargaPaket[pilihRuang][0]);
        printf("2. %s (%d)\n", paket[1], hargaPaket[pilihRuang][1]);
        printf("Pilih: ");
        scanf("%d", &pilihPaket);

        if (pilihPaket > 0)
            pilihPaket--;

        int total = hitungBiaya(pilihRuang, jam, pilihPaket);

        printf("\n===== STRUK PEMBAYARAN =====\n");
        printf("Nama Penyewa : %s\n", nama);
        printf("Ruangan      : %s\n", ruangan[pilihRuang]);
        printf("Durasi       : %d jam\n", jam);
        if (pilihPaket != -1)
            printf("Paket        : %s (%d)\n", paket[pilihPaket], hargaPaket[pilihRuang][pilihPaket]);
        else
            printf("Paket        : Tidak ada\n");
        printf("Total Bayar  : %d\n", total);

        simpanFile(nama, ruangan[pilihRuang],
                   (pilihPaket == -1 ? "Tidak ada" : paket[pilihPaket]),
                   total);

        status[pilihRuang] = 0;

        printf("\nTransaksi berhasil disimpan.\n");

        menu();
    }

    else if (pilih == 3)
    {
        printf("Terima kasih!\n");
        return;
    }

    else
    {
        printf("Pilihan tidak valid.\n");
        menu();
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void enkripsi(char *teks, int operator_key);
void dekripsi(char *teks, char *kunci);

int main()
{
    do
    {
        char teks[100], kunci[100];
        int operator_key, pil;
        system("cls");
        printf("Menu :\n1. Enkripsi\n2. Dekripsi\n3. Exit\n\nSilahkan pilih menu: ");
        scanf("%d", &pil);
        fflush(stdin);
        if (pil == 1)
        {
            printf("Masukkan teks: ");
            gets(teks);
            printf("Masukkkan kunci: ");
            scanf("%d", &operator_key);
            enkripsi(teks, operator_key);
        }
        else if (pil == 2)
        {
            printf("Masukkan nama file Chippertext: ");
            gets(teks);
            strcat(teks, ".txt"); // tambahkan ekstensi ".txt" ke nama file
            printf("Masukkan nama file Chipkunci: ");
            gets(kunci);
            strcat(teks, ".txt"); // tambahkan ekstensi ".txt" ke nama file
            dekripsi(teks, kunci);
        }
        else if (pil == 3)
        {
            printf("Terima kasih telah menggunakan program ini!");
            exit(0);
        }
        else
        {
            printf("Maaf, Pilihan anda tidak tersedia!");
        }
        getchar();
    } while (1);
}

void enkripsi(char *teks, int operator_key)
{
    FILE *f;
    int i = 0, j;
    f = fopen("sender.txt", "a");
    // tuliskan teks asli dan kunci enkripsi ke dalam sender.txt
    fprintf(f, "Teks: %s\n", teks);
    fprintf(f, "kunci: %d\n", operator_key);
    fprintf(f, "+---Pesan berhasil dikirim---+\n\n");
    fclose(f);
    // proses enkripsi
    f = fopen("chiptext.txt", "a");
    // Hitung panjang teks asli
    while (teks[i] != '\0')
    {
        i++;
    }
    // tuliskan teks terenkripsi ke dalam file chiptext.txt
    fprintf(f, "\nChippertext:");
    for (j = 0; j < i; j++)
    {
        fprintf(f, " %i", teks[j] / operator_key);
    }
    fclose(f);
    f = fopen("chipkunci.txt", "a");
    // tuliskan kunci enkripsi ke dalam file kunci.txt
    fprintf(f, "Chip kunci:");
    for (j = 0; j < i; j++)
    {
        fprintf(f, " %i", teks[j] % operator_key);
    }
    fprintf(f, " %i\n", operator_key);
    fclose(f);
}

void dekripsi(char *teks, char *kunci)
{
    FILE *fp, *fk;
    int i = 0, j, operator_key;
    char *data, *temp;
    fp = fopen(teks, "r");
    // baca isi file text.txt dengan fscanf()
    while (fscanf(fp, "%d", &j) == 1)
    {
        // lakukan proses dekripsi
        teks[i] = j * operator_key;
        i++;
    }
    fclose(fp);

    fk = fopen(kunci, "r");
    // baca kunci enkripsi dari file kunci.txt
    fscanf(fk, "Chip kunci: %d", &operator_key);
    // alokasikan panjang kunci
    temp = malloc(sizeof(char) * strlen(kunci));
    // copy chip_kunci ke temp
    strcpy(temp, kunci);
    // baca isi file kunci.txt dengan fgets()
    while (fgets(temp, strlen(kunci), fk) != NULL)
    { 
        // ambil kunci dengan strtok
        data = strtok(temp, " ");
        // mengambil data terakhir dari chip_kunci
        j = 0;
        while (data != NULL)
        {
            operator_key = atoi(data);
            data = strtok(NULL, " ");
            j++;
        }
        // membuat array untuk chip_kunci
        // untuk mengubah chip kunci dari char ke int
        int key[j - 1];
        // copy chip_kunci ke temp
        strcpy(temp, kunci);
        // ambil kunci dengan strtok
        data = strtok(temp, " ");
        i = 0;
        while (data != NULL)
        {
            key[i] = atoi(data);
            data = strtok(NULL, " ");
            i++;
        }
        // dekripsi
        char text[100];
        // ambil chipertext dengan strtok
        data = strtok(teks, " ");
        i = 0;
        while (data != NULL)
        {
            // Konversi desimal plaintext dari char ke int
            int desimal = atoi(data);
            text[i] = (desimal * operator_key) + key[i];
            data = strtok(NULL, " ");
            i++;
        }
        text[i] = '\0';
    }
    fclose(fk);
    // tampilkan teks yang telah di dekripsi
    printf("\nHasil dekripsi: %s\n", teks);
}

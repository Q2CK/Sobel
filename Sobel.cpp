#include <iostream>
#include <fstream>

using namespace std;

struct BITMAPFILEHEADER { //Struktura naglowka pliku
    char bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER { //Struktura naglowka obrazu
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXpelsPerMeter;
    uint32_t biYpelsPerMeter;
    uint32_t biCrlUses;
    uint32_t biCrlImportant;
};

const char S[8][3][3] = { {  {-1, 0, 1},  //Filtr
                             {-2, 0, 2},
                             {-1, 0, 1} },

                           { { 0, 1, 2},
                             {-1, 0, 1},
                             {-2,-1, 0} }, 

                           { { 1, 2, 1},
                             { 0, 0, 0},
                             {-1,-2,-1} },

                           { { 2, 1, 0},
                             { 1, 0,-1},
                             { 0,-1,-2} },

                           { { 1, 0,-1},
                             { 2, 0,-2},
                             { 1, 0,-1} },

                           { { 0,-1,-2},
                             { 1, 0,-1},
                             { 2, 1, 0} },

                           { {-1,-2,-1},
                             { 0, 0, 0},
                             { 1, 2, 1} },

                           { {-2,-1, 0},
                             {-1, 0, 1},
                             { 0, 1, 2} } };

void BFH(ifstream& ifs, BITMAPFILEHEADER& bfh) //Funkcja spisujace naglowek pliku
{
    ifs.read(reinterpret_cast<char*> (&bfh.bfType), 2);
    ifs.read(reinterpret_cast<char*> (&bfh.bfSize), 4);
    ifs.read(reinterpret_cast<char*> (&bfh.bfReserved1), 2);
    ifs.read(reinterpret_cast<char*> (&bfh.bfReserved2), 2);
    ifs.read(reinterpret_cast<char*> (&bfh.bfOffBits), 4);
}

void BIH(ifstream& ifs, BITMAPINFOHEADER& bih) //Funkcja spisujace naglowek obrazu
{
    ifs.read(reinterpret_cast<char*> (&bih.biSize), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biWidth), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biHeight), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biPlanes), 2);
    ifs.read(reinterpret_cast<char*> (&bih.biBitCount), 2);
    ifs.read(reinterpret_cast<char*> (&bih.biCompression), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biSizeImage), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biXpelsPerMeter), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biYpelsPerMeter), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biCrlUses), 4);
    ifs.read(reinterpret_cast<char*> (&bih.biCrlImportant), 4);
}

void zapisz(ofstream &wyj, BITMAPFILEHEADER naglowekF, BITMAPINFOHEADER naglowekI, char** obraz, int szerokosc) { //Funkcja zapisujaca wynik
    wyj.write(reinterpret_cast<char*> (&naglowekF.bfType), 2);
    wyj.write(reinterpret_cast<char*> (&naglowekF.bfSize), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekF.bfReserved1), 2);
    wyj.write(reinterpret_cast<char*> (&naglowekF.bfReserved2), 2);
    wyj.write(reinterpret_cast<char*> (&naglowekF.bfOffBits), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biSize), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biWidth), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biHeight), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biPlanes), 2);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biBitCount), 2);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biCompression), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biSizeImage), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biXpelsPerMeter), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biYpelsPerMeter), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biCrlUses), 4);
    wyj.write(reinterpret_cast<char*> (&naglowekI.biCrlImportant), 4);
    for (int i = 0; i < naglowekI.biHeight; i++) {
        wyj.write(obraz[i], szerokosc);
    }
}

void wyswietlNaglowek(BITMAPFILEHEADER naglowekF, BITMAPINFOHEADER naglowekI) { //Wyswietlanie parametrow naglowka pliku i obrazu
    cout << "File header:" << endl;

    cout << "bfType: " << naglowekF.bfType[0] << naglowekF.bfType[1] << endl;
    cout << "bfSize: " << naglowekF.bfSize << endl;
    cout << "bfReserved1: " << naglowekF.bfReserved1 << endl;
    cout << "bfReserved2: " << naglowekF.bfReserved2 << endl;
    cout << "biOffBits: " << naglowekF.bfOffBits << endl;

    cout << endl << "Image header:" << endl;

    cout << "biSize: " << naglowekI.biSize << endl;
    cout << "biWidth: " << naglowekI.biWidth << endl;
    cout << "biHeight: " << naglowekI.biHeight << endl;
    cout << "biPlanes: " << naglowekI.biPlanes << endl;
    cout << "biBitCount: " << naglowekI.biBitCount << endl;
    cout << "biCompression: " << naglowekI.biCompression << endl;
    cout << "biSizeImage: " << naglowekI.biSizeImage << endl;
    cout << "biXpelsPerMeter: " << naglowekI.biXpelsPerMeter << endl;
    cout << "biYpelsPerMeter: " << naglowekI.biYpelsPerMeter << endl;
    cout << "biCrlUses: " << naglowekI.biCrlUses << endl;
    cout << "biCrlImportant: " << naglowekI.biCrlImportant << endl;
}

int main() {
    string nazwaWej, nazwaWyj;

    cout << "Plik wejsciowy: ";
    cin >> nazwaWej;
    cout << endl;
    cout << "Plik wyjsciowy: ";
    cin >> nazwaWyj;
    cout << endl;

    ifstream wej(nazwaWej, ios::in  | ios::binary);
    ofstream wyj(nazwaWyj, ios::out | ios::binary);
    BITMAPFILEHEADER naglowekF;
    BITMAPINFOHEADER naglowekI;

    if (wej.is_open()) {
        BFH(wej, naglowekF);
        BIH(wej, naglowekI);
    }
    else {
        cout << "Blad pliku";
        return 0;
    }

    wyswietlNaglowek(naglowekF, naglowekI);

    int zera = naglowekI.biWidth % 4;
    int szerokosc = naglowekI.biWidth * 3 + zera;

    unsigned char** obraz = new unsigned char* [naglowekI.biHeight];
    unsigned char** wynik = new unsigned char* [naglowekI.biHeight];
    for (int i = 0; i < naglowekI.biHeight; i++) {
        obraz[i] = new unsigned char[szerokosc];
        wynik[i] = new unsigned char[szerokosc];
    }

    for (int y = 0; y < naglowekI.biHeight; y++) {
        for (int x = 0; x < szerokosc; x++) {
            wynik[y][x] = 0;
        }
    }

    if (wej.is_open()) {
        for (int y = 0; y < naglowekI.biHeight; y++) {
            for (int x = 0; x < szerokosc; x++) {
                obraz[y][x] = 0;
            }
            wej.read((char*)obraz[y], szerokosc);
        }
    }
    else {
        cout << "Blad pliku";
        return 0;
    }

    for (int y = 1; y < naglowekI.biHeight - 1; y++) { //Glowna petla przetwarzajaca obraz
        for (int x = 1; x < naglowekI.biWidth - 1; x++) {
            int B = 0;
            int G = 0;
            int R = 0;
            for (int m = 0; m < 8; m++) {
                int tempB = 0;
                int tempG = 0;
                int tempR = 0;
                for (int my = 0; my < 3; my++) {
                    for (int mx = 0; mx < 3; mx++) {
                        tempB += S[m][my][mx] * obraz[y - 1 + my][3 * (x - 1 + mx)];
                        tempG += S[m][my][mx] * obraz[y - 1 + my][3 * (x - 1 + mx) + 1];
                        tempR += S[m][my][mx] * obraz[y - 1 + my][3 * (x - 1 + mx) + 2];
                    }
                }

                if (tempB > 255)
                    tempB = 255;
                else if (tempB < 0)
                    tempB = 0;

                if (tempG > 255)
                    tempG = 255;
                else if (tempG < 0)
                    tempG = 0;

                if (tempR > 255)
                    tempR = 255;
                else if (tempR < 0)
                    tempR = 0;

                B += tempB; // WARIANT I
                G += tempG;
                R += tempR;

                /*if (tempB > B) // WARIANT II (jasniejszy wynik)
                    B = tempB;
                if (tempG > G)
                    G = tempG;
                if (tempR > R)
                    R = tempR;*/
            }

            wynik[y][3 * x] = B / 8; // WARIANT I
            wynik[y][3 * x + 1] = G / 8;
            wynik[y][3 * x + 2] = R / 8;

            /*wynik[y][3 * x] = B; // WARIANT II (jasniejszy wynik)
            wynik[y][3 * x + 1] = G;
            wynik[y][3 * x + 2] = R; */
        }
    }
   

    if (wyj.is_open()) {
        zapisz(wyj, naglowekF, naglowekI, (char**)wynik, szerokosc);
    }
    else {
        cout << "File error";
        return 0;
    }

    for (int i = 0; i < naglowekI.biHeight; i++) { //Usuwanie dynamicznej tablicy
        delete[] obraz[i];
        delete[] wynik[i];
    }
    delete[] obraz;
    delete[] wynik;

    return 0;
}
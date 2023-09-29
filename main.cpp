#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>


void paddingString(std::string &text,int ukuran){
	if(text.length()==ukuran){
		return;
	}
	size_t total = ukuran - text.length();
	for(int i=0;i<total;i++){
		text+='@';
	}
}

std::string decryptXOR(std::string ciphertext, std::string key) {
    size_t padding = 0;

    // Mencari perbedaan length, menambahkan karakter ke string yang lebih pendek
    ciphertext.length() > key.length() ? paddingString(key, std::max(ciphertext.length(), key.length())) : paddingString(ciphertext, std::max(ciphertext.length(), key.length()));
    // Mereset builder string
    std::stringstream builder("");
    for (int i = 0; i < std::max(ciphertext.length(), key.length()); i++) {

        std::bitset<8> biner1(ciphertext[i]);
        std::bitset<8> biner2(key[i]);

        std::bitset<8> resultXOR = biner1 ^ biner2;
        builder << static_cast<char>(resultXOR.to_ulong());
    }
    return builder.str();
}

void encryptXOR(){
	std::string plain,key;
	size_t padding=0;
	system("cls");
	std::cout<<"XOR ENCRYPT\n===============================\n";
	std::cout<<"Masukan Teks : ";std::getline(std::cin,plain);
	std::cout<<"Masukan Key : ";std::getline(std::cin,key);
	/*
		Manipulasi Plain Teks.
		 - Penghapusan Spasi
		 - Menghilangkan Huruf Yang Ganda.
	*/
	//Penghapusan spasi
	plain.erase(std::remove(plain.begin(), plain.end(), ' '), plain.end());
	std::cout<<"Remove space result : "<<plain<<std::endl;
	
	//penghapusan huruf ganda
	std::stringstream builder;
	builder<<plain[0];
	for(int i=1;i<plain.length();i++){
		if(plain[i]!=plain[i-1]){
			builder<<plain[i];
		}
	}
	//Memngubah plainteks
	plain = builder.str();
	//Mencari perbedaan length, menambahkan karakter ke string yang lebih pendek
	plain.length()>key.length() ? paddingString(key,std::max(plain.length(),key.length())) :paddingString(plain,std::max(plain.length(),key.length()));
	//mereset builder string
	builder.str("");
	for(int i=0;i<std::max(plain.length(),key.length());i++){
		
		std::bitset<8> biner1(plain[i]);
		std::bitset<8> biner2(key[i]);
		
		std::bitset<8> resultXOR = biner1 ^ biner2;
		builder<<static_cast<char>(resultXOR.to_ulong());
	}
	std::cout<<"\nAfter Modified\n";
	std::cout<<"Plain = "<<plain<<std::endl;
	std::cout<<"Key = "<<key<<std::endl;
	std::cout<<"Result Encrypt = "<<builder.str()<<std::endl;
	std::cout<<"==========\nDecrypt = "<<decryptXOR(builder.str(),key)<<std::endl;
}

std::string decryptRailFence(std::string cipher, int kunci)
{
    // Membuat matriks untuk mendekripsi pesan
    // kunci = baris, panjang(cipher) = kolom
    char rail[kunci][cipher.length()];

    // Mengisi matriks rail untuk membedakan antara karakter terisi dan karakter kosong
    for (int i = 0; i < kunci; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    // Untuk menentukan arah aliran
    bool arah_ke_bawah;

    int baris = 0, kolom = 0;

    // Menandai tempat-tempat dengan '*'
    for (int i = 0; i < cipher.length(); i++)
    {
        // Memeriksa arah aliran
        if (baris == 0)
            arah_ke_bawah = true;
        if (baris == kunci - 1)
            arah_ke_bawah = false;

        // Menempatkan penanda
        rail[baris][kolom++] = '*';

        // Mencari baris berikutnya menggunakan tanda arah
        arah_ke_bawah ? baris++ : baris--;
    }

    // Sekarang kita dapat mengonstruksi matriks rail
    int indeks = 0;
    for (int i = 0; i < kunci; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && indeks < cipher.length())
                rail[i][j] = cipher[indeks++];

    // membaca matriks dalam pola zig-zag untuk mengonstruksi
    // teks hasil dekripsi
    std::string hasil;

    baris = 0, kolom = 0;
    for (int i = 0; i < cipher.length(); i++)
    {
        // Memeriksa arah aliran
        if (baris == 0)
            arah_ke_bawah = true;
        if (baris == kunci - 1)
            arah_ke_bawah = false;

        // Menempatkan penanda
        if (rail[baris][kolom] != '*')
            hasil.push_back(rail[baris][kolom++]);

        // Mencari baris berikutnya menggunakan tanda arah
        arah_ke_bawah ? baris++ : baris--;
    }
    return hasil;
}

void encryptRailFence(){
	system("cls");
	std::string teks; 
	int kunci;
	std::cout<<"Rail Fence ENCRYPT\n===============================\n";
	std::cout<<"Masukan Teks : ";std::getline(std::cin,teks);
	std::cout<<"Masukan Key : ";std::cin>>kunci;
    // Membuat matriks untuk mengenkripsi pesan
    // kunci = baris, panjang(teks) = kolom
    char rail[kunci][(teks.length())];

    // Mengisi matriks rail untuk membedakan antara karakter terisi dan karakter kosong
    for (int i = 0; i < kunci; i++)
        for (int j = 0; j < teks.length(); j++)
            rail[i][j] = '\n';

    // Untuk menentukan arah aliran
    bool arah_ke_bawah = false;
    int baris = 0, kolom = 0;

    for (int i = 0; i < teks.length(); i++)
    {
        // Memeriksa arah aliran
        // Membalik arah jika kita baru saja mengisi baris atas atau bawah
        if (baris == 0 || baris == kunci - 1)
            arah_ke_bawah = !arah_ke_bawah;

        // Mengisi huruf yang sesuai
        rail[baris][kolom++] = teks[i];

        // Mencari baris berikutnya menggunakan tanda arah
        arah_ke_bawah ? baris++ : baris--;
    }

    // Sekarang kita dapat mengonstruksi cipher menggunakan matriks rail
   std::string hasil;
    for (int i = 0; i < kunci; i++)
        for (int j = 0; j < teks.length(); j++)
            if (rail[i][j] != '\n')
                hasil.push_back(rail[i][j]);

    std::cout<<"\nAfter Modified\n";
	std::cout<<"Plain = "<<teks<<std::endl;
	std::cout<<"Key = "<<kunci<<std::endl;
	std::cout<<"Result Encrypt = "<<hasil<<std::endl;
	std::cout<<"==========\nDecrypt = "<<decryptRailFence(hasil,kunci)<<std::endl;
}


std::string encryptCaesarCipher(std::string teks, int kunci) {
    std::string hasil = "";
    for (int i = 0; i < teks.length(); i++) {
        // Periksa apakah karakter adalah huruf
        if (isalpha(teks[i])) {
            char shift = isupper(teks[i]) ? 'A' : 'a';
            hasil += char(((teks[i] + kunci - shift) % 26) + shift);
        } else {
            // Jika bukan huruf, tambahkan karakter aslinya ke hasil
            hasil += teks[i];
        }
    }
    return hasil;
}

// Fungsi untuk mendekripsi pesan dengan Caesar Cipher
std::string decryptCaesarCipher(std::string teks, int kunci) {
    return encryptCaesarCipher(teks, 26 - kunci);
}

void caesarCipher() {
	system("cls");
    std::string teks,d;
    int kunci;
    std::cout<<"Caesar CipherENCRYPT\n===============================\n";
	std::cout<<"Masukan Teks : ";std::getline(std::cin,teks);
	std::cout<<"Masukan Key : ";std::cin>>kunci;
	std::cout<<"\nAfter Modified\n";
	std::cout<<"Plain = "<<teks<<std::endl;
	std::cout<<"Key = "<<kunci<<std::endl;
	std::cout<<"Result Encrypt = "<<encryptCaesarCipher(teks,kunci)<<std::endl;
	d = encryptCaesarCipher(teks,kunci);
	std::cout<<"==========\nDecrypt = "<<decryptCaesarCipher(d,kunci)<<std::endl;
}

int main(int argc, char** argv) {
	int a=0;
	std::cout<<"Pilih Mode Enkripsi\n1.XOR\n2.CAESAR CHIPPER\n3.Rail Fence\n4.SUPERENCRYPT"<<std::endl;
	std::cin>>a;std::cin.ignore();
	switch(a){
		case 1:
			encryptXOR();
			break;
		case 2:
			caesarCipher();
			break;
		case 3:
			encryptRailFence();
			break;
		default:
			break;
	}
}


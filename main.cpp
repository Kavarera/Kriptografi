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

int main(int argc, char** argv) {
	int a=0;
	std::cout<<"Pilih Mode Enkripsi\n1.XOR\n2.CAESAR CHIPPER\n3.\n4.SUPERENCRYPT"<<std::endl;
	std::cin>>a;std::cin.ignore();
	switch(a){
		case 1:
			encryptXOR();
			break;
		default:
			break;
	}
}

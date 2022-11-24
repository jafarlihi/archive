// AES-128 encryption implementation in C++
// BMU - 2016-2017-Spring Information Security class, extra project
// Hikmat Jafarli (150105031), hceferli@std.qu.edu.az

#include <iostream>
#include <cstring>
#include "aes.h"

using namespace std;

int main() {
	unsigned char inputMessage[] = "This message will be encrypted."; // Enter the message you want to encrypt
	unsigned char masterKey[16] = { 6, 5, 7, 3, 1, 0, 14, 4, 2, 13, 1, 1, 6, 3, 7, 9 }; // Master key of encryption (128 bits = 16 bytes)

	int inputMessageLength = strlen((const char*)inputMessage);
	int lengthAfterPadding = inputMessageLength;

	// Adds padding to the message if it doesn't make perfect 16 byte blocks
	if (lengthAfterPadding % 16 != 0) { lengthAfterPadding = (lengthAfterPadding / 16 + 1) * 16; }
	unsigned char* messageWithPadding = new unsigned char[lengthAfterPadding];
	for (int c = 0; c < lengthAfterPadding; c++) {
		if (c >= inputMessageLength) messageWithPadding[c] = 0; // Padding with 0s
		else messageWithPadding[c] = inputMessage[c];
	}

	unsigned char expandedKey[176];
	expandKey(masterKey, expandedKey);

	for (int c = 0; c < lengthAfterPadding; c += 16) { encrypt(masterKey, expandedKey, messageWithPadding + c); }

	cout <<"Encryption result (in hexadecimal):" << endl;
	for (int c = 0; c < lengthAfterPadding; c++) { hexOutput(messageWithPadding[c]); cout << " "; }

	delete[] messageWithPadding;
	return 0;
}

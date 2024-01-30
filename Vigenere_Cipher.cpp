#include <iostream>

using namespace std;

string GenerateKey(string& str, string& key)
{
    for (char ch : str)
    {
        key.push_back(ch);
    }

    return key;
}

string Encrypt(string& plaintext, string& key)
{
    string ciphertext;
    for (int i = 0; i < plaintext.size(); ++i)
    {
        char p = plaintext[i];
        char k = key[i];
        char baseP,baseK, c;
        baseP = isupper(p) ? 'A' : 'a';
        baseK = isupper(k) ? 'A' : 'a';
        c = ((p - baseP) + (key[i] - baseK)) % 26 +'A';
        ciphertext.push_back(c);
    }

    return ciphertext;
}

string Decrypt(string& ciphertext, string& key)
{
    string originaltext;
    for (int i = 0; i < ciphertext.size(); ++i)
    {
        char c = ciphertext[i];
        char k = key[i];
        char baseC,baseK, p;
        baseC = isupper(c) ? 'A' : 'a';
        baseK = isupper(k) ? 'A' : 'a';
        p = ((c - baseC) - (key[i] - baseK) + 26) % 26 +'A';
        originaltext.push_back(p);
    }

    return originaltext;
}

void Vigenere_Cipher()
{
    string plaintext;
    string keyword;

    cout << "Enter message : ";
    getline(cin, plaintext);
    cout << "Enter keyword : ";
    getline(cin, keyword);

    string key = GenerateKey(plaintext, keyword);

    string ciphertext = Encrypt(plaintext, key);
    cout << "Encrypted message -> " << ciphertext << endl;

    string originaltext = Decrypt(ciphertext, key);
    cout << "Decrypted message -> " << originaltext << endl;
}
int main()
{
    Vigenere_Cipher();
    return 0;
}

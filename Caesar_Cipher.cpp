#include <iostream>

using namespace std;

string decrypt(string str, int key);

string encrypt(string plaintext, int key)
{

    string ciphertext;

    for(char& ch : plaintext)
    {
        if(isalpha(ch))
        {
            char base;
            base=isupper(ch) ? 'A' : 'a';
            ch=(ch-base+key)%26+base;
        }
        ciphertext.push_back(ch);
    }

    return ciphertext;
}

string decrypt(string encryptedtext, int key)
{
    return encrypt(encryptedtext,26-key);;
}
int main()
{
    string message;
    int key;

    cout<<"Enter your Message : ";
    cin>>message;
    cout<<"Enter the key -> ";
    cin>>key;

    string encryptedMessage=encrypt(message,key);
    cout<<"Encrypted Message : "<<encryptedMessage<<endl;

    string decryptedMessage=decrypt(encryptedMessage,key);
    cout<<"Decrypted Message : "<<decryptedMessage<<endl;

    return 0;
}

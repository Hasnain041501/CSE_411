#include<bits/stdc++.h>

using namespace std;

int arr[4];
char KeyTable[5][5]={{'h','a','s','n','i'},
                    {'b','c','d','e','f'},
                    {'g','y','k','l','m'},
                    {'o','p','q','r','z'},
                    {'t','u','v','w','x'}};

string plaintext,ciphertext;

void LowerCase(string& str)
{
    int i=0;
    for(auto x:str){

          str.at(i++)=(char)tolower(x);
    }
    cout<<"Lowercase text : "<<str<<endl;
}

void Prepare(string& plaintext)
{
    int len=plaintext.length();
    if((len%2) != 0)
    {
        plaintext.append("x");
    }
    cout<<"Pair format : "<<plaintext<<endl;
}

void Search(char a, char b)
{
    if(a=='j') a=='i';
    if(b=='j') b=='i';

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            if(KeyTable[i][j]==a)
            {
                arr[0]=i;
                arr[1]=j;
            }
            else if(KeyTable[i][j]==b)
            {
                arr[2]=i;
                arr[3]=j;
            }
        }
    }
}

int mod5(int num){ return num%5; }

void Encrypt(string& plaintext)
{
    for(int i=0; i<plaintext.length(); i+=2)
    {
        Search(plaintext[i],plaintext[i+1]);

        if(arr[0]==arr[2])
        {

            ciphertext.push_back(KeyTable[arr[0]][mod5(arr[1]+1)]);
            ciphertext.push_back(KeyTable[arr[0]][mod5(arr[3]+1)]);
        }
        else if(arr[1]==arr[3])
        {
            ciphertext.push_back(KeyTable[mod5(arr[0]+1)][arr[1]]);
            ciphertext.push_back(KeyTable[mod5(arr[2]+1)][arr[1]]);
        }
        else{
            ciphertext.push_back(KeyTable[arr[0]][arr[3]]);
            ciphertext.push_back(KeyTable[arr[2]][arr[1]]);
        }
    }
}

void PlayfairCipher()
{
    cout<<"Enter text : ";
    cin>>plaintext;

    Prepare(plaintext);
    LowerCase(plaintext);
    Encrypt(plaintext);

    cout<<"Encrypted Text -> "<<ciphertext<<endl;
}

int main()
{
    PlayfairCipher();

    return 0;
}

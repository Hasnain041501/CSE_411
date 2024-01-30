#include<bits/stdc++.h>

using namespace std;

int arr[4];
string plaintext,ciphertext;
char KeyTable[5][5]={{'h','a','s','n','i'},
                    {'b','c','d','e','f'},
                    {'g','y','k','l','m'},
                    {'o','p','q','r','z'},
                    {'t','u','v','w','x'}};


string LowerCase(string str)
{
    int i=0;
    for(auto x:str){

          str.at(i++)=(char)tolower(x);
    }
  return str;
}

void Prepare()
{
    int len=plaintext.length();
    if((len%2) != 0)
    {
        plaintext.at(len++)='x';
        plaintext.at(len)='\0';
    }
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

    cout<<arr[0]<<arr[1]<<arr[2]<<arr[3]<<endl;
}

int mod5(int num){ return num%5; }

void Encrypt(string plaintext)
{
    cout<<"Encrypted Text -> "<<ciphertext<<endl;
    for(int i=0; i<plaintext.length()-1; i+=2)
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

        cout<<"Encrypted Text -> "<<ciphertext<<endl;

    }


}

void PlayfairCipher()
{
    Encrypt(plaintext);

}

int main()
{
    cout<<"Enter text : ";
    cin>>plaintext;

    PlayfairCipher();



    return 0;
}

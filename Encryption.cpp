#include <stdio.h>
#include <stdlib.h>


unsigned char * g (unsigned char wInput[4], int counter)
{
    unsigned char * wReady = malloc(4);
    unsigned char temp[4] = "";
    unsigned char a = wInput[0];
    for(int i =0;i<3; i++)
    {
        temp[i] = wInput[(i+1)];
    }
    temp[3] = a;

    for (int i =0; i<4;i++)
        temp[i] = s[temp[i]];

    //unsigned char array formed for xoring with rcon

    unsigned char array2[4] = "";
    array2[0] = rcon[counter];
    array2[1] = array2[2] = array2[3] = 0x00;

    for (int i=0;i<4;i++)
    wReady[i] = temp[i] ^ array2[i];
    return wReady;
} 

unsigned char * keyExpansion(unsigned char key[16])
{
    unsigned char words[44][4];
    for (int i = 0; i < 44; ++i)
    {
        for (int j = 0; j <4; ++j)
        {
            words[i][j]=0x00;
        }
    }
    
    unsigned char * expandedKey = malloc(176);
    
    int byteCount = 0; //this is to keep a count on the bytes of the expandedKey array
    
    for (int i=0;i<16;i++)
            expandedKey[i] = key[i];

    for(int j=0;j<4;j++)
    {
         for(int k=0;k<4;k++)
         {
            words[j][k] = expandedKey[byteCount];
            byteCount++;
         }
    }
    for(int l=4;l<44;l++)
    {
        if((l%4)==0)
        {
            for(int m=0;m<4;m++)
            {
                words[l][m] = words[(l-4)][m] ^ g(words[l-1], (l/4))[m];
            }
        }
        else
        {
            for(int n=0;n<4;n++)
            {
                words[l][n] = words[l-1][n] ^ words[l-4][n];
            }
        }
    }

    int loc=0;
    for(int i=0;i<44;i++ )
    {
        for(int j=0;j<4;j++)
        {
            expandedKey[loc] = words[i][j];
            loc++;
        }
    }
    return expandedKey;
}


void AESEncryption(unsigned char * plainText, unsigned char * expandedKey, unsigned char * cipher)
{
    unsigned char * state = malloc(16);
    //unsigned char * expandedKey = malloc(176);
    //expandedKey = keyExpansion(Key);


    //key addition for the first round
    for (int i = 0; i < 16; ++i)
    {
     state[i] = plainText[i] ^ expandedKey[i];
    }

    //now the 9 rounds begin
    for(int rounds = 1; rounds<10; rounds++)
    {
        byteSubShiftRow(state);
        mixColumns(state);
        int counter = 0;
        int loc = rounds*16;
        while(counter<16)
        {
            state[counter] ^= expandedKey[loc];
            loc++;
            counter++;
        }
    }

    //10th round
    byteSubShiftRow(state);
    for(int i=0; i<16;i++)
    {
        cipher[i] = state[i] ^ expandedKey[i+160];
    }
    free(state);
}
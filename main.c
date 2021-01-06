#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][2] = {"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][3]= {"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};

const char languages[2][8]= {"english", "german"};

//Ýngilizce dilinin frekans deðerleri
const float frequency_eng[20]= { 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Almanca dilinin frekans deðerleri
const float frequency_germ[20]= { 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances [2]= {0,0};


void filter_str(char str[])
{
    int i,j;
    for (i = 0; i<sizeof(str)/sizeof(str[0]); ++i)
    {
        while (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] == '\0'))
        {
            for (j = i; str[j] != '\0'; ++j)
            {
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }

    printf("Output Text: ");
    puts(str);
}

void calculate_frequencies_bi(char str[])
{
    int i,j;
    float keep=0;
    float keep2=0;

    for(i=0; i<10; i++)
    {
        for(j=0; j<100; j++)
        {
            if(str[j]==matrix_bigram_strings[i][0] && str[j+1]==matrix_bigram_strings[i][1])
            {
                keep++;
                j++;
                keep2++;
                calculated_frequencies[i]=keep;

            }
        }
        keep=0;
    }

    printf("%f ADET BIGRAM\n",keep2);

    for(i=0; i<10; i++)
    {
        printf("[");
        for(j=0; j<2; j++)
        {
            printf("%c",matrix_bigram_strings[i][j]);
        }
        printf("] -- %f\n",calculated_frequencies[i]);
    }

}


void calculate_frequencies_tri(char str[])
{
    int i,j;
    float keep=0;
    float keep2=0;
    for(i=0; i<10; i++)
    {
        for(j=0; j<100; j++)
        {
            if(str[j]==matrix_trigram_strings[i][0] && str[j+1]==matrix_trigram_strings[i][1] && str[j+2]==matrix_trigram_strings[i][2])
            {
                keep++;
                j=j+2;
                keep2++;
                calculated_frequencies[i+10]=keep;

            }
        }
        keep=0;
    }

    printf("%f ADET TRIGRAM\n",keep2);

    for(i=0; i<10; i++)
    {
        printf("[");
        for(j=0; j<3; j++)
        {
            printf("%c",matrix_trigram_strings[i][j]);
        }
        printf("] -- %f\n",calculated_frequencies[10+i]);
    }
}


void calculate_distances()
{
    int i;
    float eng_keep=0;
    float ger_keep=0;
    float eng_dis,ger_dis;
    for(i=0; i<20; i++)
    {
        eng_keep=eng_keep+pow(calculated_frequencies[i]-frequency_eng[i],2);
        ger_keep=ger_keep+pow(calculated_frequencies[i]-frequency_germ[i],2);
    }
    eng_dis=sqrt(eng_keep);
    ger_dis=sqrt(ger_keep);

    distances[0]=eng_dis;
    distances[1]=ger_dis;


}
void detect_lang()
{
    int i;
    float a=7.414498-distances[1];
    float b=5.349055-distances[0];
    if(a<0)
    {
        for(i=0; i<8; i++)
        {
            printf("%c",languages[0][i]);
        }
    }
    else if(b<0)
    {
        for(i=0; i<8; i++)
        {
            printf("%c",languages[1][i]);
        }
    }

    else if(b<a)
    {
        for(i=0; i<8; i++)
        {
            printf("%c",languages[0][i]);
        }
    }
    else if(b>a)
    {
        for(i=0; i<8; i++)
        {
            printf("%c",languages[1][i]);
        }
    }

}

int main()
{
    char str[100];
    printf("METNI GIRINIZ:\n");
    gets(str);

    filter_str(str);
    calculate_frequencies_bi(str);
    calculate_frequencies_tri(str);
    calculate_distances();
    detect_lang();

}

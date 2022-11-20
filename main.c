#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct DataSet
{
    char id[20];
    char product[100];
    char issue[100];
    char company[100];
    char state[10];
    char complaintId[20];
    char ZIP[10];
};

struct DataSet records[1000];

struct DataSet similars[1000][1000];
int numberOfArraysInSimilars = 0;
int sizeOfEveryArrayInSimilars[1000];

void getProducts(int start, int end)
{
    // rows = end-start
    char *tmp;
    int rows = 0;
    FILE *file = fopen("out.csv", "r");

    if (!file)
    {
        printf("Could not open the file\n");
        return 0;
    }

    char content[1024];

    for (int i = 0; fgets(content, 1024, file) != NULL; i++)
    {

        tmp = strtok(content, ",");
        strcpy(records[i].id, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].product, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].issue, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].company, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].state, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].complaintId, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].ZIP, tmp);

        // printf("index i= %i  ID: %s, %s, %s, %s, %s, %s, %s \n", i, records[i].id, records[i].product, records[i].issue,
        //      records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);

        if (rows > end)
        {
            break;
        }
        rows++;
        // printf("\n");
    }

    fclose(file);
}

int numberOfWords(char *s)
{
    int count = 1;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ' && s[i + 1] != ' ')
            count++;
    }
    return count;
}

void wordsOfSentence(char newString[20][10], char *str)
{
    int i, j, ctr;

    j = 0;
    ctr = 0;
    for (i = 0; i <= (strlen(str)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str[i] == ' ' || str[i] == '\0')
        {
            newString[ctr][j] = '\0';
            ctr++; // for next word
            j = 0; // for next word, init index to 0
        }
        else
        {
            newString[ctr][j] = tolower(str[i]);
            j++;
        }
    }
}

float similarityPersentage(char *a, char *b)
{
    int similarWords = 0;
    float persentage;
    int len1 = numberOfWords(a);
    int len2 = numberOfWords(b);
    int greatest = len1;

    if (greatest < len2)
        greatest = len2;

    char wordsArr1[20][10];
    char wordsArr2[20][10];
    wordsOfSentence(wordsArr1, a);
    wordsOfSentence(wordsArr2, b);

    if (len1 > len2)
    {
        for (int i = 0; i < len1; i++)
        {
            for (int j = 0; j < len2; j++)
            {
                if (strcmp(wordsArr1[i], wordsArr2[j]) == 0)
                {
                    // printf("%s %s, i: %d, j: %d\n", wordsArr1[i], wordsArr2[j], i, j);
                    similarWords++;
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < len2; i++)
        {
            for (int j = 0; j < len1; j++)
            {
                if (strcmp(wordsArr2[i], wordsArr1[j]) == 0)
                {
                    // printf("%s %s, i: %d, j: %d\n", wordsArr1[i], wordsArr2[j], i, j);
                    similarWords++;
                    break;
                }
            }
        }
    }

    // printf("word num: %d\n", similarWords);
    persentage = (similarWords / (float)greatest) * 100;
    // printf("persentage: %f", persentage);
    return persentage;
}

int checkSimilarity(struct DataSet data)
{

    printf(" ");
}

void sortProducts(float originalPersentage)
{
    float persentage;
    int count;
    for (int i = 1; i < 1000; i++)
    {
        // Starting The Block
        count = 0;
        for (int j = i + 1; j < 1000; j++)
        {
            // printf("before: %s , %s\n", records[1].product, records[i].product);
            persentage = similarityPersentage(records[i].product, records[j].product);
            if (persentage > originalPersentage)
            {
                printf("%s , %s, j: %d\n", records[i].product, records[j].product, j);
                similars[numberOfArraysInSimilars][count] = records[j];
                count++;
            }
        }
        // perscheck = similarityPersentage(records[i].product, records[j].product);
        sizeOfEveryArrayInSimilars[numberOfArraysInSimilars] = count;
        numberOfArraysInSimilars++;
        // End of The Block
    }
}

void showSimilars()
{

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < sizeOfEveryArrayInSimilars[0]; j++)
        {
            printf("index i= %i  ID: %s, %s, %s, %s, %s, %s, %s \n", i, similars[i][j].id, similars[i][j].product, similars[i][j].issue,
                   similars[i][j].company, similars[i][j].state, similars[i][j].complaintId, similars[i][j].ZIP);
        }
    }
}

int main()
{
    getProducts(0, 1000);
    sortProducts(60);
    showSimilars();
    printf("numberOfArraysInSimilars: %d\n", numberOfArraysInSimilars);
    printf("sizeOfEveryArrayInSimilars: %d\n", sizeOfEveryArrayInSimilars[0]);
    // int arraySize = sizeof(similars[0]) / sizeof(struct DataSet);
    // printf("size of array: %d \n ", arraySize);
    //  char records[1000][7][1000];
    //  getProducts(0, 100);
    //  records = sortProducts(0,100);
    //  int a = numberOfWords("Credit reporting credit repair services personal consumer reports");
    //  printf("%d", a);
    //  similarityPersentage("Credit reporting credit repair services personal consumer reports", "Credit reporting");
    //  char newString[20][10];
    //  wordsOfSentence(newString, "Credit reporting credit repair services personal consumer reports");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>

typedef struct DataSet
{
    char id[20];
    char product[100];
    char issue[100];
    char company[100];
    char state[10];
    char complaintId[20];
    char ZIP[10];
} DataSet;

struct DataSet *records;
// struct DataSet records[100000];

struct DataSet **similars;
int numberOfArraysInSimilars = 0;
int sizeOfEveryArrayInSimilars[100];

void test(int start);
void showSimilars();
int checkSimilarity(struct DataSet data);
float similarityPersentage(char *a, char *b);
int wordsOfSentence(char newString[30][20], char *str);
int numberOfWords(char *s);

void getProducts(int start, int end)
{
    records = (struct DataSet *)malloc(1167023 * sizeof(struct DataSet));
    similars = (DataSet **)malloc(50 * sizeof(DataSet *));
    for (int i = 0; i < 50; i++)
    {
        similars[i] = (DataSet *)malloc(sizeof(DataSet) * 800000);
    }
    // rows = end-start
    char *tmp;
    int rows = start;
    int count = 1;
    char content[1024];
    // Opening The file
    FILE *file = fopen("nostopwords.csv", "r");

    if (!file)
    {
        printf("Could not open the file\n");
        return;
    }
    // getting to the start record
    while (count < start + 1)
    {
        fgets(content, 1024, file);
        count++;
    }

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

        printf("ID: %s, %s, %s, %s, %s, %s, %s \n", records[i].id, records[i].product, records[i].issue,
               records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);

        rows++;
        if (rows > end)
        {
            break;
        }

        printf("\n");
    }

    fclose(file);
}

void sortProducts(float originalPersentage, int limit)
{
    float persentage;
    int count;
    int similarityCheck;
    for (int i = 1; i < limit; i++)
    {
        // Check if the item in the similars array or not
        //     if yes go to the next i
        //     if not start the block
        similarityCheck = checkSimilarity(records[i]);
        // printf("similarityCheck: %d\n", similarityCheck);
        if (similarityCheck == 1)
        {
            // Starting The Block
            count = 0;
            for (int j = i + 1; j < limit; j++)
            {
                persentage = similarityPersentage(records[i].product, records[j].product);
                printf("ID(%s): %s , %s, %f\n", records[i].id, records[1].product, records[i].product, persentage);
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
}

struct args{
    int start;
    int end;
    FILE * file;
}typedef args;

int main()
{
    // test(0);

    // getProducts(0, 10);
    // getProducts(11, 15);
    // getProducts(16, 25);
    // getProducts(0, 6);

    // sortProducts(60, 6);
    // showSimilars();
    // printf("numberOfArraysInSimilars: %d\n", numberOfArraysInSimilars);
    // for (int i = 0; i < numberOfArraysInSimilars; i++)
    //     printf("sizeOfEveryArrayInSimilars [%s] (%d): %d\n", similars[i]->product, i, sizeOfEveryArrayInSimilars[i]);

    // int arraySize = sizeof(similars[0]) / sizeof(struct DataSet);
    // printf("size of array: %d \n ", arraySize);
    //  char records[1000][7][1000];
    //  getProducts(0, 100);
    //  records = sortProducts(0,100);
    //  int a = numberOfWords("Credit reporting credit repair services personal consumer reports");
    //  printf("%d", a);
    
    //similarityPersentage("  Checking savings account ", "   Checking Savings account ");

    struct args *args1 = malloc (sizeof (struct args));
    args1->start = 0;
    args1->end = 100;
    args1->file = fopen("stopwords.csv","r");

    struct args *args2 = malloc (sizeof (struct args));
    args2->start = 101;
    args2->end = 200;
    args2->file = fopen("stopwords.csv","r");

    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, &threading, args1);
    pthread_create(&t2, NULL, &threading, args2);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    // char newString[20][10];
    // int k = wordsOfSentence(newString, "Checking savings account ");
    // printf("k: %d", k);

    return 0;
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

int wordsOfSentence(char newString[30][20], char *str)
{
    int i, j, ctr;
    j = 0;
    ctr = 0;
    for (i = 0; i <= (strlen(str)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]

        if (str[i] == ' ' || str[i] == '\0')
        {
            if (strlen(newString[ctr]) != 0)
            {
                newString[ctr][j] = '\0';
                ctr++; // for next word
                j = 0; // for next word, init index to 0
            }
        }
        else
        {
            newString[ctr][j] = tolower(str[i]);
            j++;
        }
    }
    return ctr;
}

float similarityPersentage(char a[20], char b[20])
{
    int similarWords = 0;
    float persentage;
    char wordsArr1[30][10] = {""};
    char wordsArr2[30][10] = {""};
    // printf("-%s-\n", a);
    // printf("-%s-\n", b);
    int len1 = wordsOfSentence(wordsArr1, a);
    int len2 = wordsOfSentence(wordsArr2, b);
    int greatest;

    // printf("len1: %d\n", len1);
    // printf("len2: %d\n", len2);
    if (len1 > len2)
    {
        greatest = len1;
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
        greatest = len2;
        for (int i = 0; i < len2; i++)
        {
            for (int j = 0; j < len1; j++)
            {
                if (strcmp(wordsArr2[i], wordsArr1[j]) == 0)
                {
                    printf("%s %s, i: %d, j: %d\n", wordsArr1[i], wordsArr2[j], i, j);
                    similarWords++;
                    break;
                }
            }
        }
    }

    // printf("word num: %d\n", similarWords);
    persentage = (similarWords / (float)greatest) * 100;
    printf("persentage: %f", persentage);
    return persentage;
}

int checkSimilarity(struct DataSet data)
{
    // Takes the data and compare it to the similars array
    // if 100% match return 0 -> Don't Start The Block Go to the next i (Data Set)
    // else return 1 -> Start Searching for the record with the Block
    float persentage;
    if (numberOfArraysInSimilars == 0)
    {
        return 1;
    }
    for (int i = 0; i < numberOfArraysInSimilars; i++)
    {
        persentage = similarityPersentage(data.product, similars[i]->product);
        // printf("persentage: %f\n", persentage);
        if (persentage == 100.0)
        {
            return 0;
        }
    }
    return 1;
}

void showSimilars()
{

    for (int i = 0; i < numberOfArraysInSimilars; i++)
    {
        for (int j = 0; j < sizeOfEveryArrayInSimilars[i]; j++)
        {
            printf("index i= %i  ID: %s, %s, %s, %s, %s, %s, %s \n", i, similars[i][j].id, similars[i][j].product, similars[i][j].issue,
                   similars[i][j].company, similars[i][j].state, similars[i][j].complaintId, similars[i][j].ZIP);
        }
    }
}

void test(int start)
{
    char *tmp;
    int rows = 0;
    FILE *file = fopen("nostopwords.csv", "r");

    if (!file)
    {
        printf("Could not open the file\n");
    }
    int count = 0;
    char content[1024];

    while (count < start + 1)
    {
        fgets(content, 1024, file);
        count++;
    }

    printf("%s\n", content);
    printf("ftell: %d\n", ftell(file));
    fgets(content, 1024, file);
    printf("%s\n", content);
    printf("ftell: %d\n", ftell(file));
}

char ** threading(void* arguments){
    clock_t time_start, time_end;
    double cpu_time_used;

    time_start = clock();

    struct args *args = (struct args *)arguments;
    char ** strings = malloc((args->end - args->start) * sizeof(char *));

    for(int i = 0 ; i < (args->end - args->start) ; i++){
        strings[i] = malloc(sizeof(char) * 1024);
    }

    int count = 0;
    char content[1024];
    while (count < args->start + 1)
    {
        fgets(content, 1024, args->file);
        count++;
    }
    
    for(int i = 0 ; i < (args->end - args->start) ; i++){
        fgets(content, 1024, args->file);
        for(int j = 0 ; j < (args->end - args->start) ; j++){
            strings[i][j] = content;
            printf()
        }
    }

    time_end = clock();
    cpu_time_used = ((double) (time_end - time_start)) / CLOCKS_PER_SEC;
    return strings; 
}
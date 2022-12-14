#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

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

struct Args
{
    int start;
    int end;
} typedef Args;

// struct DataSet records[100000];

float originalPersentage = 60;

struct DataSet **similars;
int numberOfArraysInSimilars = 0;
int sizeOfEveryArrayInSimilars[20] = {0};

void test(int start);
void showSimilars();
int checkSimilarity(struct DataSet data);
float similarityPersentage(char *a, char *b);

void sortProducts1(struct DataSet *records, int limit)
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
            similars[numberOfArraysInSimilars][count] = records[i];
            count++;
            for (int j = i + 1; j < limit; j++)
            {
                persentage = similarityPersentage(records[i].product, records[j].product);
                // printf("I(%d): %s , %s, %f, org: %f\n", j, records[i].product, records[j].product, persentage, originalPersentage);
                if (persentage > originalPersentage)
                {
                    // printf("%s , %s, j: %d\n", records[i].product, records[j].product, j);
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
void sortProducts(struct DataSet *records, int limit)
{
    printf("Sorting...\n");
    float persentage;
    int count;
    int similarityCheck;
    char category[20][100] = {"Checking savings account",
                              "Debt collection",
                              "Credit reporting credit repair services personal consumer reports",
                              "Mortgage",
                              "Student loan",
                              "Vehicle loan lease",
                              "Credit card prepaid card",
                              "Payday loan title loan personal loan",
                              "Money transfer virtual currency money service",
                              "Credit reporting",
                              "Credit card",
                              "Bank account service",
                              "Consumer Loan",
                              "Prepaid card",
                              "Other financial service",
                              "Payday loan",
                              "Money transfers",
                              "Virtual currency"};

    // printf("----------%s\n", category[0]);

    float persentages[20];
    for (int i = 1; i < limit; i++)
    {

        for (int k = 0; k < 18; k++)
        {
            persentages[k] = similarityPersentage(records[i].product, category[k]);
            // printf("KBefore(%d): %s , %s, %f, org: %f\n", k, records[i].product, category[k], persentages[k], originalPersentage);
            if (persentages[k] > originalPersentage)
            {
                // printf("I(%d): %s , %s, %f, org: %f\n", i, records[i].product, category[k], persentages[k], originalPersentage);
                int position = sizeOfEveryArrayInSimilars[k];
                similars[k][position] = records[i];
                sizeOfEveryArrayInSimilars[k]++;
            }
        }
    }
}

void *getProducts(void *arguments)
{
    // getting start and end from arguments
    struct Args *args = (struct Args *)arguments;
    int start = args->start;
    int end = args->end;
    printf("start: %d, end: %d\n", start, end);
    int limit = end - start;
    struct DataSet *records;
    records = (struct DataSet *)malloc((limit + 5) * sizeof(struct DataSet));

    // rows = end-start
    char *tmp;
    int rows = start;
    int count = 1;
    char content[1024];
    // Opening The file
    FILE *file = fopen("out.csv", "r");

    if (!file)
    {
        printf("Could not open the file\n");
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

        // printf("ID: %s, %s, %s, %s, %s, %s, %s \n", records[i].id, records[i].product, records[i].issue,
        //     records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);

        rows++;
        if (rows > end)
        {
            break;
        }

        printf("\n");
    }

    fclose(file);
    // sorting the records
    // printf("\n\noriginalPersentage: %f\n\n", originalPersentage);
    printf("Done Reading start: %d\n", start);
    sortProducts1(records, limit);
}

int wordsOfSentence(char newString[30][10], char *str)
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
    // for (int k = 0; k < ctr; k++)
    // {
    //     printf("-%s-\n", newString[k]);
    // }
    return ctr;
}

void *threadedSort(int NUM_THREADS, float persentage)
{
    originalPersentage = persentage;
    // next block will be moved to thread function
    similars = (DataSet **)malloc(50 * sizeof(DataSet *));
    for (int i = 0; i < 50; i++)
    {
        similars[i] = (DataSet *)malloc(sizeof(DataSet) * 800000);
    }

    int start, end;

    int num = 1000000 / NUM_THREADS;

    pthread_t threads[NUM_THREADS];
    struct Args *args = malloc(sizeof(struct Args) * NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        args[i].start = i * num + 1;
        args[i].end = (i + 1) * num;
        // printf("start: %d, end: %d\n", args[i].start, args[i].end);
        pthread_create(&threads[i], NULL, getProducts, &args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void getProducts1(int start, int end)
{
    int limit = end - start;
    struct DataSet *records;
    records = (struct DataSet *)malloc((limit + 5) * sizeof(struct DataSet));
    // rows = end-start
    char *tmp;
    int rows = start;
    int count = 1;
    char content[1024];
    // Opening The file
    FILE *file = fopen("out.csv", "r");

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

    FILE *datafile;
    if ((datafile = fopen("datafile.bin", "w")) == NULL)
    {
        printf("Error Opening\n");
        return;
    }
    // printf("22222222\n");
    struct DataSet newData;
    for (int i = 0; fgets(content, 1024, file) != NULL; i++)
    {
        // printf("33333\n");
        tmp = strtok(content, ",");
        strcpy(records[i].id, tmp);
        strcpy(newData.id, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].product, tmp);
        strcpy(newData.product, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].issue, tmp);
        strcpy(newData.issue, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].company, tmp);
        strcpy(newData.company, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].state, tmp);
        strcpy(newData.state, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].complaintId, tmp);
        strcpy(newData.complaintId, tmp);

        tmp = strtok(NULL, ",");
        strcpy(records[i].ZIP, tmp);
        strcpy(newData.ZIP, tmp);

        // printf("ID: %s, %s, %s, %s, %s, %s, %s \n", records[i].id, records[i].product, records[i].issue,
        //        records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);
        fwrite(&newData, sizeof(struct DataSet), 1, datafile);

        rows++;
        if (rows > end)
        {
            break;
        }

        printf("\n");
    }

    fclose(file);
    fclose(datafile);
    // sortProducts1(records, limit);
}

void NoThreadSort(int limit, float persentage)
{
    originalPersentage = persentage;
    // next block will be moved to thread function
    similars = (DataSet **)malloc(20 * sizeof(DataSet *));
    for (int i = 0; i < 20; i++)
    {
        similars[i] = (DataSet *)malloc(sizeof(DataSet) * 100000);
    }

    int start, end;

    // printf("11111111111\n");
    getProducts1(0, limit);
}

void readBinFile()
{
    FILE *file;
    if ((file = fopen("datafile.bin", "r")) == NULL)
    {
        printf("Error Opening\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    int endOfTheFile = ftell(file);
    int idx;

    if (endOfTheFile == 0)
    {
        printf("No records");
    }
    rewind(file);
    for (int i = 0;; i++)
    {
        struct DataSet data;
        size_t num = fread(&data, sizeof(struct DataSet), 1, file);
        printf("size: %d\n", num);
        printf("ID: %s, %s, %s, %s, %s, %s, %s \n", data.id, data.product, data.issue,
               data.company, data.state, data.complaintId, data.ZIP);
        idx = ftell(file);
        if (idx == endOfTheFile)
        {
            break;
        }
    }

    fclose(file);
}

int main()
{
    clock_t time_start = clock();
    // NoThreadSort(1000000, 60);
    // readBinFile();
    // threadedSort(8, 60);
    clock_t time_end = clock();
    double cpu_time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
    printf("\nTime: %f\n", cpu_time_used);
    // sortProducts(60, 6);
    // showSimilars();
    // printf("numberOfArraysInSimilars: %d\n", numberOfArraysInSimilars);
    // for (int i = 0; i < numberOfArraysInSimilars; i++)
    //     printf("sizeOfEveryArrayInSimilars [%s] (%d): %d\n", similars[i]->product, i, sizeOfEveryArrayInSimilars[i]);

    // float per = 25.00000;
    // float org = 60.0;
    // if (per > org)
    // {
    //     printf("Yeah\n");
    // }
    // int arraySize = sizeof(similars[0]) / sizeof(struct DataSet);
    // printf("size of array: %d \n ", arraySize);
    //  char records[1000][7][1000];
    //  getProducts(0, 100);
    //  records = sortProducts(0,100);
    //  int a = numberOfWords("Credit reporting credit repair services personal consumer reports");
    //  printf("%d", a);

    // float n = similarityPersentage("  Checking savings account ", "Debt collection");
    // printf("p: %f\n", n);
    // char newString[30][10] = {""};
    // int g = wordsOfSentence(newString, " Checking savings account ");
    // printf("g: %d\n", g);
    // for (int k = 0; k < 3; k++)
    // {
    //     printf("-%s-\n", newString[k]);
    // }

    return 0;
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
    // for (int k = 0; k < len1; k++)
    // {
    //     printf("-%s-\n", wordsArr1[k]);
    // }
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
                    // printf("%s %s, i: %d, j: %d\n", wordsArr1[i], wordsArr2[j], i, j);
                    similarWords++;
                    break;
                }
            }
        }
    }

    // printf("word num: %d\n", similarWords);
    persentage = (similarWords / (float)greatest) * 100;
    // printf("persentage: %f\n", persentage);
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
    FILE *file = fopen("sorted.csv", "w");

    if (!file)
    {
        printf("Could not open the file\n");
        return;
    }

    for (int i = 0; i < numberOfArraysInSimilars; i++)
    {
        for (int j = 0; j < sizeOfEveryArrayInSimilars[i]; j++)
        {
            fprintf(file, "%s, %s, %s, %s, %s, %s, %s", similars[i][j].id, similars[i][j].product, similars[i][j].issue,
                    similars[i][j].company, similars[i][j].state, similars[i][j].complaintId, similars[i][j].ZIP);

            if (ferror(file))
            {
                printf("Error in file");
            }
        }
    }
}

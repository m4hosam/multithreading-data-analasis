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

struct DataSet *records;

float originalPersentage = 60;

struct DataSet **similars;
int numberOfArraysInSimilars = 0;
int sizeOfEveryArrayInSimilars[30] = {0};

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
        persentage = similarityPersentage(data.product, similars[i][0].product);
        // printf("persentage: %f\n", persentage);
        if (persentage == 100.0)
        {
            return 0;
        }
    }
    return 1;
}

int checkSimilarityWithArray(char lastSimilars[50][200], char *str, int count)
{
    // Takes the data and compare it to the similars array
    // if 100% match return 0 -> Don't Start The Block Go to the next i (Data Set)
    // else return 1 -> Start Searching for the record with the Block

    float persentage;
    // printf("Count: %d\n\n", count);
    if (count == 0)
    {
        return 1;
    }
    for (int i = 0; i < count; i++)
    {
        // printf("\nForm check siimilarity: -%s-and-%s-\n\n", lastSimilars[i], str);
        persentage = similarityPersentage(lastSimilars[i], str);
        // printf("persentage: %f\n", persentage);
        if (persentage == 100.0)
        {
            // printf("\n2222222Form check siimilarity: -%s-and-%s-\n\n", lastSimilars[i], str);
            return 0;
        }
    }
    return 1;
}

void saveSimilars()
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

void sortProducts(struct DataSet *records, int limit)
{
    clock_t time_start = clock();
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
    clock_t time_end = clock();
    double cpu_time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
    printf("\nTime in Sort: %f\n", cpu_time_used);
}

void getProducts(int start, int end)
{
    int limit = end - start;

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
        // fwrite(&newData, sizeof(struct DataSet), 1, datafile);

        rows++;
        if (rows > end)
        {
            break;
        }

        printf("\n");
    }

    fclose(file);
    sortProducts(records, limit);
    free(records);
}

void NoThreadSort(int limit, float persentage)
{
    originalPersentage = persentage;

    records = (struct DataSet *)malloc((limit + 5) * sizeof(struct DataSet));
    // next block will be moved to thread function
    similars = (DataSet **)malloc(20 * sizeof(DataSet *));
    for (int i = 0; i < 20; i++)
    {
        similars[i] = (DataSet *)malloc(sizeof(DataSet) * (limit * 8 / 10));
    }

    int start, end;

    getProducts(0, limit);
}

void startSenaryo2()
{
    // clear the file of senaryo 2;
    FILE *file = fopen("senaryo2.csv", "w");
    fclose(file);
}

void senaryo2(int start, int end, float orgPersentage)
{
    int ctr = 0;
    char lastSimilars[5000][200];
    FILE *file = fopen("senaryo2.csv", "a");

    // read arrays of similars
    // arrays will be divided on threads
    // numberOfArraysInSimilars / threads
    int limit;
    int count = 0;
    int numberOfArraysInSenaryo2;
    float persentage;
    int similarityCheck;
    if (end >= numberOfArraysInSimilars)
    {
        end = numberOfArraysInSimilars;
    }

    // loop in the arrays to get Issue similars with the persentage
    for (int i = start; i < end; i++)
    {
        limit = sizeOfEveryArrayInSimilars[i];
        // loop inside every array of selected similar arrays
        for (int j = 0; j < limit; j++)
        {
            //  printf("similarityCheck: %d\n", similarityCheck);
            // for (int z = 0; z < count; z++)
            // {
            // }
            similarityCheck = checkSimilarityWithArray(lastSimilars, similars[i][j].issue, ctr);
            if (similarityCheck == 1)
            {

                // Starting The Block
                // comparing each item in similars array to the next till the end
                count = 0;
                // store the first element you see
                // printf("-%d----%s, %s, %s, %s, %s, %s, %s\n", ctr, similars[i][j].id, similars[i][j].product, similars[i][j].issue,
                //        similars[i][j].company, similars[i][j].state, similars[i][j].complaintId, similars[i][j].ZIP);

                // printf("limit: %d\n", limit);
                strcpy(lastSimilars[ctr], similars[i][j].issue);
                // printf("i: %d,j: %d, limit: %d, start: %d, end: %d\n", i, j, limit, start, end);
                fprintf(file, "%s, %s, %s, %s, %s, %s, %s", similars[i][j].id, similars[i][j].product, similars[i][j].issue,
                        similars[i][j].company, similars[i][j].state, similars[i][j].complaintId, similars[i][j].ZIP);
                // printf("33333333333333333\n");
                count++;
                ctr++;
                for (int k = j + 1; k < limit; k++)
                {
                    persentage = similarityPersentage(similars[i][j].issue, similars[i][k].issue);
                    // printf("I(%d): %s , %s, %f, org: %f\n", j, records[i].product, records[j].product, persentage, originalPersentage);
                    // if element found store it
                    if (persentage > orgPersentage)
                    {
                        // printf("-----%s, %s, %s, %s, %s, %s, %s\n", similars[i][k].id, similars[i][k].product, similars[i][k].issue,
                        //        similars[i][k].company, similars[i][k].state, similars[i][k].complaintId, similars[i][k].ZIP);
                        fprintf(file, "%s, %s, %s, %s, %s, %s, %s", similars[i][k].id, similars[i][k].product, similars[i][k].issue,
                                similars[i][k].company, similars[i][k].state, similars[i][k].complaintId, similars[i][k].ZIP);
                        count++;
                    }
                }
                // End of The Block
            }
        }
    }
    // Add them into array
    // Save them to senaryo2.csv
    fclose(file);
}
void startSenaryo3()
{
    FILE *file = fopen("senaryo3.csv", "w");
    fclose(file);
}

void senaryo3(int start, int end, int complaintIdi, float orgPersentage, int limit)
{
    int ctr = 0;
    int count = 0;
    int similarityCheck;
    char lastSimilars[50][200] = {""};
    FILE *file = fopen("senaryo3.csv", "a");
    float persentage;
    char complaintId[20];
    char issue[200] = "";
    sprintf(complaintId, "%d", complaintIdi);

    for (int idx = 0; idx < limit; idx++)
    {
        if (strcmp(records[idx].complaintId, complaintId) == 0)
        {
            strcpy(issue, records[idx].issue);
            break;
        }
    }

    if (strcmp(issue, "") != 0)
    {
        printf("Issue: %s\n\n", issue);

        for (int i = start; i < end; i++)
        {

            persentage = similarityPersentage(records[i].issue, issue);
            // printf("I(%d): %s , %s, %f, org: %f\n", j, records[i].product, records[j].product, persentage, originalPersentage);
            if (persentage > orgPersentage)
            {
                printf("-1----%s, %s, %s, %s, %s, %s, %s\n", records[i].id, records[i].product, records[i].issue,
                       records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);
                fprintf(file, "%s, %s, %s, %s, %s, %s, %s", records[i].id, records[i].product, records[i].issue,
                        records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);
            }
        }
    }
    else
    {
        printf("Error in complaintId \nnot found\n");
    }

    fclose(file);
}

void startSenaryo4(int threadsNo)
{
    char tmp[30];
    for (int i = 1; i < threadsNo + 1; i++)
    {
        sprintf(tmp, "senaryo4_%d.csv", i);
        FILE *file = fopen(tmp, "w");
        fclose(file);
    }
}

// void senaryo4(int start, int end, float persentage, int threadNo)
// {
//     // threads No is used to store the result to the related csv file
// }

int getNumberOfArraysInSimilars()
{
    return numberOfArraysInSimilars;
}

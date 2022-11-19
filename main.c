#include <stdio.h>
#include <string.h>

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

struct DataSet records[1000000];

void sortProducts(int start, int end)
{
    // rows = end-start
    char *tmp;
    // char similars[1000][7][200];

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

        printf("index i= %i  ID: %s, %s, %s, %s, %s, %s, %s \n", i, records[i].id, records[i].product, records[i].issue,
               records[i].company, records[i].state, records[i].complaintId, records[i].ZIP);
        // for (int j = 0; v != NULL; j++, v = strtok(NULL, ","))
        // {
        //     strcpy(temp[i][j], v);
        //     // printf("j: %d :%s ", j, v);
        // }

        rows++;
        if (rows > end)
        {
            break;
        }
        // printf("\n");
    }

    fclose(file);

    // Getting the similarity will be moved to another function
    printf("rows: %d\n", rows);
    // printf("row 0: %s\n", records[1][2]);

    /*for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%s ", records[i][j]);
        }
        printf("\n");
    }*/
    // return records;
}

int main()
{
    // char records[1000][7][1000];
    sortProducts(0, 100);
    // records = sortProducts(0,100);
    /*
    char records[1000][7][200];
    char ch[20] = "text";
    strcpy(records[0][1], ch);
    printf("%s",records[0][1] );
*/
    return 0;
}

#include <stdio.h>
#include <string.h>

void sortProducts(char records[1000][7][1000], int start, int end)
{
    int rows = 0;
    FILE *file = fopen("out.csv", "r");

    if (!file)
    {
        printf("Could not open the file\n");
        return 0;
    }

    char content[1024];

    for(int i = 0 ; fgets(content, 1024, file) != NULL; i++)
    {

        char *v = strtok(content, ",");
        //printf("i: %d\n", i);
        for(int j = 0 ; v != NULL ; j++, v = strtok(NULL, ","))
        {
            sprintf(records[i][j], v);
            //printf("j: %d :%s ", j, v);
        }
        rows++;
        if(rows > end){
            break;
        }
        //printf("\n");
    }

    fclose(file);
    //printf("rows: %d\n",rows);
    //printf("row 0: %s\n", records[1][2]);
/*
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < 7 ; j++)
        {
            printf("%s ", records[i][j]);
        }
        printf("\n");
    }*/
    //return records;


}


int main()
{
    //back in 15 min

    char records[1000][7][1000];
    sortProducts(records,0,100);
    //records = sortProducts(0,100);
    for (int i = 0 ; i < 100 ; i++)
    {
        for (int j = 0 ; j < 7 ; j++)
        {
            printf("%s ", records[i][j]);
        }
        printf("\n");
    }
    //char records[1000][7][200];
    //char ch[20] = "text";
    //strcpy(records[0][1], ch);
    //records[0][0] = ch;
    //printf("%s",records[0][1] );

    return 0;
}

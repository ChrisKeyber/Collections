#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
struct books_rec{
    int price;
    char author[100];
    char name [100];
};
//file exists error problem
int file_exists(const char *filename) // https://www.learnc.net/c-tutorial/c-file-exists/ 
{
    FILE *fp = fopen(filename, "r");
    int is_exist = 0;
    if (fp != NULL) //check the file name is in directory or not
    {
        is_exist = 1;
        fclose(fp); 
    }
    return is_exist;
}

int valindex(const char *filename){
    int boo= 0;
    FILE *fp = fopen(filename, "r");
    if(file_exists(filename)==0){
        boo = 1;
    }
    char check[500]; //48-57, 0-9
    fgets(check, 500, fp);
    for(int i=0;i<strlen(check);i++){
        if(check[i]<48 || check[i]>57){
            boo = 1;
        } else{
            boo = 0;
        }
    }
    return boo;
}

int main(){
    int i;
    char collection[100], filename[100];
    int lastrec=0;
    printf("When you open the program, you have seen the \"readme!\" file attaching");
    printf("\nEnter collection name: ");
    gets(collection);
    strcpy(filename, collection);
    strcat(filename, ".txt");
    char indexf[100];
    strcpy(indexf, collection);
    strcat(indexf, ".inx");
    FILE * fpinx = fopen(indexf, "r");
    fflush(stdin);

    if(file_exists(filename) ==0){
        if(file_exists(indexf)==1){
            printf("name repeate index");
            return 1;
        }
        FILE * fpa = fopen(filename, "a");
        FILE * fpw = fopen(filename, "w");
        fprintf(fpw, "Colletion name: %s", collection);
        fclose(fpw);
        printf("How many books in your collection: ");
        int amount;
        scanf("%d", &amount);
        fflush(stdin);
        struct books_rec book[amount] ;

        char name_temp[100], aut_temp[100];
        for(i=0;i<amount;i++){ //collecting 
            lastrec++;
            printf("%d. book name: ", i+1);
            gets(name_temp);
            strcpy(book[i].name, name_temp);
            printf("Price: ");
            scanf("%d", &book[i].price);
            fflush(stdin);
            printf("Author name: ");
            gets(aut_temp);
            strcpy(book[i].author, aut_temp);
        }
        fprintf(fpa, "\n\nBelows are the record\n\n");
        for(i=0;i<amount;i++){
            fprintf(fpa, "Index:%d \n", i+1);
            fprintf(fpa, "Book: %s \n", book[i].name);
            fprintf(fpa, "By: %s \n", book[i].author);
            fprintf(fpa, "Price: $%d \n\n\n", book[i].price);
        }

        FILE * fin= fopen(indexf, "w");
        fprintf(fin, "%d", lastrec);
        fclose(fin);

        printf("File created, you may exit");
    } else{
        printf("Collection has already existed, 1 for add rec, 2 for cancel 3 for del: ");
        int choice;
        scanf("%d", &choice);
        fflush(stdin);
        if(choice == 1){
            FILE * fpa = fopen(filename, "a");
            if(valindex(indexf)==1){
                printf("Index error(you have edit wrong things/ File is missing)");
                return 1;
            }
            if(valindex(indexf)==1 && file_exists(filename)==0){
                printf("Reocrds error");
            }
            fscanf(fpinx, "%d", &lastrec);
            printf("How many books you want to add: ");
            int amount;
            scanf("%d", &amount);
            fflush(stdin);
            struct books_rec book[amount] ;
            char name_temp[100], aut_temp[100];
            for(i=0;i<amount;i++){ //collecting 
                printf("%d. book name: ", ++lastrec);
                gets(name_temp);
                strcpy(book[i].name, name_temp);
                printf("Price: ");
                scanf("%d", &book[i].price);
                fflush(stdin);
                printf("Author name: ");
                gets(aut_temp);
                strcpy(book[i].author, aut_temp);
            }
            printf("\n\n");
            for(i=0;i<amount;i++){
                fprintf(fpa, "index:%d\n", lastrec);
                fprintf(fpa, "Book: %s \n", book[i].name);
                fprintf(fpa, "By: %s \n", book[i].author);
                fprintf(fpa, "Price: $%d \n\n\n", book[i].price);
            }
            FILE * fprewrite = fopen(indexf, "w");
            fprintf(fprewrite, "%d", lastrec);
            printf("Procedure done, you may close the program\n\n");
            system("\nPause\n");
        }else if(choice==2){
            printf("\nprogram stopped");
            system("\nPause\n");
            return 1;
        }
         else if(choice == 3){
            if(file_exists(filename) == 1){
                printf("Are you sure you want to delete this? type 1 for yes 0 for no: ");
                int choice1;
                scanf("%d", &choice1);
                if(choice1 == 1){
                    remove(indexf);
                    remove(filename);
                } else{
                    printf("Not valid, for security, program closed");
                    puts("File not deleted");
                    system("\nPause\n");
                    return 1;
                }
            } else {
                printf("File doesn't exist");
                system("\nPause\n");
                return 1;
            }
        }else{
            printf("Invalid number");
            system("\nPause\n");
            return 1;
        }
    }
}

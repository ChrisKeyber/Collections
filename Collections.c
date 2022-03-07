#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
//put error into a txt file called errored, with time, Error type in it
struct books_rec{
    int price;
    char author[100];
    char name [100];
};
//file exists error problem
int file_exists(char directory[], char filename[])
{
    char comdf[100];
    strcpy(comdf, directory);
    strcat(comdf, "//");
    strcat(comdf, filename);
    FILE *fp = fopen(comdf, "r");        //the file name include directory, then it will be ok
    int is_exist = 0;
    if (fp != NULL) //check the file name is in directory or not
    {
        is_exist = 1;
        fclose(fp); 
    }
    return is_exist;
}

int valindex(char directory[], char filename[]){ //filename = indexf
    char comdf[100];
    strcpy(comdf, directory);
    strcat(comdf, "//");
    strcat(comdf, filename);

    FILE *fp = fopen(comdf, "r");
    if(file_exists(directory, filename)==0){
        return 1;
    }
    char check[500]; 
    fgets(check, 500, fp); //getting each character into one data slot
    for(int i=0;i<strlen(check);i++){
        if(check[i]<48 || check[i]>57){
            return 2;
        } else{
            return 0;
        }
    }

}

int count_files(char directory[]){
    int filesnum=0;
    DIR * dp = opendir(directory);
    struct dirent* entity;
    entity = readdir(dp);
    while(entity!=NULL){
        filesnum++;
        entity =  readdir(dp);
    }
    return filesnum;
}

// num 5
int main(){
    int i;
    char collection[100];
    int lastrec=0;
    printf("When you use the program, you should have seen the \"readme!\" file attaching");
    printf("\nEnter collection name: ");
    gets(collection);

    char direname[100];
    strcpy(direname, collection);
    mkdir(direname);

    char filetxt[100];
    strcpy(filetxt, collection);
    strcat(filetxt, ".txt");

    char com_filetxt[100];
    strcpy(com_filetxt, direname);
    strcat(com_filetxt, "//");
    strcat(com_filetxt, filetxt);

    char indexf[100];
    strcpy(indexf, collection);
    strcat(indexf, ".inx");

    char com_indexf[100];
    strcpy(com_indexf, direname);
    strcat(com_indexf, "//");
    strcat(com_indexf, indexf);

    char error_log[100];
    strcpy(error_log, collection);
    strcat(error_log, " .log.txt");

    char com_erlog[100];
    strcpy(com_erlog, direname);
    strcat(com_erlog, "//");
    strcat(com_erlog, error_log);

    FILE * fpinxr = fopen(com_indexf, "r");
    fflush(stdin);

    if(file_exists(direname, filetxt) ==0){
        FILE* fperrorw = fopen(com_erlog, "w");
        FILE* fperrora = fopen(com_erlog, "a");
        if(file_exists(direname, indexf)==1){
            printf("Index exist but record file doesn't"); 
            fprintf(fperrora, "Missing files: txt(suggested delete folder)\n\n");
            return 1;
        }
        if(opendir(direname)!=0 && file_exists(direname, filetxt)==0 && file_exists(direname, indexf)==0 && file_exists(direname, error_log)==0){
            printf("Warn!: detected existing folder");
            fprintf(fperrora, "Warning: Existing files detected\n\n");
            int openchoice ;
            printf("Process? 1 for yes, 0 for no: \n");
            scanf("%d", &openchoice);
            while(openchoice!=0 && openchoice !=1){
                fflush(stdin);
                printf("Invalid: ");
                scanf("%d", &openchoice);
            }
            if(openchoice == 0){
                fprintf(fperrora, "Closing activity: stopped adding new records to existing files\n\n");
                return 1;
            } else{
                printf("Continue\n");
            }
        }

        FILE * fpw = fopen(com_filetxt, "w");
        FILE * fpa = fopen(com_filetxt, "a");
        fprintf(fpw, "Colletion name: %s", collection);
        fclose(fpw);
        printf("How many books in your collection: ");
        int amount;
        while(scanf("%d", &amount) == 0){
            printf("Enter number!\nHow many books in your collection: ");
            fprintf(fperrora, "Invalid input: Books collections\n\n");
            fflush(stdin);
        }

        fflush(stdin);
        struct books_rec book[amount] ;

        char name_temp[100], aut_temp[100];
        for(i=0;i<amount;i++){ //collecting 
            lastrec++;
            printf("%d. book name: ", i+1);
            gets(name_temp);
            strcpy(book[i].name, name_temp);
            printf("Price: ");
            while(scanf("%d", &book[i].price) == 0){
                printf("Enter number!\nPrice: ");
                fprintf(fperrora, "Invalid input: Books prices\n\n");
                fflush(stdin);
            }
            fflush(stdin);
            printf("Author name: ");
            gets(aut_temp);
            strcpy(book[i].author, aut_temp);
        }
        fprintf(fpa, "\n\nBooks:\n\n");
        for(i=0;i<amount;i++){
            fprintf(fpa, "Index:%d \n", i+1);
            fprintf(fpa, "Book: %s \n", book[i].name);
            fprintf(fpa, "By: %s \n", book[i].author);
            fprintf(fpa, "Price: $%d \n\n", book[i].price);
        }

        FILE * findex= fopen(com_indexf, "w");
        fprintf(findex, "%d", lastrec);
        fclose(findex);
        printf("Collection file created, you may exit\n\n");
        fclose(fpinxr);
        system("Pause");
    } 
    else{
        FILE* fperrora = fopen(com_erlog, "a");
        printf("Collection has already existed, 1 for add rec, 2 for cancel 3 for del: ");
        int choice;
        while(scanf("%d", &choice)==0 && choice<1 || choice>3){
            printf("Not valid, Retry: ");
            fprintf(fperrora, "Invalid input: dupicated files branch selections\n\n");
            fflush(stdin);
        }
        if(choice == 1){
            if(count_files(direname)>5){
            printf("Warn!: Folder contain unneccessary content\n");
            fprintf(fperrora, "Warning: Folder contain unneccessary content\n\n");
            int openchoice ;
            printf("Process? 1 for yes, 0 for no: \n");
            scanf("%d", &openchoice);
            while(openchoice!=0 && openchoice !=1){
                fflush(stdin);
                printf("Invalid: ");
                fprintf(fperrora, "Invalid input: unneccessary content branch\n\n");
                scanf("%d", &openchoice);
            }
            if(openchoice == 0){
                fprintf(fperrora, "Closing activities: stopped futher process to folder contain redundant files\n\n");
                return 1;
            } else{
                printf("Continue\n");
            }
        }
            FILE * fpa = fopen(com_filetxt, "a");

            if(valindex(direname, indexf)==1){
                printf("Index is missing");
                fprintf(fperrora, "Missing Files: Index\n\n");
                return 1;
            }
            if(valindex(direname, indexf)==2){
                printf("Index being edited with invalid data type");
                fprintf(fperrora, "Invalid input: Index contain invalid data type\n\n");
                return 1;
            }
            fscanf(fpinxr, "%d", &lastrec);
            printf("How many books you want to add: ");
            int amount;
            while(scanf("%d", &amount) == 0){
                printf("Enter number!\nHow many books in your collection: ");
                fprintf(fperrora, "Invalid input: Books amounts in collections\n\n");
                fflush(stdin);
            }
            fflush(stdin);
            struct books_rec book[amount] ;
            char name_temp[100], aut_temp[100];
            for(i=0;i<amount;i++){ //collecting 
                printf("%d. book name: ", ++lastrec);       //index keep adding while getting records
                gets(name_temp);
                strcpy(book[i].name, name_temp);
                printf("Price: ");
                while(scanf("%d", &book[i].price) == 0){
                    printf("Enter number!\nPrice: ");
                    fprintf(fperrora, "Invalid input: price of books\n\n");
                    fflush(stdin);
                }
                fflush(stdin);
                printf("Author name: ");
                gets(aut_temp);
                strcpy(book[i].author, aut_temp);
            }
            printf("\n\n");
            /*---------------------------------------------------*/
            for(i=0;i<amount;i++){
                fprintf(fpa, "index:%d\n", lastrec);
                fprintf(fpa, "Book: %s \n", book[i].name);
                fprintf(fpa, "By: %s \n", book[i].author);
                fprintf(fpa, "Price: $%d \n\n\n", book[i].price);
            }
            /*---------------------------------------------------*/
            FILE * fprewrite = fopen(com_indexf, "w");  //For rewriting a index to inx
            fprintf(fprewrite, "%d", lastrec);
            fclose(fprewrite);
            /*---------------------------------------------------*/
            printf("Procedure done, you may close the program\n\n");
            system("\nPause\n");
        }

        if(choice==2){
            printf("\nprogram stopped\n");
            fprintf(fperrora, "Closing activities: Stop further edit to exisitng files & directory\n\n");
            system("\nPause\n");
            return 1;
        }

        if(choice == 3){
            if(file_exists(direname, filetxt) == 1 && opendir(direname)!=0 ){
                printf("Are you sure you want to delete this? type 1 for yes 0 for no: ");
                int choice1;
                while(scanf("%d", &choice1) ==0 ,choice1<0 || choice1>1){
                        printf("Not valid, Retry: ");
                        fprintf(fperrora, "Invalid input: delete directory choice branch\n\n");
                        fflush(stdin);
                    } 
                if(choice1 == 1){
                    fclose(fpinxr);
                    fclose(fperrora);
                    remove(com_filetxt);
                    remove(com_indexf);
                    remove(com_erlog);
                    rmdir(direname);
                    FILE * fpdeleted = fopen("Deleted reminders.txt", "w");
                    fprintf(fpdeleted, "Your collections: \"%s\" has been deleted, you can delete this file now", collection);
                    puts("Files are deleted");
                    system("Pause");
                    return 1;
                } else if(choice ==0 ){
                    puts("File not deleted");
                    fprintf(fperrora, "Closing activity: rejected on deleteing directory\n\n");
                    system("\nPause\n");
                    return 1;
                }
            } else {
                printf("destination doesn't exist");
                fprintf(fperrora, "Missing destination: destination doesn't exist\n\n");
                system("\nPause\n");
                return 1;
            }
        }   
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient{
    int id;
    char name[25];
    int age;
    char illness[50];
};

struct patient emptyPatient = {0, "", 0, ""};
struct patient person;

FILE *fp;

void list(){
    fp = fopen("patients.txt","r+");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    printf("ID\tName\tAge\tIllness\n");
    while(!feof(fp)){
        fread(&person,sizeof(struct patient),1,fp);
        printf("%d\t%s\t%d\t%s\n",person.id,person.name,person.age,person.illness);
    }
    fclose(fp);
}

void update(){
    fp = fopen("patients.txt","r+");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    int patientID;
    printf("Enter patient ID to update:");
    scanf("%d",&patientID);
    fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
    fread(&person,sizeof(struct patient),1,fp);
    if(person.id == 0){
        printf("\nThe patient you want to update does not exist.\n");
    }
    else{
        fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
        fread(&person,sizeof(struct patient),1,fp);
        printf("\n*****Patient Information to Update*****\n");
        printf("ID:%d Name:%s Age:%d Illness:%s\n",patientID,person.name,person.age,person.illness);
        printf("*******************************\n");
        printf("Illness status:");
        char newIllness[50];
        scanf("%s",person.illness);
        printf("Age:");
        int newAge;
        scanf("%d",&newAge);
        person.age = newAge;
        fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
        fwrite(&person,sizeof(struct patient),1,fp);
        printf("\nUpdate successful.\n");
    }
    fclose(fp);
}

void delete(){
    fp = fopen("patients.txt","r+");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    int patientID;
    printf("Enter patient ID to delete:");
    scanf("%d",&patientID);
    fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
    fread(&person,sizeof(struct patient),1,fp);
    if(person.id == 0){
        printf("\nThe patient you want to delete does not exist.\n");
    }
    else{
        fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
        fwrite(&emptyPatient,sizeof(struct patient),1,fp);
        printf("\nPatient successfully deleted.\n");
    }
    fclose(fp);
}

void add(){
    fp = fopen("patients.txt","r+");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    int patientID;
    printf("Enter patient ID to add:");
    scanf("%d",&patientID);
    fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
    fread(&person,sizeof(struct patient),1,fp);
    if(person.id != 0){
        printf("\nThe patient you want to add already exists in the system.\n");
    }
    else{
        person.id = patientID;
        printf("\nEnter patient name, age:");
        scanf("%s %d",person.name,&person.age);
        printf("\nIllness:");
        scanf("%s",person.illness);
        fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
        fwrite(&person,sizeof(struct patient),1,fp);
        printf("\nRecord operation successful.\n");
    }
    fclose(fp);
}

void find(){
    fp = fopen("patients.txt","r+");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    int patientID;
    printf("Enter patient ID to find:");
    scanf("%d",&patientID);
    fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
    fread(&person,sizeof(struct patient),1,fp);
    if(person.id == 0){
        printf("The patient you are looking for does not exist.\n");
    }
    else{
        fseek(fp,(patientID-1)*sizeof(struct patient),SEEK_SET);
        fread(&person,sizeof(struct patient),1,fp);
        printf("\n*****Searched Patient Information*****\n");
        printf("ID:%d Name:%s Age:%d",patientID,person.name,person.age);
        printf("\nIllness:%s",person.illness);
        printf("\nPatient information display operation successful.\n");
    }
    fclose(fp);
}

void createList(){
    fp = fopen("patients.txt","w");
    if(fp == NULL){
        printf("File could not be created.");
        exit(0);
    }
    for(int i=0;i<100;i++){
        fwrite(&emptyPatient,sizeof(struct patient),1,fp);
    }
    fclose(fp);
    printf("\nSpace allocated for 100 patients.\n");
}

int main(){
    while(1){
        int choice;
        printf("1-Create list (reset).\n");
        printf("2-Add patient.\n");
        printf("3-Find patient.\n");
        printf("4-Delete patient.\n");
        printf("5-Update patient record.\n");
        printf("6-List patients.\n");
        printf("0-Exit\n");
        printf("Your choice:");
        scanf("%d",&choice);

        switch(choice){
            case 1:system("cls");
            createList();
            break;
            case 2:system("cls");
            add();
            break;
            case 3:system("cls");
            find();
            break;
            case 4:system("cls");
            delete();
            break;
            case 5:system("cls");
            update();
            break;
            case 6:system("cls");
            list();
            break;
            case 0:printf("\nExiting.\n");
            exit(0);
            break;
            default:printf("\nInvalid choice.\n");
            break;
        }
    }

    return 0;
}

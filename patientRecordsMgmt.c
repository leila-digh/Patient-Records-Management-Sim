/*****************************************************************************/
/* A3 Part2                                                                  */
/* records.c                                                                 */
/* Program for patient records management within a hospital setting.         */
/*  allow hospital administrators to query the data and obtain some          */
/*    summary information                                                    */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h> // for the rand() function
#include <string.h>
#include <time.h>




struct PatientType {
    char firstName[7];
    char familyName[11];
    int department;
    int dailyCost;
    int numberOfDays;
    int serverity;
};

int menu();
void operations(struct PatientType *patients, int size);

void populatePatient(struct PatientType *patients);
void populateRecords(struct PatientType *patients, int size);

void printPatient(struct PatientType *patients);
void printRecords(struct PatientType *patients, int size);
void printRecordSummary(struct PatientType *patients, int size);
void printHeader();
void printFooter();

void getInput(char* tempIn);
int patientSearchHelper(struct PatientType *patients, char *familyName);
void patientSearch(struct PatientType *patients, char *familyName, int size);

void quitProgram(struct PatientType *patients, int size);



int main(int argc, char *argv[]) {
    srand(time(NULL)); 
    int NUM_PATIENTS;
    int choice;
    if(argc != 2){ //more than 2 strings
        printf("You must enter a vaild number of patients\n");
        printf("Only one positve integer\n");
        return 1;
    }
    NUM_PATIENTS = atoi(argv[1]);
    // NUM_PATIENTS = 10; //comment this out
    
    struct PatientType **patients = (struct PatientType **) malloc(sizeof(struct PatientType *)* NUM_PATIENTS);
    if(patients == NULL){
        printf("error: could not allocate memory for the array \n");
        return (1);
    }
    for(int i = 0; i < NUM_PATIENTS; i++) {
        patients[i] = (struct PatientType *) malloc(sizeof(struct PatientType));  //malloc to be freed
        // empArr[i] = NULL;
        if(patients[i] == NULL){
            printf("error: could not allocate memory for the employee \n");
            return (1);
        }
    }
    populateRecords(*patients, NUM_PATIENTS);
    operations(*patients, NUM_PATIENTS);    

    return 0;
}

/*
This is a menu function that allows the user to make decisions as to how they 
access the records
*/
int menu(){
    int select;
    printf("\n\n\nHospital Records Menu\n");
    printf("-----------------------\n\n");

    printf("1. Print all patient records.\n");
    printf("2. Summary of the patient records.\n");
    printf("3. Search for all patients by Family Name.\n"); 
    printf("4. Size of the structure.\n");
    printf("5. Quit.\n");

    printf("Please make a selection: ");
    scanf("%d", &select); 
    while(getchar() != '\n');

    if(select < 1 ||select > 5 ){
        printf("Invalid selection, Try again.\n\n");
        return menu();
    }

    return select;

}
/*
This function populates an index in the patient array with random parmaters
that are still withing the bounds.
The names are selected from an array.
departement is randomly selected, 1-6
dailycost is randomly selected, 1-50
numberOfDays is randomly selected, 0-30
serverity is randomly selected, 0-3
*/
void populatePatient(struct PatientType *patients){
    char *firstName[]={"Emily","Liam","Sophia","Noah","Olivia","Ethan","Ava","Lucas"};
    char *lastName[]={"Smith","Patel","Tremblay","Nguyen","MacDonald"};


    int fnSize = sizeof(firstName) / sizeof(firstName[0]);
    int snSize = sizeof(lastName) / sizeof(lastName[0]);

    int fn_i = rand() % fnSize;
    int sn_i= rand() % snSize;

    strcpy((patients)->firstName,firstName[fn_i]);
    strcpy((patients)->familyName,lastName[sn_i]);
    
    (patients)->department = (int)(rand() % 6 + 1); //1-6
    (patients)->dailyCost = (int)(rand() % 50 + 1); //1-50
    (patients)->numberOfDays = (int)(rand() % 30); // 0-30,
    (patients)->serverity = (int)(rand() % 3); // 0-3


}
/*
This function iteratively populates each index in patients[] using populatePatient as a helper function
*/
void populateRecords(struct PatientType *patients,int size){
     for(int i = 0; i < size; i++){
        populatePatient(&patients[i]);
    }

}
/*
this function prints the menu from the menu function
it takes in a choice that the user inputs and keeps calling itself until the user quits
*/
void operations(struct PatientType *patients, int size){
    int choice = menu();
    char search[15];
    if (choice == 1) {
            printRecords(patients,size);
        } else if (choice == 2) {
            printRecordSummary(patients,size);
        } else if (choice == 3) {
            getInput(search);
            patientSearch(patients,search,size);
        } else if (choice == 4) {
            printf("The size of the structure is: ");
            printf("%zu\n", sizeof(struct PatientType));
        } else if (choice == 5) {
            quitProgram(patients,size);
            return;
        }
        operations(patients,size);
}
/* This function prints patient information at one index of the patinet array*/
void printPatient(struct PatientType *patients){
        printf("|%12s| %12s | %02d | %8d| %8d | %8d |\n", 
        patients->firstName, 
        patients->familyName,
        patients->department,
        patients->dailyCost,
        patients->numberOfDays,
        patients->serverity
        );
}
/*
This function iteratively print each index in patients[] using printPatient as a helper function
*/
void printRecords(struct PatientType *patients, int size){
    printHeader();
    for (int i = 0; i < size; i++) {
        printPatient(&patients[i]);
    }
    printFooter();

}
/* 
this function calcultes the
Total number of patients
Total number of patients in each department
Average daily cost of patients
Average days spent in hospital
Severity level with highest patient count
*/
void printRecordSummary(struct PatientType *patients, int size){
    int totalPatients = size;
    int totalD1=0,totalD2=0,totalD3=0,totalD4=0,totalD5=0,totalD6=0;

    int totalCost;
    int avgDailyCost = 0;
    int totalDays;
    int avgDaysSpend = 0;
    int s0 =0, s1=0, s2=0, s3=0;
    int highestOccSeverity = 0; //highest occuring severity count

    //count Depts
    for(int i =0; i < size; i++){
        if(patients[i].department == 1){
            totalD1 ++;
        }
        if(patients[i].department == 2){
            totalD2 ++;
        }
        if(patients[i].department == 3){
            totalD3 ++;
        }
        if(patients[i].department == 4){
            totalD4 ++;
        }
        if(patients[i].department == 5){
            totalD5 ++;
        }
        if(patients[i].department == 6){
            totalD6 ++;
        }
    }

    //Avg cost
    for(int i =0; i < size; i++){
        totalCost += patients[i].dailyCost;
    }
    avgDailyCost = totalCost/size;

    //Avg Days
    for(int i =0; i < size; i++){
        totalDays += patients[i].numberOfDays;
    }
    avgDaysSpend = totalDays/size;

    //highest occuring severity count
    for(int i =0; i < size; i++){
        
        if(patients[i].serverity == 0){
            s0 ++;
        }
        if(patients[i].serverity == 1){
            s1 ++;
        }
        if(patients[i].serverity == 2){
            s2 ++;
        }
        if(patients[i].serverity == 3){
            s3 ++;
        }        
    }
    // highestOccSeverity = s0;
    if(s0 > s1 && s0 > s2 && s0 > s3){
        highestOccSeverity = 0;
    } else if(s1 > s2 && s1 > s3){
        highestOccSeverity = 1;
    } else if(s2 > s3){
        highestOccSeverity = 2;
    } else {
        highestOccSeverity = 3;
    }


    printf("Record Summary\n");
    printf("-----------------\n");
    printf("Total number of patients = %d\n", totalPatients);
    printf("Total number of patients in:\n");
    printf("        D1: %3d\n", totalD1);
    printf("        D2: %3d\n", totalD2);
    printf("        D3: %3d\n", totalD3);
    printf("        D4: %3d\n", totalD4);
    printf("        D5: %3d\n", totalD5);
    printf("        D6: %3d\n", totalD6);
    printf("Average daily cost of patients = %d\n", avgDailyCost);
    printf("Average days spent in hospital = %d\n", avgDaysSpend);
    printf("Severity level with highest patient count = %d\n", highestOccSeverity);
}
/*
this is a helper function that compares an index of the patient array to a user inputes string to search for 
patients by last name
*/
int patientSearchHelper(struct PatientType *patients, char *familyName){
    if((strcmp(patients->familyName, familyName) == 0)){
        return 1;
    }else{
        return 0;
    }
}
/*
This function iteratively searches each index in patients[] using patientSearchHelper as a helper function
and prints if there is a match or prints an error message
*/
void patientSearch(struct PatientType *patients, char *familyName, int size){
    int matches = 0;
    printHeader();
    for(int i = 0; i < size; i++) {
        if(patientSearchHelper(&patients[i], familyName)){
            printPatient(&patients[i]);
            matches++;
        }
    }
    
    if(matches == 0){
        printf("Error: There is not souch name in records\n");
    }
    printFooter();

}

/*
this function let's the user confirm that they are quitting
and frees allocated memory
*/
void quitProgram(struct PatientType *patients, int size){
    printf("WARNING: You have opted to quit\n");
    printf("Enter 0 to confirm\n");
    int input;
    scanf("%d", &input); 
    while(getchar() != '\n');
    if(input == 0){
        free(patients);
        printf("Goodbye!");
    }


}
/*
this function gets a string input from the user.
it is used when the user searches by last name.
*/
void getInput(char* tempIn){
    printf("Enter a family name to search for\n");
    scanf("%s", tempIn); 
    while(getchar() != '\n');
}

void printHeader(){
    printf("===================================================================\n");
    printf("|%12s %12s %5s %10s %10s %10s|\n", "First Name", "Last Name", "Dpt", "DailyCost","Days", "Serverity");
    printf("===================================================================\n");
    
}
void printFooter(){
    printf("===================================================================");
}

# Patient Records Management Sim

This project simulates a hospital patient records management system, enabling administrators to store and retrieve patient data, generate summaries and search through records.  The program generates a specified number of random patient records based on user input (an int greater than 5 and less than 20).If the input falls outside this range, an error message is displayed. The program prompts the user to choose options from a menu to manage or view the Patient Records List.


###### This project demonstrates my understanding of;
  	1. Bitwise Operations
  	2. Pointers (Structure Pointers and Double Pointers)
  	3. Error Checking
   	4. Programming Conventions
    5. Dynamic Memory Allocation
    6. Random Data Generation
    7. Command-line Arguments



### How to compile and run
1. Save the file to your computer
2. Open the command line/terminal and navigate to the directory you have the file saved in
3. Enter the following commands to compile and run the program:
   ```
   gcc -o records patientRecordsMgmt.c
   ./records [int]
  
     ```
   (where [int] represents your desired number of patients)
4. Follow the prompts in the terminal

Example:
```
./records 7



Hospital Records Menu
-----------------------

1. Print all patient records.
2. Summary of the patient records.
3. Search for all patients by Family Name.
4. Size of the structure.
5. Quit.
Please make a selection: 
1
===================================================================
|  First Name    Last Name   Dpt  DailyCost       Days  Serverity|
===================================================================
|        Liam|     Tremblay | 05 |       47|        4 |        2 |
|        Noah|       Nguyen | 02 |       45|        4 |        2 |
|        Liam|     Tremblay | 01 |       26|       26 |        0 |
|       Ethan|       Nguyen | 03 |       10|       27 |        0 |
|      Sophia|    MacDonald | 01 |       38|       16 |        0 |
|        Noah|        Patel | 06 |       12|       14 |        0 |
|       Emily|       Nguyen | 03 |       47|       29 |        0 |
===================================================================


Hospital Records Menu
-----------------------

1. Print all patient records.
2. Summary of the patient records.
3. Search for all patients by Family Name.
4. Size of the structure.
5. Quit.
Please make a selection: 

```

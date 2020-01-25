/***********************************************
Program Name:   database.c
Author:         Joshua Marsh (006689196)
Date Submitted: 1/24/2020
Class:          CSCI 112
Instructor:     Richard Stegman
Compiler:       Microsoft Visual Studios
OS:             Windows 10 pro 64 bit
Description:    Manipulation of structures. Each section of the lab will be designed
within its own function, passing parameters as necessary.
Input Files:    payfile.txt
Output Files:   csis.txt
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
FILE* fpIn;
FILE *fpOut;
/*This is the structure used to organize input data from "payfile.txt".*/
typedef struct {
    char first[8];
    char initial[2];
    char last[10];
    char street[17];
    char city[12];
    char state[3];
    char zip[6];
    int age;
    char sex[2];
    int tenure;
    double salary;
} Employee;
/*List of functions used*/
int main(void);
void strsub(char buf[], char sub[], int start, int end);
int inputData(Employee workers[]);
void displayData(Employee workers[], int maxWorkers);
void maleNames(Employee workers[], int maxWorkers);
void highestPaidWoman(Employee workers[], int maxWorkers);
void lowestPaidMan(Employee workers[], int maxWorkers);
double averageSalary(Employee workers[], int maxWorkers);
void femalesUnderAverage(Employee workers[], int maxWorkers, double average);
void maleRatio(Employee workers[], int maxWorkers, double average);
void experiencedEmployee(Employee workers[], int maxWorkers);
void setRaise(Employee workers[], int maxWorkers);
void zipCode(Employee workers[], Employee temp[], int maxWorkers);
/*This is the main function of program.*/
int main(void) {
    int maxWorkers;
    double average;
    Employee workers[MAX];
    Employee temp[MAX];

    fopen_s(&fpOut, "csis.txt", "w");

    maxWorkers = inputData(workers);
    displayData(workers, maxWorkers);
    maleNames(workers, maxWorkers);
    highestPaidWoman(workers, maxWorkers);
    lowestPaidMan(workers, maxWorkers);
    average = averageSalary(workers, maxWorkers);
    femalesUnderAverage(workers, maxWorkers, average);
    maleRatio(workers, maxWorkers, average);
    experiencedEmployee(workers, maxWorkers);
    setRaise(workers, maxWorkers);
    zipCode(workers, temp, maxWorkers);
    
    fclose(fpOut);
    return 0;
}
/*This function allows us to organize input information from "payfile.txt".*/
void strsub(char buf[], char sub[], int start, int end) {
    int i, j;

    for (j = 0, i = start; i <= end; i++, j++) {
        sub[j] = buf[i];
    }
    sub[j] = '\0';
}
/*This function inputs data from file "payfile.txt".*/
int inputData(Employee workers[]) {
    int i = 0;
    char buf[MAX];
    char temp[MAX];
    FILE* fpIn;

    fopen_s(&fpIn, "payfile.txt", "r");

    if (fpIn == NULL) {
        puts("File payfile.txt could not be opened for input.");
        exit(1);
    }
    while (!feof(fpIn)) {
        fgets(buf, MAX, fpIn);
        strsub(buf, workers[i].first, 0, 6);
        strsub(buf, workers[i].initial, 8, 8);
        strsub(buf, workers[i].last, 10, 18);
        strsub(buf, workers[i].street, 20, 35);
        strsub(buf, workers[i].city, 37, 47);
        strsub(buf, workers[i].state, 49, 50);
        strsub(buf, workers[i].zip, 52, 56);
        strsub(buf, temp, 58, 59);
        workers[i].age = atoi(temp);
        strsub(buf, workers[i].sex, 61, 61);
        strsub(buf, temp, 63, 63);
        workers[i].tenure = atoi(temp);
        strsub(buf, temp, 65, 70);
        workers[i].salary = atof(temp);
        ++i;
    }
    fclose(fpIn);
    return i; /*i becomes maxWorkers*/
}
/*This function displays the input data from function inputData.*/
void displayData(Employee workers[], int maxWorkers) {

    printf("%s\t%s\t%s\t\t%s\t\t\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n",
        "First", "Initial", "Last", "Street", "City", "State", "Zip", "Age", "Sex", "Tenure", "Salary");
    printf("%s\t%s\t%s\t\t%s\t\t\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n",
        "-----", "-------", "----", "------", "----", "-----", "---", "---", "---", "------", "------");
    fprintf(fpOut, "%s\t%s\t%s\t\t%s\t\t\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n",
        "First", "Initial", "Last", "Street", "City", "State", "Zip", "Age", "Sex", "Tenure", "Salary");
    fprintf(fpOut, "%s\t%s\t%s\t\t%s\t\t\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\n",
        "-----", "-------", "----", "------", "----", "-----", "---", "---", "---", "------", "------");

    for (int i = 0; i < maxWorkers; i++) {
       printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\t%d\t%6.2lf\n",
           workers[i].first, workers[i].initial, workers[i].last, workers[i].street, workers[i].city,
           workers[i].state, workers[i].zip, workers[i].age, workers[i].sex, workers[i].tenure,
           workers[i].salary);
       fprintf(fpOut, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\t%d\t%6.2lf\n",
           workers[i].first, workers[i].initial, workers[i].last, workers[i].street, workers[i].city,
           workers[i].state, workers[i].zip, workers[i].age, workers[i].sex, workers[i].tenure,
           workers[i].salary);
    }
}
/*This function lists all the men on payroll.*/
void maleNames(Employee workers[], int maxWorkers) {
    printf("\nHere is a list of all the men on payroll: \n");
    fprintf(fpOut, "\nHere is a list of all the men on payroll: \n");
    for (int i = 0; i < maxWorkers; i++) {
        if (strcmp(workers[i].sex, "M") == 0) {
            printf("%s %s\n", workers[i].first, workers[i].last);
            fprintf(fpOut, "%s %s\n", workers[i].first, workers[i].last);
        }
    }
}
/*This function outputs the highest paid female on payroll.*/
void highestPaidWoman(Employee workers[], int maxWorkers) {
    Employee highest;
    Employee females[MAX];
    int j = 0;

    for (int i = 0; i < maxWorkers; i++) {
        if (strcmp(workers[i].sex, "F") == 0) {
            females[j] = workers[i];
            j++;
        }
    }
    highest = females[0];
    for (int i = 1; i < j; i++) {
        if (females[i].salary > highest.salary) {
            highest = females[i];
        }
        
    }
    printf("\nThe highest paid female is: \n");
    fprintf(fpOut, "\nThe highest paid female is: \n");
    printf("%s %s\n", highest.first, highest.last);
    fprintf(fpOut, "%s %s\n", highest.first, highest.last);
}
/*This function outputs the lowest paid male on payroll.*/
void lowestPaidMan(Employee workers[], int maxWorkers) {
    Employee lowest;
    Employee males[MAX];
    int j = 0;

    for (int i = 0; i < maxWorkers; i++) {
        if (strcmp(workers[i].sex, "M") == 0) {
            males[j] = workers[i];
            j++;
        }
    }
    lowest = males[0];
    for (int i = 1; i < j; i++) {
        if (males[i].salary < lowest.salary) {
            lowest = males[i];
        }
    }
    printf("\nThe lowest paid male is: \n");
    fprintf(fpOut, "\nThe lowest paid male is: \n");
    printf("%s %s\n", lowest.first, lowest.last);
    fprintf(fpOut, "%s %s\n", lowest.first, lowest.last);
}
/*This function finds the average salary of maxWorkers(all employees) on payroll.*/
double averageSalary(Employee workers[], int maxWorkers){
    double sum = 0.0;

    for (int i = 0; i < maxWorkers; i++) {
        sum += workers[i].salary;
    }

    printf("\nThe average salary between all employees: \n");
    fprintf(fpOut, "\nThe average salary between all employees: \n");
    printf("$%6.2lf\n", sum / maxWorkers);
    fprintf(fpOut, "$%6.2lf\n", sum / maxWorkers);

    return (sum / maxWorkers);
}
/*This function outputs the females that are below the average salary.*/
void femalesUnderAverage(Employee workers[], int maxWorkers, double average) {
    Employee females[MAX];
    int j = 0;

    for (int i = 0; i < maxWorkers; i++) {
        if (strcmp(workers[i].sex, "F") == 0) {
            females[j] = workers[i];
            j++;
        }
    }

    printf("\nFemales on payroll earning less than the average: \n");
    fprintf(fpOut, "\nFemales on payroll earning less than the average: \n");

    for (int i = 0; i < j; i++) {
        if (females[i].salary < average) {
            printf("%s %s\n", females[i].first, females[i].last);
            fprintf(fpOut, "%s %s\n", females[i].first, females[i].last);
        }
    }
}
/*This function finds the males above and below the average salary. It then outputs the ratio to 3 decimal places.*/
void maleRatio(Employee workers[], int maxWorkers, double average) {
    Employee males[MAX];
    int j = 0;
    int high = 0;
    int low = 0;
    double ratio;

    for (int i = 0; i < maxWorkers; i++) {
        if (strcmp(workers[i].sex, "M") == 0) {
            males[j] = workers[i];
            j++;
        }
    }
    for (int i = 0; i < j; i++) {
        if (males[i].salary > average) {
            high++;
        }
    }
    for (int i = 0; i < j; i++) {
        if (males[i].salary < average) {
            low++;
        }
    }

    ratio = ((double)(high * 100 / j) / (double)(low * 100 / j));

    printf("\nPercentage of males earning more than average: %.3lf\n", (double)(high *100 / j));
    printf("Percentage of males earning less than average: %.3lf\n", (double)(low * 100 / j));
    printf("Ratio of males earning more than average over earning less than average: %.3lf\n", ratio);
    fprintf(fpOut, "\nRatio of males earning more than average: %.2lf\n", (double)(high * 100/ j));
    fprintf(fpOut, "Ratio of males earning less than average: %.2lf\n", (double)(low * 100 / j));
    fprintf(fpOut, "Ratio of males earning more than average over earning less than average: %.3lf\n", ratio);
}
/*This function outputs the first and last name of the employees who make more than $3500 per year,
        have been with the company for at least 5 years, and who are over 30 years old.*/
void experiencedEmployee(Employee workers[], int maxWorkers) {

    printf("\nMost valuable employees: \n");
    fprintf(fpOut, "\nMost valuable employees: \n");

    for (int i = 0; i < maxWorkers; i++) {
        if (((workers[i].salary * 52) > 35000) && (workers[i].tenure >= 5) && (workers[i].age > 30)) {
            printf("%s %s\n", workers[i].first, workers[i].last);
            fprintf(fpOut, "%s %s\n", workers[i].first, workers[i].last);
        }
    }
}
/*This function finds employees earning under $350.00 per week and gives them a 10 percent increase in pay.
            It then outputs the found employees first, last, new salary.*/
void setRaise(Employee workers[], int maxWorkers) {

    printf("\nThese employees get 10 percent raises, this is their new salary: \n");
    fprintf(fpOut, "\nThese employees get 10 percent raises, this is their new salary: \n");

    for (int i = 0; i < maxWorkers; i++) {
        if (workers[i].salary < 350.00) {
            workers[i].salary *= 1.10;
            printf("%s %s $%.2lf\n", workers[i].first, workers[i].last, workers[i].salary);
            fprintf(fpOut, "%s %s $%.2lf\n", workers[i].first, workers[i].last, workers[i].salary);
        }
    }
}
/*This function organizes zip codes in ascending order and outputs 
                     first, last and zip code of maxWorkers(total # of employees).*/
void zipCode(Employee workers[], Employee temp[], int maxWorkers) { 
    int i, j;    

    printf("\nZip Codes organized in ascending order (Extra Credit):\n");
    fprintf(fpOut, "\nZip Codes organized in ascending order (Extra Credit):\n");

    for (i = 1; i < maxWorkers; i++)
        for (j = 0; j < maxWorkers - i; j++) {
            if (strcmp(workers[j].zip, workers[j + 1].zip) > 0) {
                temp[j] = workers[j];
                workers[j] = workers[j + 1];
                workers[j + 1] = temp[j];
            }
        }
    for (i = 0; i < maxWorkers; i++) {
        printf("%s %s %s\n", workers[i].first, workers[i].last, workers[i].zip);
        fprintf(fpOut, "%s %s %s\n", workers[i].first, workers[i].last, workers[i].zip);
    }
}

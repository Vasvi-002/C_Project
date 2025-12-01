//Employee Payroll System (with Tax & Reports)
//• Store employee details (name, ID, salary).
//• Compute gross/net salary with allowances and deductions.
//• Apply income tax slabs automatically.
//• Generate pay slip report (written to file).
//• Search employees by ID or name.
#include <stdio.h>
#include <string.h>
#define MAX 100   // maximum number of employees
// STRUCTURE DECLARED
struct Emp {
    int id;
    char name[50];
    float salary;
};
// FUNCTION DECLARATIONS
void addEmp();
void delEmp();
void showAll();
void searchEmp();
void sortName();
void genSlip();
float getTax(float g);
// global array of employees
struct Emp e[MAX];
int count = 0;
// FUNCTION TO ADD EMPLOYEE
void addEmp() {
    if(count == MAX) {
        printf("Employee list full.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &e[count].id);

    printf("Enter Name: ");
    scanf("%s", e[count].name);

    printf("Enter Basic Salary: ");
    scanf("%f", &e[count].salary);

    count++; // increase employee count

    printf("Employee added.\n");
}
// FUNCTION TO DELETE EMPLOYEE
void delEmp() {
    int x, i, j, found = 0;

    printf("Enter ID to delete: ");
    scanf("%d", &x);

    for(i = 0; i < count; i++) {
        if(e[i].id == x) {
            found = 1;

         
            for(j = i; j < count - 1; j++) {
                e[j] = e[j + 1];
            }

            count--;
            printf("Employee deleted.\n");
            break;
        }
    }

    if(found == 0)
        printf("ID not found.\n");
}
// FUNCTION TO SHOW ALL EMPLOYEES

void showAll() {
    int i;

    if(count == 0) {
        printf("No employee records found.\n");
        return;
    }

    for(i = 0; i < count; i++) {
        printf("%d  %s  %.2f\n", e[i].id, e[i].name, e[i].salary);
    }
}
// FUNCTION TO SEARCH EMPLOYEE

void searchEmp() {
    int ch, x, i, found = 0;
    char sname[50];

    printf("Search by: 1-ID  2-Name : ");
    scanf("%d", &ch);

    if(ch == 1) {

        printf("Enter ID: ");
        scanf("%d", &x);

        for(i = 0; i < count; i++) {
            if(e[i].id == x) {
                found = 1;
                printf("Found: %d  %s  %.2f\n", e[i].id, e[i].name, e[i].salary);
                break;
            }
        }
    }
    else {

        printf("Enter Name: ");
        scanf("%s", sname);

        for(i = 0; i < count; i++) {
            if(strcmp(e[i].name, sname) == 0) {
                found = 1;
                printf("Found: %d  %s  %.2f\n", e[i].id, e[i].name, e[i].salary);
                break;
            }
        }
    }

    if(found == 0)
        printf("Not found.\n");
}
// FUNCTION TO SORT NAMES

void sortName() {
    int i, j;
    struct Emp temp;

    for(i = 0; i < count - 1; i++) {
        for(j = i + 1; j < count; j++) {

            // alphabetically compare names
            if(strcmp(e[i].name, e[j].name) > 0) {
                temp = e[i];
                e[i] = e[j];
                e[j] = temp;
            }
        }
    }

    printf("Employees sorted by name.\n");
}
// CALCULATE TAX BASED ON GROSS
float getTax(float g) {
    float t = 0;

    if(g <= 250000)
        t = 0;
    else if(g <= 500000)
        t = 0.05 * (g - 250000);
    else if(g <= 1000000)
        t = 12500 + 0.20 * (g - 500000);
    else
        t = 112500 + 0.30 * (g - 1000000);

    return t;
}
// GENERATE PAYSLIP IN A FILE
void genSlip() {
    int x, i, found = 0;
    FILE *fp;

    printf("Enter ID for payslip: ");
    scanf("%d", &x);

    for(i = 0; i < count; i++) {
        if(e[i].id == x) {
            found = 1;

            float basic = e[i].salary;
            float hra = 0.10 * basic;
            float da  = 0.05 * basic;
            float gross = basic + hra + da;

            float tax = getTax(gross);
            float net = gross - tax;

            fp = fopen("payslip.txt", "w");

            fprintf(fp, "PAY SLIP\n");
            fprintf(fp, "--------------------\n");
            fprintf(fp, "ID: %d\n", e[i].id);
            fprintf(fp, "Name: %s\n", e[i].name);
            fprintf(fp, "Basic Salary: %.2f\n", basic);
            fprintf(fp, "HRA: %.2f\n", hra);
            fprintf(fp, "DA: %.2f\n", da);
            fprintf(fp, "Gross Salary: %.2f\n", gross);
            fprintf(fp, "Tax: %.2f\n", tax);
            fprintf(fp, "Net Salary: %.2f\n", net);

            fclose(fp);

            printf("Payslip saved in 'payslip.txt'.\n");
            break;
        }
    }

    if(found == 0)
        printf("ID not found.\n");
}
// MAIN FUNCTION (MENU DRIVEN)
int main() {
    int ch;

    while(1) {

        printf("\n--- EMPLOYEE PAYROLL SYSTEM ---\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Show All Employees\n");
        printf("4. Search Employee\n");
        printf("5. Sort by Name\n");
        printf("6. Generate Payslip\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);

        if(ch == 1) addEmp();
        else if(ch == 2) delEmp();
        else if(ch == 3) showAll();
        else if(ch == 4) searchEmp();
        else if(ch == 5) sortName();
        else if(ch == 6) genSlip();
        else if(ch == 7) break;
        else printf("Invalid choice.\n");
    }

    return 0;
}

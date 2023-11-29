/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient *patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ",
               patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData *data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient *patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ",
               patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{

    int recordsFound = 0; // Variable to track if any eligible records are found

    displayPatientTableHeader();

    for (int i = 0; i < max; i++)
    {
        // Check if the patient number is non-zero
        if (patient[i].patientNumber != 0)
        {
            // Display a single patient record based on 'fmt'
            displayPatientData(&patient[i], fmt);

            recordsFound = 1; // Set recordsFound to 1, indicating at least one eligible record is found
        }
    }

    // If no eligible records were found, display "*** No records found ***"
    if (!recordsFound)
    {
        printf("*** No records found ***\n");
    }
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int choice, flag = 1;
    while (flag)
    {
        printf("Search Options\n==========================\n1) By patient number\n2) By phone number\n..........................\n0) Previous menu\n..........................\nSelection: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch (choice)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;

        case 0:
            flag = 0;
            printf("\n");
            break;
            
        }
        
    }
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int index = -1;

    // Find a free element in the array
    for (int i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
            break;
        }
    }

    // Check if a free element was found
    if (index != -1)
    {
        // Determine the next unique patient number
        int nextNumber = nextPatientNumber(&patient[i], max);

        // Assign the next patient number to the element at the found index
        patient[index].patientNumber = nextNumber;

        // Get user input for the new record
        inputPatient(&patient[index]);

        // Display confirmation message
        printf("\n*** New patient record added ***\n");
    }
    else
    {
        // Display error message if array is full
        printf("ERROR: Patient listing is FULL!\n");
    }
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patientnum;
    scanf("%d", &patientnum);
    printf("\n");
    clearInputBuffer();
    if (findPatientIndexByPatientNum(patientnum, patient, max)!=-1)
    {
        menuPatientEdit(&patient[findPatientIndexByPatientNum(patientnum, patient, max)]);
    }
    else
    {
        printf("ERROR: Patient record not found!");
    }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void removePatient(struct Patient patient[], int max)
{
    int patientNum, recordExists;
    char removeRecord;
    printf("Enter the patient number:\n");
    scanf("%d", &patientNum);
    clearInputBuffer();
    recordExists = findPatientIndexByPatientNum(patientNum, patient, max);
    if (recordExists != -1)
    {
        displayPatientData(&patient[recordExists], FMT_FORM);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
        return;
    }
    printf("\n");
    printf("Are you sure you want to remove this patient record? (y/n): \n");
    scanf(" %c", &removeRecord);
    clearInputBuffer();
    if (removeRecord == 'y')
    {
        patient[recordExists].patientNumber = 0;
        strcpy(patient[recordExists].name, "");
        strcpy(patient[recordExists].phone.description, "");
        strcpy(patient[recordExists].phone.number, "");
        printf("Patient record has been removed!\n");
    }
    else
    {
        printf("Operation aborted.\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientnum;
    printf("\nSearch by patient number: ");
    scanf("%d", &patientnum);
    printf("\n");
    clearInputBuffer();
    if (findPatientIndexByPatientNum(patientnum, patient, max) != -1)
    {
        displayPatientData(&patient[findPatientIndexByPatientNum(patientnum, patient, max)], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char searchPhoneNumber[PHONE_LEN + 1];

    printf("\nSearch by phone number: ");
    scanf("%10[^\n]", searchPhoneNumber);
    clearInputBuffer();

    // Display table header
    printf("\n");
    displayPatientTableHeader();

    int found = 0;

    for (int i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, searchPhoneNumber) == 0)
        {
            // Display data for the current patient
            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maxPatientNumber = 0;

    // Iterate through the patient array to find the largest patient number
    for (int i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > maxPatientNumber)
        {
            maxPatientNumber = patient[i].patientNumber;
        }
    }

    // Return the next patient number (one more than the current maximum)
    return maxPatientNumber + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{

    for (int i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            // Patient record found, return the index
            return i;
        }
    }

    // Patient record not found
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n------------------\nNumber: %05d\nName  : ", patient->patientNumber);
    scanf("%[^\n]", patient->name);
    clearInputBuffer();
    printf("\n");
    printf("Phone Information\n-----------------");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone *phone)
{
    int inp, flag = 1;
    printf("\nHow will the patient like to be contacted?\n1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");
    scanf("%d", &inp);
    clearInputBuffer();
    switch (inp)
    {
    case 1:
        strcpy(phone->description, "CELL");
        
        break;

    case 2:
        strcpy(phone->description, "HOME");
        
        break;

    case 3:
        strcpy(phone->description, "WORK");
        
        break;

    case 4:
        strcpy(phone->description, "TBD");
        
        flag = 0;
        break;
    }
    if (flag)
    {   printf("\nContact: %s",phone->description);
        printf("\nNumber : ");
        scanf(" %[^\n]", phone->number);
        clearInputBuffer();
    }
}

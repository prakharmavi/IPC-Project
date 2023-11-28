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
#include <ctype.h>
//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

int calStringLen(char *str)
{
    int len = 0;

    // Iterate through the characters until the null-terminating character is encountered
    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}
int inputInt()
{
    int num, flg = 1;
    char entr;
    do
    {
        if (scanf("%d%c", &num, &entr) != 2 || entr != '\n')
        {
            printf("Error! Input a whole number: ");
            while (getchar() != '\n')
                ;
        }
        else
        {
            flg = 0;
        }
    } while (flg);
    return num;
}

int inputIntPositive()
{
    int value, flg = 1;
    char entr;

    do
    {
        scanf("%d%c", &value, &entr);
        if (entr == '\n')
        {
            if (value < 0)
            {
                printf("ERROR! Value must be > 0: ");
            }
            else
            {
                flg = 0;
            }
        }
    } while (flg);
    return value;
}

int inputIntRange(int lowerBound, int upperBound)
{
    int num, flg = 1;
    char entr = ' ';
    do
    {
        if (scanf("%d%c", &num, &entr) != 2 || entr != '\n')
        {
            printf("Error! Input a whole number: ");
            while (getchar() != '\n')
                ;
        }
        else if (!(num >= lowerBound && num <= upperBound))
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
        else
        {
            flg = 0;
        }
    } while (flg);
    return num;
}

char inputCharOption(char word[])
{
    int i, temp = 0, flg = 1;
    char letter;
    do
    {
        scanf(" %c", &letter);
        for (i = 0; i < calStringLen(word) && temp != 1; i++)
        {
            if (letter == word[i])
            {
                temp = 1;
            }
        }
        if (temp != 1)
        {
            printf("ERROR: Character must be one of [%s]: ", word);
        }
        else
        {
            flg = 0;
        }
    } while (flg);

    return letter;
}

void inputCString(char *name, int min, int max)
{
    int length = 0, flg = 1;
    do
    {
        scanf(" %[^\n]", name);
        length = calStringLen(name);
        if (!(length >= min && length <= max))
        {
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", max);
            }
            else if ((max - min) == 1)
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
            else
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
        }
        else
        {
            flg = 0;
        }
    } while (flg);
}

void displayFormattedPhone(char *phoneNumber)
{
    if (phoneNumber == NULL)
    {
        printf("(___)___-____");
        return;
    }
    int length = calStringLen(phoneNumber), i, flg = 0, digit;
    if (length != 10)
    {
        flg = 1;
        printf("(___)___-____");
    }
    else
    {
        for (i = 0; i < length && flg != 1; i++)
        {
            digit = isdigit(phoneNumber[i]);
            if (digit == 0)
            {
                flg = 1;
                printf("(___)___-____");
            }
        }
    }

    if (flg != 1)
    {

        for (i = 0; i < length; i++)
        {
            if (i == 0)
            {
                printf("(%c", phoneNumber[i]);
            }
            else if (i == 3)
            {
                printf(")%c", phoneNumber[i]);
            }
            else if (i == 6)
            {
                printf("-%c", phoneNumber[i]);
            }
            else
            {
                printf("%c", phoneNumber[i]);
            }
        }
    }
}
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256
#define PASSWORD_LEN 16

char hash(int num1, int num2);
char mapToUpper(int num);
char mapToLower(int num);
char mapToDigit(int num);
char mapToPunctuation(int num);
void getPassword(char rootPassword[], int rootPasswordSize, char currentStation[], char currentStationSize, char password[]);
void generateFourRandomNumber(int keyNumber, int passwordSize, int* pos1, int* pos2, int* pos3, int* pos4);

int main()
{
    char rootPassword[MAX_LEN];
    char currentStation[MAX_LEN];
    char password[MAX_LEN];
    printf("Please input root password:\n>>> ");
    scanf("%s", rootPassword);
    printf("Please input current station:\n>>> ");
    scanf("%s", currentStation);
    int rootPasswordSize = strlen(rootPassword);
    int currentStationSize = strlen(currentStation);
    getPassword(rootPassword, rootPasswordSize, currentStation, currentStationSize, password);
    printf("\nPASSWORD: %s\n\n", password);
    system("pause");
    return 0;
}

char hash(int num1, int num2)
{
    int c = ((1 << 3) ^ (1 >> 3) ^ num1 ^ num2) % 126;
    if (c < 33) {
        c = 126 - c;
    }
    return c;
}

char mapToUpper(int num)
{
    if (isupper(num)) {
        return num;
    } else if (islower(num)) {
        return toupper(num);
    } else {
        return 65 + (90 - 65) / (33, 126) * (num - 33);
    }
}

char mapToLower(int num)
{
    if (islower(num)) {
        return num;
    } else if (isupper(num)) {
        return tolower(num);
    } else {
        return 97 + (122 - 97) / (33, 126) * (num - 33);
    }
}

char mapToDigit(int num)
{
    if (isdigit(num)) {
        return num;
    }
    return 48 + (57 - 48) / (33, 126) * (num - 33);
}

char mapToPunctuation(int num)
{
    if ((num >= 33 && num <= 47) || (num >= 58 && num <= 64) || (num >= 91 && num <= 96) || (num >= 123 && num <= 126)) {
        return num;
    }
    return 33 + (47 - 33) / (33, 126) * (num - 33);
}

void generateFourRandomNumber(int keyNumber, int passwordSize, int* pos1, int* pos2, int* pos3, int* pos4)
{
    srand(keyNumber);
    *pos1 = (rand() + 1) % passwordSize;
    do {
        *pos2 = (rand() + 2) % passwordSize;
        if (*pos2 != *pos1) {
            break;
        }
    } while (true);
    do {
        *pos3 = (rand() + 3) % passwordSize;
        if (*pos3 != *pos1 && *pos3 != *pos2) {
            break;
        }
    } while (true);
    do {
        *pos4 = (rand() + 4) % passwordSize;
        if (*pos4 != *pos1 && *pos4 != *pos2 && *pos4 != *pos3) {
            break;
        }
    } while (true);
}

void getPassword(char rootPassword[], int rootPasswordSize, char currentStation[], char currentStationSize, char password[])
{
    password[PASSWORD_LEN] = '\0';
    int keyNumber = 0;
    for (int i = 0; i < currentStationSize; ++i) {
        keyNumber += currentStation[i];
    }
    for (int i = 0; i < rootPasswordSize; ++i) {
        password[i] = hash(rootPassword[i], keyNumber);
    }
    srand(keyNumber);
    for (int i = rootPasswordSize; i < PASSWORD_LEN; ++i) {
        password[i] = hash(rand(), keyNumber);
    }
    int pos1, pos2, pos3, pos4;
    generateFourRandomNumber(keyNumber, PASSWORD_LEN, &pos1, &pos2, &pos3, &pos4);
    password[pos1] = mapToUpper(password[pos1]);
    password[pos2] = mapToLower(password[pos2]);
    password[pos3] = mapToDigit(password[pos3]);
    password[pos4] = mapToPunctuation(password[pos4]);
}

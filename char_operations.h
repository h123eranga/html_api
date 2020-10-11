#ifndef CHAR_OPERATIONS_H
#define CHAR_OPERATIONS_H

int isCharPointersEquals(char *lhsPtr, char *rhsPtr)
{
    int i = 0;
    while (lhsPtr[i] != '\0')
    {
        if (lhsPtr[i] == rhsPtr[i])
        {
            i++;
            continue;
        }
        return lhsPtr[i] == rhsPtr[i];
    }
    return 1;
}

int getCharPointerLength(char *ptr)
{
    int i = 0;
    while (ptr[i] != '\0')
    {
        i++;
    }
    return i;
}

char *swapCharPointers(char *newCharPointer, char *oldCharPointer)
{
    int i = 0;
    while (oldCharPointer[i] != '\0')
    {
        newCharPointer[i] = oldCharPointer[i];
        i++;
    }
    return newCharPointer;
}

char *getSubstring(int startingIndex, char *subString, char *original)
{
    //printf("substring:%d-%c\n", startingIndex, original[startingIndex]);
    int i = 0;
    while (original[startingIndex] != '\0')
    {
        //printf("token:%c\n", original[startingIndex]);
        subString[i] = original[startingIndex];
        i++;
        startingIndex++;
    }
    return subString;
}

#endif
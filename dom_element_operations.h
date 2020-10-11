#ifndef DOM_ELEMENT_OPERATIONS_H
#define DOM_ELEMENT_OPERATIONS_H

#include <stdio.h>
#include "models.h"

int getDomElementPointerLength(DOMElement *domElements)
{
    int i = 0;
    while (domElements != NULL && domElements->tag != NULL)
    {
        //printf("element:%s-%s\n", domElements->tag, domElements->innerText);
        domElements++;
        i++;
    }
    return i;
}

DOMElement *swapDomElementPointers(DOMElement *newDOMElementPointer, DOMElement *oldDOMElementPointer)
{
    for (int i = 0; i < getDomElementPointerLength(oldDOMElementPointer); i++)
    {
        newDOMElementPointer[i] = oldDOMElementPointer[i];
        printf("swap:%d\n", i);
    }
    return newDOMElementPointer;
}

void printDomTree(DOMElement *domElements)
{
    for (int i = 0; i < getDomElementPointerLength(domElements); i++)
    {
        printf("TAG : %s\n", domElements[i].tag);
        printf("INNER TEXT : %s\n", domElements[i].innerText);
    }
}

#endif
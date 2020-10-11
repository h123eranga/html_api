#include <stdio.h>
#include <malloc.h>

// dom element structures and support methods

struct DOMElement
{
    char *tag;
    char *innerText;
    struct DOMElement *childElements;
};

// support methods for dom manipulation

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

long getDomElementPointerLength(struct DOMElement *domElements)
{
    return sizeof(domElements) / sizeof(*domElements);
}

struct DOMElement *swapDomElementPointers(struct DOMElement *newDomElements, struct DOMElement *oldDomElements)
{
    printf(">>>>>>>>>>>>>>>>>swap>>>>>>>>>>>>>\n");
    // for (int i = 0; i < sizeof(oldDomElements) / sizeof(struct DOMElement); i++)
    // {
    //     newDomElements[i] = oldDomElements[i];
    // }
    // return newDomElements;
    //printf("not null:%d", oldDomElements == NULL);
    if (oldDomElements != NULL)
    {
        //printf("<<<<jhjg<<<<<<%s\n", oldDomElements[0].tag);
        int i = 0;
        while (oldDomElements[i].tag != NULL)
        {
            printf("do:%s\n", oldDomElements[0].tag);
            // newDomElements[i].tag = oldDomElements[i].tag;
            // newDomElements[i].innerText = oldDomElements[i].innerText;
            // newDomElements[i].childElements = NULL;
            newDomElements[i] = oldDomElements[i];
            i++;
        }
    }
    printf("new element:%s\n", newDomElements[0].tag);
    return newDomElements;
}

int main()
{
    FILE *file;
    file = fopen("index.html", "r");
    int c;
    char *tag = "";
    char *innerText = "";
    int tagIndex = 0;
    int textIndex = 0;
    int tagStarted = 0;
    int endTagStarted = 0;
    int innerTextStarted = 0;
    struct DOMElement rootElement;
    //printf("ed : %lu\n", sizeof(tag));
    while ((c = fgetc(file)) != EOF)
    {
        printf("meet tag:%c\n", c);
        if (c == 60) // <
        {
            printf("1");
            if (tag[0] != '\0')
            {
                tag = (char *)malloc(1 * sizeof(char));
                tag = "";
            }
            else
            {
            }
            tagStarted = 1;
            if (innerTextStarted)
            {
                innerTextStarted = 0;
            }
            continue;
        }
        else if (c == 62) // >
        {
            printf("2");
            printf(">>>>>>>>inner text:%s\n", innerText);
            tagIndex = 0;
            tagStarted = 0;
            //printf("root tag:%s\n", rootElement.tag);
            if (endTagStarted)
            {
                endTagStarted = 0;
            }
            else
            {
                if (rootElement.tag[0] != '\0')
                {
                    //printf("this is child:%s\n", tag);
                    struct DOMElement childElement;
                    childElement.tag = tag;
                    long childElementsSize = getDomElementPointerLength(rootElement.childElements);
                    //printf("size:%lu\n", childElementsSize);
                    //printf("size of:%lu\n", sizeof(struct DOMElement));
                    struct DOMElement *existingChildElements = (struct DOMElement *)malloc((childElementsSize + 1) * sizeof(struct DOMElement));
                    existingChildElements = swapDomElementPointers(existingChildElements, rootElement.childElements);
                    existingChildElements[childElementsSize] = childElement;
                    existingChildElements[childElementsSize].childElements = NULL;
                    existingChildElements[childElementsSize + 1].tag = NULL;
                    existingChildElements[childElementsSize + 1].innerText = NULL;
                    existingChildElements[childElementsSize + 1].childElements = NULL;
                    //printf("size:%lu\n", getDomElementPointerLength(existingChildElements));
                    printf(">>>>>>1>>>>>%s\n", existingChildElements[0].tag);
                    printf(">>>>>>2>>>>>%d\n", existingChildElements[1].tag == NULL);
                    //printf("not null:%d", existingChildElements != NULL);

                    rootElement.childElements = (struct DOMElement *)malloc((childElementsSize + 1) * sizeof(struct DOMElement));
                    rootElement.childElements = swapDomElementPointers(rootElement.childElements, existingChildElements);
                    printf("size:%lu\n", childElementsSize);
                    printf(">>>>>>>>>>>%s\n", rootElement.childElements[0].tag);
                    free(existingChildElements);
                }
                else
                {
                    rootElement.tag = tag;
                    printf(">>>>>>>>adding tag:%s\n", tag);
                    rootElement.childElements = NULL;
                }
            }
            continue;
        }
        else if (c == 47) // /
        {
            printf("3");
            endTagStarted = 1;
            if (innerText[0] != '\0')
            {
                rootElement.innerText = innerText;
                printf("inner text add:%s\n", innerText);
                innerText = (char *)malloc(1 * sizeof(char));
                innerText = "";
            }
        }
        else if (tagStarted)
        {
            printf("4");
            int tagSize = getCharPointerLength(tag);
            char *existingTag = (char *)malloc((tagSize + 1) * sizeof(char));
            existingTag = swapCharPointers(existingTag, tag);
            existingTag[tagSize] = c;
            existingTag[tagSize + 1] = '\0';

            tag = (char *)malloc((tagSize + 1) * sizeof(char));
            tag = swapCharPointers(tag, existingTag);
            free(existingTag);
            tagIndex++;
        }
        else if (!tagStarted && !endTagStarted)
        {
            printf("5");
            printf(">>>>>>><<<<<<<<<<%d\n", c);
            if (c != 10 && c != 32) // new line, space
            {
                innerTextStarted = 1;
                //printf("meet text:%c\n", c);
                int textSize = getCharPointerLength(innerText);
                char *existingInnerText = (char *)malloc((textSize + 1) * sizeof(char));
                existingInnerText = swapCharPointers(existingInnerText, innerText);
                existingInnerText[textSize] = c;
                existingInnerText[textSize + 1] = '\0';

                innerText = (char *)malloc((textSize + 1) * sizeof(char));
                innerText = swapCharPointers(innerText, existingInnerText);
                free(existingInnerText);
                textIndex++;
            }
        }
    }
    fclose(file);

    printf("root element tag:%s\n", rootElement.tag);
    printf("root element inner text:%s\n", rootElement.innerText);
    printf("root element tag:%s\n", rootElement.childElements[0].tag);
    printf("root element inner text:%s\n", rootElement.childElements[0].innerText);
    // if (rootElement.childElements != NULL)
    // {
    //     int i = 0;
    //     while (rootElement.childElements[i].tag != NULL)
    //     {
    //         printf("child %d tag:%s\n", i, rootElement.childElements[i].tag);
    //         i++;
    //     }
    // }

    return 0;
}
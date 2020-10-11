#ifndef PARSER_H
#define PARSER_H
#include "models.h"
#include "dom_element_operations.h"

enum TOKENS
{
    TAG = 1,
    END = 2,
    INNER_TEXT = 3
};

DOMElement *getDOMTree(DOMElement *domElements, char *tokens)
{
    int i = 0;
    char *token = "";
    int tokenSize = 0;
    int tagStarted = 0;
    int tagEnded = 0;
    int tagIndex = 0;
    int innerTextStarted = 0;
    DOMElement domElement;
    //printf("start\n");
    while (tokens[i] != '\0')
    {
        printf("character:%c\n", tokens[i]);
        if (tokens[i] == 58 && token != "")
        {
            printf("found token end:%s\n", token);
            if (isCharPointersEquals(token, "TAG"))
            {
                printf("started tag\n");
                tagStarted = 1;
                tagIndex++;
            }
            else if (isCharPointersEquals(token, "INNER_TEXT"))
            {
                printf("inner text found\n");
                innerTextStarted = 1;
            }
            else if (isCharPointersEquals(token, "END"))
            {
                printf("add the new element to main dom elements:%s\n", domElement.tag);
                // DOMElement *old = NULL;
                // DOMElement *els = NULL;
                // DOMElement newel;
                // int size = getDomElementPointerLength(old);
                // printf("size:%d\n", size);
                // printf("old size:%d\n", size);
                // els = (DOMElement *)malloc((1 + size) * sizeof(DOMElement));
                // els = swapDomElementPointers(els, old);
                // //els = reverse(size, els);
                // printf("size:%d\n", getDomElementPointerLength(els));
                // //els[0].i = 10;
                // //els[0].next = NULL;
                // newel.tag = "div";
                // els[size].tag = newel.tag;
                // els[size].childElements = newel.childElements;
                // //printf("i:%d\n", els->i);
                // printf("size:%d\n", getDomElementPointerLength(els));
                // old = (DOMElement *)malloc((getDomElementPointerLength(els)) * sizeof(DOMElement));

                // old = swapDomElementPointers(old, els);
                // printf("size:%d\n", getDomElementPointerLength(old));

                //newels[1].i = 30;
                // printf("add the new element to main dom elements:%s\n", domElement.tag);
                int domElementsSize = getDomElementPointerLength(domElements);
                printf("size:%d\n", domElementsSize);

                DOMElement *existingDomElements = NULL;
                existingDomElements = (DOMElement *)malloc((1 + domElementsSize) * sizeof(DOMElement));
                existingDomElements = swapDomElementPointers(existingDomElements, domElements);
                printf("size:%d\n", domElementsSize);

                printf("domElementsSize:%d\n", getDomElementPointerLength(existingDomElements));

                printf("tag:%s\n", domElement.tag);
                printf("innerText:%s\n", domElement.innerText);
                existingDomElements[domElementsSize].tag = (char *)malloc(getCharPointerLength(domElement.tag) * sizeof(char));
                existingDomElements[domElementsSize].tag = domElement.tag;
                existingDomElements[domElementsSize].innerText = (char *)malloc(getCharPointerLength(domElement.innerText) * sizeof(char));
                existingDomElements[domElementsSize].innerText = domElement.innerText;
                existingDomElements[domElementsSize].childElements = domElement.childElements;

                int existingSize = getDomElementPointerLength(existingDomElements);
                printf("existingDomElements size:%d\n", existingSize);
                domElements = (DOMElement *)malloc(existingSize * sizeof(DOMElement));
                domElements = swapDomElementPointers(domElements, existingDomElements);
                printf("size is:%d\n", getDomElementPointerLength(domElements));

                tagStarted = 0;
                domElement.tag = NULL;
                domElement.innerText = NULL;
                domElement.childElements = NULL;
                token = (char *)malloc(1 * sizeof(char));
                token = "";
                i++;
                continue;
            }
            else
            {
                //printf("else tag:tag started:%d-inner started:%d\n", tagStarted, innerTextStarted);
                if (tagStarted)
                {
                    if (innerTextStarted)
                    {
                        domElement.innerText = (char *)malloc(getCharPointerLength(token) * sizeof(char));
                        domElement.innerText = swapCharPointers(domElement.innerText, token);
                        innerTextStarted = 0;
                    }
                    else
                    {
                        domElement.tag = (char *)malloc(getCharPointerLength(token) * sizeof(char));
                        domElement.tag = swapCharPointers(domElement.tag, token);
                        domElement.innerText = NULL;
                        domElement.childElements = NULL;

                        if (tagIndex > 1)
                        {
                            printf("i is:%d\n", i);
                            int tokensSize = getCharPointerLength(tokens);
                            char *childTokens = (char *)malloc((tokensSize - i + 1) * sizeof(char));
                            childTokens = getSubstring(i + 1, childTokens, tokens);
                            childTokens[tokensSize - i + 1] = '\0';
                            printf("child tokens:%s\n", childTokens);
                            domElement.childElements = getDOMTree(domElement.childElements, childTokens);
                        }

                        // add the new dom element to dom elements

                        printf("start recursion:%s\n", domElement.tag);
                    }
                }
            }
            token = (char *)malloc(1 * sizeof(char));
            token = "";
            i++;
            continue;
        }
        else
        {
            int tokenSize = getCharPointerLength(token);
            printf("tokens size:%d-%s\n", tokenSize, token);
            char *existingToken = (char *)malloc((tokenSize + 1) * sizeof(char));
            existingToken = swapCharPointers(existingToken, token);
            //printf("current token:%d,%c\n", i, tokens[i]);
            existingToken[tokenSize] = tokens[i];
            existingToken[tokenSize + 1] = '\0';

            token = (char *)malloc((tokenSize + 1) * sizeof(char));
            token = swapCharPointers(token, existingToken);
            token[tokenSize + 1] = '\0';
            printf("current token:%s\n", token);
            free(existingToken);
        }
        i++;
    }
    return domElements;
}

#endif
#include <stdio.h>
#include <malloc.h>
#include "char_operations.h"
#include "tokenizer.h"
#include "parser.h"
#include "models.h"

int main()
{
    FILE *file;
    file = fopen("index.html", "r");
    char *tokens = "";
    tokens = getTokens(file, tokens);
    fclose(file);

    printf("tokens:%s\n", tokens);

    DOMElement *domElements = NULL;
    domElements = getDOMTree(domElements, tokens);

    //printf("dom size:%d\n", getDomElementPointerLength(domElements));

    //printDomTree(domElements);

    return 0;
}
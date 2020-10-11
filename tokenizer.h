#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>

char *getTokens(FILE *file, char *tokens)
{
    int c;
    char *tag = "";
    char *innerText = "";
    int tagStarted = 0;
    int endTagStarted = 0;
    int innerTextStarted = 0;

    char *token = "";
    // "TAG:HTML,INNER_TEXT:TEST CONTENT,END,TAG:DIV,TAG:SPAN,INNER_TEXT:TEST SPAN CONTENT,END,END"
    while ((c = fgetc(file)) != EOF)
    {
        if (c == 60) // <
        {
            tagStarted = 1;
            if (innerTextStarted)
            {
                //printf("inner tex:%s\n", token);
                innerTextStarted = 0;
                int tokenSize = getCharPointerLength(token);
                int tokensSize = getCharPointerLength(tokens);
                char *existingTokens = (char *)malloc((tokensSize + 13 + tokenSize) * sizeof(char));
                existingTokens = swapCharPointers(existingTokens, tokens);
                existingTokens[tokensSize] = 'I';
                existingTokens[tokensSize + 1] = 'N';
                existingTokens[tokensSize + 2] = 'N';
                existingTokens[tokensSize + 3] = 'E';
                existingTokens[tokensSize + 4] = 'R';
                existingTokens[tokensSize + 5] = '_';
                existingTokens[tokensSize + 6] = 'T';
                existingTokens[tokensSize + 7] = 'E';
                existingTokens[tokensSize + 8] = 'X';
                existingTokens[tokensSize + 9] = 'T';
                existingTokens[tokensSize + 10] = ':';
                int i = 0;
                while (token[i] != '\0')
                {
                    existingTokens[tokensSize + i + 11] = token[i];
                    i++;
                }
                existingTokens[tokensSize + 11 + tokenSize] = ':';
                existingTokens[tokensSize + 12 + tokenSize] = '\0';

                tokens = (char *)malloc((tokensSize + 13 + tokenSize) * sizeof(char));
                tokens = swapCharPointers(tokens, existingTokens);
                free(existingTokens);
            }
            if (token[0] != '\0')
            {
                token = (char *)malloc(1 * sizeof(char));
                token = "";
            }
            else
            {
            }
            continue;
        }
        else if (c == 62) // >
        {
            tagStarted = 0;
            if (endTagStarted)
            {
                endTagStarted = 0;
                int tokenSize = getCharPointerLength(token);
                int tokensSize = getCharPointerLength(tokens);
                char *existingTokens = (char *)malloc((tokensSize + 6 + tokenSize) * sizeof(char));
                existingTokens = swapCharPointers(existingTokens, tokens);
                existingTokens[tokensSize] = 'E';
                existingTokens[tokensSize + 1] = 'N';
                existingTokens[tokensSize + 2] = 'D';
                existingTokens[tokensSize + 3] = ':';
                int i = 0;
                while (token[i] != '\0')
                {
                    existingTokens[tokensSize + i + 4] = token[i];
                    i++;
                }
                existingTokens[tokensSize + 4 + tokenSize] = ':';
                existingTokens[tokensSize + 5 + tokenSize] = '\0';

                tokens = (char *)malloc((tokensSize + 6 + tokenSize) * sizeof(char));
                tokens = swapCharPointers(tokens, existingTokens);
                free(existingTokens);
            }
            else
            {
                int tokenSize = getCharPointerLength(token);
                int tokensSize = getCharPointerLength(tokens);
                char *existingTokens = (char *)malloc((tokensSize + 6 + tokenSize) * sizeof(char));
                existingTokens = swapCharPointers(existingTokens, tokens);
                existingTokens[tokensSize] = 'T';
                existingTokens[tokensSize + 1] = 'A';
                existingTokens[tokensSize + 2] = 'G';
                existingTokens[tokensSize + 3] = ':';
                int i = 0;
                while (token[i] != '\0')
                {
                    existingTokens[tokensSize + i + 4] = token[i];
                    i++;
                }
                existingTokens[tokensSize + 4 + tokenSize] = ':';
                existingTokens[tokensSize + 5 + tokenSize] = '\0';

                tokens = (char *)malloc((tokensSize + 6 + tokenSize) * sizeof(char));
                tokens = swapCharPointers(tokens, existingTokens);
                free(existingTokens);
            }
            if (token[0] != '\0')
            {
                token = (char *)malloc(1 * sizeof(char));
                token = "";
            }
            continue;
        }
        else if (c == 47) // /
        {
            endTagStarted = 1;
            continue;
        }
        else if (tagStarted)
        {
            int tokenSize = getCharPointerLength(token);
            char *existingToken = (char *)malloc((tokenSize + 1) * sizeof(char));
            existingToken = swapCharPointers(existingToken, token);
            existingToken[tokenSize] = c;
            existingToken[tokenSize + 1] = '\0';

            token = (char *)malloc((tokenSize + 1) * sizeof(char));
            token = swapCharPointers(token, existingToken);
            free(existingToken);
        }
        else if (!tagStarted && !endTagStarted)
        {
            if (c != 10 && c != 32) // new line, space
            {
                innerTextStarted = 1;
                int tokenSize = getCharPointerLength(token);
                char *existingToken = (char *)malloc((tokenSize + 1) * sizeof(char));
                existingToken = swapCharPointers(existingToken, token);
                existingToken[tokenSize] = c;
                existingToken[tokenSize + 1] = '\0';

                token = (char *)malloc((tokenSize + 1) * sizeof(char));
                token = swapCharPointers(token, existingToken);
                free(existingToken);
            }
        }
    }
    return tokens;
}

#endif
#ifndef MODELS_H
#define MODELS_H

typedef struct
{
    char *tag;
    char *innerText;
    struct DOMElement *childElements;
} DOMElement;

#endif
#include <stdio.h>
#include <malloc.h>

typedef struct
{
    char *tag;
    struct el *next;
} el;

// struct el
// {
//     int i;
//     struct el *next;
// };

int getsize(el *els)
{
    int i = 0;
    while (els != NULL && els->tag != NULL)
    {
        //printf("continue\n");
        els++;
        i++;
    }
    return i;
}

el *reverse(int size, el *els)
{
    for (int i = 0; i < size; i++)
    {
        els++;
    }
    return els;
}

el *swap(el *newels, el *els)
{
    for (int i = 0; i < getsize(els); i++)
    {
        newels[i] = els[i];
    }
    return newels;
}

void printel(el *els)
{
    for (int i = 0; i < getsize(els); i++)
    {
        printf("els i:%s\n", els[i].tag);
    }
}

int main()
{
    //el *old = (el *)malloc(1 * sizeof(el));
    //old[0].i = 90;
    //old[0].next = NULL;
    el *old = NULL;
    el *els = NULL;
    el newel;
    int size = getsize(old);
    printf("size:%d\n", size);
    printf("old size:%d\n", size);
    els = (el *)malloc((1 + size) * sizeof(el));
    els = swap(els, old);
    //els = reverse(size, els);
    printf("size:%d\n", getsize(els));
    //els[0].i = 10;
    //els[0].next = NULL;
    newel.tag = "div";
    //els[size].tag = newel.tag;
    //els[size].next = newel.next;
    //printf("i:%d\n", els->i);
    printf("size:%d\n", getsize(els));
    old = (el *)malloc((getsize(els)) * sizeof(el));

    printel(els);
    old = swap(old, els);
    printf("size:%d\n", getsize(old));
    //newels[1].i = 30;
    printel(old);
    printel(els);
    // printf("size:%d\n", getsize(newels));
    return 0;
}
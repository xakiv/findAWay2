#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "minpriorityqueue.h"

heap_t *create_heap(int n)
{
    heap_t *h = calloc(1,sizeof (heap_t));
    h->nodes = calloc(n, sizeof(node_t));
    h->len = 0;
    h->size = n;
    return h;
}

void free_heap(heap_t* h)
{
    free(h->nodes);
    free(h);
}

void push_heap (heap_t *h, int data, float priority) {
    if(h->len < h->size)
    {
        h->nodes[h->len].data = data;
        h->nodes[h->len].priority = priority;
        h->len = h->len + 1;
    }

}

int extract_min(heap_t *h) {
    int i;
    int data_min = -1;
    float priority_min = FLT_MAX;
    int index_min = -1;
    for (i =0; i < h->len; i++)
    {
        if(h->nodes[i].priority < priority_min)
        {
            data_min = h->nodes[i].data;
            priority_min = h->nodes[i].priority;
            index_min = i;
        }
    }

    for (i = index_min; i < h->len - 1; i++)
    {
        h->nodes[i].data = h->nodes[i+1].data;
        h->nodes[i].priority = h->nodes[i+1].priority;
    }
    h->len = h->len - 1;

    return data_min;
}

bool isEmpty(heap_t *h)
{
    return h->len <= 0;
}


float get_priority(heap_t *h, int v)
{
    int i = 0;
    float p = -1.0f;
    for(i = 0; i < h->len; i++)
    {
        if (h->nodes[i].data == v)
        {
            p = h->nodes[i].priority;
            break;
        }
    }
    return p;
}


bool is_in(heap_t *h, int v)
{
    return (get_priority(h, v) != -1.f);
}

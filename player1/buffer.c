#include "buffer.h"

void initialise_Buffer (PPong_Buffer * buffer)
{
 buffer->count = 0;
 buffer->head = NULL;
 buffer->tail = NULL;
}

void free_Buffer (PPong_Buffer * buffer)
{
    struct Node* tmp;

   while (buffer->head != NULL)
    {
       tmp = buffer->head;
       buffer->head = buffer->head->next;
       free(tmp);
    }
}

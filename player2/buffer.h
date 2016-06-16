#ifndef BUFFER_H
#define BUFFER_H

#include <SDL/SDL.h>

 struct Node{ 
    SDL_Rect position;
    struct Node *next;
};

 typedef struct BUFFER{
    struct Node *head;
    struct Node *tail;
    int count;   
} PPong_Buffer;

void initialise_Buffer (PPong_Buffer * buffer);
void free_Buffer (PPong_Buffer * buffer);

static inline void 
add_Node (PPong_Buffer * buffer, struct Node * node)
{
  if(!buffer->head)
  {
	buffer->head = node;
	buffer->tail  = node;
	buffer->count++;
  }
  else
  {
        buffer->tail->next = node;
	buffer->tail = node;      
	buffer->count++;
  }    
}

/*static inline SDL_Rect
get_Position (PPong_Buffer * buffer)
{
    SDL_Rect position;
  if(buffer->count > 0)
  {
      position = buffer->head->position;
              
       buffer->head=buffer->head->next;
       buffer->count--;
  }
return position;
    
}*/
#endif // BUFFER_H


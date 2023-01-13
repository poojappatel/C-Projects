#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void lru_init_queue(Set *set) {
  LRUNode *s = NULL;
  LRUNode **pp = &s;  // place to chain in the next node
  for (int i = 0; i < set->line_count; i++) {
    Line *line = &set->lines[i];
    LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
    node->line = line;
    node->next = NULL;
    (*pp) = node;
    pp = &((*pp)->next);
  }
  set->lru_queue = s;
}

void lru_init(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    lru_init_queue(&sets[i]);
  }
}

void lru_destroy(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    LRUNode *p = sets[i].lru_queue;
    LRUNode *n = p;
    while (p != NULL) {
      p = p->next;
      free(n);
      n = p;
    }
    sets[i].lru_queue = NULL;
  }
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
  // TODO:
  // Implement the LRU algorithm to determine which line in
  // the cache should be accessed.
  //


  /*
  //LRUNode *prev_node = (LRUNode *)(malloc(sizeof(LRUNode)));
  LRUNode *prev_node = NULL;
  // LRUNode *curr_node = (LRUNode *)(malloc(sizeof(LRUNode)));
  LRUNode *curr_node = set->lru_queue;
  while (curr_node != NULL) {
    if ((curr_node->line->valid == 1) && curr_node->line->tag == tag) {
      result->line = curr_node->line;
      result->access = HIT;
      break;
    } else if (!(curr_node->line->valid)) {
      result->access = COLD_MISS;
      result->line = curr_node->line;
      curr_node->line->valid = 1;
      curr_node->line->tag = tag;
      break;
    } else if (curr_node->next == NULL) {
      result->access = CONFLICT_MISS;
      result->line = curr_node->line;
      curr_node->line->tag = tag;
      break;
    } else {
      prev_node = curr_node;
      curr_node = curr_node->next;
      // continue;
    }
  
  }
    // if (prev_node != NULL) {
    prev_node->next = curr_node->next;
    curr_node->next = set->lru_queue;
    set->lru_queue = curr_node;
    // result->line = curr_node->line;
  
}
  */


 
  LRUNode *curr_node;
  LRUNode **prev_node = &(set->lru_queue);
  //curr_node = *prev_node;
  while ((*prev_node) != NULL) {
    curr_node = *prev_node;
    if (curr_node->line->valid && curr_node->line->tag == tag) {
      result->access = HIT;
      result->line = curr_node->line;
      break;
    } else if(!(curr_node->line->valid)){
      result->access = COLD_MISS;
      result->line = curr_node->line;
      curr_node->line->valid = 1;
      curr_node->line->tag = tag;
      break;
    } else if(curr_node->next == NULL){
      result->access = CONFLICT_MISS;
      result->line = curr_node->line;
      curr_node->line->tag = tag;
      break;
    } else {
      prev_node = &((*prev_node)->next);
      continue;
  
    }
  }
    *prev_node = curr_node->next;
    curr_node->next = set->lru_queue;
    set->lru_queue = curr_node;

  
}

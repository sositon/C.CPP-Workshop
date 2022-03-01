//
// Created by omer siton on 22/11/2021.
//
#include "HashSet.h"
#define QUAD_PROBING(HASH, I, CAP) ((HASH) + ((I + (I*I)) / 2)) & (CAP - 1)

/**
 * save non empty Nodes on the hashset, clear the hash_set and then create
 * resized NodesList
 * @param hash_set the source hashset
 * @param new_size the new size to resize to
 * @return NodesList contains the old nodes but in different size
 */
int nodes_list_resize (HashSet *hash_set, size_t new_size)
{
  if (!hash_set || !hash_set->NodesList || !new_size)
    return 0;
  //// save nonempty nodes data
  Value *tmp = malloc (hash_set->size * sizeof (Value));
  size_t tmp_size = hash_set->size;
  for (size_t i = 0, j = 0; i < hash_set->capacity; ++i)
  {
    if (hash_set_at (hash_set, (int) i)){
      tmp[j] = hash_set->value_cpy(hash_set_at (hash_set, (int) i));
      j++;
    }
    if (j == tmp_size)
      break;
  }
  //// clear hashset
  hash_set_clear (hash_set);
  if (hash_set->capacity < new_size)
  {
    hash_set->NodesList = realloc (hash_set->NodesList,
                                   new_size * sizeof (Node *));
    for (size_t i = hash_set->capacity ; i < new_size; ++i)
      hash_set->NodesList[i] = node_alloc (
          hash_set->value_cpy, hash_set->value_cmp, hash_set->value_free);
    hash_set->capacity *= HASH_SET_GROWTH_FACTOR;
  }
  else if (hash_set->capacity > new_size)
  {
    for (size_t i = new_size; i < hash_set->capacity; ++i)
      node_free (&(hash_set->NodesList[i]));
    hash_set->NodesList = realloc (hash_set->NodesList,
                                   new_size * sizeof (Node *));
    hash_set->capacity /= HASH_SET_GROWTH_FACTOR;
  }
  //// insert to the new NodesList
  for (size_t i = 0; i < tmp_size; ++i)
  {
    if (!(hash_set_insert (hash_set, tmp[i])))
    {
      for (size_t j = 0; j < tmp_size; ++j)
        hash_set->value_free (&tmp[j]);
      free (tmp);
      return 0;
    }
  }
  for (size_t j = 0; j < tmp_size; ++j)
    hash_set->value_free (&tmp[j]);
  free (tmp);
  return 1;
}
/**
 * Allocates dynamically new hash set.
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL or if one of the function pointers is null.
 */
HashSet *hash_set_alloc (HashFunc hash_func, HashSetValueCpy value_cpy,
                         HashSetValueCmp value_cmp,HashSetValueFree value_free)
{
  if (!hash_func || !value_cpy || !value_cmp || !value_free)
    return NULL;
  HashSet *hash_set = malloc (sizeof (HashSet));
  hash_set->hash_func = hash_func;
  hash_set->value_cpy = value_cpy;
  hash_set->value_cmp = value_cmp;
  hash_set->value_free = value_free;
  hash_set->size = 0;
  hash_set->capacity = HASH_SET_INITIAL_CAP;
  //// allocate memory with nodes
  hash_set->NodesList = malloc (hash_set->capacity * sizeof (Node *));
  for (size_t i = 0; i < hash_set->capacity; ++i)
    hash_set->NodesList[i] = node_alloc (value_cpy, value_cmp, value_free);
  return hash_set;
}

/**
 * Frees the hash set and all its elements.
 * @param p_hash_set pointer to pointer to a hash_set.
 */
void hash_set_free (HashSet **p_hash_set)
{
  if (!p_hash_set || !(*p_hash_set))
    return;
  Node *cur_node;
  for (size_t i = 0; i < (*p_hash_set)->capacity; ++i)
    {
      cur_node = ((*p_hash_set)->NodesList)[i];
      node_free (&cur_node);
    }
  free ((*p_hash_set)->NodesList);
  free (*p_hash_set);
  *p_hash_set = NULL;
}

/**
 * Inserts a new Value to the hash set.
 * The function inserts *new*, *copied*, *dynamically allocated* Value,
 * @param hash_set the hash set where we want to insert the new element
 * @param value a Value we would like to add to the hashset
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hash_set_insert (HashSet *hash_set, Value value)
{
  if (!hash_set || !value)
    return 0;
  if (!hash_set->hash_func|| !hash_set->value_cpy || !hash_set->value_free
    || !hash_set->value_cmp)
    return 0;
  if (hash_set_contains_value (hash_set, value))
    return 0;
  size_t cap = hash_set->capacity, ind, i=0;
  do
    {
      ind = QUAD_PROBING(hash_set->hash_func (value), i, cap);
      if (i == 0)
        hash_set->NodesList[ind]->hashCount ++;
      if (!(hash_set_at (hash_set, (int) ind)))
      {
        if (set_node_data (hash_set->NodesList[ind], value))
          break;
        else
          return 0;
      }
      i++;
    }while (i < cap);
  hash_set->size ++;
  if (hash_set_get_load_factor (hash_set) >= HASH_SET_MAX_LOAD_FACTOR)
  {
    //// save the values inside the hash_table and copy them into the new
    /// nodelist
    if (!nodes_list_resize (hash_set,
                            hash_set->capacity * HASH_SET_GROWTH_FACTOR))
      return 0;
  }
  return 1;
}

/**
 * The function checks if the given value exists in the hash set.
 * @param hash_set a hash set.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash set, 0 otherwise.
 */
int hash_set_contains_value (HashSet *hash_set, Value value)
{
  if (!hash_set || !value || !(hash_set->NodesList))
    return 0;
  size_t i = 0;
  do{
    size_t ind = QUAD_PROBING(hash_set->hash_func (value), i,
                              hash_set->capacity);
    Node *cur_node = hash_set->NodesList[ind];
    if (!i && !get_hash_count (cur_node))
      return 0;
    if (check_node (cur_node, value) == 1)
      return 1;
    i++;
  }while (i < hash_set->capacity);
  return 0;
}

/**
 * The function erases a Value.
 * @param hash_set a hash set.
 * @param value the value to be erased from the hashtable
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int hash_set_erase (HashSet *hash_set, Value value)
{
  if (!hash_set || !value)
    return 0;
  if (!hash_set->hash_func|| !hash_set->value_cpy || !hash_set->value_free
  || !hash_set->value_cmp)
    return 0;
  if (!hash_set_contains_value (hash_set, value))
    return 0;
  size_t cap = hash_set->capacity, ind, i=0;
  size_t first_ind = QUAD_PROBING(hash_set->hash_func (value),i, cap);
  hash_set->NodesList[first_ind]->hashCount --;
  do
  {
    ind = QUAD_PROBING(hash_set->hash_func (value), i, cap);
    if (check_node (hash_set->NodesList[ind], value) == 1)
    {
      clear_node (hash_set->NodesList[ind]);
      break;
    }
    i++;
  }while (i < cap);
  hash_set->size --;
  if (hash_set_get_load_factor (hash_set) <= HASH_SET_MIN_LOAD_FACTOR)
  {
    //// save the values inside the hash_table and copy them into the new
    /// nodelist
    if (!nodes_list_resize
    (hash_set,hash_set->capacity / HASH_SET_GROWTH_FACTOR))
      return 0;
  }
  return 1;
}

/**
 * This function returns the load factor of the hash set.
 * @param hash_set a hash set.
 * @return the hash set's load factor, -1 if the function failed.
 */
double hash_set_get_load_factor (HashSet *hash_set)
{
  if (!hash_set || !(hash_set->capacity))
    return -1;
  return (double) (hash_set->size) / (double) (hash_set->capacity);
}

/**
 * This function deletes all the values in the hash set.
 * @param hash_set a hash set to be cleared.
 */
void hash_set_clear (HashSet *hash_set)
{
  if (!hash_set || !(hash_set->NodesList))
    return;
  for (size_t i = 0; i < hash_set->capacity; ++i)
    {
      if (hash_set->NodesList[i]->data)
        clear_node (hash_set->NodesList[i]);
      hash_set->NodesList[i]->hashCount = 0;
    }
  hash_set->size = 0;
}

/**
 * This function gets the element in the hashset hashed to the indexed value
 * @param hash_set the hashset
 * @param value the index of the node in the hashtable that we would like to
 * have its value
 * @return the element in the hashset hashed to the indexed value
 * NULL in case of an error or an empty node or an unexpected value
 */
Value hash_set_at (HashSet *hash_set, int value)
{
  if (!hash_set || !hash_set->NodesList
      || value >= (int)(hash_set->capacity) || value < 0)
    return NULL;
  if (!hash_set->NodesList[value])
    return NULL;
  return hash_set->NodesList[value]->data;
}

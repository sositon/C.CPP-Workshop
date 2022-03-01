#include "ex2.h"

#define START_FLAG 1
#define END_FLAG 0
#define SUCCESS 1
#define FAILURE 0
#define DEF_OPEN_MODE "r"
#define START "s"
#define GROWTH_FACTOR 2
#define DEF_ALLOC_SIZE 5
#define DELIMITERS ","
#define DEF_BUFFER_SIZE 1027
#define DEF_POINTER_ERR_MSG "pointers are invalid"
#define DEF_ALLOC_ERR_MSG "allocation fail"
#define DEF_FILE_ERR_MSG "file open fail"
#define DEF_BASE 10
#define DEF_ERR_INIT "ERROR: %s() - %s.\n"

LinkedList *new_linked_list (Node *head, Node *tail)
{
  LinkedList *linked_list = malloc (sizeof (*linked_list));
  if (linked_list != NULL)
    {
      linked_list->head = head;
      linked_list->tail = tail;
    }
  return linked_list;
}

Node *new_node (Node *next, Node *prev, int *data, size_t len)
{
  Node *new_node = malloc (sizeof (*new_node));
  if (new_node != NULL)
    {
      new_node->next = next;
      new_node->prev = prev;
      new_node->data = malloc (len * sizeof (int));
      new_node->len = len;
    }
  memcpy(new_node->data, data, len * sizeof (int));
  free (data);
  data = NULL;
  return new_node;
}

void *safe_realloc (void *pt, size_t new_size)
{
  void *tmp = realloc (pt, new_size);
  if (tmp == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
      free (pt);
      pt = NULL;
      return NULL;
    }
  return tmp;
}

/** This function prints contents of linked list
*/
void print_list (LinkedList *list)
{
  Node *node = list->head;
  printf ("<-> ");
  while (node != NULL)
    {
      for (size_t i = 0; i < node->len; ++i)
        {
          if (i == (node->len) - 1)
            {
              printf ("%d", node->data[i]);
            }
          else printf ("%d,", node->data[i]);
        }
      node = node->next;
      printf (" <-> ");
    }
  printf ("\n");
}

/**
 * Adds a node as the head of the list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_start_linked_list (LinkedList *const list, Node *const node)
{
  // check pointers
  if (list == NULL || node == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return;
    }
  // link node to the list head
  node->next = list->head;
  // init node prev to NULL, since we add it to the beginning
  node->prev = NULL;
  // change prev of list head if exist to node
  if (list->head != NULL)
    {
      list->head->prev = node;
    }
  // move the head pointer to node
  list->head = node;
  // check if tail pointer is empty
  if (list->tail == NULL)
    {
      list->tail = node;
    }
}

/**
 * Adds a node as the tail of the list.
 *
 * Assumptions:
 *   You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_end_linked_list (LinkedList *const list, Node *const node)
{
  // check pointers
  if (list == NULL || node == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return;
    }
  // link node to the list tail
  node->prev = list->tail;
  // init node next to NULL, since we add it to the end
  node->next = NULL;
  // change next of list tail if exist to node
  if (list->tail != NULL)
    {
      list->tail->next = node;
    }
  // move the tail pointer to node
  list->tail = node;
  // check if head pointer is empty
  if (list->head == NULL)
    {
      list->head = node;
    }
}
/**
 * this function check if a given Node is in LinkedList
 * @param list LinkedList*
 * @param node Node*
 * @return 1 if yes, else 0
 */
int is_node_in_list (LinkedList *const list, Node *const node)
{
  Node *cur_node = list->head;
  while (cur_node)
    {
      if (cur_node == node)
        {
          return SUCCESS;
        }
      cur_node = cur_node->next;
    }
  return FAILURE;
}
/**
 * removes a node from the list and frees it's resources.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You cannot assume the node is in the list. In this case don't free its resources.
 *    To be sure - you are supposed to compare the given node to the nodes in the list using == operator.
 *
 * In case of errors:
 *    Invalid pointer - print informative error message to stderr and return from function.
 *
 * @param list pointer to list to remove a node from.
 * @param node pointer to the node to remove from the list.
 */
void remove_node (LinkedList *const list, Node *const node)
{
  // check pointers
  if (list == NULL || node == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return;
    }
  if (is_node_in_list (list, node))
    {
      // if node to be deleted is head node
      if (list->head == node)
        {
          list->head = node->next;
        }
      // if node to be deleted is tail node
      if (list->tail == node)
        {
          list->tail = node->prev;
        }
      // change next only if node to be deleted is not the last node
      if (node->next != NULL)
        {
          node->next->prev = node->prev;
        }
      // change prev only if node to be deleted is not the first node
      if (node->prev != NULL)
        {
          node->prev->next = node->next;
        }
      // finally, free the memory occupied by node
      free (node->data);
      node->data = NULL;
      free (node);
    }
}

/**
 * Frees the resources (all dynamic allocations) of the given list.
 *
 * Assumptions:
 *    You cannot assume the pointer is valid.
 *
 * In case of errors:
 *    Invalid pointer - This means there is nothing to free, just return from function.
 *
 * @param list the list to free.
 */
void free_linked_list (LinkedList *const list)
{
  // check if list pointer is NULL
  if (list == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return;
    }
  // remove nodes
  Node *cur_node = list->head;
  while (cur_node)
    {
      Node *next_node = cur_node->next;
      remove_node (list, cur_node);
      cur_node = next_node;
    }
  // finally, free the memory occupied by list
  free (list);
}

/**
 * calculates the grade average of every node in the linked list.
 * and adds it to the average array
 *@return average_arr
 */
double *average_helper (double *average_arr, Node *cur_node,
                        size_t *num_elements_in_returned_array,
                        size_t *capacity)
{
  while (cur_node)
    {
      // init average
      double average = 0;
      if (cur_node->data != NULL)
        {
          // loop over data to calculate average
          for (int i = 0; i < (int) cur_node->len; ++i)
            {
              average += cur_node->data[i];
            }
          average /= (double) cur_node->len;
          // check if average_arr have free space
          if (*num_elements_in_returned_array == *capacity)
            {
              *capacity *= GROWTH_FACTOR;
              average_arr = safe_realloc (average_arr,
                                          *capacity * sizeof (double));
              if (average_arr == NULL)
                {
                  fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
                  return NULL;
                }
            }
          average_arr[*num_elements_in_returned_array] = average;
          (*num_elements_in_returned_array)++;
        }
      cur_node = cur_node->next;
    }
  return average_arr;
}
/**
 * calculates the grade average of every node in the linked list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You don't know the number of nodes in the linkedlist in advance.
 *    You can assume that there is at least one node with data != NULL (i.e. len > 0).
 *    You can assume that for each node 'len' is indeed the length of 'data'
 *     (in particular len=0 <=> data=NULL).
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Node with NULL data - don't count the node in the calculation.
 *
 * @param list: LinkedList pointer to linked list from whom to calculate grade averages.
 * @param num_elements_in_returned_array: pointer to unsigned long, that should
 * contain the number of nodes in the list
 * (for nodes with data != NULL) when the function finishes execution. To be clear - at the start of the function,
 * (*num_elements_in_returned_array) is a garbage value, and this function should set its value.
 *    @Note: Nodes with NULL data should not be count in the calculation.
 *    Therefore *num_elements_in_returned_array <= numOfNodes.
 * @return array of grade averages per node. To be clear - this means you should
 * calculate the grade average of every node and save it into an array, which you will return from the function.
 */
double *get_averages (LinkedList *const list,
                      size_t *const num_elements_in_returned_array)
{
  // check pointer
  if (list == NULL || num_elements_in_returned_array == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return NULL;
    }
  // init num_elements_in_returned_array
  *num_elements_in_returned_array = 0;
  // init average_arr to return
  size_t capacity = DEF_ALLOC_SIZE;
  double *average_arr = malloc (capacity * sizeof (*average_arr));
  // check if malloc failed
  if (average_arr == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
      return NULL;
    }
  // start calculate averages
  Node *cur_node = list->head;
  return average_helper (average_arr, cur_node, num_elements_in_returned_array,
                         &capacity);
}

/** continue reading the last string put into strtok
* continue to parse until there is nothing left to parse in buffer
* - that's when strtok will return NULL */
int parse_helper (int *data_pt, char *token, size_t *capacity,
                  size_t *counter)
{
  while ((token = strtok (NULL, DELIMITERS)))
    {
      // check if realloc is needed
      if (*counter == *capacity)
        {
          *capacity *= GROWTH_FACTOR;
          data_pt = safe_realloc (data_pt, *capacity * sizeof (int));
          if (data_pt == NULL)
            {
              return FAILURE;
            }
        }
      data_pt[*counter] = (int) strtol (token, NULL, DEF_BASE);
      ++(*counter);
    }
  return SUCCESS;
}
/**
 * opens a file safely
 * @param file const char *const - path file
 * @return File* if succeed, else NULL
 */
FILE *file_safe_open (const char *const file)
{
  // pointer check
  if (file == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_POINTER_ERR_MSG);
      return NULL;
    }
  // file open
  FILE *fd = fopen (file, DEF_OPEN_MODE);
  if (fd == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_FILE_ERR_MSG);
      return NULL;
    }
  return fd;
}
/**
 * opens a file from a given filename and parses it's contents into a LinkedList.
 *
 * Assumptions:
 *    You cannot assume the filename is OK (meaning - you cannot assume it is a valid path to a file).
 *    You cannot assume anything on the number of ints in a row of the file, just that it is >= 1.
 *    You can assume that if the file opened, then it is exactly in the format specified in the exercise PDF.
 *    You can assume max line length of 1024.
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    File open fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *
 * Think - in what mode should we open this file? (read? write? append?)
 *
 * @param file filename of input file that needs to be parsed.
 * @return pointer to LinkedList instance, whose nodes and data arrays were parsed from the given file.
 */
LinkedList *parse_linked_list (const char *const filename)
{
  FILE *fd = file_safe_open (filename);
  if (fd == NULL)
    {
      return NULL;
    }
  // create new linked list
  LinkedList *parse_linked_list = new_linked_list (NULL, NULL);
  if (parse_linked_list == NULL)
    {
      fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
      fclose (fd);
      return NULL;
    }
  char buffer[DEF_BUFFER_SIZE] = {0}, *token = NULL;
  // start parsing
  while (fgets (buffer, DEF_BUFFER_SIZE, fd) != NULL)
    {
      // init variables
      int flag = END_FLAG;
      size_t len = 0, capacity = DEF_ALLOC_SIZE;
      // set the string to parse, read first token
      token = strtok (buffer, DELIMITERS);
      if (strcmp (token, START) == 0)
        {
          flag = START_FLAG;
        }
      int *data = malloc (capacity * sizeof (int));
      if (data == NULL)
        {
          fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
          fclose (fd);
          return NULL;
        }
      while ((token = strtok (NULL, DELIMITERS)))
        {
          // check if realloc is needed
          if (len == capacity)
            {
              capacity *= GROWTH_FACTOR;
              data = safe_realloc (data, capacity * sizeof (int));
              if (data == NULL)
                {
                  fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
                  fclose (fd);
                  return NULL;
                }
            }
          data[len] = (int) strtol (token, NULL, DEF_BASE);
          len++;
        }
      //    realloc to the exact size of the data array
      data = safe_realloc (data, (len) * sizeof (int));
      if (data == NULL)
        {
          fprintf (stderr, DEF_ERR_INIT, __func__, DEF_ALLOC_ERR_MSG);
          fclose (fd);
          return NULL;
        }
      Node *tmp_node = new_node (NULL, NULL, data, len);
      if (flag)
        {
          add_to_start_linked_list (parse_linked_list, tmp_node);
        }
      else add_to_end_linked_list (parse_linked_list, tmp_node);
    }
  fclose (fd);
  return parse_linked_list;
}
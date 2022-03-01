//
// Created by Eli Levinkopf on 29/10/2021.
//
#include "ex2.h"

#define LINE "\n=============================================================================\n"

//=============================================================================
/**
 * Prints the linked list
 * @param list
 */
void print_linked_list (struct LinkedList *list)
{
  if (!list)
	{
	  fprintf (stderr, "The function got an invalid pointer\n");
	  return;
	}
  Node *tmp = list->head;
  printf ("NULL <---> ");
  while (tmp)
	{
	  size_t size = tmp->len - 1;
	  if (tmp->len != 0)
		{
		  for (size_t i = 0; i <= size; i++)
			{
			  if (i == 0)
				{
				  printf ("{");
				}
			  printf ("%d", tmp->data[i]);
			  if (i != size)
				{
				  printf (",");
				}
			  if (i == size)
				{
				  printf ("}");
				}
			}
		}
	  else
		{
		  printf ("{}");
		}
	  printf (" <---> ");
	  tmp = tmp->next;
	}
  printf ("NULL\n");
}

//=============================================================================
/**
 * adds manually nods to linked list and removes them.
 * check the functions: add_to_start_linked_list, add_to_end_linked_list and remove_node.
 * @return 1 if pass, 0 otherwise
 */
int manual_linked_list ()
{
  LinkedList *manual_list = calloc (1, sizeof (LinkedList));
  Node *node_1 = calloc (1, sizeof (Node));
  Node *node_2 = calloc (1, sizeof (Node));
  Node *node_3 = calloc (1, sizeof (Node));
  Node *node_4 = calloc (1, sizeof (Node));

  size_t len_1 = 1, len_2 = 1, len_3 = 1, len_4 = 1;
  node_1->len = len_1, node_2->len = len_2;
  node_3->len = len_3, node_4->len = len_4;

  node_1->data = calloc (len_1, sizeof (int));
  node_2->data = calloc (len_2, sizeof (int));
  node_3->data = calloc (len_3, sizeof (int));
  node_4->data = calloc (len_4, sizeof (int));

  node_1->data[0] = 10, node_2->data[0] = 2;
  node_3->data[0] = 3, node_4->data[0] = 4;

  printf ("%s", "manual list: ");
  print_linked_list (manual_list);
  printf ("\n%s", "add node 1 to s: \nmanual list: ");
  add_to_start_linked_list (manual_list, node_1);
  print_linked_list (manual_list);
  printf ("\n%s", "add node 2 to e: \nmanual list: ");
  add_to_end_linked_list (manual_list, node_2);
  print_linked_list (manual_list);
  printf ("\n%s", "add node 3 to s: \nmanual list: ");
  add_to_start_linked_list (manual_list, node_3);
  print_linked_list (manual_list);
  printf ("\n%s", "add node 4 to e: \nmanual list: ");
  add_to_end_linked_list (manual_list, node_4);
  print_linked_list (manual_list);
  printf ("\n%s", "remove node 4: \nmanual list: ");
  remove_node (manual_list, node_4);
  print_linked_list (manual_list);
  printf ("\n%s", "remove node 1: \nmanual list: ");
  remove_node (manual_list, node_1);
  print_linked_list (manual_list);
  printf ("\n%s", "remove node 3: \nmanual list: ");
  remove_node (manual_list, node_3);
  print_linked_list (manual_list);
  printf ("\n%s", "remove node 2: \nmanual list: ");
  remove_node (manual_list, node_2);
  print_linked_list (manual_list);
  puts (LINE);
  if (manual_list->head || manual_list->tail)
	{
	  fprintf (stderr, "fail in test: 'manual_linked_list'\n");
	  free (manual_list);
	  return 0;
	}
  free (manual_list);
  printf ("%s", "pass test: 'manual_linked_list'\n");
  return 1;
}

//=============================================================================
/**
 * checks if node->len is exactly the the number of integers in node->data
 * @param list linked list from file 'LinkedList.txt'
 * @return 1 if pass, 0 otherwise
 */
int check_len (LinkedList *list)
{
  if (!list)
	{
	  fprintf (stderr, "The function got an invalid pointer\n");
	  return 0;
	}
  int size_of_nodes_in_list_1[5] = {4, 2, 3, 283};
  Node *tmp = list->head;
  int i = 0;
  while (tmp)
	{
	  if ((size_t)size_of_nodes_in_list_1[i] !=tmp->len)
		{
          fprintf (stderr, "got: %lu , wanted: %d\n", tmp->len, size_of_nodes_in_list_1[i]);
		  fprintf (stderr,
				   "The capacity of data is not equal to the number of element in data. => fail in test: 'check_len'\n");
		  return 0;
		}
	  tmp = tmp->next;
	  i++;
	}
  printf ("%s", "pass test: 'check_len'\n");
  return 1;
}

//=============================================================================
/**
 * check if the pointer 'num_elements_in_returned_array' contain the number of (not empty) nodes in the list and if the function 'get_averages' return the correct averages.
 * @param list linked list from file 'LinkedList.txt'
 * @return 1 if pass, 0 otherwise
 */
int check_get_averages (LinkedList *list)
{
  int num_of_not_empty_data = 4;
  double expected_averages_array[4] = {48.0, 5.0, 0.0, 141.0};
  size_t num_elements_in_returned_array = 0;
  double *averages_array = get_averages (list, &num_elements_in_returned_array);
  if ((size_t)num_of_not_empty_data != num_elements_in_returned_array)
	{
	  fprintf (stderr, "got: %zu , wanted: %d\n", num_elements_in_returned_array, num_of_not_empty_data);
	  fprintf (stderr,
			   "the value of 'num_elements_in_returned_array' is incorrect => fail in test: 'check_get_averages'\n");
	  return 0;
	}
  for (int i = 0; i < (int)num_elements_in_returned_array; i++)
	{
	  if (expected_averages_array[i] != averages_array[i])
		{
		  fprintf (stderr, "got: %d , wanted: %zu\n", expected_averages_array[i],  averages_array[i]);
		  free (averages_array);
		  fprintf (stderr,
				   "at least one of the averages is incorrect => fail in test: 'check_get_averages'\n");
		  return 0;
		}
	}
  free (averages_array);
  printf ("%s", "pass test: 'check_get_averages'\n");
  return 1;
}

//=============================================================================
int check_errors ()
{
  LinkedList *list = calloc (1, sizeof (LinkedList));
  Node *node = calloc (1, sizeof (Node));
  size_t num_elements_in_returned_array = 0;
  add_to_start_linked_list (list, NULL);
  add_to_start_linked_list (NULL, node);
  add_to_end_linked_list (list, NULL);
  add_to_end_linked_list (NULL, node);
  remove_node (list, node);
  remove_node (list, NULL);
  remove_node (NULL, node);
  get_averages (NULL, &num_elements_in_returned_array);
  get_averages (list, NULL);
  parse_linked_list ("this is not a valid path");
  free (list);
  free (node);
  return 1;
}

//=============================================================================
int main (int argc, char *argv[])
{
  if (argc != 2)
	{
	  fprintf (stderr, "the number of arguments != 2");
	  return 0;
	}
  LinkedList *list = parse_linked_list (argv[1]);
  puts (LINE);
  printf ("list from file: ");
  print_linked_list (list);
  puts (LINE);
  int test_1 = manual_linked_list ();
  int test_2 = check_len (list);
  int test_3 = check_get_averages (list);
  check_errors ();
  if (test_1 && test_2 && test_3)
	{
	  printf ("%s",
			  "\n*******************\n* passed all test *\n*******************\n\n");
	}
  free_linked_list (list);

  return 0;
}
// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018

// This makes sure that we include the header file only once
#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER


// document analysis project linked list structs

// this contains both the word and the number of times the word occurs in the document.
struct word_entry
{
	char *unique_word ;			// be sure to malloc exactly enough space to hold the string for the word include the '\0'.
	int word_count ;			// The number of times this word occurs in the input document (by definition at least one).
} ;

// 
struct node
{
	struct word_entry one_word ;// a word we have seen at least once with the number of occurrences.
	struct node *p_previous ;	// set to NULL if this node is the first in the list.
	struct node *p_next ;		// set to NULL if this node is the last in the list
} ;

struct linked_list
{
	struct node *p_head ;	// points to the first node in the list. NULL if the list is empty.
	struct node *p_tail ;	// points to the last node in the list. NULL if the list is empty.
	struct node *p_current ;// points to the most recently added or accessed record. NULL if the list is empty.
} ;


// linked list function prototypes

extern struct node *create_node( char *word ) ;
extern int add_node_at_head( struct linked_list *p_list, char *word ) ;
extern int clear_linked_list( struct linked_list *p_list ) ;
extern int add_node_after_current( struct linked_list *p_list, char *word ) ;
extern int find_word( struct linked_list *p_list, char *word ) ;

#endif	// matches the #ifndef at the beginning that avoids multiple inclusions.

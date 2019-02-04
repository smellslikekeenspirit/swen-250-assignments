// unit_tests.c
// Larry L. Kiser Oct. 22, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "linked_list_functions.h"
#include "unit_tests.h"

// Simple boolean assert function for unit testing
// DO NOT MODIFY THIS FUNCTION
int assert( int test_result, char error_format[], ... ) {
	va_list arguments ;
	static int test_number = 1 ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! test_result ) {
		va_start( arguments, error_format ) ;
		printf( "Test # %d failed: ", test_number ) ;
		vprintf( error_format, arguments ) ;
		printf( "\n" ) ;
		result = 0 ;
	}
	test_number++ ;
	return result ;
}

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

int test()
{
	int passcount = 0 ;
	int failcount = 0 ;
	int result = 0 ;		// general purpose work variable for functions that return integers
	struct linked_list list1 ;		// list list pointers for one list
	//struct word_entry one_entry ;	// general purpose return struct for unit tests
	
	// Initialize local stack data
	memset( &list1, 0, sizeof( list1 ) ) ;		// set all pointers to NULL (zero)
	
	// Tests for create_node function
	printf( "\n========= tests for create_node ================================================\n" ) ;
	struct node *p_one_node = create_node( "test" ) ;
	
	// Test 1 test p_next
	if ( p_one_node == NULL )
	{
		assert( 0 ,"p_one_node is NULL -- exiting unit tests" ) ;		// mark assertion failure on NULL node pointer
		return ++failcount ;
	}
	assert( p_one_node->p_next == NULL,
		"The p_next pointer must be NULL but it is not NULL" )
		? passcount++ : failcount++ ;
	
	// Test 2 test p_previous
	assert( p_one_node->p_previous == NULL,
		"The p_previous must be NULL but it is not NULL" )
		? passcount++ : failcount++ ;
	
	// Test 3 test unique_word is not NULL
	char *p_unique_word = NULL ;
	p_unique_word = p_one_node->one_word.unique_word ;	// get a pointer to the unique word to simplify code
	assert( p_unique_word != NULL,
		"The unique word string must not be NULL" )
		? passcount++ : failcount++ ;
	
	// Test 4 now see that the correct word was copied
	// program will crash here if unique_word is NULL
	assert( p_unique_word != NULL && strcmp( p_unique_word, "test" ) == 0,
		"The unique word string must not be NULL and must match \"test\". Actually contains %s", p_unique_word )
		? passcount++ : failcount++ ;
	
	// Test 5 confirm that the word count is 1
	assert( p_one_node->one_word.word_count == 1,
		"The word_count must be 1. Actually is %d", p_one_node->one_word.word_count )
		? passcount++ : failcount++ ;
              
	
	printf( "%d tests passed. \n========= tests for add_node_at_head and clear_linked_list (just one node)======\n", passcount ) ;
	
	// Test 6 Verify that NULL word is handled correctly
	result = add_node_at_head( NULL, "first" ) ;
	assert( result == 0,
		"Must return 0 if the linked_list pointer is NULL. Your function returned %d", result )
		? passcount++ : failcount++ ;
		
	// Test 7 check for NULL pointer on word
	result = add_node_at_head( &list1, NULL ) ;
	assert( result == 0,
		"Must return 0 if the word is NULL. Your function returned %d", result )
		? passcount++ : failcount++ ;
	
	// Test 8 check for empty word
	result = add_node_at_head( &list1, "" ) ;
	assert( result == 0,
		"Must return 0 if the word is an empty string. Your function returned %d", result )
		? passcount++ : failcount++ ;
	
	// Test 9 now add our first word
	result = add_node_at_head( &list1, "first" ) ;
	assert( result == 1,
		"Must return 1 on a successful add of a new node. Your function returned %d", result )
		? passcount++ : failcount++ ;
	
	// Test 10 check that the head, current, and tail pointers are all the same
	assert( list1.p_head != NULL && list1.p_head == list1.p_current && list1.p_head == list1.p_tail,
		"After adding one record to any empty list all three pointers must be the same and not NULL" )
		? passcount++ : failcount++ ;
	
	// Test 11 check that the correct word is actually stored in that node
	if ( list1.p_head == NULL )
	{
		assert( 0 ,"list1.p_head is NULL -- exiting unit tests" ) ;		// mark assertion failure on NULL node pointer
		return ++failcount ;
	}
	assert( strcmp( list1.p_head->one_word.unique_word, "first" ) == 0,
		"The word stored must be \"first\" but the actual word is \"%s\"", list1.p_head->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 12 now clear the linked list
	result = clear_linked_list( &list1 ) ;
	assert( result == 1,
		"List has only one entry so the cleared count must be 1. Your function returned %d", result )
		? passcount++ : failcount++ ;

	if ( result != 1 )
	{
		printf( "\nImplement clear_linked_list since it is needed by subsequent tests\nExiting unit tests.\n" ) ;
		return failcount ;
	}
	
	// Test 13 now confirm that list1 now has three empty pointers
	assert( ! (list1.p_head || list1.p_tail || list1.p_current),
		"All three pointers in list1 must now be NULL" )
		? passcount++ : failcount++ ;
		
	// Test 14 now confirm that clear the linked list works correctly on a list that is already empty
	result = clear_linked_list( &list1 ) ;
	assert( result == 0,
		"List is empty so the cleared count must be 0. Your function returned %d", result )
		? passcount++ : failcount++ ;
	
	printf( "\n========= tests for add_node_at_head and clear_linked_list (two nodes)==========\n" ) ;
	// Test 15 Add two words to the head of the list
	result = add_node_at_head( &list1, "last" ) ;
	result = add_node_at_head( &list1, "first" ) ;
	assert( list1.p_head != NULL && list1.p_head == list1.p_current && list1.p_head != list1.p_tail,
		"After adding two records to an empty list head and current must be the same and tail must be different" )
		? passcount++ : failcount++ ;

	// Test 16 Now check that the first word is first
	assert( strcmp( list1.p_head->one_word.unique_word, "first" ) == 0,
		"The word stored must be \"first\" but the actual word is \"%s\"", list1.p_head->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 17 Now check that the second word is last
	assert( strcmp( list1.p_tail->one_word.unique_word, "last" ) == 0,
		"The word stored must be \"last\" but the actual word is \"%s\"", list1.p_head->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 18 Check that the next pointer in the head node points to the tail.
	assert( list1.p_head->p_next == list1.p_tail,
		"The p_next member of the p_head node must point to the same node as p_tail when two words are in the list" )
		? passcount++ : failcount++ ;
	
	// Test 19 Check that the previous pointer in the tail node points to the head.
	assert( list1.p_tail->p_previous == list1.p_head,
		"The p_previous member of the p_tail node must point to the same node as p_head when two words are in the list" )
		? passcount++ : failcount++ ;
	
	// Test 20 now clear the linked list
	result = clear_linked_list( &list1 ) ;
	assert( result == 2,
		"List has two entries so the cleared count must be 2. Your function returned %d", result )
		? passcount++ : failcount++ ;
	
	// Test 21 now confirm that list1 now has three empty pointers
	assert( ! (list1.p_head || list1.p_tail || list1.p_current),
		"All three pointers in list1 must now be NULL" )
		? passcount++ : failcount++ ;
		
	printf( "\n========= tests for add_node_after_current =====================================\n" ) ;

	// Test 22 confirm that we can add a node to an empty list.
	result = add_node_after_current( &list1, "beginning") ;
	if ( list1.p_head == NULL )
	{
		assert( 0 ,"Implement add_node_after_current now. Exiting unit tests now.\n" ) ;		// mark assertion failure on NULL node pointer
		failcount++ ;
		return failcount ;
	}
	assert( result == 1 && strcmp( list1.p_current->one_word.unique_word, "beginning" ) == 0,
		"Added a new word to empty list using add_node_after_current. List should have \"beginning\" but has %s",
		list1.p_current->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 23 confirm that we can add a second node after the first node.
	result = add_node_after_current( &list1, "whatever") ;
	assert( result == 1 && strcmp( list1.p_current->one_word.unique_word, "whatever" ) == 0,
		"Added a second word to the list using add_node_after_current. List should have \"whatever\" but has %s",
		list1.p_current->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 24 checks that the tail pointer was updated to point to the new last node in the list.
	assert( list1.p_current == list1.p_tail,
		"The new node is at the end so the current and the tail must be the same." )
		? passcount++ : failcount++ ;

	// Test 25 checks that the new node's next pointer is NULL (since it is the end of the list)
	assert( list1.p_current->p_next == NULL,
		"The new node is at the end so its next pointer must be NULL." )
		? passcount++ : failcount++ ;

	// Test 26 move to first node and add a new word after the first node
	list1.p_current = list1.p_head ;		// now move to the first node in the list.
	result = add_node_after_current( &list1, "middle") ;
	assert( result == 1 && strcmp( list1.p_current->one_word.unique_word, "middle" ) == 0,
		"Added a new word to empty list using add_node_after_current. List should have \"middle\" but has %s",
		list1.p_current->one_word.unique_word )
		? passcount++ : failcount++ ;

	// Test 27 the head's next pointer must be the same as the current pointer.
	assert( list1.p_head->p_next == list1.p_current,
		"The head node's next must be the same as the current." )
		? passcount++ : failcount++ ;

	// Test 28 the current pointer's previous must point to the head
	assert( list1.p_current->p_previous == list1.p_head,
		"The current pointer's previous must point to the head." )
		? passcount++ : failcount++ ;

	// Test 29 the current pointer's next must point to the tail
	assert( list1.p_current->p_next == list1.p_tail,
		"The current pointer's next must point to the tail." )
		? passcount++ : failcount++ ;

	// Test 30 the tail's previous must point to the current
	assert( list1.p_tail->p_previous == list1.p_current,
		"The tail's previous must point to the current." )
		? passcount++ : failcount++ ;

	printf( "\n========= tests for find_word bad input checks =================================\n" ) ;
	
	// Test 31 test NULL linked list pointer
	result = find_word( NULL, "a" ) ;
	assert( result == -1,
		"Expected to get -1 result due to null linked list pointer but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 32 test empty linked list (head is NULL)
	struct linked_list list2 ;
	memset( &list2, 0, sizeof( list2 ) ) ;	// set everything to NULL and 0
	result = find_word( &list2, "a" ) ;
	assert( result == -1,
		"Expected to get -1 result due to an empty linked list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 33 test NULL pointer to the word to be found
	result = find_word( &list1, NULL ) ;
	assert( result == -1,
		"Expected to get -1 result due to a NULL pointer for word but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 34 test empty string for word
	result = find_word( &list1, "" ) ;
	assert( result == -1,
		"Expected to get -1 result due to word being an empty string but find_word returned %d", result )
		? passcount++ : failcount++ ;

	
	printf( "\n========= tests for find_word for words in the list ============================\n" ) ;

	// Test 35 Now search for the first word in the list which is "beginning" so expect result == 1
	result = find_word( &list1, "beginning" ) ;
	assert( result == 1,
		"Expected to find match for \"beginning\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 36 find_word must set current to point to the first node in the list because "beginning" is in that first node.
	assert( list1.p_head == list1.p_current,
		"The current pointer must be set to the first node in the list because that node has the word \"beginning\"" )
		? passcount++ : failcount++ ;
		
	// Test 37 Now search for the last word in the list which is "whatever" so expect result == 1
	result = find_word( &list1, "whatever" ) ;
	assert( result == 1,
		"Expected to find match for \"whatever\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 38 find_word must set current to point to the last node in the list because "whatever" is in last node.
	assert( list1.p_tail == list1.p_current,
		"The current pointer must be set to the last node in the list because that node has the word \"whatever\"" )
		? passcount++ : failcount++ ;
		
	// Test 39 Now search for the middle word in the list which is "middle" so expect result == 1
	result = find_word( &list1, "middle" ) ;
	assert( result == 1,
		"Expected to find match for \"middle\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 40 find_word must set current to point to the second node in the list because "middle" is in that second node.
	assert( list1.p_head->p_next == list1.p_current,
		"The current pointer must be set to the first node in the list because that node has the word \"middle\"" )
		? passcount++ : failcount++ ;
		
	printf( "\n========= tests for find_word for words not in the list ========================\n" ) ;

	// Test 41 Now search for a word that is before the first word in the list "apple" so expect result == 0 and p_current == NULL
	result = find_word( &list1, "apple" ) ;
	assert( result == 0,
		"Expected to not find a match for \"apple\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 42 find_word must set current to NULL because "apple" is in before the first word in the list.
	assert( list1.p_current == NULL,
		"The current pointer must be set to NULL in the list because \"apple\" is before the first word in the list" )
		? passcount++ : failcount++ ;
		
	// Test 43 Now search for a word that goes after "beginning" and before "middle" so expect result == 0 and p_current == p_head
	result = find_word( &list1, "cat" ) ;
	assert( result == 0,
		"Expected to not find a match for \"cat\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 44 find_word must set current to p_head because "cat" would go between "beginning" and "middle" in the list.
	assert( list1.p_current == list1.p_head,
		"The current pointer must be set to p_head in the list because \"cat\" would go right after the first word in the list" )
		? passcount++ : failcount++ ;
		
	// Test 45 Now search for a word that goes after "middle" and before "whatever" so expect result == 0 and
	//         p_current == p_head->p_next which is the second node in the list.
	result = find_word( &list1, "student" ) ;
	assert( result == 0,
		"Expected to not find a match for \"student\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 46 find_word must set current to p_head->p_next because "student" would go between "middle" and "whatever" in the list.
	assert( list1.p_current == list1.p_head->p_next,
		"The current pointer must be set to p_head->p_next in the list because \"student\" would go right after the second word in the list" )
		? passcount++ : failcount++ ;
		
	// Test 47 Now search for a word that goes after "whatever" so expect result == 0 and p_current == p_tail which is the last node in the list.
	result = find_word( &list1, "zebra" ) ;
	assert( result == 0,
		"Expected to not find a match for \"zebra\" in the list but find_word returned %d", result )
		? passcount++ : failcount++ ;

	// Test 48 find_word must set current to p_tail because "zebra" would go after "whatever" in the list.
	assert( list1.p_current == list1.p_tail,
		"The current pointer must be set to p_tail in the list because \"zebra\" would go after the last word in the list" )
		? passcount++ : failcount++ ;
		

	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}

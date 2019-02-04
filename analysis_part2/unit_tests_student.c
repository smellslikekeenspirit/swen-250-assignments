// unit_tests student additions
// Larry L. Kiser Oct. 22, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "analysis.h"
#include "unit_tests_analysis.h"
#include "unit_tests.h"

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// do the unit tests
// returns the number of failed tests.
int test_student()
{
	int passcount = 0 ;
	int failcount = 0 ;
	struct linked_list list1 ;		// list list pointers for one list
	
	// Initialize local stack data
	memset( &list1, 0, sizeof( list1 ) ) ;		// set all pointers to NULL (zero)
	
	printf( "\n========= student generated tests on MLK excerpt ===============================\n" ) ;
	int result = read_file( &list1, "MLK_dream_excerpt.txt" ) ;
	assert( result == 113,
		"1 read_file processing MLK_dream_excerpt. Expect word count of 113 returned but got %d.", result )
		? passcount++ : failcount++ ;

	// Add a test to verify that the word "day" is used three times in the list.
	struct word_entry word = get_first_word(&list1);
        while (strcmp(word.unique_word, "day") != 0)
            word = get_next_word(&list1);
        result = word.word_count;
        assert( result == 3, "my test 1: day is used 3 times in the list excluding the addition, but got %d", result )
                ? passcount++ : failcount++ ;
        
	// Add a test to verify that the word AFTER the word "have" is the word "heat".
        find_word(&list1, "have");
        word = get_next_word(&list1);
        assert( strcmp(word.unique_word,"heat") == 0,
                "word AFTER the word have is the word heat, but got %s", word.unique_word )
                ? passcount++ : failcount++ ;

	// Add a test to verify that the last word in the list is "with"
	word = get_last_word(&list1);
        assert( strcmp(word.unique_word,"with") == 0,
                "last word in the list is with, but got %s", word.unique_word )
                ? passcount++ : failcount++ ;
        
	// Add a test to verify that the next to the last word is "will"	
        word = get_prev_word(&list1);
        assert( strcmp(word.unique_word,"will") == 0,
                "word next to last word in the list is will, but got %s", word.unique_word )
                ? passcount++ : failcount++ ;
        result = clear_linked_list( &list1 ) ;
	assert( result == 62,
		"6 clear linked list expected to remove 62 entries but got %d.", result )
		? passcount++ : failcount++ ;

	printf( "\nSummary of analysis unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}


#include "include/criterion/internal/new_asserts.h"
#include "universal.h"
#include "include/criterion/criterion.h"
#include "include/criterion/parameterized.h"
#include "include/criterion/new/assert.h"
#include <stdio.h>
#include <string.h>

t_history lst;

Test(entry, add, .description="Test of entry_add")
{
	lst = NULL;
	

}
Test(history, clean, .description="Test of history_clean")
{
	lst = NULL;
	history_clean(NULL);
	history_clean(&lst);
	lst = malloc(sizeof(*lst));
	cr_assert(lst, "lst1 malloc error");
	lst->content = malloc(sizeof(char) * 11);
	cr_assert(lst->content, "lst1.content malloc error");
	lst->next = malloc(sizeof(*lst));
	cr_assert(lst->next, "lst2 malloc error");
	lst->next->content = malloc(sizeof(char) * 11);
	cr_assert(lst->content, "lst2.content malloc error");
	lst->next->next = NULL;
	history_clean(&lst);
	cr_expect(lst == NULL);
}

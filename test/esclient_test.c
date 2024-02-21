#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <string.h>

#include "../src/esclient.h" 


void assert_string(const char *string, const char *criterion) {
    cr_assert(strstr(string, criterion) != NULL,
              "Assertion failed: '%s' not found in '%s'", criterion, string);
}


Test(esclient, init) {
	esclient_init("a_base_url");

	assert_string(base_url(), "a_base_url");
}

#include <criterion/criterion.h>
#include "../src/elasticc.h"

Test(elasticc, initialize_library) {
	int result = elasticc_init();

	cr_assert(result == 0, "initialization failure");
}

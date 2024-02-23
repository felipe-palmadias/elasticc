#include <criterion/criterion.h>
#include "../src/elasticc.h"
#include "../src/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assert_that_the_cluster_data_file_was_created() {
	char *home = getenv("HOME");
	char *file_path = xmalloc(sizeof(home) + sizeof("/.elasticc/cluster.dat") + 1);
	strcpy(file_path, home);
	strcat(file_path, "/.elasticc/cluster.dat");
	FILE *fp = fopen(file_path, "r");
	cr_assert(fp != NULL, "Cluster data file not found");

	// finally
	fclose(fp);
	free(file_path);
}

Test(elasticc, initialize_library) {
	int result = elasticc_init();

	cr_assert(result == 0, "initialization failure");
	assert_that_the_cluster_data_file_was_created();
}




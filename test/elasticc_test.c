#include <criterion/criterion.h>
#include "../src/elasticc.h"
#include "../src/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// fixture
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

// fixture
cluster_t *a_simple_cluster(char *name, char *uri) {
	cluster_t *cluster = (struct cluster_t*)xmalloc(sizeof(struct cluster_t));
	cluster->name = name;
	cluster->uri = uri;
	return cluster;
}

Test(elasticc, initialize_library) {
	int result = elasticc_init();

	cr_assert(result == 0, "initialization failure");
	assert_that_the_cluster_data_file_was_created();
}


Test(elasticc, returns_npe__when_cluster_is_null) {
	cluster_t *c = NULL;

	int result = elasticc_add_cluster(c);

	cr_assert(result == -1);
}

Test(elasticc, returns_error_when_name_is_bigger) {
	cluster_t *c = a_simple_cluster("abcdefghijklmnopqrstuvxyz_abcdefghijklmnopqrstuvxyz", "http://test.com");

	int result = elasticc_add_cluster(c);

	cr_assert(result == -3);

	// finally
	free(c);
}

Test(elasticc, returns_error_when_name_has_non_alphanumeric_char) {
	cluster_t *c = a_simple_cluster("invalid char", "http://test.com");

	int result = elasticc_add_cluster(c);

	cr_assert(result == -3);

	// finally
	free(c);
}

Test(elasticc, returns_error_when_name_is_empty) {
	cluster_t *c = a_simple_cluster("", "http://test.com");

	int result = elasticc_add_cluster(c);

	cr_assert(result == -3);

	// finally
	free(c);
}

Test(elasticc, returns_error_when_uri_is_invalid) {
	cluster_t *c = a_simple_cluster("valid_name", "ht://invalid_uri");

	int result = elasticc_add_cluster(c);
	
	cr_assert(result == -4);

	// finally
	free(c);
}

Test(elasticc, adds_new_cluster) {
	cluster_t *c = a_simple_cluster("valid_name", "http://test.com:8080");

	int result = elasticc_add_cluster(c);
	
	cr_assert(result == 0);

	// finally
	free(c);
}

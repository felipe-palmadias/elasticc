#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../src/cluster.h"
#include "../src/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fixture
cluster_t *a_simple_cluster(char *name, char *uri) {
	cluster_t *cluster = (struct cluster_t*)xmalloc(sizeof(struct cluster_t));
	cluster->name = name;
	cluster->uri = uri;
	return cluster;
}



Test(cluster, test_insert_cluster) {
	cluster_t *cluster = a_simple_cluster("cluster1", "http://test.com");

	int result = cluster_insert(cluster);

	cr_assert(result == 0);
}


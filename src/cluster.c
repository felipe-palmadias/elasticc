#include "cluster.h"


/*
 * Function: cluster_insert
 * ------------------------
 * This function inserts a cluster to database (file $HOME/.elasticc/cluster.dat), 
 * which is structured as a key-value properties file.
 *
 * Return:
 * 	- returns 0 if the cluster was successfully inserted into the database.
 * 	- returns -1 if failure
 */
int cluster_insert(cluster_t *cluster) {
	return 0;
}


/*
 * Function: cluster_exists_by_name
 * ---------------------------------
 * Checks if a cluster with the given name exists in the database located at file $HOME/.elasticc/cluster.dat,
 * which is structured as a key-value properties file.
 *
 * Parameters:
 * 	- name: The name of the cluster to check for existence.
 *
 * Returns:
 * 	- 1 if a cluster with the given name exists in the database.
 * 	- 0 otherwise.
 */
int cluster_exists_by_name(char *name) {
	return 1;
}

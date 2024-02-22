#ifndef __ELASTICC_H__
#define __ELASTICC_H__

typedef struct {
	char* name;
	char* uri;
} Cluster;


/*
 * Function: elasticc_add_cluster
 * ------------------------------
 * Add new cluster to the list of clusters
 *
 * Parameters:
 * 	- cluster: A pointer to the Cluster struct representing de cluster to be added.
 *
 * Return:
 * 	- returns 0 if the cluster was successfully created.
 *  	- returns 1 if the cluster name already exists
 *  	- returns 2 if the cluster name is invalid.
 *  	- returns 3 if the cluster uri is invalid. 
 *
 */
int elasticc_add_cluster(Cluster* cluster);


/*
 * Function: elasticc_user_cluster
 * -------------------------------
 * Sets the active cluster to be used for subsequent operations.
 *
 * Parameters: 
 * 	- cluster_name: A pointer to string containing the name of the cluster.
 *
 * Return:
 * 	- returns 0 if the cluster with de provided name is successfully set as active.
 * 	- returns 1 if the cluster name provided does not exists.
 *
 */
int elasticc_use_cluster(char* cluster_name);

#endif

#include <stdlib.h>
#include "elasticc.h"
#include "util.h"
#include "cluster.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <regex.h>

// Error codes
#define __ERR_ON_CREATE_FOLDER -1
#define __ERR_NPE -1

// Constants
#define __RESOURCE_FOLDER "/.elasticc"
#define __FOLDER_EXIST 1
#define __FOLDER_CREATED 0


/*
 * Function: _try_create_folder
 * ----------------------------
 * Tries to create a folder at the specified path.
 *
 * Return:
 * 	- returns 0 if folder was created
 * 	- returns 1 if folder exists
 * 	- returns -1 if failure
 */
int _try_create_folder(char *folder_path) {
	int result = 0;
	if (mkdir(folder_path, 0700) == -1) {
		if (errno == EEXIST) { 
			result = __FOLDER_EXIST;
		} else {
			result = __ERR_ON_CREATE_FOLDER;
		}
	} else {
		result = __FOLDER_CREATED;
	}
	return result;
}

/*
 * Function: _create_resource_folder
 * ---------------------------------
 * Creates a resources directory .elasticc in $HOME folder.
 *
 * Return:
 * 	- returns 0 if folder was created
 * 	- returns 1 if folder exists
 * 	- returns -1 if failure.
 */
int _create_resource_folder() {
	int result = 0;

	// get home folder path
	char *home_folder = getenv("HOME");
	if (home_folder == NULL)
		return __ERR_ON_CREATE_FOLDER;

	// create home folder path
	char *folder_path = xmalloc(strlen(home_folder) + strlen(__RESOURCE_FOLDER) + 1);
	strcpy(folder_path, home_folder);
	strcat(folder_path, __RESOURCE_FOLDER);

	result = _try_create_folder(folder_path);

	free(folder_path);

	return result;
}

/*
 * Function: elasticc_init
 * -----------------------
 * Initializes the elasticc library.
 * This function sets up any required resources and environment for using other functions in the library.
 * It creates a data directory named ".elasticc" in the user's home directory if it doesn't already exist.
 *
 * Return:
 * 	- returns 0 indicating the initialization success.
 * 	- returns non-zero value indicate failure.
 */
int elasticc_init() {
	if (_create_resource_folder() == __ERR_ON_CREATE_FOLDER) {
		return __ERR_ON_CREATE_FOLDER;
	}

	return 0;
}

/*
 * Function: elasticc_add_cluster
 * ------------------------------
 * Add new cluster to the list of clusters
 *
 * Parameters:
 * 	- cluster: A pointer to the cluster_t struct representing de cluster to be added.
 *
 * Return:
 * 	- returns 0 if the cluster was successfully created
 * 	- returns -1 if cluster variable is NULL
 */
int elasticc_add_cluster(struct cluster_t *cluster) {
	if (cluster == NULL) {
		return __ERR_NPE;
	}

	return cluster_insert(cluster);
}


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
int elasticc_use_cluster(char* cluster_name) {
	return 0;
}



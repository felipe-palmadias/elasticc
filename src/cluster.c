#include "cluster.h"
#include "util.h"
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

// Error codes
#define __ERR_ON_CREATE_DATA_FILE -1
#define __ERR_NPE -1
#define __ERR_INVALID_CLUSTER_NAME -3
#define __ERR_INVALID_CLUSTER_URI -4

// Constants
#define __CLUSTER_DATA_FILE "/cluster.dat"
#define __FILE_CREATED 0
#define __RESOURCE_FOLDER "/.elasticc"

/*
 * Function: _try_create_cluster_data_file
 * ---------------------------------------
 * Tries to create a cluster data file at the specified file path.
 *
 * Return:
 * 	- returns 0 if file was created or exists
 * 	- returns -1 if failure
 *
 */
int _try_create_cluster_data_file(char *file_path) {
	FILE *fp;
	fp = fopen(file_path, "w");
	if (fp) {
		fclose(fp);
		return __FILE_CREATED;
	}
	return __ERR_ON_CREATE_DATA_FILE;
}

/*
 * Function: _create_cluster_data_file
 * ------------------------------------
 * Creates a cluster data file on $HOME/.elasticc/cluster.dat
 *
 * Return:
 * 	- returns 0 if create successfully
 * 	- returns 1 if file exists
 * 	- returns -1 if failure
 */
int _create_cluster_data_file() {
	char *home_folder = getenv("HOME");
	if (home_folder == NULL) return __ERR_ON_CREATE_DATA_FILE;

	// File path is $HOME/.elasticc/cluster.data
	char *cluster_file_path = xmalloc(strlen(home_folder) + strlen(__RESOURCE_FOLDER) + strlen(__CLUSTER_DATA_FILE) + 1);
	strcpy(cluster_file_path, home_folder);
	strcat(cluster_file_path, __RESOURCE_FOLDER);
	strcat(cluster_file_path, __CLUSTER_DATA_FILE);

	int result = _try_create_cluster_data_file(cluster_file_path);

	free(cluster_file_path);

	return result;
}

/*
 * Function: _is_regex_match
 * -------------------------
 * Checks if a given string matches a regular expression pattern.
 *
 * Return:
 * 	- returns 1 if the string matches the pattern, 0 otherwise.
 */
int _is_regex_match(char *pattern, char* str) {
	regex_t regex;
	regcomp(&regex, pattern, REG_EXTENDED);

	int result = regexec(&regex, str, 0, NULL, 0);
	regfree(&regex);

	return !result;
}

/*
 * Function: _is_valid_cluster_name
 * --------------------------------
 * Checks if the provided string is a valid cluster name.
 * A valid cluster name contains only alphanumeric characters, hyphens, and underscores,
 * and must be between 1 and 32 characters long.
 *
 * Return:
 * 	- returns 1 if cluster name is valid
 * 	- returns 0 if cluster name is invalid
 */
int _is_valid_cluster_name(char *name) {
	char *pattern = "^[a-zA-Z0-9_-]{1,32}$";
	return _is_regex_match(pattern, name);
}

/*
 * Function: _is_valid_cluster_uri
 * --------------------------------
 * Checks if the provided string is a valid cluster uri.
 * A valid cluster uri contains a valid elastic search uri access point.
 *
 * Return:
 * 	- returns 1 if cluster uri is valid
 * 	- returns 0 if cluster uri is invalid
 */
int _is_valid_cluster_uri(char *uri) {
	char *pattern = "^(https?://)?[a-zA-Z0-9\\-\\.]+(:[0-9]+)?(/[a-zA-Z0-9\\-\\._\\?\\,\\'\\/\\\\\\+&amp;%\\$#\\=~]*)?$";
	return _is_regex_match(pattern, uri);
}

/*
 * Function: cluster_insert
 * ------------------------
 * This function inserts a cluster to database (file $HOME/.elasticc/cluster.dat), 
 * which is structured as a key-value properties file.
 *
 * Return:
 * 	- returns 0 if the cluster was successfully inserted into the database
 * 	- returns -1 if cluster variable is NULL
 *  	- returns -2 if the cluster name already exists
 *  	- returns -3 if the cluster name is invalid
 *  	- returns -4 if the cluster uri is invalid
 */
int cluster_insert(cluster_t *cluster) {

	if (cluster == NULL) {
		return __ERR_NPE;
	}

	if (!_is_valid_cluster_name(cluster->name)) {
		return __ERR_INVALID_CLUSTER_NAME;
	}

	if (!_is_valid_cluster_uri(cluster->uri)) {
		return __ERR_INVALID_CLUSTER_URI;
	}

	return 0;
}


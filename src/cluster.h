#ifndef __CLUSTER_H__
#define __CLUSTER_H__

typedef struct cluster_t {
	char *name;
	char *uri;
} cluster_t;


int cluster_insert(cluster_t *cluster);

#endif

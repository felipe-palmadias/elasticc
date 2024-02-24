#ifndef __ELASTICC_H__
#define __ELASTICC_H__

typedef struct cluster_t {
	char *name;
	char *uri;
} cluster_t;

int elasticc_init();
int elasticc_add_cluster(struct cluster_t *cluster); 

#endif

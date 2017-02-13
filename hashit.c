// Jordana Approvato, Jennifer Cafiero, and Catherine Javadian
// We pledge our honor that we have abided by the Stevens Honor System

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 101

typedef struct {
    char* keys[TABLE_SIZE];
    int num_keys;
} hash_set;

char * EMPTY = "empty";

void clear_table(hash_set *set) {
	int count = 0;
	while (count < TABLE_SIZE) {
		if (set->keys[count] != NULL) {
			//free(set->keys[count]);
			set->keys[count] = NULL;
		}
		count++;
	}
	return;
}

int hash(char *key) {
	int sum = 0;
	int check = 0;
	int i = 1;
	while(key[check]) {
		sum += (key[check])*(i);
		check++;
		i++;
	}
	sum *= 19;
	return (sum % TABLE_SIZE);
}

int in_hash(hash_set *set, char *key) {
	int hashk = hash(key);
	int k = 0;
	int i = 0;
	while (i < 20) {
		k = (hashk + (i*i) + (i*23))%TABLE_SIZE;
		if (set->keys[k] == NULL) {
			return 0;
		}
		if (strcmp(key, set->keys[k]) == 0) {
			return -1;
		}
		i++;
	}
	return 0;
}

int insert_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int k = hashk;
	int count = 0;
	if (in_hash(set, key) == 0) {
		while (count <= 20) {
			if (set->keys[k] == EMPTY || set->keys[k] == NULL) {
				set->keys[k] = key;
				return 0;
			}
			if (strcmp(key, set->keys[k]) == 0) {
				return -1;
			}
			k = (hashk + (count*count) + (count*23))%TABLE_SIZE;
			count++;
		}
	}
	return -1;
}

int delete_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int k = hashk;
	int count = 0;
	while (count <= 20) {
		if (set->keys[k] == NULL) {
			return -1;
		}
		if (set->keys[k] != EMPTY) {
			if (strcmp(key, set->keys[k]) == 0) {
				free(set->keys[k]);
				set->keys[k] = EMPTY;
				return 0;
			}
		}
		k = (hashk + (count*count) + (count*23))%TABLE_SIZE;
		count++;
	}
	return -1;
}

void display_keys(hash_set *set) {
	int i = 0;
	while (i < TABLE_SIZE) {
		if (set->keys[i] != NULL && set->keys[i] != EMPTY) {
			printf("%i:",i);
			printf("%s\n",set->keys[i]);
		}
		i++;
	}
	return;
}

int main() {
	int lines;
	int ops;
	hash_set * hash = (hash_set *)malloc(sizeof(hash_set));
	int count = 0;
	while (count < TABLE_SIZE) {
		hash->keys[count] = NULL;
		count++;
	}
	char * input = (char *)malloc(sizeof(char)*19);
	char * key;
	scanf("%d", &lines);
	while (lines > 0) {
		scanf("%d", &ops);
		while (ops > 0) {
			scanf("%s", input);
			key = (char *)malloc(sizeof(char)*15);
			char check = input[0];
			strncpy(key, input+4, 15);
			if (check == 'A') {
				if (insert_key(hash, key) == 0) {
					hash->num_keys++;
				}
			} else {
				if (delete_key(hash, key) != -1) {
					hash->num_keys--;
				}
			}
			ops--;
		}
		printf("%i\n", hash->num_keys);
		display_keys(hash);
		clear_table(hash);
		free(key);
		hash->num_keys = 0;
		lines--;
	}
	free(hash);
	free(input);
	return 0;
}




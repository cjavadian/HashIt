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

void clear_table(hash_set *set) {
	for (int i = 0; i < 101; i++) {
		if (&set[i] != NULL || &set[i] == 'empty') {
			&set[i] = NULL;
		}
	}
	return;
}

int hash(char *key) {
	int ch = 0;
	int hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		ch += toascii(key[i])*(i+1);
	}
	ch *= 19;
	hash = (ch % 101);
	return hash;
}

int insert_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int count = 1;
	while (set[hash] != NULL || set[hash] != 'empty') {
		hashk += (count*count) + (count*23);
		count++;
		if (count == 19) {
			return -1;
		}
	}
	set[hashk] = key;
	return 0;
}

int delete_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int count = 1;
	while (set[hash] != key) {
		hashk += (count*count) + (count*23);
		count++;
		if (count == 19) {
			return -1;
		}
	}
	set[hashk] = 'empty';
	return 0;
}

void display_keys(hash_set *set) {
	for (int i = 0; i < 101; i++) {
		if (set[i] != NULL || set[i] != 'empty') {
			printf("%i:",i);
			printf("%i\n",set[i]);
		}
	}
	return;
}

void main() {
	int lines;
	int ops;
	int keys;
	hash_set *hash;
	scanf("%d", &lines);
	while (lines > 0) {
		scanf("%d", &ops);
		while (ops > 0) {
			char * input = (char *)malloc(sizeof(char)*19);
			scanf("%s", input);
			char *key;
			char check = input[0];
			strncpy(key, input+4, 15);
			if (check == 'A') {
				insert_key(hash, key);
				keys++;
			} else {
				delete_key(hash, key);
				keys--;
			}
			ops--;
		}
		display_keys(hash);
		clear_table(hash);
		lines--;
	}
}




#include "propel_matr.h"
#include <stdlib.h>
#include <assert.h>

struct pc_matr *pc_matr_init(int rows, int cols)
{
	struct pc_matr *ret = malloc(sizeof(struct pc_matr));
	if (!ret)
		return NULL;

	ret->rows = rows;
	ret->cols = cols;

	ret->data = malloc(sizeof(struct pc_val**)*rows);
	if (!ret->data) return NULL;
	for (int i = 0; i < rows; i++) {
		ret->data[i] = malloc(sizeof(struct pc_val*)*cols);
		if (!ret->data[i]) return NULL;
	}

	return ret;
}

struct pc_matr *pc_matr_mul(struct pc_matr *A, struct pc_matr *B)
{
	assert(A->cols == B->rows);
	struct pc_matr *ret = pc_matr_init(A->rows, B->cols);
	if (!ret)
		return NULL;
	
	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < B->cols; j++) {
			ret->data[i][j] = pc_val_init(0);
			/* todo */
		}
	}
}

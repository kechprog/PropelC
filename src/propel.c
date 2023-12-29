#include "propel.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

static const char *pc_op_name(enum pc_op op) {
	switch (op) {
		case PC_OP_SUM:
			return "SUM";
		case PC_OP_MUL:
			return "MUL";
		case PC_OP_POW:
			return "POW";
		case PC_OP_RELU:
			return "RELU";
		case PC_OP_NONE:
			return "NONE";
	};
}

struct pc_val* pc_val_init(PC_FLOAT val)
{
	struct pc_val *ret = malloc(sizeof(struct pc_val));
	if (!ret)
		return NULL;

	ret->val = val;
	ret->op = PC_OP_NONE;
	ret->children = NULL;

	return ret;
}

/* frees everything except pc_val_init values */
void pc_valal_free(struct pc_val *x)
{
	if (x->op != PC_OP_NONE)
		return;
	
	pc_valal_free(x->children[0]);
	if (x->op & (PC_OP_SUM | PC_OP_MUL | PC_OP_POW)) {
		pc_valal_free(x->children[1]);
		free(x->children);
	}
}

/*-----------------------------------------------------------------*/
/*                           OPERATIONS                            */
/*-----------------------------------------------------------------*/
struct pc_val* pc_val_sum(struct pc_val *a, struct pc_val *b)
{
	assert(a != b);
	struct pc_val *ret = malloc(sizeof(struct pc_val));
	if (!ret)
		return NULL;

	ret->val = a->val + b->val;
	ret->op = PC_OP_SUM;
	ret->children = malloc(2*sizeof(struct pc_val*));
	if (!ret->children)
		return NULL;
	ret->children[0] = a;
	ret->children[1] = b;

	return ret;
}

struct pc_val* pc_val_mul(struct pc_val *a, struct pc_val *b)
{
	assert(a != b);
	struct pc_val *ret = malloc(sizeof(struct pc_val));
	if (!ret)
		return NULL;

	ret->val = a->val * b->val;
	ret->op = PC_OP_MUL;
	ret->children = malloc(2*sizeof(struct pc_val*));
	if (!ret->children)
		return NULL;
	ret->children[0] = a;
	ret->children[1] = b;

	return ret;
}

struct pc_val* pc_val_pow(struct pc_val *a, struct pc_val *b)
{
	assert(a != b);
	struct pc_val *ret = malloc(sizeof(struct pc_val));
	if (!ret)
		return NULL;

	ret->val = PC_POW_FUNC(a->val, b->val);
	ret->op = PC_OP_POW;
	ret->children = malloc(2*sizeof(struct pc_val*));
	if (!ret->children)
		return NULL;
	ret->children[0] = a;
	ret->children[1] = b;

	return ret;
}

struct pc_val* pc_val_relu(struct pc_val *x)
{
	struct pc_val *ret = malloc(sizeof(struct pc_val));
	if (!ret)
		return NULL;

	ret->val = (x->val>0) * x->val;
	ret->op = PC_OP_RELU;
	ret->children = &x;

	return ret;
}

/* backward */
static void _backward(struct pc_val *x)
{
	struct pc_val *a, *b;

	switch (x->op) {
		case PC_OP_NONE:
			return;

        case PC_OP_SUM:
			a = x->children[0];
			b = x->children[1];
			b->grad = a->grad = x->grad * 1.0;
			_backward(a);
			_backward(b);
		break;

        case PC_OP_MUL:
			a = x->children[0];
			b = x->children[1];
			a->grad = x->grad * b->val;
			b->grad = x->grad * a->val;
			_backward(a);
			_backward(b);
		break;

        case PC_OP_POW:
			/* y = a^b */
			a = x->children[0];
			b = x->children[1];
			/* dy/da = b*a^(b-1)*/
			a->grad = x->grad * b->val * PC_POW_FUNC(a->val, b->val-1.);
			/* dy/db = lna * a^b */
			b->grad = x->grad * x->val * log(a->val);
			_backward(a);
			_backward(b);
		break;

        case PC_OP_RELU:
			printf("Not implemented!\n");
		break;
	}
}

void pc_val_backward(struct pc_val *x)
{
	x->grad = 1.0;
	_backward(x);
}

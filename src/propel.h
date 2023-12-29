#pragma once

#define PC_FLOAT double
#define PC_POW_FUNC pow
#define PC_LOG_FUNC log

enum pc_op {
	PC_OP_SUM  = 1,
	PC_OP_MUL  = 1 << 1,
	PC_OP_POW  = 1 << 2,
	PC_OP_RELU = 1 << 3,
	PC_OP_NONE = 4 << 4,
};

struct pc_val {
	PC_FLOAT val;	
	PC_FLOAT grad; /* only valid after pc_backward(x) */

	enum pc_op op;
	struct pc_val **children;
};

struct pc_val* pc_val_init(PC_FLOAT val);

void pc_val_free(struct pc_val *x);

struct pc_val* pc_val_sum(struct pc_val *a, struct pc_val *b);

struct pc_val* pc_val_mul(struct pc_val *a, struct pc_val *b);

struct pc_val* pc_val_pow(struct pc_val *a, struct pc_val *b); /* a^b */

struct pc_val* pc_val_relu(struct pc_val *x);

/* TODO: */
struct pc_val* pc_val_sin(struct pc_val *x);
struct pc_val* pc_val_cos(struct pc_val *x);
struct pc_val* pc_value_log(struct pc_val *a, struct pc_val *b);

void pc_val_backward(struct pc_val *x);

#include <stdio.h>
#include "propel.h"

int main(void) 
{
	struct pc_val *a = pc_val_init(10),
			      *b = pc_val_init(14),
			      *c = pc_val_init(2),
			      *a_plus_b = pc_val_sum(a,b),
			      *y = pc_val_pow(a_plus_b, c);
	
	pc_val_backward(y);
	printf("dy/da = %f\n", a->grad);

	return 0;
}

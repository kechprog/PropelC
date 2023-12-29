#include "propel.h"

/*     COLOUMNS
 *  _____________
 * |_|_|_|_|_|_|_|
 * |_|_|_|_|_|_|_| R
 * |_|_|_|_|_|_|_| O
 * |_|_|_|_|_|_|_| W
 * |_|_|_|_|_|_|_| S
 * |_|_|_|_|_|_|_|
 *
 */
struct pc_matr {
	int rows, cols;
	struct pc_val ***data; /* W x H */
};

struct pc_matr *pc_matr_init(int rows, int cols);

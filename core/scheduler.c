#include <core/eos.h>

/* mapping table */
int8u_t const _os_map_table[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
int8u_t const _os_unmap_table[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

void _os_init_scheduler() {
	PRINT("initializing scheduler module.\n");
	
	/* initialize ready_group */
	_os_ready_group = 0;

	/* initialize ready_table */
	int8u_t i;
	for (i=0; i<READY_TABLE_SIZE; i++) {
		_os_ready_table[i] = 0;
	}
}

int32u_t _os_get_highest_priority() {
	int8u_t y = _os_unmap_table[_os_ready_group];
	return (int32u_t)((y << 3) + _os_unmap_table[_os_ready_table[y]]);
}

void _os_set_ready(int8u_t priority) {
	/* set corresponding bit of ready_group to 1 */
	_os_ready_group |= _os_map_table[priority >> 3];

	/* set corresponding bit of ready_table to 1 */
	_os_ready_table[priority >> 3] |= _os_map_table[priority & 0x07];
}

void _os_unset_ready(int8u_t priority) {
	/* set corresponding bit of ready_table to 0 */
	if ((_os_ready_table[priority >> 3] &= ~_os_map_table[priority & 0x07]) == 0) {
		/* if no ready task exists in the priority group, set corresponding bit of ready_group to 0 */
		_os_ready_group &= ~_os_map_table[priority >> 3];
	}
}

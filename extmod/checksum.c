// Include required definitions first.
#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"

STATIC mp_obj_t checksum_sum(mp_obj_t data) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data, &bufinfo, MP_BUFFER_READ);
    uint32_t csum = 0;
    uint16_t tmp;
    uint8_t *buf = bufinfo.buf;
    uint16_t len = bufinfo.len;
	while(len)
	{
		if(len == 1)
		{
			tmp = (*buf)<<8;
			len--;
		}
		else
		{
			tmp = *buf++;
			tmp <<= 8;
			tmp |= *buf++;
			len -=2;
		}
		csum += tmp;
	}
	while(csum & 0xFFFF0000)
	{
		csum  = (csum >> 16) + (csum & 0xFFFF);
	}
	csum = (0xFFFF - csum) & 0xFFFF;
    return MP_OBJ_NEW_SMALL_INT(csum);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(checksum_sum_obj, checksum_sum);

STATIC const mp_rom_map_elem_t checksum_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_checksum) },
    { MP_ROM_QSTR(MP_QSTR_sum), MP_ROM_PTR(&checksum_sum_obj) },
};
STATIC MP_DEFINE_CONST_DICT(checksum_module_globals, checksum_module_globals_table);

// Define module object.
const mp_obj_module_t checksum_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&checksum_module_globals,
};

// Register the module to make it available in Python
MP_REGISTER_MODULE(MP_QSTR_checksum, checksum_user_cmodule, MODULE_CHECKSUM_ENABLED);


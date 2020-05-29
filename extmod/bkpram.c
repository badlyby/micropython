#include "py/runtime.h"
#include "py/mphal.h"
typedef struct _bkpram_mem_obj_t {
    mp_obj_base_t base;
    unsigned elem_size; // in bytes
} bkpram_mem_obj_t;

const mp_obj_type_t bkpram_mem_type;

const bkpram_mem_obj_t bkpram_mem8_obj = {{&bkpram_mem_type}, 1};
const bkpram_mem_obj_t bkpram_mem16_obj = {{&bkpram_mem_type}, 2};
const bkpram_mem_obj_t bkpram_mem32_obj = {{&bkpram_mem_type}, 4};

STATIC uintptr_t bkpram_mem_get_addr(mp_obj_t addr_o, uint align) {
    uintptr_t addr = mp_obj_int_get_truncated(addr_o);
    if ((addr & (align - 1)) != 0) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("address %08x is not aligned to %d bytes"), addr, align));
    }
    return addr;
}

STATIC void bkpram_mem_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind;
    bkpram_mem_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "<%u-bit memory>", 8 * self->elem_size);
}

STATIC mp_obj_t bkpram_mem_subscr(mp_obj_t self_in, mp_obj_t index, mp_obj_t value) {
    // TODO support slice index to read/write multiple values at once
    bkpram_mem_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (value == MP_OBJ_NULL) {
        // delete
        return MP_OBJ_NULL; // op not supported
    } else if (value == MP_OBJ_SENTINEL) {
        // load
        uintptr_t addr = bkpram_mem_get_addr(index, self->elem_size);
        uint32_t val;
        switch (self->elem_size) {
            case 1: val = (*(uint8_t*)(addr+BKPSRAM_BASE)); break;
            case 2: val = (*(uint16_t*)(addr+BKPSRAM_BASE)); break;
            default: val = (*(uint32_t*)(addr+BKPSRAM_BASE)); break;
        }
        return mp_obj_new_int(val);
    } else {
        // store
        uintptr_t addr = bkpram_mem_get_addr(index, self->elem_size);
        uint32_t val = mp_obj_get_int_truncated(value);
        switch (self->elem_size) {
            case 1: (*(uint8_t*)(addr+BKPSRAM_BASE)) = val; break;
            case 2: (*(uint16_t*)(addr+BKPSRAM_BASE)) = val; break;
            default: (*(uint32_t*)(addr+BKPSRAM_BASE)) = val; break;
        }
        return mp_const_none;
    }
}

STATIC mp_obj_t bkpram_init(void) {
    __HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	HAL_PWREx_EnableBkUpReg();
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_0(bkpram_init_obj, bkpram_init);

const mp_obj_type_t bkpram_mem_type = {
    { &mp_type_type },
    .name = MP_QSTR_mem,
    .print = bkpram_mem_print,
    .subscr = bkpram_mem_subscr,
};

STATIC const mp_rom_map_elem_t bkpram_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),            MP_ROM_QSTR(MP_QSTR_bkpram) },
    { MP_ROM_QSTR(MP_QSTR_init),                MP_ROM_PTR(&bkpram_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem8),                MP_ROM_PTR(&bkpram_mem8_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem16),               MP_ROM_PTR(&bkpram_mem16_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem32),               MP_ROM_PTR(&bkpram_mem32_obj) },

};

STATIC MP_DEFINE_CONST_DICT(bkpram_module_globals, bkpram_module_globals_table);

const mp_obj_module_t bkpram_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&bkpram_module_globals,
};

// Register the module to make it available in Python
MP_REGISTER_MODULE(MP_QSTR_bkpram, bkpram_module, MODULE_BKPRAM_ENABLED);


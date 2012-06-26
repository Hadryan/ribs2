#ifndef _DS__H_
#define _DS__H_

#include "ribs_defs.h"
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "template.h"
#include "logger.h"

/* public interface */
#define DS_FIELD_INITIALIZER { NULL, 0 }
#define DS_FIELD(T) struct TEMPLATE(ds_field,T)
#define DS_FIELD_INIT(T,x,f) TEMPLATE_FUNC(ds_field,T,init)((x),f)
#define DS_FIELD_BEGIN(x) ((x)->mem)
#define DS_FIELD_END(x) (DS_FIELD_BEGIN(x) + (x)->num_elements)
#define DS_FIELD_GET_VAL(x,i) (*(DS_FIELD_BEGIN(x) + i))

/*
 * example:
 *   DS_FIELD(uint32_t) ds_my_field = DS_FIELD_INITIALIZER;
 *   DS_FIELD_INIT(uint32_t, &ds_my_field, "my_field.ds");
 *   printf("my_field = %u\n", DS_FIELD_GET_VAL(&ds_my_field, record));
 *
 * using begin and end:
 *   uint32_t *my_field = DS_FIELD_BEGIN(&ds_my_field);
 *   uint32_t *my_field1_end = DS_FIELD_END(&ds_my_field);
 */

/* internal stuff */
#ifdef T
#undef T
#endif

enum
{
    ds_type_int8_t,
    ds_type_uint8_t,
    ds_type_int16_t,
    ds_type_uint16_t,
    ds_type_int32_t,
    ds_type_uint32_t,
    ds_type_int64_t,
    ds_type_uint64_t,
    ds_type_float,
    ds_type_double,
};

#define _DS_TYPE(x) ds_type_ ## x
#define DS_TYPE(x) _DS_TYPE(x)
#define _DS_TYPE_TO_STR(x) case ds_type_ ## x: return STRINGIFY(DS_TYPE(x))

static inline const char *ds_type_to_string(int64_t t) {
    switch(t) {
        _DS_TYPE_TO_STR(int8_t);
        _DS_TYPE_TO_STR(uint8_t);
        _DS_TYPE_TO_STR(int16_t);
        _DS_TYPE_TO_STR(uint16_t);
        _DS_TYPE_TO_STR(int32_t);
        _DS_TYPE_TO_STR(uint32_t);
        _DS_TYPE_TO_STR(int64_t);
        _DS_TYPE_TO_STR(uint64_t);
        _DS_TYPE_TO_STR(float);
        _DS_TYPE_TO_STR(double);
    default:
        return "unknown";
    }
}

#define T int8_t
#include "ds_field.h"
#undef T

#define T uint8_t
#include "ds_field.h"
#undef T

#define T int16_t
#include "ds_field.h"
#undef T

#define T uint16_t
#include "ds_field.h"
#undef T

#define T int32_t
#include "ds_field.h"
#undef T

#define T uint32_t
#include "ds_field.h"
#undef T

#define T int64_t
#include "ds_field.h"
#undef T

#define T uint64_t
#include "ds_field.h"
#undef T

#define T float
#include "ds_field.h"
#undef T

#define T double
#include "ds_field.h"
#undef T

#endif // _DS__H_

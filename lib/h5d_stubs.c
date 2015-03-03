#include <assert.h>
#include <stdio.h>
#include <caml/bigarray.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include "hdf5.h"
#include "h5d_stubs.h"
#include "h5g_stubs.h"
#include "h5i_stubs.h"
#include "h5p_stubs.h"
#include "h5s_stubs.h"
#include "h5t_stubs.h"
#include "loc_stubs.h"

static struct custom_operations h5d_ops = {
  "hdf5.h5d",
  custom_finalize_default,
  custom_compare_default,
  custom_compare_ext_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default
};

static value alloc_h5d(hid_t id)
{
  raise_if_fail(id);
  value v = caml_alloc_custom(&h5d_ops, sizeof(hid_t), 0, 1);
  H5D_val(v) = id;
  return v;
}

value hdf5_h5d_create(value loc_id_v, value name_v, value dtype_id_v, value lcpl_id_v,
    value dcpl_id_v, value dapl_id_v, value space_id_v)
{
  CAMLparam5(loc_id_v, name_v, dtype_id_v, lcpl_id_v, dcpl_id_v);
  CAMLxparam2(dapl_id_v, space_id_v);

  CAMLreturn(alloc_h5d(H5Dcreate2(
    Loc_val(loc_id_v),
    String_val(name_v),
    H5T_val(dtype_id_v),
    H5S_val(space_id_v),
    H5P_opt_val(lcpl_id_v),
    H5P_opt_val(dcpl_id_v),
    H5P_opt_val(dapl_id_v))));
}

value hdf5_h5d_create_bytecode(value *argv, int argn)
{
  assert(argn == 7);
  return hdf5_h5d_create(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

value hdf5_h5d_open(value loc_id_v, value dapl_id_v, value name_v)
{
  CAMLparam3(loc_id_v, dapl_id_v, name_v);
  CAMLreturn(alloc_h5d(H5Dopen2(
    Loc_val(loc_id_v),
    String_val(name_v),
    H5P_opt_val(dapl_id_v))));
}

void hdf5_h5d_close(value dataset_id_v)
{
  CAMLparam1(dataset_id_v);
  raise_if_fail(H5Dclose(H5D_val(dataset_id_v)));
  CAMLreturn0;
}

value hdf5_h5d_get_space(value dataset_id_v)
{
  CAMLparam1(dataset_id_v);
  CAMLreturn(alloc_h5s(H5Dget_space(H5D_val(dataset_id_v))));
}

value hdf5_h5d_get_type(value dataset_id_v)
{
  CAMLparam1(dataset_id_v);
  CAMLreturn(alloc_h5t(H5Dget_type(H5D_val(dataset_id_v))));
}

void hdf5_h5d_read(value dataset_id_v, value mem_type_id_v, value mem_space_id_v,
  value file_space_id_v, value xfer_plist_id_v, value buf_v)
{
  CAMLparam5(dataset_id_v, mem_type_id_v, mem_space_id_v, file_space_id_v,
    xfer_plist_id_v);
  CAMLxparam1(buf_v);

  raise_if_fail(H5Dread(
    H5D_val(dataset_id_v),
    H5T_val(mem_type_id_v),
    H5S_val(mem_space_id_v),
    H5S_val(file_space_id_v),
    H5P_opt_val(xfer_plist_id_v),
    Caml_ba_data_val(buf_v)));

  CAMLreturn0;
}

void hdf5_h5d_read_bytecode(value *argv, int argn)
{
  assert(argn == 6);
  hdf5_h5d_read(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

void hdf5_h5d_write(value dataset_id_v, value mem_type_id_v, value mem_space_id_v,
  value file_space_id_v, value xfer_plist_id_v, value buf_v)
{
  CAMLparam5(dataset_id_v, mem_type_id_v, mem_space_id_v, file_space_id_v,
    xfer_plist_id_v);
  CAMLxparam1(buf_v);

  raise_if_fail(H5Dwrite(
    H5D_val(dataset_id_v),
    H5T_val(mem_type_id_v),
    H5S_val(mem_space_id_v),
    H5S_val(file_space_id_v),
    H5P_opt_val(xfer_plist_id_v),
    Caml_ba_data_val(buf_v)));

  CAMLreturn0;
}

void hdf5_h5d_write_bytecode(value *argv, int argn)
{
  assert(argn == 6);
  hdf5_h5d_write(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}
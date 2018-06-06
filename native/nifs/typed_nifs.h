TYPED_NIF(add_arrays, TYPE_NAME)(ErlNifEnv *env, int32_t argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  TYPE        *first_data, *second_data, *result_data;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (TYPE*)first.data;
  second_data = (TYPE*)second.data;

  result_data = (TYPE*)enif_make_new_binary(env, first.size, &result);

  for (uint64_t i = 0; i < first.size/sizeof(TYPE); i++)
    result_data[i] = first_data[i] + second_data[i];

  return result;
}

TYPED_NIF(multiply_arrays, TYPE_NAME)(ErlNifEnv *env, int32_t argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  first, second;
  ERL_NIF_TERM  result;
  TYPE        *first_data, *second_data, *result_data;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &first )) return enif_make_badarg(env);
  if (!enif_inspect_binary(env, argv[1], &second)) return enif_make_badarg(env);

  first_data  = (TYPE*)first.data;
  second_data = (TYPE*)second.data;

  result_data = (TYPE*)enif_make_new_binary(env, first.size, &result);

  for (uint64_t i = 0; i < first.size/sizeof(TYPE); i++)
    result_data[i] = first_data[i] * second_data[i];

  return result;
}

TYPED_NIF(array_sum, TYPE_NAME)(ErlNifEnv *env, int32_t argc, const ERL_NIF_TERM *argv) {
  ErlNifBinary  array;
  TYPE        *array_data;
  TOP_TYPE sum = 0;

  (void)(argc);

  if (!enif_inspect_binary(env, argv[0], &array)) return enif_make_badarg(env);

  array_data  = (TYPE*)array.data;

  for (uint64_t i = 0; i < array.size/sizeof(TYPE); i++)
    sum += array_data[i];

  return ENIF_MAKE_VAL(sum);
}
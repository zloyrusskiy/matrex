#include <stdint.h>
#include <string.h>
#include <time.h>

#include "erl_nif.h"

typedef unsigned char byte;


#define CAT(a, b, c) a ## b ## c

#define TYPED_NIF(title, type_name) \
        static ERL_NIF_TERM CAT(title, _, type_name)

#define ENIF_MAKE_VAL(VAL) _Generic(VAL, \
        int64_t: enif_make_int64(env, VAL), \
        uint64_t: enif_make_uint64(env, VAL), \
        double: enif_make_double(env, VAL))

#define TOP_TYPE int64_t

#define TYPE uint8_t
#define TYPE_NAME byte
#include "typed_nifs.h"

#undef TYPE
#undef TYPE_NAME
#define TYPE int16_t
#define TYPE_NAME int16
#include "typed_nifs.h"

#undef TYPE
#undef TYPE_NAME
#define TYPE int32_t
#define TYPE_NAME int32
#include "typed_nifs.h"

#undef TYPE
#undef TYPE_NAME
#define TYPE int64_t
#define TYPE_NAME int64
#include "typed_nifs.h"

#undef TOP_TYPE
#define TOP_TYPE double

#undef TYPE
#undef TYPE_NAME
#define TYPE float
#define TYPE_NAME float32
#include "typed_nifs.h"

#undef TYPE
#undef TYPE_NAME
#define TYPE double
#define TYPE_NAME float64
#include "typed_nifs.h"

#define TYPED_NIFS_DECL(NAME, ARGC, FLAGS) \
  {#NAME "_byte", ARGC, NAME##_byte, FLAGS}, \
  {#NAME "_int16", ARGC, NAME##_int16, FLAGS}, \
  {#NAME "_int32", ARGC, NAME##_int32, FLAGS}, \
  {#NAME "_int64", ARGC, NAME##_int64, FLAGS}, \
  {#NAME "_float32", ARGC, NAME##_float32, FLAGS}, \
  {#NAME "_float64", ARGC, NAME##_float64, FLAGS}

static ErlNifFunc nif_functions[] = {
  TYPED_NIFS_DECL(add_arrays, 2, 0),
  TYPED_NIFS_DECL(multiply_arrays, 2, 0),
  TYPED_NIFS_DECL(array_sum, 1, 0)
};


// Solely to silence coveralls.travis task errors on Travis CI
int
upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info) {
  // Silence "unused var" warnings.
  (void)(env);
  (void)(priv_data);
  (void)(old_priv_data);
  (void)(load_info);

  return 0;
}

// Used for RNG initialization.
int
load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info) {
  // Silence "unused var" warnings.
  (void)(env);
  (void)(priv_data);
  (void)(load_info);

  srandom(time(NULL) + clock());

  return 0;
}

ERL_NIF_INIT(Elixir.Matrex.Array.NIFs, nif_functions, load, NULL, upgrade, NULL)

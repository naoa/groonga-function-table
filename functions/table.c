#include <string.h>
#include <stdlib.h>
#include <groonga/plugin.h>

#ifdef __GNUC__
# define GNUC_UNUSED __attribute__((__unused__))
#else
# define GNUC_UNUSED
#endif

static grn_bool
grn_obj_is_key_table(GNUC_UNUSED grn_ctx *ctx, grn_obj *obj)
{
  grn_bool is_table = GRN_FALSE;

  if (!obj) {
    return GRN_FALSE;
  }

  switch (obj->header.type) {
  case GRN_TABLE_HASH_KEY :
  case GRN_TABLE_PAT_KEY :
  case GRN_TABLE_DAT_KEY :
    is_table = GRN_TRUE;
  default :
    break;
  }

  return is_table;
}


static grn_obj *
func_table_get_value(grn_ctx *ctx, GNUC_UNUSED int nargs, GNUC_UNUSED grn_obj **args,
            grn_user_data *user_data)
{
  grn_obj *result = NULL;

  if (nargs < 3) {
    GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                     "table_get_value(): wrong number of arguments (%d for 3)", nargs);
    goto exit;
  }

  {
    grn_obj *table = args[0];
    grn_obj *accessor_str = args[1];
    grn_obj *key_str = args[2];

    grn_obj *accessor = NULL;

    if (!grn_obj_is_key_table(ctx, table)) {
      GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                       "table_get_value(): 1st argument should be table having key_type");
      goto exit;
    }

    if (GRN_TEXT_LEN(accessor_str) == 0) {
      GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                       "table_get_value(): 2nd argument should be specified table's column name as string");
      goto exit;
    }

    if (GRN_TEXT_LEN(key_str) == 0) {
      GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                       "table_get_value(): 3rd argument should be key value as string");
      goto exit;
    }

    accessor = grn_obj_column(ctx, table,
                              GRN_TEXT_VALUE(accessor_str), GRN_TEXT_LEN(accessor_str));
    if (!accessor) {
      GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                       "table_get_value(): coludn't find column");
      goto exit;
    }

    {
      grn_id id;
      id = grn_table_get(ctx, table, GRN_TEXT_VALUE(key_str), GRN_TEXT_LEN(key_str));
      if (id != GRN_ID_NIL) {
        if ((result = grn_plugin_proc_alloc(ctx, user_data, grn_obj_get_range(ctx, accessor), 0))) {
          grn_obj_get_value(ctx, accessor, id, result);
        }
      }
    }

    grn_obj_close(ctx, accessor);
  }

exit :

  if (!result) {
    result = grn_plugin_proc_alloc(ctx, user_data, GRN_DB_VOID, 0);
  }

  return result;
}

grn_rc
GRN_PLUGIN_INIT(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  grn_proc_create(ctx, "table_get_value", -1, GRN_PROC_FUNCTION,
                  func_table_get_value, NULL, NULL, 0, NULL);

  return ctx->rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

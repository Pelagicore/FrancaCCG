#include "simpleFranca_common.h"
#include <glib.h>
#include <gio/gio.h>

void FrancaccodegenVerySimpleFrancaInterface_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot);

GDBusProxy* FrancaccodegenVerySimpleFrancaInterface_createforBusFinish(GAsyncResult* result);

void FrancaccodegenVerySimpleFrancaInterface_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer));


void FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s(GDBusProxy *proxy, gint16 arg_firstNumber, gint16 arg_secondNumber, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s_finish(GDBusProxy *proxy, gint32 *out_sumOfNumbers_out0, const gchar * *out_stringOfNumbers_out1, GAsyncResult *result);

void FrancaccodegenVerySimpleFrancaInterface_theSecondMethod__s__s(GDBusProxy *proxy, const gchar * arg_theString, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_theSecondMethod__s__s_finish(GDBusProxy *proxy, const gchar * *out_anotherString_out0, GAsyncResult *result);

void FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u(GDBusProxy *proxy, OBJECTLIST_TYPE arg_objectName, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u_finish(GDBusProxy *proxy, COLOR_TYPE *out_objectColor_out0, GAsyncResult *result);


void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set(GDBusProxy *proxy, guint32 value, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set_finish(GDBusProxy *proxy, GAsyncResult *result);
void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finish(GDBusProxy *proxy, guint32 *value, GAsyncResult *result);

void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set(GDBusProxy *proxy, gchar *value, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set_finish(GDBusProxy *proxy, GAsyncResult *result);
void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get_finish(GDBusProxy *proxy, gchar **value, GAsyncResult *result);

void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set(GDBusProxy *proxy, COLOR_TYPE value, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set_finish(GDBusProxy *proxy, GAsyncResult *result);
void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get_finish(GDBusProxy *proxy, guint32 *value, GAsyncResult *result);

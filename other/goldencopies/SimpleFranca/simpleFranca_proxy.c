#include "simpleFranca_proxy.h"
#include <stdio.h>
#include <stdlib.h>

void FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s(GDBusProxy *proxy, gint16 arg_firstNumber, gint16 arg_secondNumber, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "theOnlyMethod", 
        g_variant_new ("(nn)", arg_firstNumber, arg_secondNumber),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s_finish (GDBusProxy *proxy, gint32 *out_sumOfNumbers_out0, const gchar * *out_stringOfNumbers_out1, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to theOnlyMethod did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        // Put results of method call in parameters
        GVariant *sumOfNumbers_out0_variant;
        sumOfNumbers_out0_variant = g_variant_get_child_value(wrapped, 0);
        *out_sumOfNumbers_out0 = g_variant_get_int32(sumOfNumbers_out0_variant);

        GVariant *stringOfNumbers_out1_variant;
        stringOfNumbers_out1_variant = g_variant_get_child_value(wrapped, 1);
        *out_stringOfNumbers_out1 = g_variant_get_string(stringOfNumbers_out1_variant, NULL);
        *success = TRUE;
    }
}




void FrancaccodegenVerySimpleFrancaInterface_theSecondMethod__s__s(GDBusProxy *proxy, const gchar * arg_theString, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "theSecondMethod", 
        g_variant_new ("(s)", arg_theString),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_theSecondMethod__s__s_finish (GDBusProxy *proxy, const gchar * *out_anotherString_out0, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to theSecondMethod did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
    
    // Put results from method call in parameters
    GVariant *anotherString_out0_variant;
    anotherString_out0_variant = g_variant_get_child_value(wrapped, 0);
    *out_anotherString_out0 = g_variant_get_string(anotherString_out0_variant, NULL);
    *success = TRUE;
    }
}




void FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u(GDBusProxy *proxy, OBJECTLIST_TYPE arg_objectName, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "getColorOfObject", 
        g_variant_new ("(u)", arg_objectName),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u_finish (GDBusProxy *proxy, COLOR_TYPE *out_objectColor_out0, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to getColorOfObject did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
    

    // Put results from method call in parameters
    GVariant *objectColor_out0_variant;
    objectColor_out0_variant = g_variant_get_child_value(wrapped, 0);
    *out_objectColor_out0 = g_variant_get_uint32(objectColor_out0_variant);
    *success = TRUE;
    }
}




// This function is called from implementation to create a proxy for the specified D-bus service
void FrancaccodegenVerySimpleFrancaInterface_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot) {
    g_dbus_proxy_new_for_bus (
        bus_type,
        flags,
        NULL, 
        name,
        objectPath,
        "Francaccodegen.verySimpleFrancaInterface",
        NULL, //Gcancellable
        slot, // GAsyncReadyCallback callback
        NULL); // gpointer user_data
}

// This function is called from implementation to finish creating proxy
GDBusProxy* FrancaccodegenVerySimpleFrancaInterface_createforBusFinish(GAsyncResult* result) {
    GError *error = NULL;
    GDBusProxy* proxy = g_dbus_proxy_new_for_bus_finish(result, &error);
    if (error == NULL) {
        return proxy;
    } else {
        printf("ERROR: Cannot create proxy. Server stub is possibly offline.\nGError content: %s\nClosing proxy...\n", error->message);
        exit(1);
        return NULL;
    }
}

void FrancaccodegenVerySimpleFrancaInterface_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer)) {
    g_signal_connect (proxy,
                    "g-properties-changed",
                    G_CALLBACK(callback),
                    NULL);
}




void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set(GDBusProxy *proxy, guint32 value, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Set", 
        g_variant_new ("(ssv)", "Francaccodegen.verySimpleFrancaInterface", "anIntegerAttribute", g_variant_new_uint32(value)),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set_finish (GDBusProxy *proxy, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to anIntegerAttribute_u_set did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        *success = TRUE;
    }
}

void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Get", 
        g_variant_new ("(ss)", "Francaccodegen.verySimpleFrancaInterface", "anIntegerAttribute"),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finish(GDBusProxy *proxy, guint32 *value, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to anIntegerAttribute_u_get did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        GVariant *value_variant;
        value_variant = g_variant_get_child_value(wrapped, 0);  
        *value = g_variant_get_uint32(g_variant_get_variant(value_variant));
        *success = TRUE;
    }
}




void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set(GDBusProxy *proxy, gchar *value, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Set", 
        g_variant_new ("(ssv)", "Francaccodegen.verySimpleFrancaInterface", "aStringAttribute", g_variant_new_string(value)),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set_finish (GDBusProxy *proxy, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to aStringAttribute_s_set did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        *success = TRUE;
    }
}

void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Get", 
        g_variant_new ("(ss)", "Francaccodegen.verySimpleFrancaInterface", "aStringAttribute"),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get_finish(GDBusProxy *proxy, gchar **value, GAsyncResult *result, gboolean *success) {
   // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to aStringAttribute_s_get did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        GVariant *value_variant;
        value_variant = g_variant_get_child_value(wrapped, 0);  
        *value = g_variant_get_string(g_variant_get_variant(value_variant), NULL);
        *success = TRUE;
    }
}




void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set(GDBusProxy *proxy, COLOR_TYPE value, const GAsyncReadyCallback callback) {
    
    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Set", 
        g_variant_new ("(ssv)", "Francaccodegen.verySimpleFrancaInterface", "anEnumAttribute", g_variant_new_uint32(value)),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set_finish (GDBusProxy *proxy, GAsyncResult *result, gboolean *success) {
   // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to anEnumAttribute_u_set did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        *success = TRUE;
    }
}

void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Get", 
        g_variant_new ("(ss)", "Francaccodegen.verySimpleFrancaInterface", "anEnumAttribute"),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get_finish(GDBusProxy *proxy, COLOR_TYPE *value, GAsyncResult *result, gboolean *success) {
   // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to anEnumAttribute_u_get did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        GVariant *value_variant;
        value_variant = g_variant_get_child_value(wrapped, 0);  
        *value = g_variant_get_uint32(g_variant_get_variant(value_variant));
        *success = TRUE;
    }
}

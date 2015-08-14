#include "MediaIndexer_proxy.h"
#include <stdio.h>
#include <stdlib.h>        


void OrgGeniviMediamanagerIndexer_getDatabasePath____s_u(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "getDatabasePath", 
        NULL,
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void OrgGeniviMediamanagerIndexer_getDatabasePath____s_u_finish (GDBusProxy *proxy, const gchar * *out_output_out0, IndexerError_type *out_e_out1, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to getDatabasePath____s_u did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        // Put results from method call in parameter

        GVariant *output_out0_variant;
        output_out0_variant = g_variant_get_child_value(wrapped, 0);
        *out_output_out0 = g_variant_get_string(output_out0_variant, NULL);

        GVariant *e_out1_variant;
        e_out1_variant = g_variant_get_child_value(wrapped, 1);
        *out_e_out1 = g_variant_get_uint32(e_out1_variant);

        *success = TRUE;
    }
}

void OrgGeniviMediamanagerIndexer_stopIndexing____u(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "stopIndexing", 
        NULL,
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void OrgGeniviMediamanagerIndexer_stopIndexing____u_finish (GDBusProxy *proxy, IndexerError_type *out_e_out0, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to stopIndexing____u did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        // Put results from method call in parameter

        GVariant *e_out0_variant;
        e_out0_variant = g_variant_get_child_value(wrapped, 0);
        *out_e_out0 = g_variant_get_uint32(e_out0_variant);

        *success = TRUE;
    }
}

void OrgGeniviMediamanagerIndexer_startIndexing____u(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "startIndexing", 
        NULL,
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 
}

void OrgGeniviMediamanagerIndexer_startIndexing____u_finish (GDBusProxy *proxy, IndexerError_type *out_e_out0, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to startIndexing____u did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {

        // Put results from method call in parameter

        GVariant *e_out0_variant;
        e_out0_variant = g_variant_get_child_value(wrapped, 0);
        *out_e_out0 = g_variant_get_uint32(e_out0_variant);

        *success = TRUE;
    }
}


// This function is called from implementation to create a proxy for the specified D-bus service
void OrgGeniviMediamanagerIndexer_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot) {
    g_dbus_proxy_new_for_bus (
        bus_type,
        flags,
        NULL, 
        name,
        objectPath,
        "org.genivi.mediamanager.Indexer",
        NULL, //Gcancellable
        slot, // GAsyncReadyCallback callback
        NULL); // gpointer user_data
}

// This function is called from implementation to finish creating proxy
GDBusProxy* OrgGeniviMediamanagerIndexer_createforBusFinish(GAsyncResult* result) {
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


void OrgGeniviMediamanagerIndexer_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer)) {
    g_signal_connect (proxy,
                      "g-properties-changed",
                      G_CALLBACK(callback),
                      NULL);
}       


void OrgGeniviMediamanagerIndexer_indexerStatus_u_set(GDBusProxy *proxy, IndexerStatus_type value, const GAsyncReadyCallback callback) {

    g_dbus_proxy_call(
        proxy, 
        "org.freedesktop.DBus.Properties.Set", 
        g_variant_new ("(ssv)", "org.genivi.mediamanager.Indexer", "indexerStatus", g_variant_new_uint32(value)),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        callback,
        NULL); 

}

void OrgGeniviMediamanagerIndexer_indexerStatus_u_set_finish (GDBusProxy *proxy, GAsyncResult *result, gboolean *success) {

    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to indexerStatus_u_set did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        *success = TRUE;
    }
}

void OrgGeniviMediamanagerIndexer_indexerStatus_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback) {

g_dbus_proxy_call(
    proxy, 
    "org.freedesktop.DBus.Properties.Get", 
    g_variant_new ("(ss)", "org.genivi.mediamanager.Indexer", "indexerStatus"),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    NULL,
    callback,
    NULL); 
}

void OrgGeniviMediamanagerIndexer_indexerStatus_u_get_finish(GDBusProxy *proxy, IndexerStatus_type *value, GAsyncResult *result, gboolean *success) {
    // Get result from method call from d-bus proxy
    GVariant *wrapped;
    GError *error = NULL;
    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

    if (error != NULL) {
        printf("WARNING: Method call to indexerStatus_u_get did not succeed.\nGError content: %s\n", error->message);
        *success = FALSE;
    } else {
        GVariant *value_variant;
        value_variant = g_variant_get_child_value(wrapped, 0);  
        *value = g_variant_get_uint32(g_variant_get_variant(value_variant));
        *success = TRUE;
    }
}


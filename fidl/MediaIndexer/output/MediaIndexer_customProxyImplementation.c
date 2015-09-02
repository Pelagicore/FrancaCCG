#include "MediaIndexer_proxy.h"
#include <stdio.h>

GDBusProxy* proxy;

// DEBUG: Input used for testing purposes.
gint16 testInput1 = 100;
gint16 testInput2 = 33;


// This function is called from simpleFranca_proxy when method call is finished.
// It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
void on_getDatabasePath____s_i_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    const gchar * output_out0_result;
    IndexerError_type e_out1_result;
    gboolean success = FALSE;
    OrgGeniviMediamanagerIndexer_getDatabasePath____s_i_finish(proxy, &output_out0_result, &e_out1_result, result, &success);
    
    // success now contains whether method call was successful or not
    // _result variables now contains the results of the method call.
    // Implementation goes here
    printf("Proxy received reply to getDatabasePath method call.\n");
}

// This function is called from simpleFranca_proxy when method call is finished.
// It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
void on_stopIndexing____i_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    IndexerError_type e_out0_result;
    gboolean success = FALSE;
    OrgGeniviMediamanagerIndexer_stopIndexing____i_finish(proxy, &e_out0_result, result, &success);
    
    // success now contains whether method call was successful or not
    // _result variables now contains the results of the method call.
    // Implementation goes here
    printf("Proxy received reply to stopIndexing method call.\n");
}

// This function is called from simpleFranca_proxy when method call is finished.
// It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
void on_startIndexing____i_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    IndexerError_type e_out0_result;
    gboolean success = FALSE;
    OrgGeniviMediamanagerIndexer_startIndexing____i_finish(proxy, &e_out0_result, result, &success);
    
    // success now contains whether method call was successful or not
    // _result variables now contains the results of the method call.
    // Implementation goes here
    printf("Proxy received reply to startIndexing method call, now calling stopIndexing remotely...\n");
    void (*stopIndexingPointer)(GObject *obj, GAsyncResult *result, gpointer userdata);
    stopIndexingPointer = &on_stopIndexing____i_finished;
    OrgGeniviMediamanagerIndexer_stopIndexing____i(proxy, stopIndexingPointer);
    // END DEBUG
    
}

void on_OrgGeniviMediamanagerIndexer_indexerStatus_i_set_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    gboolean success = FALSE;

    OrgGeniviMediamanagerIndexer_indexerStatus_i_set_finish(proxy, result, &success);
    // success now contains whether method call was successful or not
}

void on_OrgGeniviMediamanagerIndexer_indexerStatus_i_get_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    IndexerStatus_type indexerStatus_i;
    gboolean success = FALSE;

    OrgGeniviMediamanagerIndexer_indexerStatus_i_get_finish(proxy, &indexerStatus_i, result, &success);
    // success now contains whether method call was successful or not
    // indexerStatus_i now contains current value of property.
    // Implementation goes here    

}



void on_properties_changed (GDBusProxy          *proxy,
                            GVariant            *changed_properties,
                            const gchar* const  *invalidated_properties,
                            gpointer             user_data)
{
    // Implementation of the handling of the PropertiesChanged signal is done here.
    // Note that local cache is automatically updated and needs not to be implemented here.
}


// This function is called from OrgGeniviMediamanagerIndexer_proxy when proxy has been created.
// It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
void proxy_created(GObject *obj, GAsyncResult *result, gpointer userdata) {
    proxy = OrgGeniviMediamanagerIndexer_createforBusFinish(result);
    // Proxy has been created.

    // Connect to signal handler.
    OrgGeniviMediamanagerIndexer_connectToPropertiesChanged(proxy, &on_properties_changed);
    printf("Proxy implementation successfully connected to remote server.\n");
    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.
    void (*startIndexingPointer)(GObject *obj, GAsyncResult *result, gpointer userdata);
    startIndexingPointer = &on_startIndexing____i_finished;
    printf("Proxy implementation making remote call to startIndexing method...\n");
    OrgGeniviMediamanagerIndexer_startIndexing____i(proxy, startIndexingPointer);
    // END DEBUG
   
}

int main(int argc, char **argv) {

    // Create pointer to function to call when proxy has been created.
    GAsyncReadyCallback proxycreated_pointer = &proxy_created;

    // Connect to D-Bus service.
    OrgGeniviMediamanagerIndexer_createForBus(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, "org.genivi.mediamanager.Indexer", "/org/genivi/mediamanager/Indexer", proxycreated_pointer);

    // Run main loop.
    GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
    g_main_run(mainloop);
    return 0;
}

#include "MediaIndexer_stub.h"
#include <stdio.h>
#include <stdlib.h>

void OrgGeniviMediamanagerIndexer_connect(GBusType bustype) {

    // Create D-Bus Introspection structure from XML
    nodeinfo = g_dbus_node_info_new_for_xml(interfaceXml0, NULL);

    if (nodeinfo == NULL) {
        printf("ERROR: Couldn't create introspection data structures from XML: \n%s\n", interfaceXml0);
        exit(1);
    }    

    // Start D-Bus service
    owner_id = g_bus_own_name (bustype,
                               "org.genivi.mediamanager.Indexer",
                               G_BUS_NAME_OWNER_FLAGS_NONE,
                               OrgGeniviMediamanagerIndexer_on_bus_acquired,
                               OrgGeniviMediamanagerIndexer_on_name_acquired,
                               OrgGeniviMediamanagerIndexer_on_name_lost,
                               NULL,
                               NULL);
    }

void OrgGeniviMediamanagerIndexer_dereference() {
    g_bus_unown_name (owner_id);
    g_dbus_node_info_unref (nodeinfo);
}

// When bus acquired, register interface in the d-bus connection
void OrgGeniviMediamanagerIndexer_on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){
    guint registration_id;

    static const GDBusInterfaceVTable interface_vtable =
    {
        OrgGeniviMediamanagerIndexer_on_method_call,
        OrgGeniviMediamanagerIndexer_on_get_property,
        OrgGeniviMediamanagerIndexer_on_set_property
    };


    registration_id = g_dbus_connection_register_object (connection,
                                                         "/org/genivi/mediamanager/Indexer",
                                                         nodeinfo->interfaces[0],
                                                         &interface_vtable,
                                                         NULL,  /* user_data */
                                                         NULL,  /* user_data_free_func */
                                                         NULL); /* GError** */

    g_assert (registration_id > 0);

}

// The following functions needs to be here. They do nothing (except printing errors) for now.
void OrgGeniviMediamanagerIndexer_on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){
}

void OrgGeniviMediamanagerIndexer_on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data){
    printf("ERROR: Lost D-Bus name: %s\n", name);
    exit(1);
}

GVariant* OrgGeniviMediamanagerIndexer_on_get_property (GDBusConnection  *connection,
                                          const gchar      *sender,
                                          const gchar      *object_path,
                                          const gchar      *interface_name,
                                          const gchar      *property_name,
                                          GError          **error,
                                          gpointer          user_data){

    // TODO error handling, should use the gerror since it is already here

    GVariant *ret;
    ret = NULL;

    if (g_strcmp0 (property_name, "indexerStatus") == 0) {
        ret = g_variant_new_uint32(indexerStatus_u);
    } else 
    {
        printf("ERROR: Interface does not contain property: %s\n", property_name);
        exit(1);
    }
    return ret;
}

gboolean OrgGeniviMediamanagerIndexer_on_set_property (GDBusConnection  *connection,
                                         const gchar      *sender,
                                         const gchar      *object_path,
                                         const gchar      *interface_name,
                                         const gchar      *property_name,
                                         GVariant         *value,
                                         GError          **error,
                                         gpointer          user_data){

    if (g_strcmp0 (property_name, "indexerStatus") == 0)
    {
        if (indexerStatus_u != g_variant_get_uint32(value))
        {
            indexerStatus_u = g_variant_get_uint32(value);
            // Unless com.pelagicore.FrancaCCodeGen.Enum.NoSubscriptions annotation is set to true, send PropertiesChanged signal
            // Annotation is set to TRUE. Do not send signal.
        }
    } else
    {
        printf("ERROR: Interface does not contain property: %s\n", property_name);
        exit(1);
    }
    return *error == NULL;
}

// Register method handler function
void register_handler(Handlers_enum e, void* f){
    switch (e)
    {
    case GETDATABASEPATH____S_U:
        methodsStruct.getDatabasePath____s_uHandler = (getDatabasePath____s_uSignature)f;
        break;
    case STOPINDEXING____U:
        methodsStruct.stopIndexing____uHandler = (stopIndexing____uSignature)f;
        break;
    case STARTINDEXING____U:
        methodsStruct.startIndexing____uHandler = (startIndexing____uSignature)f;
        break;

    default:
        printf("ERROR: No such handler enum defined: %u\n", e);
        exit(1);
    }
}

// Handle method calls
void OrgGeniviMediamanagerIndexer_on_method_call(GDBusConnection *connection,
                                   const gchar *sender,
                                   const gchar *object_path,
                                   const gchar *interface_name,
                                   const gchar *method_name,
                                   GVariant *parameters,
                                   GDBusMethodInvocation *invocation,
                                   gpointer user_data){
    // TODO needs to compare on other stuff (ie signature) than name, can be collisions

    if (g_strcmp0 (method_name, "getDatabasePath") == 0) 
    {
        const gchar * output_out0;
        IndexerError_type e_out1;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.getDatabasePath____s_uHandler != NULL) {
            methodsStruct.getDatabasePath____s_uHandler(&output_out0, &e_out1);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(su)", output_out0, e_out1));
    } else
    if (g_strcmp0 (method_name, "stopIndexing") == 0) 
    {
        IndexerError_type e_out0;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.stopIndexing____uHandler != NULL) {
            methodsStruct.stopIndexing____uHandler(&e_out0);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(u)", e_out0));
    } else
    if (g_strcmp0 (method_name, "startIndexing") == 0) 
    {
        IndexerError_type e_out0;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.startIndexing____uHandler != NULL) {
            methodsStruct.startIndexing____uHandler(&e_out0);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(u)", e_out0));
    } else

    {
        printf("ERROR: No such method in registered D-Bus interface. Method name: %s\n", method_name);
        exit(1);
    }

}

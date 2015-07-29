#include "simpleFranca_stub.h"
#include <stdio.h>
#include <stdlib.h>

void FrancaccodegenVerySimpleFrancaInterface_connect(GBusType bustype) {

    // Create D-Bus Introspection structure from XML
    nodeinfo = g_dbus_node_info_new_for_xml(interfaceXml0, NULL);

    if (nodeinfo == NULL) {
        printf("ERROR: Couldn't create introspection data structures from XML: \n%s\n", interfaceXml0);
        exit(1);
    }    

    // Start D-Bus service
    owner_id = g_bus_own_name (bustype,
                                 "Francaccodegen.verySimpleFrancaInterface",
                                 G_BUS_NAME_OWNER_FLAGS_NONE,
                                 FrancaccodegenVerySimpleFrancaInterface_on_bus_acquired,
                                 FrancaccodegenVerySimpleFrancaInterface_on_name_acquired,
                                 FrancaccodegenVerySimpleFrancaInterface_on_name_lost,
                                 NULL,
                                 NULL);
    }

void FrancaccodegenVerySimpleFrancaInterface_dereference() {
    g_bus_unown_name (owner_id);
    g_dbus_node_info_unref (nodeinfo);
}

// When bus acquired, register interface in the d-bus connection
void FrancaccodegenVerySimpleFrancaInterface_on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){
    guint registration_id;

    static const GDBusInterfaceVTable interface_vtable =
    {
        FrancaccodegenVerySimpleFrancaInterface_on_method_call,
        FrancaccodegenVerySimpleFrancaInterface_on_get_property,
        FrancaccodegenVerySimpleFrancaInterface_on_set_property
    };


    registration_id = g_dbus_connection_register_object (connection,
                            "/Francaccodegen/verySimpleFrancaInterface",
                            nodeinfo->interfaces[0],
                            &interface_vtable,
                            NULL,  /* user_data */
                            NULL,  /* user_data_free_func */
                            NULL); /* GError** */

    g_assert (registration_id > 0);

}

// The following functions needs to be here. They do nothing (except printing errors) for now.
void FrancaccodegenVerySimpleFrancaInterface_on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){
}

void FrancaccodegenVerySimpleFrancaInterface_on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data){
    printf("ERROR: Lost D-Bus name: %s\n", name);
    exit(1);
}

GVariant* FrancaccodegenVerySimpleFrancaInterface_on_get_property (GDBusConnection  *connection,
                            const gchar      *sender,
                            const gchar      *object_path,
                            const gchar      *interface_name,
                            const gchar      *property_name,
                            GError          **error,
                            gpointer          user_data){

    // TODO error handling, should use the gerror since it is already here
    
    GVariant *ret;
    ret = NULL;
    
    if (g_strcmp0 (property_name, "anIntegerAttribute") == 0)
    {
        ret = g_variant_new_uint32(anIntegerAttribute_u);
    } else
    if (g_strcmp0 (property_name, "aStringAttribute") == 0)
    {
        ret = g_variant_new_string(aStringAttribute_s);
    } else 
    if (g_strcmp0 (property_name, "anEnumAttribute") == 0)
    {
        ret = g_variant_new_uint32(anEnumAttribute_u);
    } else {
    printf("ERROR: Interface does not contain property: %s\n", property_name);
    exit(1);
    }
    return ret;
}

gboolean FrancaccodegenVerySimpleFrancaInterface_on_set_property (GDBusConnection  *connection,
                            const gchar      *sender,
                            const gchar      *object_path,
                            const gchar      *interface_name,
                            const gchar      *property_name,
                            GVariant         *value,
                            GError          **error,
                            gpointer          user_data){

    
    if (g_strcmp0 (property_name, "anIntegerAttribute") == 0)
    {
        if (anIntegerAttribute_u != g_variant_get_uint32(value))
        {

            anIntegerAttribute_u = g_variant_get_uint32(value);
            
            // Unless org.freedesktop.DBus.Property.EmitsChangedSignal annotation is set to false, send PropertiesChanged signal
            
            // Annotation is set to false. Do not send signal.
         }
    } else 
    if (g_strcmp0 (property_name, "aStringAttribute") == 0)
    {
        if (g_strcmp0 (aStringAttribute_s, g_variant_get_string (value, NULL)) != 0)
        {

            aStringAttribute_s = g_variant_dup_string (value, NULL);


            // Unless org.freedesktop.DBus.Property.EmitsChangedSignal annotation is set to false, send PropertiesChanged signal
            
            // Annotation is not set to false. Send signal.
            GVariantBuilder *builder;
            GError *local_error;
            local_error = NULL;
            builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);
            g_variant_builder_add (builder,
                                    "{sv}",
                                    "aStringAttribute",
                                    g_variant_new_string (aStringAttribute_s));
            g_dbus_connection_emit_signal (connection,
                                    NULL,
                                    object_path,
                                    "org.freedesktop.DBus.Properties",
                                    "PropertiesChanged",
                                    g_variant_new ("(sa{sv}as)",
                                                    interface_name,
                                                    builder,
                                                    NULL),
                                                    &local_error); 
            g_assert_no_error (local_error);
         }
    } else 
    if (g_strcmp0 (property_name, "anEnumAttribute") == 0)
    {
        if (anEnumAttribute_u != g_variant_get_uint32(value))
        {
           
            anEnumAttribute_u = g_variant_get_uint32(value);
            
            // Unless org.freedesktop.DBus.Property.EmitsChangedSignal annotation is set to false, send PropertiesChanged signal
            
            // Annotation is not set to false. Send signal.
            GVariantBuilder *builder;
            GError *local_error;
            local_error = NULL;
            builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);
            g_variant_builder_add (builder,
                                    "{sv}",
                                    "anEnumAttribute",
                                    g_variant_new_uint32(anEnumAttribute_u));
            g_dbus_connection_emit_signal (connection,
                                    NULL,
                                    object_path,
                                    "org.freedesktop.DBus.Properties",
                                    "PropertiesChanged",
                                    g_variant_new ("(sa{sv}as)",
                                                    interface_name,
                                                    builder,
                                                    NULL),
                                                    &local_error); 
            g_assert_no_error (local_error);
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
    case THEONLYMETHOD__N_N__I_S:
        methodsStruct.theOnlyMethod__n_n__i_sHandler = (theOnlyMethod__n_n__i_sSignature)f;
        break;
    case THESECONDMETHOD__S__S:
        methodsStruct.theSecondMethod__s__sHandler = (theSecondMethod__s__sSignature)f;
        break;
    case GETCOLOROFOBJECT__U__U:
        methodsStruct.getColorOfObject__u__uHandler = (getColorOfObject__u__uSignature)f;
        break;

    default:
        printf("ERROR: No such handler enum defined: %u\n", e);
        exit(1);
    }
}

// Handle method calls
void FrancaccodegenVerySimpleFrancaInterface_on_method_call(GDBusConnection *connection,
                const gchar *sender,
                const gchar *object_path,
                const gchar *interface_name,
                const gchar *method_name,
                GVariant *parameters,
                GDBusMethodInvocation *invocation,
                gpointer user_data){
    // TODO needs to compare on other stuff (ie signature) than name, can be collisions

    if (g_strcmp0 (method_name, "theOnlyMethod") == 0) 
    {
        gint16 firstNumber_in0 = g_variant_get_int16(g_variant_get_child_value(parameters, 0));
        gint16 secondNumber_in1 = g_variant_get_int16(g_variant_get_child_value(parameters, 1));
        gint32 sumOfNumbers_out0;
        const gchar * stringOfNumbers_out1;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.theOnlyMethod__n_n__i_sHandler != NULL) {
            methodsStruct.theOnlyMethod__n_n__i_sHandler(firstNumber_in0, secondNumber_in1, &sumOfNumbers_out0, &stringOfNumbers_out1);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(is)", sumOfNumbers_out0, stringOfNumbers_out1));
    } else
    if (g_strcmp0 (method_name, "theSecondMethod") == 0) 
    {
        const gchar * theString_in0 = g_variant_get_string(g_variant_get_child_value(parameters, 0), NULL);
        const gchar * anotherString_out0;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.theSecondMethod__s__sHandler != NULL) {
            methodsStruct.theSecondMethod__s__sHandler(theString_in0, &anotherString_out0);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(s)", anotherString_out0));
    } else
    if (g_strcmp0 (method_name, "getColorOfObject") == 0) 
    {
        OBJECTLIST_TYPE objectName_in0 = g_variant_get_uint32(g_variant_get_child_value(parameters, 0));
        COLOR_TYPE objectColor_out0;
        // Call the registered method handler, if one is registered.
        if (methodsStruct.getColorOfObject__u__uHandler != NULL) {
            methodsStruct.getColorOfObject__u__uHandler(objectName_in0, &objectColor_out0);
        } else {
            printf("ERROR: No method handler function registered for method: %s\n", method_name);
            exit(1);
        }
        //Return
        g_dbus_method_invocation_return_value (invocation, g_variant_new ("(u)", objectColor_out0));
    } else

    {
        printf("ERROR: No such method in registered D-Bus interface. Method name: %s\n", method_name);
        exit(1);
    }

}

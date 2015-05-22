#include "simpleFranca_proxy.h"
#include <stdio.h>

GDBusProxy* proxy;

// DEBUG: Input used for testing purposes.
gint16 testInput1 = 100;
gint16 testInput2 = 33;
gchar *testInput3 = "This is a test string.";
COLOR_TYPE testInput4 = BLUE;
OBJECTLIST_TYPE testInput5 = COFFEE;
// END DEBUG


void on_theOnlyMethod__n_n__i_s_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    gint32 sumOfNumbers_out0_result;
    const gchar * stringOfNumbers_out1_result;
    FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s_finish(proxy, &sumOfNumbers_out0_result, &stringOfNumbers_out1_result, result);
    // sumOfNumbers_out0_result, stringOfNumbers_out1_result now contains the results of the method call.
    // Implementation goes here    
        
    // DEBUG
    printf("Result of method call to theOnlyMethod: %d, %s \n", sumOfNumbers_out0_result, stringOfNumbers_out1_result);
    // END DEBUG
}




void on_theSecondMethod__s__s_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    const gchar * anotherString_out0_result;
    FrancaccodegenVerySimpleFrancaInterface_theSecondMethod__s__s_finish(proxy, &anotherString_out0_result, result);
    // anotherString_out0_result now contains the results of the method call.
    // Implementation goes here    
    
}




void on_getColorOfObject__u__u_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {

    COLOR_TYPE objectColor_out0_result;
    FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u_finish(proxy, &objectColor_out0_result, result);
    // objectColor_out0_result now contains the results of the method call.
    // Implementation goes here    
        
    // DEBUG
    printf("Result of method call to getColorOfObject: %u\n", objectColor_out0_result);
    // END DEBUG

}




void on_FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set_finish(proxy, result);
       
    // DEBUG
    printf("anIntegerAttribute cached value: %u. (Should not have been changed due to no PropertiesChanged signal sent!)\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anIntegerAttribute")));
    // END DEBUG
}

void on_FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    guint32 anIntegerAttribute_u;
    FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finish(proxy, &anIntegerAttribute_u, result);
    // anIntegerAttribute_u now contains current value of property.
    // Implementation goes here    
    
    // DEBUG
    printf("Result from anIntegerAttribute getter method: %u.\n", anIntegerAttribute_u);
    // END DEBUG
}




void on_FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set_finish(proxy, result);
    
    // DEBUG
    printf("aStringAttribute cached value: \"%s\" (Should not have been changed due to being read only!)\n", g_variant_get_string(g_dbus_proxy_get_cached_property(proxy, "aStringAttribute"), NULL));
    // END DEBUG
}

void on_FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    gchar* aStringAttribute_s;
    FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get_finish(proxy, &aStringAttribute_s, result);
    // aStringAttribute_s now contains current value of property.
    // Implementation goes here
    
    // DEBUG
    printf("Result from aStringAttribute getter method: \"%s\"\n", aStringAttribute_s);
    // END DEBUG
}




void on_FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set_finish(proxy, result);
    
    // DEBUG
    printf("anEnumAttribute cached value: %u\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anEnumAttribute")));
    // END DEBUG
}

void on_FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {
    COLOR_TYPE anEnumAttribute_u;
    FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finish(proxy, &anEnumAttribute_u, result);
    // anEnumAttribute_u now contains current value of property.
    // Implementation goes here
    
    // DEBUG
    printf("Result from anEnumAttribute getter method: %u.\n", anEnumAttribute_u);
    // END DEBUG
}




void on_properties_changed (GDBusProxy          *proxy,
                            GVariant            *changed_properties,
                            const gchar* const  *invalidated_properties,
                            gpointer             user_data)
{
    // Implementation of the handling of the PropertiesChanged signal is done here.

    // DEBUG: Print changes and local cache.
    if (g_variant_n_children (changed_properties) > 0)
    {
        GVariantIter *iter;
        const gchar *key;
        GVariant *value;

        g_print ("\n    *** PropertiesChanged signal received. Changed properties:\n");
        g_variant_get (changed_properties,
                    "a{sv}",
                    &iter);
        while (g_variant_iter_loop (iter, "{&sv}", &key, &value))
        {
            gchar *value_str;
            value_str = g_variant_print (value, TRUE);
            g_print ("    ***  %s -> %s\n", key, value_str);
            printf("    *** Currently cached values:\n");
            printf("    *** anIntegerAttribute: %u\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anIntegerAttribute")));
            printf("    *** aStringAttribute: %s\n", g_variant_get_string(g_dbus_proxy_get_cached_property(proxy, "aStringAttribute"), NULL));
            printf("    *** anEnumAttribute: %u\n\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anEnumAttribute")));
            g_free (value_str);
        }
        g_variant_iter_free (iter);
    }
    // END DEBUG
}

void proxy_created(GObject *obj, GAsyncResult *result, gpointer userdata) {
    proxy = FrancaccodegenVerySimpleFrancaInterface_createforBusFinish(result);
    
    // Connect to signal handler.
    FrancaccodegenVerySimpleFrancaInterface_connectToPropertiesChanged(proxy, &on_properties_changed);

    // DEBUG: After proxy has been created, call the methods with test data for testing/example purposes.
    printf("\n");   
    printf("anIntegerAttribute starting value: %u\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anIntegerAttribute")));
    printf("aStringAttribute starting value: \"%s\"\n", g_variant_get_string(g_dbus_proxy_get_cached_property(proxy, "aStringAttribute"), NULL));
    printf("anEnumAttribute starting value: %u\n", g_variant_get_uint32(g_dbus_proxy_get_cached_property(proxy, "anEnumAttribute")));
    printf("\n");   

    printf("Method call to theOnlyMethod. Proxy implementation sending data: %d and %d. Expecting result %d, %d_%d\n", testInput1, testInput2, testInput1 + testInput2, testInput1, testInput2);
    printf("Method call to getColorOfObject. Proxy implementation sending data: %u (COFFEE). Expecting result %u (BLACK)\n", testInput5, BLACK);
    printf("\n"); 
    
    printf("Setting anIntegerAttribute to %u...\n", testInput1);
    printf("Setting aStringAttribute to \"%s\"...\n", testInput3);
    printf("Setting anEnumAttribute to %u...\n", testInput4);
    printf("\n"); 
    
    printf("Method call to anIntegerAttribute getter...\n");
    printf("Method call to aStringAttribute getter...\n");
    printf("Method call to anEnumAttribute getter...\n");
    printf("\n"); 
    
    GAsyncReadyCallback theOnlyMethodFinishPointer = &on_theOnlyMethod__n_n__i_s_finished;
    GAsyncReadyCallback getColorOfObjectFinishPointer = &on_getColorOfObject__u__u_finished;
    GAsyncReadyCallback anIntegerAttributeSetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set_finished;    
    GAsyncReadyCallback aStringAttributeSetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set_finished;
    GAsyncReadyCallback anEnumAttributeSetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set_finished;
    GAsyncReadyCallback anIntegerAttributeGetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get_finished;
    GAsyncReadyCallback aStringAttributeGetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get_finished;
    GAsyncReadyCallback anEnumAttributeGetterPointer = &on_FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get_finished;

    FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_set(proxy, testInput1, anIntegerAttributeSetterPointer);
    FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_set(proxy, testInput3, aStringAttributeSetterPointer);
    FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_set(proxy, testInput4, anEnumAttributeSetterPointer);  
    FrancaccodegenVerySimpleFrancaInterface_theOnlyMethod__n_n__i_s(proxy, testInput1, testInput2, theOnlyMethodFinishPointer); 
    FrancaccodegenVerySimpleFrancaInterface_getColorOfObject__u__u(proxy, testInput5, getColorOfObjectFinishPointer); 
    FrancaccodegenVerySimpleFrancaInterface_anIntegerAttribute_u_get(proxy, anIntegerAttributeGetterPointer);
    FrancaccodegenVerySimpleFrancaInterface_aStringAttribute_s_get(proxy, aStringAttributeGetterPointer);
    FrancaccodegenVerySimpleFrancaInterface_anEnumAttribute_u_get(proxy, anEnumAttributeGetterPointer);
    // END DEBUG
}

int main(int argc, char **argv) {

    // Create pointer to callback function.
    GAsyncReadyCallback proxycreated_pointer = &proxy_created;

    // Connect to D-Bus service.
    FrancaccodegenVerySimpleFrancaInterface_createForBus(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, "Francaccodegen.verySimpleFrancaInterface", "/Francaccodegen/verySimpleFrancaInterface", proxycreated_pointer);

      // Run main loop.
    GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
    g_main_run(mainloop);
    return 0;
}

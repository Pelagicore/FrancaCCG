# -*- Mode: Python -*-

# GDBus - GLib D-Bus Library
#
# Copyright (C) 2008-2011 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General
# Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
#
# Author: David Zeuthen   <davidz@redhat.com>
#  (2014) Jonatan Palsson <jonatan.palsson@pelagicore.com>

import sys

from textwrap import dedent

from . import config
from . import utils
from . import dbustypes

# ----------------------------------------------------------------------------------------------------

SIGNAL_MAX_PARAM = 10

class CodeGenerator:
    def __init__(self, ifaces, namespace, interface_prefix, node_xmls, proxy_h, proxy_cpp, proxy_impl, stub_cpp, stub_h, stub_impl):
        self.ifaces = ifaces
        self.proxy_h = proxy_h
        self.proxy_cpp = proxy_cpp
        self.proxy_impl = proxy_impl
        self.stub_h = stub_h
        self.stub_cpp = stub_cpp
        self.stub_impl = stub_impl
        self.node_xmls = node_xmls

    def emit (self, dest, text, newline = True):
        """ Emit code to the specified file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        dest.write (text)
        if newline:
            dest.write ("\n")

    def emit_h_p (self, text, newline = True):
        """ Emit code to proxy header file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.proxy_h, text, newline)

    def emit_c_p (self, text, newline = True):
        """ Emit code to proxy cpp file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.proxy_cpp, text, newline)
        
        
    def emit_c_p_impl (self, text, newline = True):
        """ Emit code to proxy implementation c file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.proxy_impl, text, newline)



    def emit_h_s (self, text, newline = True):
        """ Emit code to stub header file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.stub_h, text, newline)

    def emit_c_s (self, text, newline = True):
        """ Emit code to stub cpp file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.stub_cpp, text, newline)

    def emit_c_s_impl (self, text, newline = True):
        """ Emit code to stub implementation c file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.stub_impl, text, newline)




    def generate_stub_header(self):
        """ Generate intro for stub header file"""
        self.emit_h_s(dedent('''\
        #include <glib.h>
        #include <gio/gio.h>
        ''').format(**locals()))
  
        for i in range(0, len(self.node_xmls)):
            node_xml = self.node_xmls[i]

            # This will encode the XML introspection data as raw bytes. This is
            # to avoid any formatting issues when embedding the introspection
            # data in the stub header file.
            self.emit_h_s ("static const char interfaceXml%d[] = { " % i, False)
            for char in node_xml:
                self.emit_h_s ("0x%s, " % char.encode("hex"), False)
            self.emit_h_s("0x00") # String null terminator
            self.emit_h_s ("};")

        # For each method, generate function pointer typedef
        for i in self.ifaces:
            for m in i.methods: 
                self.emit_h_s ("typedef void(*{m.camel_name_with_dbus_signature}Signature)({m.pointer_signature});".format(**locals()))

        # Generate the struct which will store all function pointers
        for i in self.ifaces:
            self.emit_h_s(dedent('''
            typedef struct
            {'''))
            for m in i.methods:
                self.emit_h_s ("        {m.camel_name_with_dbus_signature}Signature {m.camel_name_with_dbus_signature}Handler;".format(**locals()))
            self.emit_h_s ("} Handlers_struct;")
           
           
        # Generate the enum used in the function pointer struct
        for i in self.ifaces:
            self.emit_h_s(dedent('''
            typedef enum HandlersEnum
            {'''))
            self.emit_h_s ("        {i.func_sig_enums_string}".format(**locals()))
            self.emit_h_s ("} Handlers_enum;")
           
    
        ## Generate variable definitions and function        
        self.emit_h_s (dedent('''
        GDBusNodeInfo *nodeinfo;
        guint owner_id;
        Handlers_struct methodsStruct;
        '''))
    
        for i in self.ifaces:
    
            self.emit_h_s (dedent('''
            void {i.camel_name}_connect(GBusType bustype);

            void {i.camel_name}_dereference();

            void {i.camel_name}_on_method_call(
                    GDBusConnection *connection,
                    const gchar *sender,
                    const gchar *object_path,
                    const gchar *interface_name,
                    const gchar *method_name,
                    GVariant *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer user_data);

            void {i.camel_name}_on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data);

            void {i.camel_name}_on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data);

            void {i.camel_name}_on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data);

            void register_handler(Handlers_enum e, void* f);

            GVariant* {i.camel_name}_on_get_property (
                    GDBusConnection  *connection,
                    const gchar      *sender,
                    const gchar      *object_path,
                    const gchar      *interface_name,
                    const gchar      *property_name,
                    GError          **error,
                    gpointer          user_data);

            gboolean {i.camel_name}_on_set_property (
                    GDBusConnection  *connection,
                    const gchar      *sender,
                    const gchar      *object_path,
                    const gchar      *interface_name,
                    const gchar      *property_name,
                    GVariant         *value,
                    GError          **error,
                    gpointer          user_data);

            ''').format(**locals()))        
           
           
           
         
    def generate_stub_c(self):
        headerFileName = self.stub_h.name.rsplit("/", 1)[1]
        """ Generate introduction for stub cpp file """
        self.emit_c_s (dedent('''\
        #include "%s"
        #include <stdio.h>
        #include <stdlib.h>
        ''' % headerFileName))

        for i in self.ifaces:
            self.emit_c_s (dedent('''\
            void {i.camel_name}_connect(GBusType bustype) {{
        
                // Create D-Bus Introspection structure from XML
                nodeinfo = g_dbus_node_info_new_for_xml(interfaceXml0, NULL);
                       
                if (nodeinfo == NULL) {{
                    printf("ERROR: Couldn't create introspection data structures from XML: \\n%s\\n", interfaceXml0);
                    exit(1);
                }}    
    
                // Start D-Bus service
                owner_id = g_bus_own_name (bustype,
                                             "{i.name}",
                                             G_BUS_NAME_OWNER_FLAGS_NONE,
                                             {i.camel_name}_on_bus_acquired,
                                             {i.camel_name}_on_name_acquired,
                                             {i.camel_name}_on_name_lost,
                                             NULL,
                                             NULL);
                }}

            void {i.camel_name}_dereference() {{
                g_bus_unown_name (owner_id);
                g_dbus_node_info_unref (nodeinfo);
            }}

            // When bus acquired, register interface in the d-bus connection
            void {i.camel_name}_on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){{
                guint registration_id;
    
                static const GDBusInterfaceVTable interface_vtable =
                {{
                    {i.camel_name}_on_method_call,
                    {i.camel_name}_on_get_property,
                    {i.camel_name}_on_set_property
                }};
    
    
                registration_id = g_dbus_connection_register_object (connection,
                                        "{i.interfaceAddress}",
                                        nodeinfo->interfaces[0],
                                        &interface_vtable,
                                        NULL,  /* user_data */
                                        NULL,  /* user_data_free_func */
                                        NULL); /* GError** */
        
                g_assert (registration_id > 0);

            }}

            // The following functions needs to be here. They do nothing (except printing errors) for now.
            void {i.camel_name}_on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data){{
            }}

            void {i.camel_name}_on_name_lost(GDBusConnection *connection, const gchar *name, gpointer user_data){{
                printf("ERROR: Lost D-Bus name: %s\\n", name);
                exit(1);
            }}

            GVariant* {i.camel_name}_on_get_property (GDBusConnection  *connection,
                                        const gchar      *sender,
                                        const gchar      *object_path,
                                        const gchar      *interface_name,
                                        const gchar      *property_name,
                                        GError          **error,
                                        gpointer          user_data){{

                printf("ERROR: In {i.camel_name}_on_get_property function but we shouldn't have any properties yet(?).\\n");
                return NULL;
            }}

            gboolean {i.camel_name}_on_set_property (GDBusConnection  *connection,
                                        const gchar      *sender,
                                        const gchar      *object_path,
                                        const gchar      *interface_name,
                                        const gchar      *property_name,
                                        GVariant         *value,
                                        GError          **error,
                                        gpointer          user_data){{

                printf("ERROR: In {i.camel_name}_on_set_property function but we shouldn't have any properties yet(?).\\n");
                return FALSE;
            }}
            ''').format(**locals()))

            self.emit_c_s (dedent('''
            // Register method handler function
            void register_handler(Handlers_enum e, void* f){{
                switch (e)
                {{''').format(**locals()))
            for m in i.methods:
                self.emit_c_s ("    case {m.capital_name_with_dbus_signature}:".format(**locals()))
                self.emit_c_s ("        methodsStruct.{m.camel_name_with_dbus_signature}Handler = ({m.camel_name_with_dbus_signature}Signature)f;".format(**locals()))
                self.emit_c_s ("        break;")
            self.emit_c_s (dedent('''
                default:
                    printf("ERROR: No such handler enum defined: %u\\n", e);
                    exit(1);
                }}
            }}

            // Handle method calls
            void {i.camel_name}_on_method_call(GDBusConnection *connection,
                            const gchar *sender,
                            const gchar *object_path,
                            const gchar *interface_name,
                            const gchar *method_name,
                            GVariant *parameters,
                            GDBusMethodInvocation *invocation,
                            gpointer user_data){{
                // TODO needs to compare on other stuff (ie signature) than name, can be collisions
            ''').format(**locals()))
            for m in i.methods:
                self.emit_c_s ('''    if (g_strcmp0 (method_name, "{m.name}") == 0) '''.format(**locals()))
                self.emit_c_s ("    {")

                for a in m.in_args:
                    indexOfArg = str(m.in_args.index(a))
                    self.emit_c_s ('''        {a.ctype_out} {a.nameWithIndex} = {a.g_variant_getter}(g_variant_get_child_value(parameters, {indexOfArg}){a.g_variant_getter_extra_arguments});'''.format(**locals()))

                for a in m.out_args:
                    indexOfArg = str(m.out_args.index(a))
                    self.emit_c_s ('''        {a.ctype_out} {a.nameWithIndex};'''.format(**locals()))

                
                self.emit_c_s ('''        // Call the registered method handler, if one is registered.'''.format(**locals()))
                self.emit_c_s ('''        if (methodsStruct.{m.camel_name_with_dbus_signature}Handler != NULL) {{'''.format(**locals()))
                self.emit_c_s ('''            methodsStruct.{m.camel_name_with_dbus_signature}Handler({m.argument_string});'''.format(**locals()))
                self.emit_c_s ('''        } else {''')
                self.emit_c_s ('''            printf("ERROR: No method handler function registered for method: %s\\n", method_name);''')                
                self.emit_c_s ('''            exit(1);''')            
                self.emit_c_s ('''        }''')
                self.emit_c_s ('''        //Return''')                
                self.emit_c_s ('''        g_dbus_method_invocation_return_value (invocation, g_variant_new ("({m.out_arguments_variant_signature})", {m.out_arguments_string}));'''.format(**locals()))
                self.emit_c_s ('''    } else''')
            self.emit_c_s (dedent('''   
            {{
                printf("ERROR: No such method in registered D-Bus interface. Method name: %s\\n", method_name);
                exit(1);
            }}
                
        }}''').format(**locals()))




    def generate_stub_implementation(self):
        headerFileName = self.stub_h.name.rsplit("/", 1)[1]
        self.emit_c_s_impl ('''#include "%s"''' % headerFileName)
        
        # TODO several interfaces?
        for i in self.ifaces:
            for m in i.methods:
                self.emit_c_s_impl ('''void {m.camel_name_with_dbus_signature}Implementation({m.implementation_signature}){{'''.format(**locals()))
                self.emit_c_s_impl ('''    // Implementation of method {m.name} goes here'''.format(**locals()))
                
                ### DEBUG - SHOULD BE REMOVED!
                self.emit_c_s_impl ('''    // DEBUG CODE'''.format(**locals()))
                self.emit_c_s_impl ('''    *sumOfNumbers_out0 = firstNumber_in0 + secondNumber_in1;'''.format(**locals()))
                self.emit_c_s_impl ('''    gchar* nbr1 = g_strdup_printf("%i", firstNumber_in0);;'''.format(**locals()))
                self.emit_c_s_impl ('''    gchar* nbr2 = g_strdup_printf("%i", secondNumber_in1);;'''.format(**locals()))
                self.emit_c_s_impl ('''    *stringOfNumbers_out1 = g_strjoin("_", nbr1, nbr2, NULL);'''.format(**locals()))
                ###
                
                self.emit_c_s_impl ('''}''')
  

            self.emit_c_s_impl ('''int main(int argc, char **argv) {''')
            self.emit_c_s_impl ('''    // Register method callback functions''')         
            for m in i.methods:
                self.emit_c_s_impl ('''    void(*{m.camel_name_with_dbus_signature}_pointer)({m.pointer_signature});'''.format(**locals()))
                self.emit_c_s_impl ('''    {m.camel_name_with_dbus_signature}_pointer = &{m.camel_name_with_dbus_signature}Implementation;'''.format(**locals()))
                self.emit_c_s_impl ('''    register_handler({m.capital_name_with_dbus_signature}, {m.camel_name_with_dbus_signature}_pointer);'''.format(**locals()))                        
                self.emit_c_s_impl (''''''.format(**locals()))                


            self.emit_c_s_impl (dedent('''
                // Create D-Bus service
                {i.camel_name}_connect(G_BUS_TYPE_SESSION);

                // Create and run main loop
                GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
                g_main_loop_run (mainloop);

                {i.camel_name}_dereference();

                return 0;
            }}''').format(**locals()))




    def generate_proxy_header(self):
        self.emit_h_p(dedent('''
        #include <glib.h>
        #include <gio/gio.h>'''))
        for i in self.ifaces:
            for m in i.methods:
                self.emit_h_p(dedent('''
                void {i.camel_name}_{m.name}(GDBusProxy *proxy, {m.proxy_header_inarg_string}, const GAsyncReadyCallback callback);
 
                void {i.camel_name}_{m.name}_finish(GDBusProxy *proxy, {m.proxy_header_outarg_string}, GAsyncResult *result);''').format(**locals()))
            self.emit_h_p(dedent('''
            void {i.camel_name}_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot);
 
            GDBusProxy* {i.camel_name}_createforBusFinish(GAsyncResult* result);''').format(**locals()))
            
            
            

    def generate_proxy_c(self):
        headerFileName = self.proxy_h.name.rsplit("/", 1)[1]
        self.emit_c_p (dedent('''\
        #include "%s"
        #include <stdio.h>
        ''' % headerFileName))
        
        for i in self.ifaces:
            for m in i.methods:
                self.emit_c_p(dedent('''
                void {i.camel_name}_{m.name}(GDBusProxy *proxy, {m.proxy_header_inarg_string}, const GAsyncReadyCallback callback) {{

                    g_dbus_proxy_call(
                        proxy, 
                        "{m.name}", 
                        g_variant_new ("({m.in_arguments_variant_signature})", {m.in_arguments_string}),
                        G_DBUS_CALL_FLAGS_NONE,
                        -1,
                        NULL,
                        callback,
                        NULL); 
                }}

                void {i.camel_name}_{m.name}_finish (GDBusProxy *proxy, {m.proxy_header_outarg_string}, GAsyncResult *result) {{
                    // Get result from method call from d-bus proxy
                    GVariant *wrapped;
                    wrapped = g_dbus_proxy_call_finish(proxy, result, NULL);
    
                    // Put result from method call in parameter
                ''').format(**locals()))
                for a in m.out_args:
                    indexOfArg = str(m.out_args.index(a))
                    self.emit_c_p('''    GVariant *varOutput{indexOfArg}_variant;'''.format(**locals()))
                    self.emit_c_p('''    varOutput{indexOfArg}_variant = g_variant_get_child_value(wrapped, {indexOfArg});'''.format(**locals()))
                    self.emit_c_p('''    *out_{a.nameWithIndex} = {a.g_variant_getter}(varOutput{indexOfArg}_variant{a.g_variant_getter_extra_arguments});'''.format(**locals()))
                    self.emit_c_p(''''''.format(**locals()))
                self.emit_c_p('''}''')
      
        self.emit_c_p(dedent('''
        
        // This function is called from implementation to create a proxy for the specified D-bus service
        void {i.camel_name}_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot) {{
            g_dbus_proxy_new_for_bus (
                bus_type,
                flags,
                NULL, 
                name,
                objectPath,
                "{i.name}",
                NULL, //Gcancellable
                slot, // GAsyncReadyCallback callback
                NULL); // gpointer user_data
        }}

        // This function is called from implementation to finish creating proxy
        GDBusProxy* {i.camel_name}_createforBusFinish(GAsyncResult* result) {{
            GDBusProxy* proxy = g_dbus_proxy_new_for_bus_finish(result, NULL);
            return proxy;
        }}''').format(**locals()))    
                



    def generate_proxy_implementation(self):
        headerFileName = self.proxy_h.name.rsplit("/", 1)[1]
        self.emit_c_p_impl (dedent('''\
        #include "%s"
        #include <stdio.h>
        
        GDBusProxy* proxy;
        ''' % headerFileName))
        
        ### DEBUG - SHOULD BE REMOVED!
        self.emit_c_p_impl (dedent('''\
        // DEBUG: Input used for testing purposes.
        gint16 testInput1 = 100;
        gint16 testInput2 = 33;
        '''))
        ###
        
        for i in self.ifaces:
            for m in i.methods:
                self.emit_c_p_impl (dedent('''        
                // This function is called from simpleFranca_proxy when method call is finished.
                // It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
                void on_{m.name}_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {{
                ''').format(**locals()))
                for a in m.out_args:
                    indexOfArg = str(m.out_args.index(a))
                    self.emit_c_p_impl ('''    {a.ctype_out} {a.nameWithIndex}_result;'''.format(**locals()))
                self.emit_c_p_impl ('''    {i.camel_name}_{m.name}_finish(proxy, {m.proxy_results_addresses}, result);'''.format(**locals()))
                self.emit_c_p_impl ('''    // result variables now contains the results of the method call.'''.format(**locals()))
 
                    
                ### DEBUG - SHOULD BE REMOVED!
                self.emit_c_p_impl('''    // DEBUG''')
                self.emit_c_p_impl('''    printf("Proxy implementation got result: %d, %s \\n", sumOfNumbers_out0_result, stringOfNumbers_out1_result);''')
                ###
                
                self.emit_c_p_impl("}")

        self.emit_c_p_impl(dedent('''
        // This function is called from {i.camel_name}_proxy when proxy has been created.
        // It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
        void proxy_created(GObject *obj, GAsyncResult *result, gpointer userdata) {{
            proxy = {i.camel_name}_createforBusFinish(result);
            // Proxy has been created.
        ''').format(**locals()))
        
        ### DEBUG - SHOULD BE REMOVED!
        self.emit_c_p_impl('''    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.'''.format(**locals()))
        self.emit_c_p_impl('''    void (*finishPointer)(GObject *obj, GAsyncResult *result, gpointer userdata);'''.format(**locals()))
        self.emit_c_p_impl('''    finishPointer = &on_theOnlyMethod_finished;'''.format(**locals()))
        self.emit_c_p_impl('''    printf("Proxy implementation sending data: %d and %d. Expecting result %d, %d_%d\\n", testInput1, testInput2, testInput1 + testInput2, testInput1, testInput2);'''.format(**locals()))
        self.emit_c_p_impl('''    {i.camel_name}_theOnlyMethod(proxy, testInput1, testInput2, finishPointer);'''.format(**locals()))
        self.emit_c_p_impl('''    //'''.format(**locals()))
        ###

        self.emit_c_p_impl(dedent('''            
        }}

        int main(int argc, char **argv) {{

            // Create pointer to function to call when proxy has been created.
            void (*proxycreated_pointer)(GObject *obj, GAsyncResult *result, gpointer userdata);
            proxycreated_pointer = &proxy_created;
   
            // Connect to D-Bus service.
            {i.camel_name}_createForBus(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, "{i.name}", "{i.interfaceAddress}", proxycreated_pointer);

            // Run main loop.
            GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
            g_main_run(mainloop);
            return 0;
        }}''').format(**locals()))



    def generate(self):
        self.generate_stub_header()
        self.generate_stub_c()
        self.generate_stub_implementation()
        self.generate_proxy_header()
        self.generate_proxy_c()
        self.generate_proxy_implementation()
        
     

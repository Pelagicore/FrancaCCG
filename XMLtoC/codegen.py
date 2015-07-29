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
    def __init__(self, ifaces, namespace, interface_prefix, node_xmls, proxy_h, proxy_cpp, proxy_impl, stub_cpp, stub_h, stub_impl, common_h):
        self.ifaces = ifaces
        self.proxy_h = proxy_h
        self.proxy_cpp = proxy_cpp
        self.proxy_impl = proxy_impl
        self.stub_h = stub_h
        self.stub_cpp = stub_cpp
        self.stub_impl = stub_impl
        self.common_h = common_h
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

    def emit_c_common_h (self, text, newline = True):
        """ Emit code to common header file
            @param newline boolean indicating whether to append a newline to
                           generated code
        """
        self.emit(self.common_h, text, newline)

    def generate_stub_header(self):
        """ Generate intro for stub header file"""
        commonheader = self.common_h.name.rsplit("/", 1)[1]
        self.emit_h_s(dedent('''\
        #include "{commonheader}"
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
            
            for p in i.properties:
                self.emit_h_s (dedent('''{p.ctype_in} {p.camel_name_with_dbus_signature};''').format(**locals()))
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

                // TODO error handling, should use the gerror since it is already here
    
                GVariant *ret;
                ret = NULL;
            ''').format(**locals()))
            
            for p in i.properties:
                self.emit_c_s ('''    if (g_strcmp0 (property_name, "{p.name}") == 0) {{'''.format(**locals()))
                self.emit_c_s ('''        ret = {p.g_variant_constructor}({p.camel_name_with_dbus_signature});'''.format(**locals()))            
                self.emit_c_s ('''    }} else '''.format(**locals()))                            
           
            
            self.emit_c_s ('''    {{'''.format(**locals()))
            self.emit_c_s ('''        printf("ERROR: Interface does not contain property: %s\\n", property_name);'''.format(**locals()))        
            self.emit_c_s ('''        exit(1);'''.format(**locals()))
            self.emit_c_s ('''    }}'''.format(**locals()))            
            self.emit_c_s ('''    return ret;'''.format(**locals()))            
                
                
            self.emit_c_s (dedent('''\
            }}

            gboolean {i.camel_name}_on_set_property (GDBusConnection  *connection,
                                                     const gchar      *sender,
                                                     const gchar      *object_path,
                                                     const gchar      *interface_name,
                                                     const gchar      *property_name,
                                                     GVariant         *value,
                                                     GError          **error,
                                                     gpointer          user_data){{
            ''').format(**locals()))
            
            for p in i.properties:
                
                self.emit_c_s ('''    if (g_strcmp0 (property_name, "{p.name}") == 0)'''.format(**locals()))
                self.emit_c_s ('''    {{'''.format(**locals()))               
                if (p.ctype_in == 'const gchar *'):
                    self.emit_c_s ('''        if (g_strcmp0 ({p.camel_name_with_dbus_signature}, g_variant_get_string (value, NULL)) != 0)'''.format(**locals()))
                    self.emit_c_s ('''        {{'''.format(**locals()))                    
                    self.emit_c_s ('''            {p.camel_name_with_dbus_signature} = g_variant_dup_string (value, NULL);'''.format(**locals()))  
                else:
                    self.emit_c_s ('''        if ({p.camel_name_with_dbus_signature} != {p.g_variant_getter}(value{p.g_variant_getter_extra_arguments}))'''.format(**locals()))
                    self.emit_c_s ('''        {{'''.format(**locals()))                    
                    self.emit_c_s ('''            {p.camel_name_with_dbus_signature} = {p.g_variant_getter}(value);'''.format(**locals()))          
                     
                self.emit_c_s ('''            // Unless com.pelagicore.FrancaCCodeGen.Enum.NoSubscriptions annotation is set to true, send PropertiesChanged signal'''.format(**locals()))   

                if (p.noSubscriptions == False):
                    self.emit_c_s (''''''.format(**locals()))
                    self.emit_c_s ('''            // Annotation is set to FALSE or not set at all. Send signal.'''.format(**locals()))
                    self.emit_c_s ('''            GVariantBuilder *builder;'''.format(**locals()))                    
                    self.emit_c_s ('''            GError *local_error;'''.format(**locals()))
                    self.emit_c_s ('''            local_error = NULL;'''.format(**locals()))                    
                    self.emit_c_s ('''            builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);'''.format(**locals()))   
                    self.emit_c_s (''''''.format(**locals()))
                    self.emit_c_s ('''            g_variant_builder_add (builder,'''.format(**locals()))
                    self.emit_c_s ('''                                   "{{sv}}",'''.format(**locals()))                    
                    self.emit_c_s ('''                                   "{p.name}",'''.format(**locals()))
                    self.emit_c_s ('''                                   {p.g_variant_constructor} ({p.camel_name_with_dbus_signature}));'''.format(**locals()))
                    self.emit_c_s (''''''.format(**locals()))
                    self.emit_c_s ('''            g_dbus_connection_emit_signal (connection,'''.format(**locals()))
                    self.emit_c_s ('''                                           NULL,'''.format(**locals()))
                    self.emit_c_s ('''                                           object_path,'''.format(**locals()))
                    self.emit_c_s ('''                                           "org.freedesktop.DBus.Properties",'''.format(**locals()))
                    self.emit_c_s ('''                                           "PropertiesChanged",'''.format(**locals()))                    
                    self.emit_c_s ('''                                           g_variant_new ("(sa{{sv}}as)",'''.format(**locals()))
                    self.emit_c_s ('''                                                          interface_name,'''.format(**locals()))
                    self.emit_c_s ('''                                                          builder,'''.format(**locals()))
                    self.emit_c_s ('''                                                          NULL),'''.format(**locals()))
                    self.emit_c_s ('''                                           &local_error);'''.format(**locals()))
                    self.emit_c_s (''''''.format(**locals()))
                    self.emit_c_s ('''            g_assert_no_error (local_error);'''.format(**locals()))
                    
                else:
                    self.emit_c_s ('''            // Annotation is set to TRUE. Do not send signal.'''.format(**locals())) 
                
                self.emit_c_s ('''        }}'''.format(**locals()))   
                self.emit_c_s ('''    }} else'''.format(**locals()))               
                        
                       
            self.emit_c_s ('''    {{'''.format(**locals()))     
            self.emit_c_s ('''        printf("ERROR: Interface does not contain property: %s\\n", property_name);'''.format(**locals()))                     
            self.emit_c_s ('''        exit(1);'''.format(**locals()))     
            self.emit_c_s ('''    }}'''.format(**locals()))                                 
            self.emit_c_s ('''    return *error == NULL;'''.format(**locals()))                        
            self.emit_c_s ('''}}'''.format(**locals())) # end getter method


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
                    self.emit_c_s ('''        {a.ctype_out} {a.nameWithIndex};'''.format(**locals()))
                
                self.emit_c_s ('''        // Call the registered method handler, if one is registered.'''.format(**locals()))
                self.emit_c_s ('''        if (methodsStruct.{m.camel_name_with_dbus_signature}Handler != NULL) {{'''.format(**locals()))
                self.emit_c_s ('''            methodsStruct.{m.camel_name_with_dbus_signature}Handler({m.argument_string});'''.format(**locals()))
                self.emit_c_s ('''        } else {''')
                self.emit_c_s ('''            printf("ERROR: No method handler function registered for method: %s\\n", method_name);''')                
                self.emit_c_s ('''            exit(1);''')            
                self.emit_c_s ('''        }''')
                self.emit_c_s ('''        //Return''')                
                self.emit_c_s ('''        g_dbus_method_invocation_return_value (invocation, {m.new_out_arguments_gvariant});'''.format(**locals()))
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
                if i.camel_name == "FrancaccodegenVerySimpleFrancaInterface":
                    if m.name == "theOnlyMethod":
                        self.emit_c_s_impl ('''    // DEBUG CODE'''.format(**locals()))
                        self.emit_c_s_impl ('''    *sumOfNumbers_out0 = firstNumber_in0 + secondNumber_in1;'''.format(**locals()))
                        self.emit_c_s_impl ('''    gchar* nbr1 = g_strdup_printf("%i", firstNumber_in0);;'''.format(**locals()))
                        self.emit_c_s_impl ('''    gchar* nbr2 = g_strdup_printf("%i", secondNumber_in1);;'''.format(**locals()))
                        self.emit_c_s_impl ('''    *stringOfNumbers_out1 = g_strjoin("_", nbr1, nbr2, NULL);'''.format(**locals()))
                        self.emit_c_s_impl ('''    // END DEBUG'''.format(**locals()))
                ###
                
                self.emit_c_s_impl ('''}''')
  

            self.emit_c_s_impl ('''int main(int argc, char **argv) {''')
            self.emit_c_s_impl ('''''')
            #self.emit_c_s_impl ('''    // Declare attributes''')
            #for p in i.properties:
            #    self.emit_c_s_impl ('''    {p.camel_name_with_dbus_signature};'''.format(**locals()))   
            #self.emit_c_s_impl ('''''')      
            self.emit_c_s_impl ('''    // Register method callback functions''')         
            for m in i.methods:
                self.emit_c_s_impl ('''    {m.camel_name_with_dbus_signature}Signature {m.camel_name_with_dbus_signature}_pointer = &{m.camel_name_with_dbus_signature}Implementation;'''.format(**locals()))
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
        commonheader = self.common_h.name.rsplit("/", 1)[1]
        self.emit_h_p(dedent('''
        #include "{commonheader}"
        #include <glib.h>
        #include <gio/gio.h>'''.format(**locals())))
        for i in self.ifaces:
            self.emit_h_p(dedent('''
        
            void {i.camel_name}_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot);
 
            GDBusProxy* {i.camel_name}_createforBusFinish(GAsyncResult* result);
            
            void {i.camel_name}_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer));
            ''').format(**locals()))
            
            for m in i.methods:
                self.emit_h_p(dedent('''
                void {i.camel_name}_{m.camel_name_with_dbus_signature}(GDBusProxy *proxy{m.proxy_header_inarg_string}, const GAsyncReadyCallback callback);
                void {i.camel_name}_{m.camel_name_with_dbus_signature}_finish(GDBusProxy *proxy{m.proxy_header_outarg_string}, GAsyncResult *result, gboolean *success);''').format(**locals()))
            self.emit_h_p('''''')
            for p in i.properties:
                self.emit_h_p(dedent('''
                void {i.camel_name}_{p.camel_name_with_dbus_signature}_set(GDBusProxy *proxy, {p.ctype_in} value, const GAsyncReadyCallback callback);
                void {i.camel_name}_{p.camel_name_with_dbus_signature}_set_finish(GDBusProxy *proxy, GAsyncResult *result, gboolean *success);
                void {i.camel_name}_{p.camel_name_with_dbus_signature}_get(GDBusProxy *proxy, const GAsyncReadyCallback callback);
                void {i.camel_name}_{p.camel_name_with_dbus_signature}_get_finish(GDBusProxy *proxy, {p.ctype_in} *value, GAsyncResult *result, gboolean *success);''').format(**locals()))
            
           
            
            

    def generate_proxy_c(self):
        headerFileName = self.proxy_h.name.rsplit("/", 1)[1]
        self.emit_c_p (dedent('''\
        #include "%s"
        #include <stdio.h>
        #include <stdlib.h>        
        ''' % headerFileName))
        
        for i in self.ifaces:
            for m in i.methods:
                self.emit_c_p(dedent('''
                void {i.camel_name}_{m.camel_name_with_dbus_signature}(GDBusProxy *proxy{m.proxy_header_inarg_string}, const GAsyncReadyCallback callback) {{

                    g_dbus_proxy_call(
                        proxy, 
                        "{m.name}", 
                        {m.new_in_arguments_gvariant},
                        G_DBUS_CALL_FLAGS_NONE,
                        -1,
                        NULL,
                        callback,
                        NULL); 
                }}

                void {i.camel_name}_{m.camel_name_with_dbus_signature}_finish (GDBusProxy *proxy{m.proxy_header_outarg_string}, GAsyncResult *result, gboolean *success) {{
                    // Get result from method call from d-bus proxy
                    GVariant *wrapped;
                    GError *error = NULL;
                    wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

                    if (error != NULL) {{
                        printf("WARNING: Method call to {m.camel_name_with_dbus_signature} did not succeed.\\nGError content: %s\\n", error->message);
                        *success = FALSE;
                    }} else {{
    
                        // Put results from method call in parameter
                ''').format(**locals()))
                for a in m.out_args:
                    indexOfArg = str(m.out_args.index(a))
                    self.emit_c_p('''        GVariant *{a.nameWithIndex}_variant;'''.format(**locals()))
                    self.emit_c_p('''        {a.nameWithIndex}_variant = g_variant_get_child_value(wrapped, {indexOfArg});'''.format(**locals()))
                    self.emit_c_p('''        *out_{a.nameWithIndex} = {a.g_variant_getter}({a.nameWithIndex}_variant{a.g_variant_getter_extra_arguments});'''.format(**locals()))
                    self.emit_c_p(''''''.format(**locals()))
                self.emit_c_p('''        *success = TRUE;'''.format(**locals()))                            
                self.emit_c_p('''    }''')
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
            GError *error = NULL;
            GDBusProxy* proxy = g_dbus_proxy_new_for_bus_finish(result, &error);
            if (error == NULL) {{
                return proxy;
            }} else {{
                printf("ERROR: Cannot create proxy. Server stub is possibly offline.\\nGError content: %s\\nClosing proxy...\\n", error->message);
                exit(1);
                return NULL;
            }}
        }}
        
        
        void {i.camel_name}_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer)) {{
            g_signal_connect (proxy,
                              "g-properties-changed",
                              G_CALLBACK(callback),
                              NULL);
        }}       
        ''').format(**locals()))    
        for p in i.properties:
            self.emit_c_p(dedent('''
            void {i.camel_name}_{p.camel_name_with_dbus_signature}_set(GDBusProxy *proxy, {p.ctype_in} value, const GAsyncReadyCallback callback) {{

                g_dbus_proxy_call(
                    proxy, 
                    "org.freedesktop.DBus.Properties.Set", 
                    g_variant_new ("(ssv)", "{i.name}", "{p.name}", {p.g_variant_constructor}(value)),
                    G_DBUS_CALL_FLAGS_NONE,
                    -1,
                    NULL,
                    callback,
                    NULL); 
            
            }}
            
            void {i.camel_name}_{p.camel_name_with_dbus_signature}_set_finish (GDBusProxy *proxy, GAsyncResult *result, gboolean *success) {{
    
                // Get result from method call from d-bus proxy
                GVariant *wrapped;
                GError *error = NULL;
                wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

                if (error != NULL) {{
                    printf("WARNING: Method call to {p.camel_name_with_dbus_signature}_set did not succeed.\\nGError content: %s\\n", error->message);
                    *success = FALSE;
                }} else {{
                    *success = TRUE;
                }}
            }}
            
            void {i.camel_name}_{p.camel_name_with_dbus_signature}_get(GDBusProxy *proxy, const GAsyncReadyCallback callback) {{

            g_dbus_proxy_call(
                proxy, 
                "org.freedesktop.DBus.Properties.Get", 
                g_variant_new ("(ss)", "{i.name}", "{p.name}"),
                G_DBUS_CALL_FLAGS_NONE,
                -1,
                NULL,
                callback,
                NULL); 
            }}
            
            void {i.camel_name}_{p.camel_name_with_dbus_signature}_get_finish(GDBusProxy *proxy, {p.ctype_in} *value, GAsyncResult *result, gboolean *success) {{
                // Get result from method call from d-bus proxy
                GVariant *wrapped;
                GError *error = NULL;
                wrapped = g_dbus_proxy_call_finish(proxy, result, &error);

                if (error != NULL) {{
                    printf("WARNING: Method call to {p.camel_name_with_dbus_signature}_get did not succeed.\\nGError content: %s\\n", error->message);
                    *success = FALSE;
                }} else {{
                    GVariant *value_variant;
                    value_variant = g_variant_get_child_value(wrapped, 0);  
                    *value = {p.g_variant_getter}(g_variant_get_variant(value_variant){p.g_variant_getter_extra_arguments});
                    *success = TRUE;
                }}
            }}
            ''').format(**locals())) 



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
                void on_{m.camel_name_with_dbus_signature}_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {{
                ''').format(**locals()))
                for a in m.out_args:
                    self.emit_c_p_impl ('''    {a.ctype_out} {a.nameWithIndex}_result;'''.format(**locals()))
                self.emit_c_p_impl ('''    gboolean success = FALSE;'''.format(**locals()))
                self.emit_c_p_impl ('''    {i.camel_name}_{m.camel_name_with_dbus_signature}_finish(proxy{m.proxy_results_addresses}, result, &success);'''.format(**locals()))
                self.emit_c_p_impl ('''    '''.format(**locals()))    
                self.emit_c_p_impl ('''    // success now contains whether method call was successful or not'''.format(**locals()))
                self.emit_c_p_impl ('''    // _result variables now contains the results of the method call.'''.format(**locals()))
                self.emit_c_p_impl ('''    // Implementation goes here'''.format(**locals())) 
                    
                ### DEBUG - SHOULD BE REMOVED!
                if i.camel_name == "FrancaccodegenVerySimpleFrancaInterface":
                    if m.name == "theOnlyMethod":
                        self.emit_c_p_impl('''    // DEBUG''')
                        self.emit_c_p_impl('''    printf("Proxy implementation got result: %d, %s \\n", sumOfNumbers_out0_result, stringOfNumbers_out1_result);''')
                        self.emit_c_p_impl('''    // END DEBUG''')
                    if m.camel_name_with_dbus_signature == "theThird____":
                        self.emit_c_p_impl('''    // DEBUG''')
                        self.emit_c_p_impl('''    printf("Proxy implementation got reply on theThird() method. Yay!\\n");''')
                        self.emit_c_p_impl('''    // END DEBUG''')
                    if m.camel_name_with_dbus_signature == "theFourth__b__":
                        self.emit_c_p_impl('''    // DEBUG''')
                        self.emit_c_p_impl('''    printf("Proxy implementation got reply on theFourth(in gboolean) method. Yay!\\n");''')
                        self.emit_c_p_impl('''    // END DEBUG''')
                    if m.camel_name_with_dbus_signature == "theFifth____d":
                        self.emit_c_p_impl('''    // DEBUG''')
                        self.emit_c_p_impl('''    printf("Proxy implementation got reply on theFifth(out gdouble) method. Yay!\\n");''')
                        self.emit_c_p_impl('''    // END DEBUG''')
                ###
                
                self.emit_c_p_impl("}")


            for p in i.properties:
                self.emit_c_p_impl (dedent('''
                void on_{i.camel_name}_{p.camel_name_with_dbus_signature}_set_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {{
                    gboolean success = FALSE;
    
                    {i.camel_name}_{p.camel_name_with_dbus_signature}_set_finish(proxy, result, &success);
                    // success now contains whether method call was successful or not
                }}
                
                void on_{i.camel_name}_{p.camel_name_with_dbus_signature}_get_finished(GObject *obj, GAsyncResult *result, gpointer userdata) {{
                    {p.ctype_in} {p.camel_name_with_dbus_signature};
                    gboolean success = FALSE;
        
                    {i.camel_name}_{p.camel_name_with_dbus_signature}_get_finish(proxy, &{p.camel_name_with_dbus_signature}, result, &success);
                    // success now contains whether method call was successful or not
                    // {p.camel_name_with_dbus_signature} now contains current value of property.
                    // Implementation goes here    
    
                }}

                '''.format(**locals())))
                
        self.emit_c_p_impl(dedent('''
        void on_properties_changed (GDBusProxy          *proxy,
                                    GVariant            *changed_properties,
                                    const gchar* const  *invalidated_properties,
                                    gpointer             user_data)
        {{
            // Implementation of the handling of the PropertiesChanged signal is done here.
            // Note that local cache is automatically updated and needs not to be implemented here.
        }}


        // This function is called from {i.camel_name}_proxy when proxy has been created.
        // It must have same signature as a GAsyncReadyCallback! void function_name(GObject *source_object, GAsyncResult *res, gpointer user_data)
        void proxy_created(GObject *obj, GAsyncResult *result, gpointer userdata) {{
            proxy = {i.camel_name}_createforBusFinish(result);
            // Proxy has been created.
            
            // Connect to signal handler.
            {i.camel_name}_connectToPropertiesChanged(proxy, &on_properties_changed);
        ''').format(**locals()))
        
        ### DEBUG - SHOULD BE REMOVED!
        for i in self.ifaces:
            for m in i.methods:
                if i.camel_name == "FrancaccodegenVerySimpleFrancaInterface":
                    if m.name == "theOnlyMethod":
                        self.emit_c_p_impl('''    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.'''.format(**locals()))
                        self.emit_c_p_impl('''    void (*finishPointer)(GObject *obj, GAsyncResult *result, gpointer userdata);'''.format(**locals()))
                        self.emit_c_p_impl('''    finishPointer = &on_{m.camel_name_with_dbus_signature}_finished;'''.format(**locals()))
                        self.emit_c_p_impl('''    printf("Proxy implementation sending data: %d and %d. Expecting result %d, %d_%d\\n", testInput1, testInput2, testInput1 + testInput2, testInput1, testInput2);'''.format(**locals()))
                        self.emit_c_p_impl('''    {i.camel_name}_{m.camel_name_with_dbus_signature}(proxy, testInput1, testInput2, finishPointer);'''.format(**locals()))
                        self.emit_c_p_impl('''    // END DEBUG'''.format(**locals()))
                        
                    if m.camel_name_with_dbus_signature == "theThird____":
                        self.emit_c_p_impl('''    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.'''.format(**locals()))
                        self.emit_c_p_impl('''    void (*finishPointer3)(GObject *obj, GAsyncResult *result, gpointer userdata);'''.format(**locals()))
                        self.emit_c_p_impl('''    finishPointer3 = &on_{m.camel_name_with_dbus_signature}_finished;'''.format(**locals()))
                        self.emit_c_p_impl('''    printf("Proxy implementation calling theThird method...\\n");'''.format(**locals()))
                        self.emit_c_p_impl('''    {i.camel_name}_{m.camel_name_with_dbus_signature}(proxy, finishPointer3);'''.format(**locals()))
                        self.emit_c_p_impl('''    // END DEBUG'''.format(**locals()))
                   
                    if m.camel_name_with_dbus_signature == "theFourth__b__":
                        self.emit_c_p_impl('''    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.'''.format(**locals()))
                        self.emit_c_p_impl('''    void (*finishPointer4)(GObject *obj, GAsyncResult *result, gpointer userdata);'''.format(**locals()))
                        self.emit_c_p_impl('''    finishPointer4 = &on_{m.camel_name_with_dbus_signature}_finished;'''.format(**locals()))
                        self.emit_c_p_impl('''    printf("Proxy implementation calling theFourth(in gboolean) method...\\n");'''.format(**locals()))
                        self.emit_c_p_impl('''    {i.camel_name}_{m.camel_name_with_dbus_signature}(proxy, TRUE, finishPointer4);'''.format(**locals()))
                        self.emit_c_p_impl('''    // END DEBUG'''.format(**locals()))
                   
                    if m.camel_name_with_dbus_signature == "theFifth____d":
                        self.emit_c_p_impl('''    // DEBUG: After proxy has been created, call the method with test data for testing/example purposes.'''.format(**locals()))
                        self.emit_c_p_impl('''    void (*finishPointer5)(GObject *obj, GAsyncResult *result, gpointer userdata);'''.format(**locals()))
                        self.emit_c_p_impl('''    finishPointer5 = &on_{m.camel_name_with_dbus_signature}_finished;'''.format(**locals()))
                        self.emit_c_p_impl('''    printf("Proxy implementation calling theFifth(out gdouble) method...\\n");'''.format(**locals()))
                        self.emit_c_p_impl('''    {i.camel_name}_{m.camel_name_with_dbus_signature}(proxy, finishPointer5);'''.format(**locals()))
                        self.emit_c_p_impl('''    // END DEBUG'''.format(**locals()))     
                        
                            
    
    
    
        ###

        self.emit_c_p_impl(dedent('''            
        }}
        
        int main(int argc, char **argv) {{

            // Create pointer to function to call when proxy has been created.
            GAsyncReadyCallback proxycreated_pointer = &proxy_created;
   
            // Connect to D-Bus service.
            {i.camel_name}_createForBus(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, "{i.name}", "{i.interfaceAddress}", proxycreated_pointer);

            // Run main loop.
            GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
            g_main_run(mainloop);
            return 0;
        }}''').format(**locals()))



    def generate_common_header(self):
        # Create a list of enums.
        # Different enum types with the same name should probably not be supported at all, but at present time,
        # no error will be given.
        # For example, if enum FooBar with members = {Foo, Bar} is declared, a subsequent declaration
        # of enum FooBar with members = {Bar, Baz} will result in FooBar = {Foo, Bar, Baz}.
        listOfEnums = []
        for i in self.ifaces:
            for m in i.methods:
                for ia in m.in_args:
                    
                    for a in ia.annotations:
                        # check if annotation is enum, if so, check if name of it is already saved, otherwise process it
                        if a.key.startswith("com.pelagicore.FrancaCCodeGen.Enum."):
                            nameOfEnum = a.key.split(".")[4]
                            nameOfEnumMember = a.key.split(".")[-1]
                            valueOfEnum = a.value
                            listOfEnums.append((nameOfEnum, nameOfEnumMember, valueOfEnum))
                for oa in m.out_args:
                    for a in oa.annotations:
                        # check if annotation is enum, if so, check if name of it is already saved, otherwise process it
                        if a.key.startswith("com.pelagicore.FrancaCCodeGen.Enum."):
                            nameOfEnum = a.key.split(".")[4]
                            nameOfEnumMember = a.key.split(".")[-1]
                            valueOfEnum = a.value
                            listOfEnums.append((nameOfEnum, nameOfEnumMember, valueOfEnum))
            for p in i.properties:
                for a in p.annotations:
                    # check if annotation is enum, if so, check if name of it is already saved, otherwise process it
                    if a.key.startswith("com.pelagicore.FrancaCCodeGen.Enum."):
                        nameOfEnum = a.key.split(".")[4]
                        nameOfEnumMember = a.key.split(".")[-1]
                        valueOfEnum = a.value
                        listOfEnums.append((nameOfEnum, nameOfEnumMember, valueOfEnum))
     
            while listOfEnums:
                currentEnumName = listOfEnums[0][0]
                self.emit_c_common_h('''typedef enum {{'''.format(**locals()))
                enumsOfCurrentType = []
                for e in listOfEnums:
                    if currentEnumName == e[0] and e not in enumsOfCurrentType:
                        self.emit_c_common_h('''    {e[0]}_{e[1]} = {e[2]},'''.format(**locals()))
                        enumsOfCurrentType.append(e)
                self.emit_c_common_h('''}} {currentEnumName}_type;
                '''.format(**locals()))
                listOfEnums = [x for x in listOfEnums if x not in enumsOfCurrentType]



    def generate(self):
        self.generate_stub_header()
        self.generate_stub_c()
        self.generate_stub_implementation()
        self.generate_proxy_header()
        self.generate_proxy_c()
        self.generate_proxy_implementation()
        self.generate_common_header()
        
     

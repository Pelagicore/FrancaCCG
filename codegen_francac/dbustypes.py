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

from . import utils

class Common:
    @staticmethod
    def cSignatureForDbusSignature(sig):
        """
        The returned tuple has the following values, in order:
            - Type for "in"-parameter to generated function
            - Type for "out" parameter to generated function
            - Type for use with D-Bus function
            - function for casting D-Bus type to out-type
            - function for casting out-type to D-Bus type
            - name of glib function to fetch value from gvariant
            - extra arguments to pass to gvariant getter (i.e. ", NULL" for strings)
        """
#TODO fix this. What to keep in this code generator? Optimally, all features of dbus should be supported.
        if sig == 'b':
            return ('gboolean', 'gboolean', 'gboolean', "", "", 'g_variant_get_boolean', "")
        elif sig == 'y':
            return ('guchar', 'guchar', 'guchar', "", "", 'g_variant_get_byte', "")
        elif sig == 'n':
            return ('gint16', 'gint16', 'gint16', "", "", 'g_variant_get_int16', "")
        elif sig == 'q':
            return ('guint16', 'guint16', 'guint16', "", "", 'g_variant_get_uint16', "")
        elif sig == 'i':
            return ('gint32', 'gint32', 'gint32', "", "", 'g_variant_get_int32', "")
        elif sig == 'u':
            return ('guint32', 'guint32', 'guint32', "", "", 'g_variant_get_uint32', "")
        elif sig == 'x':
            return ('gint64', 'gint64', 'gint64', "", "", 'g_variant_get_int64', "")
        elif sig == 't':
            return ('guint64', 'guint64', 'guint64', "", "", 'g_variant_get_uint64', "")
        elif sig == 'd':
            return ('double', 'double', 'double', "", "", 'g_variant_get_double', "")
        elif sig == 's':
            return ('const gchar *', 'const gchar *', 'Glib::ustring', "Glib::ustring", "", 'g_variant_get_string', ", NULL")
        elif sig == 'o':
            return ('std::string', 'std::string', 'Glib::ustring', "", "", "", "")
        elif sig == 'g':
            return ('std::string', 'std::string', 'Glib::ustring', "", "", "", "")
        elif sig == 'ay':
            return ('std::string', 'std::string', 'std::string', "", "", "", "")
        elif sig == 'as':
            return ('std::vector<std::string> ', 'std::vector<std::string>', 'std::vector<Glib::ustring>', "Common::glibStringVecToStdStringVec", "Common::stdStringVecToGlibStringVec", "", "")
        elif sig == 'ao':
            return ('std::vector<std::string> ', 'std::vector<std::string>', 'std::vector<std::string>', "", "", "", "")
        elif sig == 'aay':
            return ('std::vector<std::string> ', 'std::vector<std::string>', 'std::vector<std::string>', "", "", "", "")
        elif sig == 'v':
            return ('Glib::VariantBase', 'Glib::VariantBase', '', '', '', '', '')
        else:
            return (None, None, None, None, None, None, None)

class Annotation:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.annotations = []

class Arg:
    def __init__(self, name, signature):
        self.name = name
        self.signature = signature
        self.annotations = []

    def post_process(self, arg_number, direction):
        if self.name == None:
            self.name = 'unnamed_arg%d'%arg_number
        self.nameWithIndex = self.name + "_" + direction
        
#TODO save index of argument here since it is used at many places
        
        (self.ctype_in, self.ctype_out, self.ctype_get, self.ctype_get_cast, self.ctype_to_dbus, self.g_variant_getter, self.g_variant_getter_extra_arguments) = Common.cSignatureForDbusSignature(self.signature)

        self.ctype_send = lambda name, param, c_class_name: "Glib::Variant<"+self.ctype_get+"> "+name+" = Glib::Variant<"+self.ctype_get+">::create(arg_"+param+");"
        self.cvalue_get = lambda varname, outvar, idx, c_class_name: "Glib::Variant<"+self.ctype_in+"> "+varname+";\n    wrapped.get_child("+varname+","+idx+");\n    "+outvar+" = "+varname+".get();"

        if self.signature == 'as':
            self.ctype_send = lambda name, param, c_class_name: "Glib::Variant<std::vector<Glib::ustring> > "+name+" = Glib::Variant<std::vector<Glib::ustring> >::create(" + c_class_name + "Common::stdStringVecToGlibStringVec(arg_" + param + "));"
            self.cvalue_get = lambda varname, outvar, idx, c_class_name: "Glib::VariantContainerBase "+varname+";\n" +\
                                 "    wrapped.get_child("+varname+", "+idx+");\n" +\
                                 "    " + c_class_name + "Common::unwrapList(".format(**locals())+outvar+", "+varname+");"
        elif self.signature == 'ao':
            self.ctype_send = lambda name, param, c_class_name: "Glib::Variant<std::vector<std::string> > "+name+" = Glib::Variant<std::vector< std::string > >::create_from_object_paths(arg_"+param+");"
            self.cvalue_get = lambda varname, outvar, idx, c_class_name: "Glib::VariantContainerBase "+varname+";\n" +\
                                 "    wrapped.get_child("+varname+", "+idx+");\n" +\
                                 "    " + c_class_name + "Common::unwrapList(".format(**locals())+outvar+", "+varname+");"
        elif self.signature == 'aay':
            self.ctype_send = lambda name, param, c_class_name: "Glib::Variant<std::vector<std::string> > "+name+" = Glib::Variant<std::vector<std::string> >::create(arg_"+param+");"
            self.cvalue_get = lambda varname, outvar, idx, c_class_name: "Glib::VariantContainerBase "+varname+";\n" +\
                                 "    wrapped.get_child("+varname+", "+idx+");\n" +\
                                 "    " + c_class_name + "Common::unwrapList("+outvar+", "+varname+");"
        elif self.signature == 'g':
            self.ctype_send = lambda name, param, c_class_name: "Glib::VariantStringBase "+name+";\n Glib::VariantStringBase::create_signature("+name+", arg_"+param+".c_str());"
        elif self.signature == 'o':
            self.ctype_send = lambda name, param, c_class_name: "Glib::VariantStringBase "+name+";\n Glib::VariantStringBase::create_object_path("+name+", arg_"+param+".c_str());"
        elif self.signature == 'v':
            self.ctype_send = lambda name, param, c_class_name: "Glib::VariantBase params = arg_" + param + ";"
            self.cvalue_get = lambda varname, outvar, idx, c_class_name: 'GVariant *output;\n' +\
                                '    g_variant_get_child(wrapped.gobj(), 0, "v", &output);\n\n' + "    " + outvar + ' = Glib::VariantBase(output);'

        if (self.ctype_in, self.ctype_out) == (None, None):
            print "Unknown signature: " + self.signature

            # default to GVariant
            self.ctype_in  = 'Glib::VariantBase'
            self.ctype_out  = 'Glib::VariantBase'
            self.ctype_send = lambda name, param: "Glib::VariantBase "+name+" = arg_"+param+";"
            self.cvalue_get = lambda varname, outvar, idx: "Glib::VariantBase "+varname+";\n  wrapped.get_child("+varname+","+idx+");\n  "+outvar+" = "+varname+";"

class Method:
    def __init__(self, name):
        self.name = name
        self.in_args = []
        self.out_args = []
        self.annotations = []

    def post_process(self, interface_prefix, cns, cns_upper, cns_lower):
        name = self.name
        self.camel_name = name

        self.name_lower = utils.camel_case_to_uscore(name).lower().replace('-', '_')
        self.name_hyphen = self.name_lower.replace('_', '-')

        arg_count = 0
        for a in self.in_args:
            a.post_process(arg_count, "in" + str(self.in_args.index(a)))
            arg_count += 1

        for a in self.out_args:
            a.post_process(arg_count, "out" + str(self.out_args.index(a)))
            arg_count += 1
        
        # Generate different representations of the method arguments    
        # TODO a nicer solution
        sigListIn = []
        sigListOut = []
        argList = []
        outArgList = []
        inArgList = []
        inArgSig = ""
        outArgSig = ""
        implSig = []
        pointerSig = []
        proxyHeaderInArgs = []
        proxyHeaderOutArgs = []
        proxyImplResults = []
        
        for a in self.in_args:
            sigListIn.append(a.signature)
            argList.append(a.nameWithIndex) #"input"  + str(self.in_args.index(a))
            inArgSig = inArgSig + a.signature
            implSig.append(a.ctype_in + " " + a.nameWithIndex) #" varInput" + str(self.in_args.index(a))
            pointerSig.append(a.ctype_in)
            proxyHeaderInArgs.append(a.ctype_in + " arg_" + a.name) #" arg_varInput" + str(self.in_args.index(a))
            inArgList.append("arg_" + a.name) #"arg_varInput"  + str(self.in_args.index(a)
        for a in self.out_args:
            sigListOut.append(a.signature)
            argList.append("&" + a.nameWithIndex) #"&output" str(self.out_args.index(a))
            outArgList.append(a.nameWithIndex) #"output" + str(self.out_args.index(a))
            outArgSig = outArgSig + a.signature
            implSig.append(a.ctype_out + " *" + a.nameWithIndex) #" *varOutput"+ str(self.out_args.index(a))
            pointerSig.append(a.ctype_out + "*")
            proxyHeaderOutArgs.append(a.ctype_out + " *out_" + a.nameWithIndex) #" *out_varOutput" + a.name + str(self.out_args.index(a))
            proxyImplResults.append("&" + a.nameWithIndex + "_result") #"&res"
        
        sigStr = "__" + "_".join(sigListIn) + "__" + "_".join(sigListOut)


        self.proxy_results_addresses = ", ".join(proxyImplResults) # res0, res1
        self.proxy_header_inarg_string = ", ".join(proxyHeaderInArgs) # gint16 arg_varInput0, gint16 arg_varInput1
        self.proxy_header_outarg_string = ", ".join(proxyHeaderOutArgs) # gint32 *arg_varOutput0
        self.pointer_signature = ", ".join(pointerSig) # gint16, gint16, gint32*
        self.implementation_signature = ", ".join(implSig) # gint16 varInput0, gint16 varInput1, gint32 *varOutput0
        self.in_arguments_variant_signature = inArgSig # nn
        self.out_arguments_variant_signature = outArgSig # i
        self.in_arguments_string = ", ".join(inArgList) # arg_varInput0, arg_varInput1
        self.out_arguments_string = ", ".join(outArgList) # output0, output1, output2
        self.argument_string = ", ".join(argList) # input0, input1, &output0
        self.camel_name_with_dbus_signature = self.name + sigStr
        self.capital_name_with_dbus_signature = self.name.upper() + sigStr.upper()



class Signal:
    def __init__(self, name):
        self.name = name
        self.args = []
        self.annotations = []

    def post_process(self, interface_prefix, cns, cns_upper, cns_lower, containing_iface):
        name = self.name
        self.name_lower = utils.camel_case_to_uscore(name).lower().replace('-', '_')
        self.name_hyphen = self.name_lower.replace('_', '-')
        self.iface_name = containing_iface.name

        arg_count = 0
        for a in self.args:
            a.post_process(arg_count)
            arg_count += 1

class Property:
    def __init__(self, name, signature, access):
        self.name = name
        self.signature = signature
        self.access = access
        self.annotations = []
        self.arg = Arg('value', self.signature)
        self.readable = False
        self.writable = False
        if self.access == 'readwrite':
            self.readable = True
            self.writable = True
        elif self.access == 'read':
            self.readable = True
        elif self.access == 'write':
            self.writable = True
        else:
            raise RuntimeError('Invalid access type %s'%self.access)

        (self.cpptype_in, self.cpptype_out, self.cpptype_get, self.cpptype_get_cast, self.cpptype_to_dbus) = Common.cppSignatureForDbusSignature(signature)

        if (self.cpptype_in, self.cpptype_out) == (None, None):
            print "Unknown signature: " + self.signature

            # default to GVariant
            self.cpptype_in  = 'const Glib::VariantBase &'
            self.cpptype_out  = 'Glib::VariantBase'

    def post_process(self, interface_prefix, cns, cns_upper, cns_lower):
        name = self.name
        self.name_lower = utils.camel_case_to_uscore(name).lower().replace('-', '_')
        self.name_hyphen = self.name_lower.replace('_', '-')
        # don't clash with the GType getter, e.g.: GType foo_bar_get_type (void); G_GNUC_CONST
        if self.name_lower == 'type':
            self.name_lower = 'type_'

        # recalculate arg
        self.arg.annotations = self.annotations
        self.arg.post_process(0)

class Interface:
    def __init__(self, name):
        self.name = name
        self.methods = []
        self.signals = []
        self.properties = []
        self.annotations = []

    def post_process(self, interface_prefix, c_namespace):
        if len(c_namespace) > 0:
            if utils.is_ugly_case(c_namespace):
                cns = c_namespace.replace('_', '')
                cns_upper = c_namespace.upper() + '_'
                cns_lower = c_namespace.lower() + '_'
            else:
                cns = c_namespace
                cns_upper = utils.camel_case_to_uscore(c_namespace).upper() + '_'
                cns_lower = utils.camel_case_to_uscore(c_namespace).lower() + '_'
        else:
            cns = ''
            cns_upper = ''
            cns_lower = ''

        name = self.name
        for prefix in interface_prefix:
            if name.startswith(prefix):
                name = name[len(prefix):]
        self.name_without_prefix = name
        name = utils.strip_dots(name)
        name_with_ns = utils.strip_dots(cns + '.' + name)
        self.camel_name = name_with_ns
        self.ns_upper = cns_upper
        self.name_lower = cns_lower + utils.camel_case_to_uscore(name)
        self.name_upper = utils.camel_case_to_uscore(name).upper()
        self.cpp_namespace_name = self.name_without_prefix.replace(".", "::")
        self.interfaceAddress = "/" + self.name.replace(".", "/")
        if cns != '':
            self.cpp_namespace_name = cns + "::" + self.cpp_namespace_name
        self.cpp_class_name = self.cpp_namespace_name.split("::")[-1]

        self.name_hyphen = self.name_upper.lower().replace('_', '-')

        funcSigEnums = []

        for m in self.methods:
            m.post_process(interface_prefix, cns, cns_upper, cns_lower)
            funcSigEnums.append(m.capital_name_with_dbus_signature)

        self.func_sig_enums_string = ", ".join(funcSigEnums)

        for s in self.signals:
            s.post_process(interface_prefix, cns, cns_upper, cns_lower, self)

        for p in self.properties:
            p.post_process(interface_prefix, cns, cns_upper, cns_lower)
            
        
            

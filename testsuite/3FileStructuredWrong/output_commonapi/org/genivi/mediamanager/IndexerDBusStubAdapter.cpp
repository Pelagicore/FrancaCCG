/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core Unknown.
* Used org.franca.core Unknown.
*
* 
*/
#include "IndexerDBusStubAdapter.h"
#include <org/genivi/mediamanager/Indexer.h>

namespace org {
namespace genivi {
namespace mediamanager {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createIndexerDBusStubAdapter(
                   const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<IndexerDBusStubAdapter>(factory, commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

INITIALIZER(registerIndexerDBusStubAdapter) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(Indexer::getInterfaceId(),
                                                               &createIndexerDBusStubAdapter);
}



IndexerDBusStubAdapterInternal::~IndexerDBusStubAdapterInternal() {
    deactivateManagedInstances();
    IndexerDBusStubAdapterHelper::deinit();
}

void IndexerDBusStubAdapterInternal::deactivateManagedInstances() {

}

const char* IndexerDBusStubAdapterInternal::getMethodsDBusIntrospectionXmlData() const {
    static const std::string introspectionData =
        "<method name=\"getInterfaceVersion\">\n"
            "<arg name=\"value\" type=\"uu\" direction=\"out\" />"
        "</method>\n"

        ""
    ;
    return introspectionData.c_str();
}

CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        IndexerStub,
        CommonAPI::Version
        > IndexerDBusStubAdapterInternal::getIndexerInterfaceVersionStubDispatcher(&IndexerStub::getInterfaceVersion, "uu");








const IndexerDBusStubAdapterHelper::StubDispatcherTable& IndexerDBusStubAdapterInternal::getStubDispatcherTable() {
    return stubDispatcherTable_;
}

const CommonAPI::DBus::StubAttributeTable& IndexerDBusStubAdapterInternal::getStubAttributeTable() {
    return stubAttributeTable_;
}

IndexerDBusStubAdapterInternal::IndexerDBusStubAdapterInternal(
        const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        CommonAPI::DBus::DBusStubAdapter(
                factory,
                commonApiAddress,
                dbusInterfaceName,
                dbusBusName,
                dbusObjectPath,
                dbusConnection,
                false),
        IndexerDBusStubAdapterHelper(
            factory,
            commonApiAddress,
            dbusInterfaceName,
            dbusBusName,
            dbusObjectPath,
            dbusConnection,
            std::dynamic_pointer_cast<IndexerStub>(stub),
            false),
        stubDispatcherTable_({
            }),
        stubAttributeTable_() {

    stubDispatcherTable_.insert({ { "getInterfaceVersion", "" }, &org::genivi::mediamanager::IndexerDBusStubAdapterInternal::getIndexerInterfaceVersionStubDispatcher });
}

const bool IndexerDBusStubAdapterInternal::hasFreedesktopProperties() {
    return false;
}

} // namespace mediamanager
} // namespace genivi
} // namespace org

/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core Unknown.
* Used org.franca.core Unknown.
*
* 
*/
#ifndef ORG_GENIVI_MEDIAMANAGER_Indexer_DBUS_PROXY_H_
#define ORG_GENIVI_MEDIAMANAGER_Indexer_DBUS_PROXY_H_

#include <org/genivi/mediamanager/IndexerProxyBase.h>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusAttribute.h>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace org {
namespace genivi {
namespace mediamanager {

class IndexerDBusProxy: virtual public IndexerProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    IndexerDBusProxy(
                    const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~IndexerDBusProxy() { }

    virtual IndexerStatusAttribute& getIndexerStatusAttribute();


    virtual void getDatabasePath(CommonAPI::CallStatus& callStatus, std::string& output);
    virtual std::future<CommonAPI::CallStatus> getDatabasePathAsync(GetDatabasePathAsyncCallback callback);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:
   CommonAPI::DBus::DBusReadonlyAttribute<IndexerStatusAttribute> indexerStatus_;


};



} // namespace mediamanager
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_MEDIAMANAGER_Indexer_DBUS_PROXY_H_

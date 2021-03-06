/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core Unknown.
* Used org.franca.core Unknown.
*
* 
*/
#ifndef ORG_GENIVI_MEDIAMANAGER_Indexer_STUB_DEFAULT_H_
#define ORG_GENIVI_MEDIAMANAGER_Indexer_STUB_DEFAULT_H_


#include <org/genivi/mediamanager/IndexerStub.h>
#include <sstream>

namespace org {
namespace genivi {
namespace mediamanager {

/**
 * Provides a default implementation for IndexerStubRemoteEvent and
 * IndexerStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class IndexerStubDefault : public virtual IndexerStub {
public:
    IndexerStubDefault();

    IndexerStubRemoteEvent* initStubAdapter(const std::shared_ptr<IndexerStubAdapter>& stubAdapter);

    const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> clientId);





protected:
    class RemoteEventHandler: public virtual IndexerStubRemoteEvent {
     public:
        RemoteEventHandler(IndexerStubDefault* defaultStub);


     private:
        IndexerStubDefault* defaultStub_;
    };
private:
    IndexerStubDefault::RemoteEventHandler remoteEventHandler_;


    CommonAPI::Version interfaceVersion_;
};

} // namespace mediamanager
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_MEDIAMANAGER_Indexer_STUB_DEFAULT_H_

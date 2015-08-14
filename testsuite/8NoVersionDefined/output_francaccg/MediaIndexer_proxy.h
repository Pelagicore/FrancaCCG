
#include "MediaIndexer_common.h"
#include <glib.h>
#include <gio/gio.h>


void OrgGeniviMediamanagerIndexer_createForBus (GBusType bus_type, GDBusProxyFlags flags, const gchar *name, const gchar *objectPath, const GAsyncReadyCallback slot);

GDBusProxy* OrgGeniviMediamanagerIndexer_createforBusFinish(GAsyncResult* result);

void OrgGeniviMediamanagerIndexer_connectToPropertiesChanged(GDBusProxy *proxy, void(*callback)(GDBusProxy*, GVariant*, const gchar* const*, gpointer));


void OrgGeniviMediamanagerIndexer_getDatabasePath____s_u(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void OrgGeniviMediamanagerIndexer_getDatabasePath____s_u_finish(GDBusProxy *proxy, const gchar * *out_output_out0, IndexerError_type *out_e_out1, GAsyncResult *result, gboolean *success);

void OrgGeniviMediamanagerIndexer_stopIndexing____u(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void OrgGeniviMediamanagerIndexer_stopIndexing____u_finish(GDBusProxy *proxy, IndexerError_type *out_e_out0, GAsyncResult *result, gboolean *success);

void OrgGeniviMediamanagerIndexer_startIndexing____u(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void OrgGeniviMediamanagerIndexer_startIndexing____u_finish(GDBusProxy *proxy, IndexerError_type *out_e_out0, GAsyncResult *result, gboolean *success);


void OrgGeniviMediamanagerIndexer_indexerStatus_u_set(GDBusProxy *proxy, IndexerStatus_type value, const GAsyncReadyCallback callback);
void OrgGeniviMediamanagerIndexer_indexerStatus_u_set_finish(GDBusProxy *proxy, GAsyncResult *result, gboolean *success);
void OrgGeniviMediamanagerIndexer_indexerStatus_u_get(GDBusProxy *proxy, const GAsyncReadyCallback callback);
void OrgGeniviMediamanagerIndexer_indexerStatus_u_get_finish(GDBusProxy *proxy, IndexerStatus_type *value, GAsyncResult *result, gboolean *success);

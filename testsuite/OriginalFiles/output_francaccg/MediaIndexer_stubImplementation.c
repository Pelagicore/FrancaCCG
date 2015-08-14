#include "MediaIndexer_stub.h"
void getDatabasePath____s_uImplementation(const gchar * *output_out0, IndexerError_type *e_out1){
    // Implementation of method getDatabasePath goes here
}
void stopIndexing____uImplementation(IndexerError_type *e_out0){
    // Implementation of method stopIndexing goes here
}
void startIndexing____uImplementation(IndexerError_type *e_out0){
    // Implementation of method startIndexing goes here
}
int main(int argc, char **argv) {

    // Register method callback functions
    getDatabasePath____s_uSignature getDatabasePath____s_u_pointer = &getDatabasePath____s_uImplementation;
    register_handler(GETDATABASEPATH____S_U, getDatabasePath____s_u_pointer);

    stopIndexing____uSignature stopIndexing____u_pointer = &stopIndexing____uImplementation;
    register_handler(STOPINDEXING____U, stopIndexing____u_pointer);

    startIndexing____uSignature startIndexing____u_pointer = &startIndexing____uImplementation;
    register_handler(STARTINDEXING____U, startIndexing____u_pointer);


    // Create D-Bus service
    OrgGeniviMediamanagerIndexer_connect(G_BUS_TYPE_SESSION);

    // Create and run main loop
    GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run (mainloop);

    OrgGeniviMediamanagerIndexer_dereference();

    return 0;
}

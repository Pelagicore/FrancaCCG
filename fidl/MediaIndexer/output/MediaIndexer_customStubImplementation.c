#include "MediaIndexer_stub.h"
#include <stdio.h>

void getDatabasePath____s_iImplementation(const gchar * *output_out0, IndexerError_type *e_out1){
    printf("Received remote call to getDatabasePath method.\n");
}
void stopIndexing____iImplementation(IndexerError_type *e_out0){
    // Implementation of method stopIndexing goes here
    printf("Received remote call to stopIndexing method.\n");
}
void startIndexing____iImplementation(IndexerError_type *e_out0){
    printf("Received remote call to startIndexing method.\n");
}
int main(int argc, char **argv) {

    // Register method callback functions
    getDatabasePath____s_iSignature getDatabasePath____s_i_pointer = &getDatabasePath____s_iImplementation;
    register_handler(GETDATABASEPATH____S_I, getDatabasePath____s_i_pointer);

    stopIndexing____iSignature stopIndexing____i_pointer = &stopIndexing____iImplementation;
    register_handler(STOPINDEXING____I, stopIndexing____i_pointer);

    startIndexing____iSignature startIndexing____i_pointer = &startIndexing____iImplementation;
    register_handler(STARTINDEXING____I, startIndexing____i_pointer);


    // Create D-Bus service
    OrgGeniviMediamanagerIndexer_connect(G_BUS_TYPE_SESSION);

    // Create and run main loop
    GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run (mainloop);

    OrgGeniviMediamanagerIndexer_dereference();

    return 0;
}

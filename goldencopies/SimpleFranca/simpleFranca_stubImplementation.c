#include "simpleFranca_stub.h"
void theOnlyMethod__n_n__i_sImplementation(gint16 firstNumber_in0, gint16 secondNumber_in1, gint32 *sumOfNumbers_out0, const gchar * *stringOfNumbers_out1){
    // Implementation of method theOnlyMethod goes here
    // DEBUG CODE
    *sumOfNumbers_out0 = firstNumber_in0 + secondNumber_in1;
    gchar* nbr1 = g_strdup_printf("%i", firstNumber_in0);;
    gchar* nbr2 = g_strdup_printf("%i", secondNumber_in1);;
    *stringOfNumbers_out1 = g_strjoin("_", nbr1, nbr2, NULL);
    // END DEBUG
}
void theSecondMethod__s__sImplementation(const gchar * theString_in0, const gchar * *anotherString_out0){
    // Implementation of method theSecondMethod goes here
}
void getColorOfObject__u__uImplementation(OBJECTLIST_TYPE objectName_in0, COLOR_TYPE *objectColor_out0){
    // Implementation of method getColorOfObject goes here
    // DEBUG CODE
    switch (objectName_in0) {
        case TOMATO:
            *objectColor_out0 = RED;
            break;
        case COFFEE:
            *objectColor_out0 = BLACK;
            break;
        case SKY:
            *objectColor_out0 = BLUE;                   
            break;
    }
    // END DEBUG
}

int main(int argc, char **argv) {

    // Initialize attributes
    anIntegerAttribute_u = 0;
    aStringAttribute_s = "This is the starting string.";
    anEnumAttribute_u = RED;

    // Register method callback functions
    theOnlyMethod__n_n__i_sSignature theOnlyMethod__n_n__i_s_pointer = &theOnlyMethod__n_n__i_sImplementation;
    register_handler(THEONLYMETHOD__N_N__I_S, theOnlyMethod__n_n__i_s_pointer);

    theSecondMethod__s__sSignature theSecondMethod__s__s_pointer = &theSecondMethod__s__sImplementation;
    register_handler(THESECONDMETHOD__S__S, theSecondMethod__s__s_pointer);
    
    getColorOfObject__u__uSignature getColorOfObject__u__u_pointer = &getColorOfObject__u__uImplementation;
    register_handler(GETCOLOROFOBJECT__U__U, getColorOfObject__u__u_pointer);

    // Create D-Bus service
    FrancaccodegenVerySimpleFrancaInterface_connect(G_BUS_TYPE_SESSION);

    // Create and run main loop
    GMainLoop *mainloop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run (mainloop);

    FrancaccodegenVerySimpleFrancaInterface_dereference();

    return 0;
}

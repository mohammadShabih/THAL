// so, we need to catch errors
// certain errors(such as errors with a peripheral)  should cause system
// shutdown. other errors may be variable out of range, variable not in correct
// data format. or too much power being drained, i2c not working 
// for dirvers we have different errors, like adress slave adress not matched,
// or no data sent, or invalid address or memory or something like that
// all of these errors should be logged. 
// function shoudl call errors, and return them, the function that call these
// functions should handle the errors. 

typedef enum {
    no_error, unknown_error, bad_paramter, bad_index, sys_failiure;
}

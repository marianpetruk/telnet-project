#include "SessionAdapter.h"


void SessionAdapter::write(const char* message, ...) {
    va_list vl;
    dprintf(out_descriptor, message, vl);
}
void SessionAdapter::write(std::string &message, ...) {
    va_list vl;
    write(message.c_str(), vl);
}

void SessionAdapter::write_error(const char* message, ...) {
    va_list vl;
    dprintf(out_descriptor, message, vl);
}
void SessionAdapter::write_error(std::string &message, ...) {
    va_list vl;
    write_error(message.c_str(), vl);
}

void SessionAdapter::set_out_descriptor(int new_descriptor) {
    out_descriptor = new_descriptor;
}
int SessionAdapter::get_out_descriptor() {
    return out_descriptor;
}

vm::VariablesMap& SessionAdapter::get_variables_map() {
    return variables_map;
}

cmake_minimum_required(VERSION 3.12)

project(pragma_interfaces)

add_subdirectory(iclient)
add_subdirectory(iserver)
add_subdirectory(ishared)

set_target_properties(iclient PROPERTIES FOLDER module_interfaces)
set_target_properties(iserver PROPERTIES FOLDER module_interfaces)
set_target_properties(ishared PROPERTIES FOLDER module_interfaces)

set_property(GLOBAL PROPERTY PRAGMA_MODULE_interfaces_SKIP_INSTALL 1)
set_property(GLOBAL APPEND PROPERTY PRAGMA_MODULE_interfaces_TARGETS ishared iserver iclient)

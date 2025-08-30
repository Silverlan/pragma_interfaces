include(${CMAKE_SOURCE_DIR}/cmake/pr_common.cmake)

set(PROJ_NAME ishared)
pr_add_library(${PROJ_NAME} SHARED)

pr_add_dependency(${PROJ_NAME} client TARGET PUBLIC)

pr_add_headers(${PROJ_NAME} "include/")
pr_add_sources(${PROJ_NAME} "src/")
pr_add_modules(${PROJ_NAME} "src/")

pr_finalize(${PROJ_NAME})

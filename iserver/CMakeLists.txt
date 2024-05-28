include(${CMAKE_SOURCE_DIR}/cmake/pr_common.cmake)

set(PROJ_NAME iserver)
pr_add_library(${PROJ_NAME} SHARED)

pr_add_dependency(${PROJ_NAME} server TARGET PUBLIC)

pr_add_headers(${PROJ_NAME} "include/")
pr_add_sources(${PROJ_NAME} "src/")

pr_finalize(${PROJ_NAME})

cmake_minimum_required(VERSION 3.16)
project(dspd3 C)

set(CMAKE_C_STANDARD 99)

add_executable(CGgaphs main.c graph_basics.c graph_basics.h graph_traversal.c graph_traversal.h graph_advanced.c graph_advanced.h graph_path_finding.c graph_path_finding.h graph_interface.c graph_interface.h utils.c utils.h graph_search.c graph_search.h)
cmake_minimum_required(VERSION 3.28)
project(ADS_Basics C)

set(CMAKE_C_STANDARD 17)

# ============================================================
# DEFINE ALL PROJECT-WIDE INCLUDE DIRECTORIES
# ============================================================
set(ALL_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        "adt_&&_ds"
        "adt_&&_ds/slist"
        "adt_&&_ds/dlist"
        "adt_&&_ds/clist"
        "adt_&&_ds/stack"
        "adt_&&_ds/queue"
        "adt_&&_ds/tree"
        "adt_&&_ds/hash"
        "adt_&&_ds/graph"
        "adt_&&_ds/heap"
        "adt_&&_ds/pq"
        algorithms
        algorithms/recursion
        algorithms/sorting
        algorithms/graph
        algorithms/dp
)

# ============================================================
# ADT & DS LIBRARY
# ============================================================
set(ADT_DS_SRC
        "adt_&&_ds/slist/slist.c"
        "adt_&&_ds/dlist/dlist.c"
        "adt_&&_ds/clist/clist.c"
        "adt_&&_ds/stack/stack.c"
        "adt_&&_ds/queue/queue.c"
        "adt_&&_ds/tree/tree.c"
        "adt_&&_ds/hash/hashtable.c"
        "adt_&&_ds/graph/graph.c"
        "adt_&&_ds/heap/heap.c"
        "adt_&&_ds/pq/pq.c"
)
add_library(adt STATIC ${ADT_DS_SRC})
target_include_directories(adt PUBLIC ${ALL_INCLUDE_DIRS})

# ============================================================
# ALGORITHMS LIBRARY
# ============================================================
set(ALGO_SRC
        algorithms/recursion/recursion_basics.c
        algorithms/recursion/combinatorics.c
        algorithms/sorting/mergesort.c
        algorithms/sorting/quicksort.c
        algorithms/sorting/heapsort.c
        algorithms/graph/graph_traversal.c
        algorithms/graph/graph_sssp.c
        algorithms/graph/graph_mst.c
        algorithms/dp/dp.c
)
add_library(algorithms STATIC ${ALGO_SRC})
target_include_directories(algorithms PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(algorithms PUBLIC adt)

# ============================================================
# MAIN EXECUTABLE
# ============================================================
add_executable(main_root main.c)
target_link_libraries(main_root algorithms)
target_include_directories(main_root PUBLIC ${ALL_INCLUDE_DIRS})

# ============================================================
# RUNSPACE EXECUTABLES
# ============================================================
function(add_runspace name)
    add_executable(${name} runspaces/${name}/${name}.c)
    target_link_libraries(${name} algorithms)
    target_include_directories(${name} PUBLIC ${ALL_INCLUDE_DIRS})
endfunction()

add_runspace(run_slist)
add_runspace(run_dlist)
add_runspace(run_clist)
add_runspace(run_stack)
add_runspace(run_queue)
add_runspace(run_tree)
add_runspace(run_graph)
add_runspace(run_heap)
add_runspace(run_hash)
# add_runspace(run_pq) # <-- COMMENTED OUT until runspaces/run_pq/run_pq.c is created
add_runspace(run_recursion)
add_runspace(run_sorting)
add_runspace(run_dp)

cmake_minimum_required(VERSION 3.5)
project(include_tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS --save-temps)


find_package(Qt5Widgets)

option(instantiate_widgets "a separate executable for selected widgets" ON)

set(SRCS
    parsepreprocessed.cpp
    collect.cpp
    mainwindow.cpp
    treemodel.cpp
    treeitem.cpp
    filltreemodel.cpp
    actions.cpp
    maincontainer.cpp
    centralwidget.cpp
    detailpanel.cpp
    overviewpanel.cpp
    tableviewheaders.cpp
    tableviewcompilationunits.cpp
    modelcu.cpp
    treepanel.cpp
    plaintextedit.cpp
    )

set(HDRS
    mainwindow.h
    treemodel.h
    treeitem.h
    centralwidget.h
    detailpanel.h
    overviewpanel.h
    tableviewheaders.h
    tableviewcompilationunits.h
    modelcu.h
    treepanel.h
    plaintextedit.h
    )

qt5_wrap_cpp(MOCS mainwindow.h ${HDRS})
qt5_add_resources(RES resources.qrc)

add_library(app STATIC  ${SRCS} ${MOCS} ${RES} )
target_link_libraries(app Qt5::Widgets)

add_executable(include_tree main.cpp )
target_link_libraries(include_tree app Qt5::Widgets)


if(instantiate_widgets)
    add_subdirectory(instantiate_widgets)
endif()


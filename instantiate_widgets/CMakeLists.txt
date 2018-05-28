

function(simple_app name main)
set(execname "inst_${name}")
add_executable(${execname} ${main})
target_link_libraries(${execname}  app Qt5::Widgets)
target_include_directories(${execname}   PRIVATE ${CMAKE_SOURCE_DIR})
endfunction(simple_app)


simple_app( centralwidget main_centralwidget.cpp)
simple_app( detailpanel main_detailpanel.cpp)
simple_app( treepanel main_treepanel.cpp)


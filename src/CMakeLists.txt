set (SOURCES
	MainWindow.cpp
	main.cpp
)

set (HEADERS
	MainWindow.h
)

set (FORMS
	MainWindow.ui
)

qt4_wrap_cpp (SOURCES ${HEADERS})
qt4_wrap_ui (FORMS ${FORMS})

add_executable (przesuwanka ${SOURCES} 
    ${HEADERS} 
    ${FORMS}
    #main.cpp
)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (przesuwanka ${QT_LIBRARIES})

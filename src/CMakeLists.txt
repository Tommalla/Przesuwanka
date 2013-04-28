set (SOURCES
	MainWindow.cpp
	NewGameDialog.cpp
	main.cpp
)

set (HEADERS
	MainWindow.h
	NewGameDialog.h
	constants.h
)

set (FORMS
	MainWindow.ui
	NewGameDialog.ui
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

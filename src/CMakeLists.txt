SET(CMAKE_CXX_FLAGS "-O2 -std=c++11") # -D QT_NO_DEBUG_OUTPUT

set (GUI_SOURCES
	MainWindow.cpp
	NewGameDialog.cpp
)

set (GUI_HEADERS
	MainWindow.h
	NewGameDialog.h
)

set (MOC_SOURCES
	GameHandler.cpp
	GraphicsScene.cpp
	GraphicsTile.cpp
)

set (MOC_HEADERS
	GameHandler.h
	GraphicsScene.h
	GraphicsTile.h
)

set (SOURCES
	main.cpp
	Board.cpp
	Point.cpp
	BitContainer.cpp
	BoardGenerator.cpp
	Game.cpp
	#GraphicsScene.cpp
)

set (HEADERS
	constants.h
	enums.h
	Board.h
	Point.h
	BitContainer.h
	BoardGenerator.h
	Game.h
	#GraphicsScene.h
)

set (FORMS
	MainWindow.ui
	NewGameDialog.ui
)

qt4_wrap_cpp (GUI_SOURCES ${GUI_HEADERS})
qt4_wrap_cpp (MOC_SOURCES ${MOC_HEADERS})
qt4_wrap_ui (FORMS ${FORMS})

add_executable (przesuwanka ${SOURCES} 
	${HEADERS} 
	${FORMS}
	${GUI_SOURCES}
	${GUI_HEADERS}
	${MOC_SOURCES}
	${MOC_HEADERS}
)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (przesuwanka ${QT_LIBRARIES})

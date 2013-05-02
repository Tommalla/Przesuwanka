set (GUI_SOURCES
	MainWindow.cpp
	NewGameDialog.cpp
)

set (GUI_HEADERS
	MainWindow.h
	NewGameDialog.h
)

set (SOURCES
	main.cpp
	Board.cpp
	Point.cpp
	BitContainer.cpp
	BoardGenerator.cpp
	Game.cpp
	GameHandler.cpp
	GraphicsScene.cpp
	GraphicsTile.cpp
)

set (HEADERS
	constants.h
	enums.h
	Board.h
	Point.h
	BitContainer.h
	BoardGenerator.h
	Game.h
	GameHandler.h
	GraphicsScene.h
	GraphicsTile.h
)

set (FORMS
	MainWindow.ui
	NewGameDialog.ui
)

qt4_wrap_cpp (GUI_SOURCES ${GUI_HEADERS})
qt4_wrap_ui (FORMS ${FORMS})

add_executable (przesuwanka ${SOURCES} 
	${HEADERS} 
	${FORMS}
	${GUI_SOURCES}
	${GUI_HEADERS}
)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (przesuwanka ${QT_LIBRARIES})

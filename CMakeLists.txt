cmake_minimum_required(VERSION 3.16)

project(Thunder_Note_Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install")

find_package(Qt6 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appThunder_Note_Client
    main.cpp
)

qt_add_resources(appThunder_Note_Client "resources"
    PREFIX "/"
    FILES
         qtquickcontrols2.conf
)

qt_add_qml_module(appThunder_Note_Client
    URI Thunder_Note_Client
    VERSION 1.0
    SOURCES
        notemodel.h notemodel.cpp
    QML_FILES
        Main.qml
        NoteListView.qml
        EditNote.qml
)

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# set_target_properties(appThunder_Note_Client PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appThunder_Note_Client
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

qt_generate_deploy_qml_app_script(
    TARGET appThunder_Note_Client
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
if (LINUX)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/appImage/notes.desktop ${CMAKE_INSTALL_PREFIX})")
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/appImage/notes.svg ${CMAKE_INSTALL_PREFIX})")
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy /usr/lib/x86_64-linux-gnu/libxcb-cursor.so ${CMAKE_INSTALL_PREFIX}/lib)")
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy /usr/lib/x86_64-linux-gnu/libxcb-cursor.so.0 ${CMAKE_INSTALL_PREFIX}/lib)")
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy /usr/lib/x86_64-linux-gnu/libxcb-cursor.so.0.0.0 ${CMAKE_INSTALL_PREFIX}/lib)")
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink bin/appThunder_Note_Client ${CMAKE_INSTALL_PREFIX}/AppRun)")
    install(CODE "execute_process(COMMAND appimagetool ${CMAKE_INSTALL_PREFIX} ${CMAKE_INSTALL_PREFIX}/../notes.AppImage)")
endif()

target_link_libraries(appThunder_Note_Client
    PRIVATE Qt6::Quick Qt6::Network
)

# include(GNUInstallDirs)
install(TARGETS appThunder_Note_Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

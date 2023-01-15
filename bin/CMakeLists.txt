add_executable(${PROJECT_NAME} sandpile_app.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE bmp)
target_link_libraries(${PROJECT_NAME} PRIVATE console_parser)
target_link_libraries(${PROJECT_NAME} PRIVATE sandpile)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
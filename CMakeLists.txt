cmake_minimum_required(VERSION 3.10)
project(Proyecto_SR38 LANGUAGES C CXX)

# Configuración del estándar
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de salida
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Archivos fuente principales
set(SOURCES_CPP
    "${PROJECT_SOURCE_DIR}/Proyecto_SR38.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Game.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/ConjuntoPersonajesNpc.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/Model.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/Personaje.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/PersonajeNpc.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/Terreno.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/Jugador/Jugador.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/OpenGLClass.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/PixelPerfectRenderer.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/Renderer2D.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/Shader2D.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/Texture2D.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas/stb_image.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Input/InputClass.cpp"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Input/gamepad.c"
    "${PROJECT_SOURCE_DIR}/lib/glad.c"
 "src/Objetos/Graficas/ResourceManager.h" "src/Objetos/Graficas/ResourceManager.cpp")

# Archivos C puros
set(SOURCES_C
    "${PROJECT_SOURCE_DIR}/lib/glad.c"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Input/gamepad.c"
)

# Crear librerías estáticas internas
add_library(glad_static STATIC ${PROJECT_SOURCE_DIR}/lib/glad.c "src/Objetos/Graficas/ResourceManager.h" "src/Objetos/Graficas/ResourceManager.cpp")
set_source_files_properties(${PROJECT_SOURCE_DIR}/lib/glad.c PROPERTIES LANGUAGE C)

add_library(gamepad_static STATIC ${PROJECT_SOURCE_DIR}/src/Objetos/Input/gamepad.c "src/Objetos/Graficas/ResourceManager.h" "src/Objetos/Graficas/ResourceManager.cpp")
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/Objetos/Input/gamepad.c PROPERTIES LANGUAGE C)
target_compile_definitions(gamepad_static PRIVATE GAMEPAD_STATIC_LIB)

# Ejecutable principal
add_executable(${PROJECT_NAME} ${SOURCES_CPP} "src/Objetos/Graficas/ResourceManager.h" "src/Objetos/Graficas/ResourceManager.cpp")

# Directorios de inclusión
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    #"${PROJECT_SOURCE_DIR}/include/glad"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/Objetos"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Entidades/Jugador"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Graficas"
    "${PROJECT_SOURCE_DIR}/src/Objetos/Input"
)

# Vincular bibliotecas
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad_static
    gamepad_static
    "${PROJECT_SOURCE_DIR}/lib/glfw3.lib"
    opengl32
)

# Copiar recursos y DLLs al binario
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/lib/glfw3.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/glfw3.dll"
)



















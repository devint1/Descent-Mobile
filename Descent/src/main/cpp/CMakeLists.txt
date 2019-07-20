cmake_minimum_required(VERSION 3.4.1)

include_directories(../../../../lib)

add_subdirectory(../../../../2d 2d)
add_subdirectory(../../../../3d 3d)
add_subdirectory(../../../../cfile cfile)
add_subdirectory(../../../../fix fix)
add_subdirectory(../../../../iff iff)
add_subdirectory(../../../../io io)
add_subdirectory(../../../../main main)
add_subdirectory(../../../../mem mem)
add_subdirectory(../../../../misc misc)
add_subdirectory(../../../../texmap texmap)
add_subdirectory(../../../../ui ui)
add_subdirectory(../../../../vecmat vecmat)

set(SOURCES
		controls.c
		keyboard.c
		main.c
		motion.c
		mouse.c
		render.c
)

add_library(descent SHARED ${SOURCES})

find_library(log-lib log)
find_library(GLESv1_CM-lib GLESv1_CM)
find_library(EGL-lib EGL)
find_library(dl-lib dl)
find_library(android-lib android)
find_library(OpenSLES-lib OpenSLES)

target_link_libraries(descent ${log-lib})
target_link_libraries(descent ${GLESv1_CM-lib})
target_link_libraries(descent ${EGL-lib})
target_link_libraries(descent ${dl-lib})
target_link_libraries(descent ${android-lib})
target_link_libraries(descent ${OpenSLES-lib})

target_link_libraries(descent cfile)
target_link_libraries(descent main-android)
target_link_libraries(descent main)
target_link_libraries(descent 3d)
target_link_libraries(descent 3d-ogles)
target_link_libraries(descent 2d)
target_link_libraries(descent 2d-ogles)
target_link_libraries(descent fix)
target_link_libraries(descent iff)
target_link_libraries(descent io)
target_link_libraries(descent mem)
target_link_libraries(descent misc)
target_link_libraries(descent texmap)
target_link_libraries(descent texmap-ogles)
target_link_libraries(descent ui)
target_link_libraries(descent vecmat)

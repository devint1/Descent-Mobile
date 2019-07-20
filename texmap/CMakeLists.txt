add_subdirectory(ogles)

set(SOURCES
		ntmap.c
		scanline.c
		tmapflat.c
)

add_library(texmap STATIC ${SOURCES})

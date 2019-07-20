set(SOURCES
		bitbltogles.c
		fontogles.c
		rectogles.c
		scaleogles.c
)

add_library(2d-ogles STATIC ${SOURCES})

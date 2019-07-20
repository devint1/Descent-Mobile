add_subdirectory(ogles)

set(SOURCES
		clipper.c
		draw.c
		globvars.c
		instance.c
		interp.c
		matrix.c
		points.c
		rod.c
		setup.c
		upvecs.c
		vecview.c
)

add_library(3d STATIC ${SOURCES})

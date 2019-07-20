set(SOURCES
		dpmi.c
		ipx.c
		joy.c
		key.c
		mono.c
		mouse.c
		timer.c
)

add_library(io STATIC ${SOURCES})
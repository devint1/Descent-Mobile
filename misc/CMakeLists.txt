set(SOURCES
		byteswap.c
		dstring.c
		error.c
		parsarg.c
		stdlib.c
)

add_library(misc STATIC ${SOURCES})

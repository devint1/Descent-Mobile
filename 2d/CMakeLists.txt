add_subdirectory(ogles)

set(SOURCES
		bitblt.c
		bitmap.c
		box.c
		canvas.c
		circle.c
		cursor.c
		disc.c
		effects.c
		font.c
		gpixel.c
		gr.c
		ibitblt.c
		lbitblt.c
		linear.c
		linearc.c
		line.c
		median.c
		modex.c
		modexc.c
		palette.c
		pcx.c
		pixel.c
		poly.c
		rect.c
		rle.c
		roller.c
		scale.c
		scanline.c
		tmapbits.c
		tpoly.c
		vesa.c
)

add_library(2d STATIC ${SOURCES})

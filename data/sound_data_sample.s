header:
	db	"SND",0		; Format ID
	dd	0		; Format Version
	dd	file_end	; File Size
	dd	0		; File ID

toc:
	dd	materials	; Materials

materials:
	dd	1		; Number of Materials
	dd	material_0

material_0:
	incbin	"data/sin440.wav"

file_end:

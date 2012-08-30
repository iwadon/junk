%macro	wav	4
	db	0		; Type
	db	%1		; Category
	db	%2		; File ID
	db	%3		; Group ID
	incbin	%4		; WAV Filename
	align	4		; (alignment)
%endmacro

;;; Header
	db	"SND",0		; Format Signature
	dd	0		; Format Version
	dd	data_end	; File Size
	dd	0		; File ID
;;; Labels
	dd	1		; Number of Labels
	dd	SE_SIN440_00

SE_SIN440_00:
	wav	12,34,56,"data/sin440.wav"

data_end:

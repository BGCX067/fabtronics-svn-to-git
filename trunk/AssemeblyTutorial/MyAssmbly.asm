
.586
.model flat,c
.stack 100h
.data

.code

doit proc
	; eax will store accumulation (sum)
	; ecx will store the count


	mov eax, 0
	mov ecx, 1

again:

	add eax, ecx
	inc ecx

	cmp ecx,3
	jle again

	ret
doit endp


end



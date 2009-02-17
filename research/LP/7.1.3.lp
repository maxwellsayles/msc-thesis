Maximize
	3 xab + 3 xpab + 2 xbc + 2 xpbc + 4 xac + 4 xpac

Subject To
	xab + xpab + xbc + xpbc <= 10
	xab + xpab + xac + xpac <= 12
	xbc + xpbc + xac + xpac <= 8
	xab + xpbc + xpac <= 6
	xpab + xbc + xpac <= 13
	xpab + xpbc + xac <= 11
\	xab + xpab >= 2
\	xbc + xpbc >= 2
\	xac + xpac >= 2

Bounds 
	xab >= 0
	xpab >= 0
	xbc >= 0
	xpbc >= 0
	xac >= 0
	xpac >= 0

End

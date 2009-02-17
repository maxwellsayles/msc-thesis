Maximize
	\ amount of flow leaving the source
	fsa + fsb + fsc


Subject To

	\ conservation constraints (flow entering is equal to the flow leaving)

	\ node a
	fsa + fba - fad = 0
	
	\ node b
	fsb - fba - fbd = 0

	\ node c
	fsc + fdc - fce = 0

	\ node d
	fad + fbd - fde - fdt = 0

	\ node e
	fce + fde - fet = 0


Bounds

	\ edge constraints
	fsa <= 3
	fsb <= 3
	fsc <= 4
	fad <= 2
	fba <= 10
	fbd <= 1
	fce <= 5
	fdc <= 1
	fde <= 1
	fdt <= 2
	fet <= 5	

	\ non-zero constraints
	fsa >= 0
	fsb >= 0
	fsc >= 0
	fad >= 0
	fba >= 0
	fbd >= 0
	fce >= 0
	fdc >= 0
	fde >= 0
	fdt >= 0
	fet >= 0

End

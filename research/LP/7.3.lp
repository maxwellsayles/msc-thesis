Maximize
	s_al + s_bob + s_chet + s_dan

Subject To

	s_al_alice + s_chet_alice <= 1
	s_al_beatrice  <= 1
	s_al_carol + s_bob_carol + s_dan_carol <= 1
	s_al_danielle + s_bob_danielle <= 1

Bounds

	s_al_alice <= 1
	s_al_beatrice <= 1
	s_al_carol <= 1
	s_al_danielle <= 1
	s_bob_carol <= 1
	s_bob_danielle <= 1
	s_chet_alice <= 1
	s_dan_carol <= 1

	s_al_alice >= 0
	s_al_beatrice >= 0
	s_al_carol >= 0
	s_al_danielle >= 0
	s_bob_carol >= 0
	s_bob_danielle >= 0
	s_chet_alice >= 0
	s_dan_carol >= 0


	s_al <= 1
	s_bob <= 1
	s_chet <= 1
	s_dan <= 1

	s_al >= 0
	s_bob >= 0
	s_chet >= 0
	s_dan >= 0


End

PacifidlogTown_House2_MapScripts::
	.byte 0

PacifidlogTown_House2_EventScript_FanClubYoungerBrother::
	lock
	faceplayer
	dotimebasedevents
	call PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag
	goto_if_set FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, PacifidlogTown_House2_EventScript_ComeBackInXDays
	call_if_set FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_MonAssessment
	call_if_unset FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_FirstMonAssessment
	setflag FLAG_MET_FANCLUB_YOUNGER_BROTHER
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, PacifidlogTown_House2_EventScript_GiveReturn
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_50_TO_99, PacifidlogTown_House2_EventScript_PutInEffort
	goto PacifidlogTown_House2_EventScript_GiveFrustration
	end

PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag::
	goto_if_unset FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	call_if_eq VAR_RESULT, 0, PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM
	return

PacifidlogTown_House2_EventScript_MonAssessment::
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_FirstMonAssessment::
	msgbox PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation, MSGBOX_DEFAULT
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM::
	clearflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	return

PacifidlogTown_House2_EventScript_GiveReturn::
	msgbox PacifidlogTown_House2_Text_AdoringPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_PutInEffort::
	msgbox PacifidlogTown_House2_Text_PutInSomeMoreEffort, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_GiveFrustration::
	msgbox PacifidlogTown_House2_Text_ViciousPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_FRUSTRATION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_ComeBackInXDays::
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox PacifidlogTown_House2_Text_GetGoodTMInXDays, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_HappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox PacifidlogTown_House2_Text_Rurii, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_VeryFriendlyWithTrainer, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_UnhappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_ENCOUNTER
	msgbox PacifidlogTown_House2_Text_Rururi, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation:
	.string "Ejem…\pSoy la persona más importante del CLUB\nde FANS de POKéMON: el hermano menor\lde nuestro PRESIDENTE.\pEstoy aquí disfrutando de unas\nmerecidas vacaciones con mis POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PacifidlogTown_House2_Text_AhYourPokemon:
	.string "¡Ah!\nTu POKéMON…$"
	.string ""

PacifidlogTown_House2_Text_AdoringPokemonTakeThis:
	.string "te quiere mucho. Salta a la vista.\pUn POKéMON tan cariñoso y adorable\nse merece una MT como ésta, ¿no?$"
	.string ""
	.string ""

PacifidlogTown_House2_Text_PutInSomeMoreEffort:
	.string "Mmmm…\nNo está mal, pero tampoco muy bien.\pTendrías que esforzarte un\npoco más, ¿no te parece?$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House2_Text_ViciousPokemonTakeThis:
	.string "tiene una mirada que da miedo.\pUn POKéMON terrorífico como éste\nse merece una MT como ésta.$"
	.string ""
	.string ""

PacifidlogTown_House2_Text_ExplainReturnFrustration:
	.string "Si un POKéMON te quiere mucho,\nel poder de RETROCESO se potencia.\pSi no te quiere, el poder de\nFRUSTRACIÓN es el que aumenta.$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_House2_Text_GetGoodTMInXDays:
	.string "Ah, sí. En pocos días, {STR_VAR_1} o así,\nrecibiré un par de MT flipantes.\pDeberías venir a verme entonces.\nTe daré la MT que convenga mejor\la tu POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""

PacifidlogTown_House2_Text_Rurii:
	.string "AZURILL: Azu, azuriril…$"

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer:
	.string "Parece que se lleva muy bien\ncon su ENTRENADOR.$"
	.string ""

PacifidlogTown_House2_Text_Rururi:
	.string "AZURILL: Azuzú, azuzuzú…$"

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch:
	.string "Parece que no se lleva muy bien\ncon su ENTRENADOR.$"
	.string ""


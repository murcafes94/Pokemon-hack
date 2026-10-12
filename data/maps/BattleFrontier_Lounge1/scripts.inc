BattleFrontier_Lounge1_MapScripts::
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder::
	chooseboxmon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	goto_if_le VAR_0x8005, 90, BattleFrontier_Lounge1_EventScript_AverageTotalIVs       @ Average of 15
	goto_if_le VAR_0x8005, 120, BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs @ Average of 20
	goto_if_le VAR_0x8005, 150, BattleFrontier_Lounge1_EventScript_HighTotalIVs         @ Average of 25
	goto_if_ge VAR_0x8005, 151, BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs     @ Average of > 25
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat::
	goto_if_eq VAR_0x8006, STAT_HP, BattleFrontier_Lounge1_EventScript_HighestIVHP
	goto_if_eq VAR_0x8006, STAT_ATK, BattleFrontier_Lounge1_EventScript_HighestIVAtk
	goto_if_eq VAR_0x8006, STAT_DEF, BattleFrontier_Lounge1_EventScript_HighestIVDef
	goto_if_eq VAR_0x8006, STAT_SPEED, BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	goto_if_eq VAR_0x8006, STAT_SPATK, BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	goto_if_eq VAR_0x8006, STAT_SPDEF, BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	goto_if_le VAR_0x8007, 15, BattleFrontier_Lounge1_EventScript_HighestIVLow
	goto_if_le VAR_0x8007, 25, BattleFrontier_Lounge1_EventScript_HighestIVMid
	goto_if_le VAR_0x8007, 30, BattleFrontier_Lounge1_EventScript_HighestIVHigh
	goto_if_ge VAR_0x8007, 31, BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro:
	.string "¡Llevo 70 años entrenando POKéMON!\n¡Todos me consideran una leyenda viva\ly me rinden sus honores!\p¡Soy el mejor CRIAPOKéMON!\pSi llegas a alcanzar mi maestría,\npodrás reconocer las habilidades\lde un POKéMON nada más verlo.\pTú parece que sabes algo de entrenar.\n¿Te interesa conocer las habilidades\lde tus propios POKéMON?\p¡Venga!\n¡Veamos a esos POKéMON que llevas ahí!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_AverageAbility:
	.string "Mmm…\pDe éste, a grandes rasgos, diría\nque posee habilidades normales.$"
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_BetterThanAverageAbility:
	.string "Mmm…\pDe éste, a grandes rasgos, diría\nque posee buenas habilidades.$"
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_ImpressiveAbility:
	.string "Mmm…\pDe éste, a grandes rasgos, diría que\nposee habilidades impresionantes.$"
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_OutstandingAbility:
	.string "Mmm…\pDe éste, a grandes rasgos, diría que\nposee habilidades extraordinarias.$"
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "Más concretamente, su punto fuerte\nestá en los PS…$"
	.string ""

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "Más concretamente, su punto fuerte\nestá en el ATAQUE…$"
	.string ""

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "Más concretamente, su punto fuerte\nestá en la DEFENSA…$"
	.string ""

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "Más concretamente, su punto fuerte\nestá en el ATAQUE ESPECIAL…$"
	.string ""

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "Más concretamente, su punto fuerte\nestá en la DEFENSA ESPECIAL…$"
	.string ""

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "Más concretamente, su punto fuerte\nestá en la VELOCIDAD…$"
	.string ""

BattleFrontier_Lounge1_Text_StatRelativelyGood:
	.string "Es una característica buena.\nMm… Sí, así la definiría yo.$"
	.string ""

BattleFrontier_Lounge1_Text_StatImpressive:
	.string "Es una característica muy buena.\nMm… Sí, así la definiría yo.$"
	.string ""

BattleFrontier_Lounge1_Text_StatOutstanding:
	.string "Es una característica extraordinaria.\nMm… Sí, así la definiría yo.$"
	.string ""

BattleFrontier_Lounge1_Text_StatFlawless:
	.string "¡Es algo sencillamente perfecto!\nMm… Sí, así lo definiría yo.$"
	.string ""

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice:
	.string "¿Cómo?\n¿Que no tienes tiempo para consejos?\p¡Deberías estar feliz por poder\naprender algo de los mayores!$"
	.string ""
	.string ""
	.string ""

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending:
	.string "Yes, what is it now?\p"
	.string "I have business that needs tending!\n"
	.string "Save it for next time!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon:
	.string "Mmm… ¿Te intrigan las habilidades\nde tus POKéMON?\p¡Venga! ¡Vamos a echarles un vistazo!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_EvenICantTell:
	.string "¡Soy un experto, no un adivino!\n¡No puedo decir nada sobre los POKéMON\lque aún no han roto el cascarón!\p¡Muéstrame un POKéMON!\n¡Lo que necesito ver es un POKéMON!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding:
	.string "¡Este señor me ha dicho\nque mi POKéMON es extraordinario!\l¡Me alegro de haberlo entrenado bien!$"
	.string ""

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt:
	.string "¡Este señor me ha dicho\nque mi POKéMON es extraordinario!\lY eso que no me he esmerado mucho…$"
	.string ""
	.string ""


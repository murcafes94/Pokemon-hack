BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	chooseboxmon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "¡Je, je, je!\n¡Yo puedo decirte lo que piensan los\lPOKéMON sobre esto de los combates!\pPorfa, ¿me dejas ver tus POKéMON?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "¡Ay!\n¡Qué carácter, oye!$"
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow::
	.string "Mmm…\p¡Dice que le gusta combatir!\n¡Aunque le hagan pupa!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow::
	.string "Mmm…\p¡Dice que le gusta combatir!\nPero que si le hacen pupa,\l¡se lo pensará dos veces!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow::
	.string "Mmm…\p¡Dice que le gusta combatir!\nPero que si le hacen pupa,\l¡se reservará!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow::
	.string "Mmm…\p¡Dice que se cuida mucho!\nPero que si le hacen pupa,\l¡se vengará!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow::
	.string "Mmm…\p¡Dice que se cuida mucho,\nle hagan o no daño!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow::
	.string "Mmm…\p¡Dice que se cuida mucho!\nPero que si le hacen pupa,\l¡se reservará!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow::
	.string "Mmm…\p¡Dice que le gusta reservarse!\n¡Y que, si le hacen pupa, no se anda\lcon pamplinas!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow::
	.string "Mmm…\p¡Dice que le gusta reservarse!\nPero que si le hacen pupa,\l¡se lo pensará dos veces!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow::
	.string "Mmm…\p¡Dice que le gusta reservarse!\nLe gusta reservarse, incluso\lsi le hacen mucha pupa.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "¡Qué tontería! ¡Los HUEVOS duermen!\n¡No puedo hablar con los HUEVOS!$"
	.string ""

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "¡Qué ricura!\n¡Esa pequeña dice que puede leerles\lel pensamiento a los POKéMON!$"
	.string ""
	.string ""

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "Me parece a mí que esa niña\ndice cosas la mar de profundas.$"
	.string ""

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "¿Sabes una cosa? \p¡Esa niña juega mucho en la casa roja!$"
	.string ""
	.string ""


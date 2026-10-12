VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_FLUFFY_TAIL
	pokemartlistend

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "En cualquier combate POKéMON,\nun ESPECIAL X es crucial.\pPotencia la fuerza de algunos\nmovimientos, pero sólo durante\lun combate.$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "Parece que no venden por ningún lado\nlibros de estrategia para ganar\len la TIENDA de BATALLA…\pHabrá que fiarse del instinto de una…$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "La NIDO BALL funciona mejor\ncon los POKéMON de menor nivel.\pVERDEGAL es el único lugar\ndonde se puede comprar una.$"
	.string ""
	.string ""
	.string ""


VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
	.string "Déjame que vea a tu POKéMON.\nQuiero saber cuánto te quiere…\pAjá…\nTu POKéMON…$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
	.string "te adora.\nEs que no te puede querer más.\lTanto amor me conmueve hasta a mí.$"
	.string ""
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
	.string "parece muy feliz.\nEs obvio que te quiere un montón.$"
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
	.string "te quiere mucho.\nParece que necesita algo más de cariño.$"
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
	.string "se está acostumbrando a ti.\nParece que tiene confianza en ti.$"
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
	.string "todavía debe acostumbrarse a ti.\nLe traes un poco al fresco.$"
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
	.string "desconfía mucho de ti.\nLos ojos le brillan de forma extraña…\lParece que no le gustas ni un pelo.$"
	.string ""
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
	.string "Ejem, no resulta nada fácil decir esto…\pLo siento, pero tu POKéMON no\nte traga. ¿No te hace sentirte fatal?$"
	.string ""
	.string ""

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
	.string "PIKACHU: ¡Pika, pika!$"


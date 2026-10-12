LilycoveCity_LilycoveMuseum_1F_MapScripts::
	.byte 0

LilycoveCity_LilycoveMuseum_1F_EventScript_Greeter::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Curator::
	lockall
	applymovement LOCALID_MUSEUM_1F_CURATOR, Common_Movement_FacePlayer
	message LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings
	waitmessage
	multichoice 20, 8, MULTI_VIEWED_PAINTINGS, TRUE
	goto_if_eq VAR_RESULT, 0, LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings
	goto_if_eq VAR_RESULT, 1, LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested
	goto_if_eq VAR_RESULT, YES, LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat, MSGBOX_SIGN
	releaseall
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe, MSGBOX_SIGN
	applymovement LOCALID_MUSEUM_1F_CURATOR, LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs
	waitmovement 0
	removeobject LOCALID_MUSEUM_1F_CURATOR
	switch VAR_FACING
	case DIR_NORTH, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth
	case DIR_WEST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest
	case DIR_EAST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast::
	lockall
	applymovement LOCALID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs:
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest:
	walk_left
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast:
	walk_right
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth:
	walk_up
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture::
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SchoolKidM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NinjaBoy::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman1::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman2::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PsychicM::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist2::
	lock
	faceplayer
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MUSEUM_1F_ARTIST_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FatMan::
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum:
	.string "Hola. Estás en el MUSEO de CALAGUA.\pTe rogamos que entres y disfrutes\nde nuestra extraordinaria colección\lde arte sobre temática POKéMON.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings:
	.string "Soy el DIRECTOR de este MUSEO\nde Bellas Artes.\pMe llena de alegría ver que alguien tan\njoven como tú se interesa por el arte.\p¿Ya has visto nuestra colección\nde pintura?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime:
	.string "Entonces no te molesto más.\nTómate el tiempo que quieras.$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings:
	.string "¿Ah, sí? Tengo entendido que\nentrenas POKéMON.\p¿También te gusta el arte?$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat:
	.string "Oh, qué pena…\pEn cualquier caso te agradezco que\nhayas venido a visitar el MUSEO.$"
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe:
	.string "¡Espléndido!\pEn ese caso, ¿te importaría\nacompañarme?$"
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting:
	.string "Éste es un cuadro muy antiguo.\nNecesita una buena restauración…$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery:
	.string "Plasma un paisaje de tiempos antiguos.\nLa escena es extraña y misteriosa.$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman:
	.string "Es un cuadro de una hermosa mujer\ncon un POKéMON en su regazo.$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon:
	.string "Es una pintura de un POKéMON\nlegendario de tiempos remotos.\pEs pura creación artística.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon:
	.string "Es una imagen de unos POKéMON PLANTA\nque se dejan mecer por una suave brisa.\pParecen muy felices.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries:
	.string "Plasma un cesto de BAYAS\ncon un aspecto delicioso.\pÑam, ñam, ¡qué hambre!$"
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica:
	.string "Es una réplica de una escultura\nmuy famosa que representa a\lun antiguo POKéMON PÁJARO.$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone:
	.string "Es una gran POKé BALL esculpida\nen roca basáltica.\pAl parecer se usaba en los festivales\nque se celebraban antiguamente.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText:
	.string "Es una gran losa de piedra cincelada\ncon POKéMON y gran cantidad de\lpequeños caracteres pertenecientes\la un antiguo y desconocido idioma.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_WorksOfMagnificence:
	.string "Hmmm…\n"
	.string "What works of great magnificence…$"

LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts:
	.string "Combatir con POKéMON es\ndivertido, cierto.\pPero no por eso hay que olvidarse\nde alimentar nuestro espíritu\lcontemplando obras de arte.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration:
	.string "Este MUSEO de ARTE alberga\nuna gran colección de pintura.\pY el DIRECTOR es muy amable.\pPara los artistas como yo, este MUSEO\nes una fuente de inspiración.$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty:
	.string "¡Qué señora tan guapa!\n¡Es casi tan guapa como mamá!$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable:
	.string "¡Qué POKéMON tan encantador!\n¡Casi tanto como mi niño!$"
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings:
	.string "Me han dicho que han ampliado\nla colección de este MUSEO de ARTE.\pPor eso he venido a toda máquina.\p¡Los nuevos cuadros están\nen el primer piso!$"
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful:
	.string "Últimamente el DIRECTOR\nestá más contento de lo normal.\pSeguro que le ha pasado algo\nmuy bueno. Sin duda.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings:
	.string "He venido aquí a ver muchas grandes\nobras y aprender de los maestros.\pMi sueño sería exponer mis\ncuadros aquí.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination:
	.string "El MUSEO de ARTE recibe cada vez\nmás turistas.\pLe viene muy bien a CALAGUA.\n¡No, le viene bien a todo HOENN!\pY me han dicho que un ENTRENADOR\nha sido quien ha conseguido las obras.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""


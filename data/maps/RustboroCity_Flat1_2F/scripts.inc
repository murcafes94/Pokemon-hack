RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "Cada día es tan duro…\p¿Que qué es duro?\n¿Hace falta preguntar?\pPues levantarse para ir\na trabajar, claro.\pLlevo fatal lo de madrugar…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "¡Anda, hola!\n¡Te doy la bienvenida a mi casa!\pUna preguntilla… ¿Has\nhecho de canguro alguna vez?\pVerás, acabo de ser padre y lo\ncierto es que estoy algo perdido.\pAhora tengo un problemilla…\nMi hija ANAPEL se ríe muy poco.\pCreo que se reiría más\nsi le dijera algo divertido.\p¿No sabrás alguna expresión\ngraciosa, por casualidad?$"
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
	.string ""

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "He estado diciendo “{STR_VAR_1}”\na ANAPEL para divertirla.\p¿No sabrás de alguna otra expresión\nque tenga más gracia?$"
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "¡Vaya, qué bien!\n¿Y cuál es?$"
	.string ""

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Oh, ¿en serio?\pBueno, pues, si se te ocurre\nalgo, soy todo oídos.$"
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Ah, ya veo.\nPues vamos a oírla, ¿vale?$"
	.string ""

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n{STR_VAR_1}.\p¡Genial! ¡¡¡Se ríe!!!\n¡Qué contento que estoy!$"
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, ya veo.\nPues vamos a oírla, ¿vale?$"
	.string ""

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}.\n{STR_VAR_1}.\pMmmm… No le hace ni pizca de gracia.\nPuede que ANAPEL sea una niña seria…$"
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Así que no se te ocurre nada.\nPues a ver si yo pienso algo…\pMmm…\n¿Qué tal “{STR_VAR_1}”?\lA ver si funciona.$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}.\n{STR_VAR_1}.\pMmmm… No le hace ni pizca de gracia.\nPuede que ANAPEL sea una niña seria…$"
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Así que no se te ocurre nada.\nPues entonces voy a intentar\lhacerle reír con lo que dije antes.\pPero, si tuvieras alguna sugerencia,\nno dudes en decírmelo, ¿vale?$"
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "¡Gracias!\pMuchísimas gracias. ¡Mi querida\nANAPEL se está riendo!\p¿Y sabes qué? No lo parecerá,\npero soy uno de los principales\linvestigadores de DEVON S.A.\pY me gustaría hacer algo\npor ti, pero no sé qué…\pYa sé, te daré más diseños de papel\npintado para las CAJAS del Sistema de\lAlmacenamiento de POKéMON del PC.\pSólo tendrás que elegir “AMIGOS”\nen el menú correspondiente. \pDe esa manera podrás acceder\na los nuevos diseños de papel pintado.$"
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
	.string ""
	.string ""
	.string ""
	.string ""

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "¡Es un MUÑECO de peluche\ncon forma de POKéMON!$"


LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "Yo soy el DISEÑADOR del JUEGO.\p¿Ah, sí? ¿Estás trabajando\nen una POKéDEX?\pCuesta trabajo completarla,\npero tú no desistas.\pY, cuando esté completa,\nven a verme.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "¡Guau! ¡Impresionante!\n¡Impresionantemente impresionante!\p¡Tu POKéDEX está llena del todo!\n¡Deben de encantarte los POKéMON!\pEstoy impresionado.\pSemejante proeza se merece\nun reconocimiento en condiciones.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "¿Eh? ¿Me hablas a mí?\nSoy el PROGRAMADOR.\pMe pregunto cómo serán las\nTRAGAPERRAS por aquí…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "Soy el DISEÑADOR GRÁFICO.\n¿A que los POKéMON de HOENN\lson particularmente interesantes?$"
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "Las PLAYERAS son monas, ¿verdad?\nCombatir contra ellas es de lo\lmás motivador…\pPero que muy motivador…\p¡Y las GEMELAS! ¿No son preciosas?\nLos combates dobles me encantan.\p¡Es que me lo paso de miedo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "No hay nada que me guste más que\nla brisa marina. ¡Qué bien se está!$"
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "Nunca puedes saber quién\nni cuándo te va a desafiar.\pPor eso nunca me voy de casa sin\nmi consola GAME BOY ADVANCE.$"
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "TRETO: Zzz…\pZzz… ¿Eh? ¡Huy, perdón!\n¡Estaba echando una cabezadita!\pHe venido a echar un vistazo a esto\nde los CONCURSOS POKéMON.\pDebo reconocer que parecen la\nmar de entretenidos, pero…\pDirás que soy un purista, pero\nprefiero un buen combate contra\lun ENTRENADOR duro de pelar.\pClaro que para gustos, los colores.\p{PLAYER}{KUN}, espero que a ti te gusten\nlos GIMNASIOS, los CONCURSOS, las\lTIENDAS de BATALLA, ¡vamos, todo!$"
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

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "TRETO: Creo que no se puede ganar\nun CONCURSO sin una buena estrategia.\pYo diría que diseñar estrategias para\nganar CONCURSOS también te ayuda\la mejorar como ENTRENADOR.$"
	.string ""
	.string ""
	.string ""


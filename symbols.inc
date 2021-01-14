const

xpm_ok : ARRAY[0..16+3] OF  pchar = (
'16 16 3 1',
' 	c None',
'.	c #00FF00',
'+	c #00FE00',
'                ',
'                ',
'                ',
'                ',
'             .++',
'           ...++',
'          ..... ',
'  ....   +....  ',
'  ..... .....   ',
'   .... ....    ',
'    ..++.+.     ',
'    ....+.      ',
'     +...       ',
'     ..++       ',
'      ...       ',
'                ');

xpm_cancel : ARRAY[0..16+3] OF  pchar = (
'16 16 3 1',
' 	c None',
'.	c #FF0000',
'+	c #FE0000',
'                ',
'                ',
'  ..            ',
'  ....     .... ',
'  ..+..   ..... ',
'   ............ ',
'    .....+..    ',
'      ....+     ',
'     ..++...    ',
'     .......    ',
'    ..++ ..++   ',
'    ...   +...  ',
'   ..+.   ....  ',
'   ...     ..   ',
'   ...          ',
'                ');

xpm_folder : ARRAY[0..16+17] OF  pchar = (
'16 16 17 1',
' 	c None',
'.	c #DA872B',
'+	c #DB9833',
'@	c #DAA635',
'#	c #DBB033',
'$	c #E6C865',
'%	c #E8CA71',
'&	c #F2D033',
'*	c #F4D650',
'=	c #F6DA66',
'-	c #F7DF78',
';	c #F6DE86',
'>	c #F5DD95',
',	c #F7E5AA',
'''	c #F9F1CF',
')	c #FDF9EA',
'!	c #FDFDF6',
'                ',
'                ',
'                ',
' #$$$$$#        ',
' #!!!!!)%%%%%%  ',
' #!;>,,!!)))!!# ',
' @!>;%$$>%%%%)# ',
' @)>>%'')!!!))!@ ',
' @!!!!!'';;-==''@ ',
' +!'',,>;-=***''+ ',
' +),,>;-==*&&''+ ',
' .!,;--=**&&&''+ ',
' +),,>>;%;$$-''. ',
'  ............. ',
'                ',
'                ');

xpm_new : ARRAY[0..16+17] OF  pchar = (
'16 16 17 1',
'  c #2E65BB',
'. c #3A79C3',
'X c #4583C5',
'o c #4C89C5',
'O c #538ECC',
'+ c #52B3F9',
'@ c #5FBEFE',
'# c #7CB1E4',
'$ c #92D1FD',
'% c #B5D9F8',
'& c #C1D8F8',
'* c #CDE2FC',
'= c #D7E7FB',
'- c #DDEAF8',
'; c #E8F0F9',
': c #F1F6F9',
'> c None',
'>>oOoOoOooo.>>>>',
'>X:::;:;:;-#O>>>',
'>o:***%*&&:%#O>>',
'>o:*=****%:*=#X>',
'>o:*****&%-::;.>',
'>o:==*=**%&%&:X>',
'>o;===*=**%%%:X>',
'>o:====*=**%*:X>',
'>X;=====****%;.>',
'>X:======****:X>',
'>X;=*=*=*****: >',
'>.;+@+++++++@:.>',
'>.-@$$$$$$$$#: >',
'> ;@@@@@@@@@@: >',
'> ;-----;:;::: >',
'>>  .   .   . >>'
);

xpm_all_new : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #4575C7',
'. c #5485CB',
'X c #4877C8',
'o c #4D7CC9',
'O c #5C8CCF',
'+ c #6295CD',
'@ c #97C0E8',
'# c #D2E5FD',
'$ c #AFD0F3',
'% c #D3E6FD',
'& c #ECF4FB',
'* c #ECF4FC',
'= c #C4DDFA',
'- c None',
'; c #4279C4',
': c #4D80C7',
':.....o;--------',
'.****#*O:-------',
'.*##@#*#@;------',
'X*#####**+------',
'.*####$@@@OO+:--',
'.*####@&&&&&&@o-',
'.**###@&%==$&=@:',
'.*#*##@&%%=$&&&O',
'.**##*@&%%===$&O',
'X*####@&%%%%=$&O',
'.*****@&%%%%==&O',
'oo    O&%&%%%=&O',
'------O&%&%%%=&O',
'------O%%%%%%=&O',
'------X&&&&&&&&X',
'------oXXXXXXXXX'
);

xpm_reopen : ARRAY[0..16+17] OF  pchar = (
'16 16 17 1',
' 	c None',
'.	c #3C698D',
'+	c #647A86',
'@	c #4F7FCA',
'#	c #5C8ECD',
'$	c #DB8D2F',
'%	c #70A0C2',
'&	c #929A9D',
'*	c #DFB24D',
'=	c #9CC1DF',
'-	c #E6C23F',
';	c #E6D9A3',
'>	c #C3DCF6',
',	c #F6DC74',
'"	c #F6E090',
')	c #E6EFF9',
'!	c #F8F9F2',
' &&&+...+&%%#   ',
' &&&&)>=+.)))=@ ',
' &++...=>%.>!>=@',
'      =.==.>))!@',
'      =.%=.>>=)#',
'-*,.....%%.....#',
'-!!!..=%%%%=..&@',
'-!"";..=%%=..>)@',
'*!""*$..==..$$)@',
'-!***;)....!!$!@',
'*!!!!!""..""!$)@',
'*!"""""";;;;!$@@',
'$!"""",,,,,-;$  ',
'$!""",,,,---;$  ',
'$!""""""",,,;$  ',
'$$$$$$$$$$$$$$  ');

xpm_open : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #D99032',
'. c #DAAC36',
'X c #F4D967',
'o c #E2BB5B',
'O c #5A8ACD',
'+ c #5F96CC',
'@ c #F7E494',
'# c #EAD790',
'$ c #92BCE5',
'% c #D1E5FD',
'& c #F4F8FB',
'* c #DCE5E4',
'= c #AFD0F3',
'- c None',
'; c #4279C4',
': c #76809C',
'------$$$$OO+;--',
'------$&&&%&&$+-',
'------$&%=%=&%$;',
'------$&%%%=%&&O',
'------$&%%%%==&O',
'.ooooX$&%%%%%=%O',
'.&&&&&$&%%%%%=&O',
'.&@@@@O&%%%%%%&O',
'.&#@o . .  . .&O',
'.&ooo#&&&&&%& &O',
' &&&&&@@@@@#* &O',
'.&@@@@######* ++',
' &@@@X@@XXXX* --',
' &@@@#XXXXXo@ --',
' *@@X##XXXoX* --',
'              --'
);

xpm_all_open : ARRAY[0..18+15] OF  pchar = (
'18 18 15 1',
' 	c None',
'.	c #92BCE5',
'+	c #5A8ACD',
'@	c #5F96CC',
'#	c #4279C4',
'$	c #F4F8FB',
'%	c #D1E5FD',
'&	c #AFD0F3',
'*	c #DAAC36',
'=	c #E2BB5B',
'-	c #F4D967',
';	c #F7E494',
'>	c #EAD790',
',	c #D99032',
'''	c #DCE5E4',
'        ....++@#  ',
'        .$$$%$$.@ ',
'      ....++@#$%.#',
'      .$$$%$$.@$$+',
'      .$%&%&$%.#$+',
'      .$%%%&%$$+%+',
'      .$%%%%&&$+$+',
'*====-.$%%%%%&%+$+',
'*$$$$$.$%%%%%&$+$+',
'*$;;;;+$%%%%%%$+$+',
'*$>;=,*,*,,*,*$+$+',
'*$===>$$$$$%$,$+@@',
',$$$$$;;;;;>'',$+  ',
'*$;;;;>>>>>>'',@@  ',
',$;;;-;;----'',    ',
',$;;;>-----=;,    ',
','';;->>---=-'',    ',
',,,,,,,,,,,,,,    '
);

xpm_all_reopen : ARRAY[0..18+17] OF  pchar = (
'18 18 17 1',
' 	c None',
'.	c #3C698D',
'+	c #5A7484',
'@	c #4A78C3',
'#	c #5B8ECE',
'$	c #8C9597',
'%	c #70A0C2',
'&	c #D99130',
'*	c #D9AC2F',
'=	c #94BCDE',
'-	c #A9C0D0',
';	c #E0BC5B',
'>	c #E8D791',
',	c #F4D966',
'"	c #CEE2F9',
')	c #F8E491',
'!	c #F0F6F8',
'        ====###@  ',
'  $$$$+..+$!"!!=# ',
'  $$$-''=+.##@!"=@',
'  $+++..="%.!=#!!#',
'      =!.-=.!"=@!#',
'      =!.%=."!!#"#',
'    .....%%.....!#',
'*;;;;..=%%%%=..$!#',
'*!!!!!..=%%-..!#!#',
'*!))))#..-=.."!#!#',
'*!>);&*&....&*!#!#',
'*!;;;>!!!.."!&!###',
'&!!!!!)))))>!&!#  ',
'*!))))>>>>>>!&##  ',
'&!))),)),,,,!&    ',
'&!)))>,,,,,;)&    ',
'&!)),>>,,,;,!&    ',
'&&&&&&&&&&&&&&    ');

xpm_save : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #366BBC',
'. c #88C062',
'X c black',
'o c #3567B2',
'O c #4C7BC2',
'+ c #6E95D1',
'@ c #77A0DE',
'# c #7AA3E2',
'$ c #C2DCBF',
'% c #8FACD6',
'& c #91B0DF',
'* c #B6CCED',
'= c #C9DAF4',
'- c #DAE6F7',
'; c #F3F7FD',
': c None',
'  ooXXXXXXXXXO::',
' =-;;;;-;;;;-*O:',
'o-&;;+;;;;;;-*=X',
'X=#;;+-;;;;--@=X',
'X=#;;+-;;;---@*X',
'X=#---;;;--=-@&X',
'X=#+++++++++++*X',
'X=##@@@@@+@@+@%X',
'X=##@@@@@@@@+@%X',
'X*###%@%@@@@@+%X',
'X*#;;;;;;;;;;+%o',
'X*%;........;+%X',
'X*&;$$$$$$$$;++X',
'X*#;........;++o',
'o**;;;;;;;;;;%+o',
'  XXXXXXXXoXoooo'
);

xpm_all_save : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #8EC461',
'. c #668FCC',
'X c #5983C2',
'o c #4371B6',
'O c #91B2E4',
'+ c #7095D1',
'@ c #6A93D2',
'# c #94B4E9',
'$ c #98B7E3',
'% c #B2CBED',
'& c #F6FAF9',
'* c #FFFFFB',
'= c #C5E3B4',
'- c None',
'; c #205AAD',
': c #3368BA',
'----------------',
'-.O.O.....;-----',
'-.O*O****O.-----',
'-.O++$$+++O.;---',
'-X$+%&%&&&&$.---',
'-.Oo$++++@+++@;-',
'-XOO$@%&%&&&&#@-',
'-XO+%@#&+&&&&#@-',
'-XOO+@%&&&&&&#o-',
'-XO@$@###$++#+@-',
'-:X@#@#++++@++o-',
'---X$@$&&&&&&$o-',
'---:o@#& =  &+o-',
'-----@%&====&$o-',
'-----:@+=+@@@oo-',
'----------------'
);

xpm_redo : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #C1A20C',
'. c #BFA217',
'X c #C4A203',
'o c #DAC407',
'O c #E9D319',
'+ c #F0DB2E',
'@ c #F7E22E',
'# c #F8E96F',
'$ c #E2CF4E',
'% c #EADB66',
'& c #FAF1A7',
'* c #C2A61D',
'= c None',
'- c #A99102',
'; c #BF9D00',
': c #BBA11B',
'=========X======',
'=========XX=====',
'=========X&X====',
'=====: .XX@&X===',
'====..####@@&X==',
'==-.$#$O@@@@@&X=',
'==.$+OOO@@@@@@&X',
'= X#oOOOooo@@#X=',
'=.#ooO#####o#X-=',
'=X#o#XXXXX##X===',
'=X##.;-==X#X====',
'=X&X=====XX=====',
'=.#X=====X======',
'=*$$-===========',
'==:%;===========',
'==-**==========='
);

xpm_undo : ARRAY[0..16+16] OF  pchar = (
'16 16 16 1',
'  c #C1A20C',
'. c #BFA217',
'X c #C4A203',
'o c #DAC407',
'O c #E9D319',
'+ c #F0DB2E',
'@ c #F7E22E',
'# c #F8E96F',
'$ c #E2CF4E',
'% c #EADB66',
'& c #FBF3AD',
'* c #F2E788',
'= c None',
'- c #A99102',
'; c #C1A313',
': c #BBA11B',
'======X=========',
'=====XX=========',
'====X&X=========',
'===X&@XX..:=====',
'==X&@@####..-===',
'=X&@@+@+O+$$.-==',
'X&@@@@@@OOO$$.==',
'-X#@@XooOOOo#X =',
'=-X#o#####Ooo#.=',
'===X##XXXXX#o#X=',
'====X#X==-;.#*X=',
'=====XX=====X&X=',
'======X=====X$.=',
'===========-$$;=',
'===========;%:==',
'===========;;-=='
);

xpm_right : ARRAY[0..15+16] OF  pchar = (
'16 15 16 1',
'  c #C1A20C',
'. c #BFA217',
'X c #C4A203',
'o c #DAC407',
'O c #E9D319',
'+ c #F0DB2E',
'@ c #F7E22E',
'# c #F8E96F',
'$ c #E2CF4E',
'% c #EADB66',
'& c #FAF1A7',
'* c #C2A61D',
'= c None',
'- c #A99102',
'; c #BF9D00',
': c #BBA11B',
'================',
'=====X==========',
'=====XX=========',
'=====X&X========',
'=====X@&X=======',
'=====X@@&X======',
'=====X@@@&X=====',
'=====X@@@@&X====',
'=====X@@@#X=====',
'=====X@@#X-=====',
'=====X@#X=======',
'=====X#X========',
'=====XX=========',
'=====X==========',
'================'
);

xpm_left : ARRAY[0..15+16] OF  pchar = (
'16 15 16 1',
'  c #C1A20C',
'. c #BFA217',
'X c #C4A203',
'o c #DAC407',
'O c #E9D319',
'+ c #F0DB2E',
'@ c #F7E22E',
'# c #F8E96F',
'$ c #E2CF4E',
'% c #EADB66',
'& c #FBF3AD',
'* c #F2E788',
'= c None',
'- c #A99102',
'; c #C1A313',
': c #BBA11B',
'================',
'==========X=====',
'=========XX=====',
'========X&X=====',
'=======X&@X=====',
'======X&@@X=====',
'=====X&@@@X=====',
'====X&@@@@X=====',
'====-X#@@XX=====',
'=====-X#@@X=====',
'=======X#@X=====',
'========X#X=====',
'=========XX=====',
'==========X=====',
'================'
);


xpm_up : ARRAY[0..16+6] OF  pchar = (
'15 16 6 1',
' 	c None',
'.	c #C4A203',
'+	c #A99102',
'@	c #FAF1A7',
'#	c #F8E96F',
'$	c #F7E22E',
'               ',
'               ',
'               ',
'               ',
'       .       ',
'     +.@.      ',
'     .#$@.     ',
'    .#$$$@.    ',
'   .#$$$$$@.   ',
'  .#$$$$$$$@.  ',
' ............. ',
'               ',
'               ',
'               ',
'               ',
'               '
);

xpm_down : ARRAY[0..16+6] OF  pchar = (
'15 16 6 1',
' 	c None',
'.	c #C4A203',
'+	c #F8E96F',
'@	c #F7E22E',
'#	c #FAF1A7',
'$	c #A99102',
'               ',
'               ',
'               ',
'               ',
'               ',
' ............. ',
'  .+@@@@@@@#.  ',
'   .+@@@@@#.   ',
'    .+@@@#.    ',
'     .+@#.     ',
'     $.#.      ',
'       .       ',
'               ',
'               ',
'               ',
'               '
);

xpm_red : ARRAY[0..14+16] OF  pchar = (
'16 14 16 1',
'  c #380001',
'. c #520000',
'X c #5E0007',
'o c #670006',
'O c #6C0003',
'+ c #780206',
'@ c #830005',
'# c #8C0004',
'$ c #9D0007',
'% c #920008',
'& c #BA0009',
'* c #B00714',
'= c #A4181B',
'- c #E05659',
'; c #FFD1D4',
': c None',
'::::::::::::::::',
'::::::::::::::::',
'::::::::::::::::',
'::::::&*$#::::::',
':::::&-*$@o:::::',
'::::&-;=#+X ::::',
'::::**=%@O. ::::',
'::::$$#@o.  ::::',
'::::#@+oX   ::::',
':::::oX.   :::::',
'::::::    ::::::',
'::::::::::::::::',
'::::::::::::::::',
'::::::::::::::::'
);

xpm_green : ARRAY[0..14+15] OF  pchar = (
'16 14 15 1',
'  c #003600',
'. c #003700',
'X c #005700',
'o c #007200',
'O c #008A00',
'+ c #008F00',
'@ c #0BA90B',
'# c #00BF00',
'$ c #04C404',
'% c #55E055',
'& c #D1FFD1',
'* c #003A00',
'= c #006F00',
'- c #00C600',
'; c None',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;-#@@O=;;;;;',
';;;;-$%@+oo=;;;;',
';;;;#%&@+oX.;;;;',
';;;;@@@++oX ;;;;',
';;;;@++ooX  ;;;;',
';;;;O+ooX  .;;;;',
';;;;=oXX   *;;;;',
';;;;;*.  .*;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;'
);

xpm_blue : ARRAY[0..14+15] OF  pchar = (
'16 14 15 1',
'  c #000036',
'. c #000037',
'X c #000057',
'o c #000072',
'O c #00008A',
'+ c #00008F',
'@ c #0B0BA9',
'# c #0000BF',
'$ c #0404C4',
'% c #5555E0',
'& c #D1D1FF',
'* c #00003A',
'= c #00006F',
'- c #0000C6',
'; c None',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;-#@@O=;;;;;',
';;;;-$%@+oo=;;;;',
';;;;#%&@+oX.;;;;',
';;;;@@@++oX ;;;;',
';;;;@++ooX  ;;;;',
';;;;O+ooX  .;;;;',
';;;;=oXX   *;;;;',
';;;;;*.  .*;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;'
);

xpm_yellow : ARRAY[0..14+15] OF  pchar = (
'16 14 15 1',
'  c #363600',
'. c #373700',
'X c #575700',
'o c #727200',
'O c #8A8A00',
'+ c #8F8F00',
'@ c #A9A90B',
'# c #BFBF00',
'$ c #C4C404',
'% c #E0E055',
'& c #FFFFD1',
'* c #3A3A00',
'= c #6F6F00',
'- c #C6C600',
'; c None',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;-#@@O=;;;;;',
';;;;-$%@+oo=;;;;',
';;;;#%&@+oX.;;;;',
';;;;@@@++oX ;;;;',
';;;;@++ooX  ;;;;',
';;;;O+ooX  .;;;;',
';;;;=oXX   *;;;;',
';;;;;*.  .*;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;',
';;;;;;;;;;;;;;;;'
);

xpm_cog : ARRAY[0..16+17] OF  pchar = (
'16 16 17 1',
' 	c None',
'.	c #4C4C4C',
'+	c #565656',
'@	c #5F5F5F',
'#	c #676767',
'$	c #6E6E6E',
'%	c #797979',
'&	c #838383',
'*	c #8D8D8D',
'=	c #A2A2A2',
'-	c #ABABAB',
';	c #B6B6B6',
'>	c #C1C1C1',
',	c #C9C9C9',
'A	c #D4D4D4',
')	c #DEDEDE',
'!	c #E9E9E9',
'       ,>       ',
'      ,!!-      ',
'  A,, >)); --=  ',
'  )!)>>AA--,!;  ',
'  >)AA)AAAA,,%  ',
'  >A,,;==>,>;*  ',
',>>A,>&  *>>,*&&',
'>!A,,=    ->;,)$',
'>)A,,;    ->;>A@',
'=*=A,,=  *>>;#++',
'  ->>>,-->>;-#  ',
'  =A>,A,,,>>,$  ',
'  >)=&&>>$$=A&  ',
'  &$# &,,@ +..  ',
'      &>;@      ',
'       +.       ');

xpm_white_page : ARRAY[0..16+17] OF  pchar = (
'16 16 17 1',
' 	c None',
'.	c #949494',
'+	c #959595',
'@	c #999999',
'#	c #E7E7E7',
'$	c #EAEAEA',
'%	c #EBEBEB',
'&	c #EDEDED',
'*	c #EFEFEF',
'=	c #F1F1F1',
'-	c #F2F2F2',
';	c #F4F4F4',
'>	c #F6F6F6',
',	c #F7F7F7',
'A	c #F9F9F9',
')	c #FAFAFA',
'!	c #FCFCFC',
'                ',
'  ,)!!!!!!,.    ',
'  );;;;=*$!#+   ',
'  !,A,,-*$!>;@  ',
'  !AAA,>-%!!!!  ',
'  !)!!),;=%$#!  ',
'  !!!!!),;-*&!  ',
'  !!!!!!),>--!  ',
'  !!!!!!!)A>>!  ',
'  !!!!!!!)AA,!  ',
'  !!!!))))),,!  ',
'  !!!!)))))))!  ',
'  !!!!!))))))!  ',
'  !!!!!!!!!!!!  ',
'  A!!!!!!!!!!A  ',
'                ');

xpm_bic : ARRAY[0..32+17] OF  pchar = (
'32 32 17 1',
' 	c None',
'.	c #030100',
'+	c #230001',
'@	c #3A0000',
'#	c #5C0000',
'$	c #790000',
'%	c #A40000',
'&	c #262423',
'*	c #D30000',
'=	c #FF0000',
'-	c #595B58',
';	c #7A7C79',
'>	c #8F918E',
',	c #9FA19E',
'A	c #AEB0AD',
')	c #BEC1BD',
'!	c #FCFEFB',
'            ........            ',
'         .....+@@+.....         ',
'       ...+$*======*$+...       ',
'      ..+%============%+..      ',
'     ..#================#..     ',
'    ..%==================%..    ',
'   ..%====================%..   ',
'  ..#======================#..  ',
'  .+========================+.  ',
' ..%========================%.. ',
' .+==========================+. ',
' .$=========*================$. ',
'..*=====*#+...@$=============*..',
'..=====$..&--&..@*============..',
'.+====#.&)!!!!!-..*===========+.',
'.@===%.-!!!!!!!!A.+===========@.',
'.@==*..!!!!!!!!!!;.$==========@.',
'.+==%.,!!!!!!!!!!!&+==========+.',
'..==#.!!!!!!!!!!!!-.*=========..',
'..*=@.!!!!!!!!!!!!>.%========*..',
' .$=+&!!!!!!!!!!!!>.%========$. ',
' .+=#.!!!!!!!!!!!!-.*========+. ',
' ..%$.A!!!!!!!!!!!&.========%.. ',
'  .+*.&!!!!!!!!!!>.#========+.  ',
'  ..#$.;!!!!!!!!).+========#..  ',
'   ..%@.-!!!!!!>..%=======%..   ',
'    ..%#..-;>-&.+%=======%..    ',
'     ..#%@....+#========#..     ',
'      ..+%=*%*========%+..      ',
'       ...+$*======*$+...       ',
'         .....+@@+.....         ',
'            ........            ');

xpm_bir : ARRAY[0..32+17] OF  pchar = (
'32 32 17 1',
' 	c None',
'.	c #000100',
'+	c #060000',
'@	c #100101',
'#	c #1E0100',
'$	c #570001',
'%	c #141613',
'&	c #880001',
'*	c #1F201E',
'=	c #AB0000',
'-	c #DB0200',
';	c #EB0000',
'>	c #FF0000',
',	c #3C3E3C',
'A	c #959794',
')	c #C6C8C5',
'!	c #FEFFFC',
'+..............................+',
'.+############################+.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>;-----------;>>>>>>>>>>>>>#.',
'.#>-@...........+=>>>>>>>>>>>>#.',
'.#>&.*,,,,,,,,,,.$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.A!!!!!!!!!).$>>>>>>>>>>>>#.',
'.#>&.%*********%.$>>>>>>>>>>>>#.',
'.#>-#...........+->>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.#>>>>>>>>>>>>>>>>>>>>>>>>>>>>#.',
'.+############################+.',
'+..............................+');

xpm_boc : ARRAY[0..32+17] OF  pchar = (
'32 32 17 1',
' 	c None',
'.	c #010300',
'+	c #220100',
'@	c #4C0000',
'#	c #870000',
'$	c #252623',
'%	c #D80000',
'&	c #FF0000',
'*	c #3A3C39',
'=	c #616360',
'-	c #797B78',
';	c #888A87',
'>	c #949693',
',	c #A6A8A5',
'A	c #B0B2AF',
')	c #C9CCC8',
'!	c #FDFFFB',
'            ........            ',
'         .....$**$.....         ',
'       ...$-)!!!!!!)-$...       ',
'      ..$,!!!!!!!!!!!!,$..      ',
'     ..=!!!!!!!!!!!!!!!!=..     ',
'    ..>!!!!!!!!!!!!!!!!!!>..    ',
'   ..>!!!!!!!!!!!!!!!!!!!!>..   ',
'  ..=!!!!!!!!!!!!!!!!!!!!!!=..  ',
'  .$!!!!!!!!!!!!!!!!!!!!!!!!$.  ',
' ..,!!!!!!!!!!!!!!!!!!!!!!!!,.. ',
' .$!!!!!!!!!!!!!!!!!!!!!!!!!!$. ',
' .-!!!!!!!!!)!!!!!!!!!!!!!!!!-. ',
'..)!!!!!)=$...*;!!!!!!!!!!!!!)..',
'..!!!!!-..+@#@..*)!!!!!!!!!!!!..',
'.$!!!!=.+%&&&&&#..)!!!!!!!!!!!$.',
'.*!!!,.@&&&&&&&&%.$!!!!!!!!!!!*.',
'.*!!!.+&&&&&&&&&&#.-!!!!!!!!!!*.',
'.$!!;.#&&&&&&&&&&&+$!!!!!!!!!!$.',
'..!!=.%&&&&&&&&&&&@.!!!!!!!!!!..',
'..)!$.&&&&&&&&&&&&#.A!!!!!!!!)..',
' .-!$+&&&&&&&&&&&&#.A!!!!!!!!-. ',
' .$!=.%&&&&&&&&&&&@.)!!!!!!!!$. ',
' ..,;.#&&&&&&&&&&&+.!!!!!!!!,.. ',
'  .$).+&&&&&&&&&&#.=!!!!!!!!$.  ',
'  ..=;.#&&&&&&&&%.$!!!!!!!!=..  ',
'   ..>*.@%&&&&&#..A!!!!!!!>..   ',
'    ..;=..@##@+.$A!!!!!!!>..    ',
'     ..=,*.....=!!!!!!!!=..     ',
'      ..$,!)A)!!!!!!!!,$..      ',
'       ...$-)!!!!!!)-$...       ',
'         .....$**$.....         ',
'            ........            ');

xpm_bor : ARRAY[0..32+17] OF  pchar = (
'32 32 17 1',
' 	c None',
'.	c #000100',
'+	c #100101',
'@	c #1E0100',
'#	c #3F0001',
'$	c #1E1F1D',
'%	c #980000',
'&	c #C70400',
'*	c #FF0000',
'=	c #565755',
'-	c #868885',
';	c #A8AAA7',
'>	c #BCBEBB',
',	c #CBCECA',
'A	c #DEE0DD',
')	c #E8EAE6',
'!	c #FEFFFC',
'................................',
'..$$$$$$$$$$$$$$$$$$$$$$$$$$$$..',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!)AAAAAAAAAAA)!!!!!!!!!!!!!$.',
'.$!,+............;!!!!!!!!!!!!$.',
'.$!-.@##########.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.%*********&.=!!!!!!!!!!!!$.',
'.$!-.+@@@@@@@@@+.=!!!!!!!!!!!!$.',
'.$!A$............>!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'.$!!!!!!!!!!!!!!!!!!!!!!!!!!!!$.',
'..$$$$$$$$$$$$$$$$$$$$$$$$$$$$..',
'................................');
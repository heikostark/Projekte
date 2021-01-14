{ **************************************************************************** }
{ ****************************** Dateiverarbeitung *************************** }
{ **************************************************************************** }

const format_txt : Tformat = (
             scientific_notation : false; {true: 1E3 false: 1000 – simpler }
             decimal_separator : true; {true: 1.234 (en) false: 1,234 (other)}
             digit_grouping : false; {true: 1,000,000 or 1.000.000 false: 1000000 – simpler}
             leading_zero : 0; { (1  0.1) or (01 00.1) or 001 or 0001 }
             trailing_zero : 0; { 1.000 or 1.00 or 1.0 or 1 }
             vector : false; {true: <1, 1, 1> false: 1, 1, 1}
             matrix : false; {true: [...]  false: ...}
      );

{ **************************************************************************** }

procedure dir_down (p1,macro : gtk_pointer); cdecl;
begin
     chdir (getdir(finput^.name));
     refreshdir;
end;

procedure dir_up (p1,macro : gtk_pointer); cdecl;
begin
{$ifdef MSWINDOWS} { C:\..\file.txt }
     finput^.name := getcurrentdir+'\'+getfile(finput^.name);
{$else}
     finput^.name := getcurrentdir+'/'+getfile(finput^.name);
{$endif}
     refreshdir;
end;

var dirname : utf16chars;

procedure dir_1;
begin
     chdir (dirname);
     refreshdir;
end;

procedure dir_dialog (p1,macro : gtk_pointer); cdecl;
begin
     dirname := getcurrentdir;
     _opendir (dirname,@dir_1);
end;

{ **************************************************************************** }
{ ********************************** Project ********************************* }
{ **************************************************************************** }

procedure proc_new_project (p1,macro : gtk_pointer); cdecl;
var s : utf16;
begin
     _cursor_watch;
     ifdraw := false;

     red.clear;
     green.clear;
     blue.clear;
     yellow.clear;
     cyan.clear;
     purple.clear;

     state[1] := true; input := 1; finput := @red;
     state[2] := false;
     state[3] := false;
     state[4] := false;
     state[5] := false;
     state[6] := false;

     ref_state[1] := true; inputedit := 1; finputedit := @red;
     ref_state[2] := false;
     ref_state[3] := false;
     ref_state[4] := false;
     ref_state[5] := false;
     ref_state[6] := false;

     tmacro(macro^).clear;
     tmacro(macro^).putconstant ('point.length','0');
     tmacro(macro^).putconstant ('point.count','0');
     tmacro(macro^).putconstant ('line.length','0');
     tmacro(macro^).putconstant ('line.count','0');
     tmacro(macro^).putconstant ('line.material','0');
     tmacro(macro^).putconstant ('object.length','0');
     tmacro(macro^).putconstant ('object.count','0');
     tmacro(macro^).putconstant ('object.name','');
     for x := 0 to 5 do
     begin
          macro_save[x] := false;
          macro_filename[x] := 'Macro'+getstring(x+1);
          _setpagelabel (subnote_macro,x,'Macro '+getstring(x+1)+' ');
     end;

     s := '';
     _setedittext (clipboard,s);
     for x := 0 to 5 do _setedittext (macro_text[x],s);

     _setpage (subnote_macro,0);

     ifdraw := true;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('new.project');
     _cursor_arrow;
end;

{ **************************************************************************** }

procedure load (macro : pointer); forward;
procedure save (macro : pointer); forward;
procedure load_macro (const filename : utf16;macro : pointer); forward;
procedure save_macro (const filename : utf16;macro : pointer); forward;

{ ***************************** Load Project ********************************* }

var dir : utf16chars;

procedure load_project (macro : pointer);
var f : tfilelist;
  procedure read_project (n : integer;const m : utf16);
  begin
       if f.length > 0 then
       for x := 1 to f.length do
       begin
            if (f.get(x) = m) then { red, green, ... }
            begin
                 input := n;
                 finput^.name := dir+f.get(x);
                 load (macro);
                 finput^.name := '';
            end;
            if (getfileextension(f.get(x)) = m) then { file.red, file.green, ... }
            begin
                 input := n;
                 finput^.name := dir+f.get(x);
                 load (macro);
                 finput^.name := dir+getfilename(f.get(x));
            end;
       end;
  end;
  procedure read_macro (n : integer;const m : utf16);
  begin
       if into (n,0,macro_length) then
       begin
            if f.length > 0 then
            for x := 1 to f.length do
            begin
                 if (f.get(x) = m) then { macro1, macro2, ... }
                 begin
                      load_macro (dir+f.get(x),macro);
                      macro_filename[n] := '';
                 end;
                 if (getfileextension(f.get(x)) = m) then { file.macro1, file.macro2, ... }
                 begin
                      load_macro (dir+f.get(x),macro);
                      macro_filename[n] := dir+getfilename(f.get(x));
                 end;
            end;
       end;
  end;
begin
     f := Default(tfilelist);
     ifdraw := false;

     {$ifdef LINUX}
             dir := dir+'/';
     {$else}
             dir := dir+'\';
     {$endif}

     f.init(dir+'*');
       finput := @red;
       read_project (1,'red');
       finput := @green;
       read_project (2,'green');
       finput := @blue;
       read_project (3,'blue');
       finput := @yellow;
       read_project (4,'yellow');
       finput := @cyan;
       read_project (5,'cyan');
       finput := @purple;
       read_project (6,'purple');
       finput := @red;
       input := 1;

       ifdraw := true;
       calculating;
       updating;
       drawing;

       _setpage (subnote_macro,0);
       read_macro (0,'macro1');
       _setpage (subnote_macro,1);
       read_macro (1,'macro2');
       _setpage (subnote_macro,2);
       read_macro (2,'macro3');
       _setpage (subnote_macro,3);
       read_macro (3,'macro4');
       _setpage (subnote_macro,4);
       read_macro (4,'macro5');
       _setpage (subnote_macro,5);
       read_macro (5,'macro6');
       _setpage (subnote_macro,0);
     f.done;
end;

procedure proc_load_project (p1,macro : gtk_pointer); cdecl;
begin
     _opendir (dir,@load_project,macro);
end;

{ *************************** Save Project *********************************** }

procedure save_project (macro : pointer);
var f : text;
    x : integer;
  procedure write_project (n : integer;const m : utf16);
  var name,old : utf16;
  begin
       input := n;
       old := finput^.name;
       name := getfile (old);
       if name <> '' then finput^.name := dir+name+'.'+m { file.red, file.green, ... }
                     else finput^.name := dir+m; { red, green, ... }
       save (macro);
       finput^.name := old;
  end;
  procedure write_macro (n : integer;const m : utf16);
  var name : utf16;
  begin
       if into (n,0,macro_length) then
       begin
            name := getfile (macro_filename[n]);
            if name <> '' then save_macro (dir+name+'.'+m,macro) { file.macro1, file.macro2, ... }
                          else save_macro (dir+m,macro); { macro1, macro2, ... }
       end;
  end;
begin
     ifdraw := false;

     {$ifdef LINUX}
             dir := dir+'/';
     {$else}
             dir := dir+'\';
     {$endif}

     finput := @red;
     write_project (1,'red');
     finput := @green;
     write_project (2,'green');
     finput := @blue;
     write_project (3,'blue');
     finput := @yellow;
     write_project (4,'yellow');
     finput := @cyan;
     write_project (5,'cyan');
     finput := @purple;
     write_project (6,'purple');
     finput := @red;
     input := 1;

     ifdraw := true;
     calculating;
     updating;
     drawing;

     _setpage (subnote_macro,0);
     write_macro (0,'macro1');
     _setpage (subnote_macro,1);
     write_macro (1,'macro2');
     _setpage (subnote_macro,2);
     write_macro (2,'macro3');
     _setpage (subnote_macro,3);
     write_macro (3,'macro4');
     _setpage (subnote_macro,4);
     write_macro (4,'macro5');
     _setpage (subnote_macro,5);
     write_macro (5,'macro6');
     _setpage (subnote_macro,0);

     {save_log}
     if assignwrite (f,dir+getstring(getdate)+'-'+getstring(gettime)+'.log') then
     begin
          if tmacro(macro^).redolength > 0 then
             for x := 1 to tmacro(macro^).redolength do writeln (f,tmacro(macro^).getredo (x));
          close (f);
     end;
end;

procedure proc_save_project (p1,macro : gtk_pointer); cdecl;
begin
     _savedir (dir,@save_project,macro);
end;

{ **************************************************************************** }
{ ******************************** Single ************************************ }
{ **************************************************************************** }

procedure proc_new (p1,macro : gtk_pointer); cdecl;
begin
     finput^.clear;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('new');
end;

{ ***************************** Reload *************************************** }

procedure reload (macro : pointer);
var ignore : real;
    ext : utf16;
    ok : boolean;
begin
     if tmacro(macro^).checkparameter (2) then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,1) then format.decimal_separator := true
                                                          else format.decimal_separator := false;
           ignore := limit (_getreal (load_ignore,macro,2),0,100);
           if finput^.name <> '' then
           begin
                 ext := getfileextension (finput^.name);
                 if (ext = 'dxf') or (ext = 'obj') or (ext = 'vtk') or
                    (ext = 'mel') or (ext = 'py') or (ext = 'am') or
                    (ext = 'trk') or (ext = 'pbm') or (ext = 'pgm') or
                    (ext = 'ppm') or (ext = 'bmp') or (ext = 'dib') or
                    (ext = 'tif') or (ext = 'png') or (ext = 'jpg')
                    then ok := _dialog_yes_no ('Possible load fail!','Detect import/export ('+ext+') file extension.','Ignore?')
                    else ok := true;
                 if ok then
                 begin
                 { New }
                      finput^.softclear;
                 { Load }
                      finput^.load (ignore);
                      state[input] := true;
                      ref_state[input] := true;
                      calculating;
                      updating;
                      drawing;
                      tmacro(macro^).writeredo ('reload',getstring(format.decimal_separator)+' '+getstring(ignore));
                 end;
           end;
           format.pop;
           _cursor_arrow;
     end;
end;

procedure proc_reload (p1,macro : gtk_pointer); cdecl;
begin
     reload (macro);
end;

{ ***************************** Load ***************************************** }

procedure load (macro : pointer);
var ignore : real;
begin
     if tmacro(macro^).checkparameter (3) then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,2) then format.decimal_separator := true
                                                          else format.decimal_separator := false;
           ignore := limit (_getreal (load_ignore,macro,3),0,100);
           if finput^.name <> '' then
           begin
                 finput^.load (ignore);
                 state[input] := true;
                 ref_state[input] := true;
                 calculating;
                 updating;
                 drawing;
                 tmacro(macro^).writeredo ('load','"'+finput^.name+'"'+' '+getstring(format.decimal_separator)+' '+getstring(ignore));
           end;
           format.pop;
           _cursor_arrow;
     end;
end;

procedure proc_load_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     load (macro);
end;

procedure proc_load (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@load,macro);
end;

{ ***************************** Gaps ***************************************** }

procedure loadgaps (macro : pointer);
var ignore : real;
begin
     if tmacro(macro^).checkparameter (3) then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,2) then format.decimal_separator := true
                                                          else format.decimal_separator := false;
           ignore := limit (_getreal (load_ignore,macro,3),0,100);
           if finput^.name <> '' then
           begin
                 finput^.load (ignore);
{TODO: Fill up gaps}
                 state[input] := true;
                 ref_state[input] := true;
                 calculating;
                 updating;
                 drawing;
                 tmacro(macro^).writeredo ('load.gaps','"'+finput^.name+'"'+' '+getstring(format.decimal_separator)+' '+getstring(ignore));
           end;
           format.pop;
           _cursor_arrow;
     end;
end;

procedure proc_loadgaps_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     loadgaps (macro);
end;

procedure proc_loadgaps (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@loadgaps,macro);
end;

{ *************************** Save ******************************************* }

procedure save (macro : pointer);
begin
     if tmacro(macro^).parameterlength = 1 then
     begin
           _cursor_watch;
           if finput^.name <> '' then
           begin
                finput^.save;
                updating;
                tmacro(macro^).writeredo ('save','"'+finput^.name+'"');
           end;
           _cursor_arrow;
     end
     else if tmacro(macro^).parameterlength = 2 then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,2) then format.decimal_separator := true else format.decimal_separator := false;
           if finput^.name <> '' then
           begin
                finput^.save;
                updating;
                tmacro(macro^).writeredo ('save','"'+finput^.name+'"'+' '+getstring(format.decimal_separator));
           end;
           format.pop;
           _cursor_arrow;
     end
     else if tmacro(macro^).parameterlength = 3 then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,2) then format.decimal_separator := true else format.decimal_separator := false;
           if _getcheckbutton(toggle_format,macro,3) then format.vector := true else format.vector := false;
           if finput^.name <> '' then
           begin
                finput^.save;
                updating;
                tmacro(macro^).writeredo ('save','"'+finput^.name+'"'+' '+getstring(format.decimal_separator)+' '+getstring(format.vector));
           end;
           format.pop;
           _cursor_arrow;
     end
     else if (tmacro(macro^).parameterlength = 4) or (not tmacro(macro^).running) then
     begin
           _cursor_watch;
           format.push;
           if _getcheckbutton(toggle_punctuation,macro,2) then format.decimal_separator := true else format.decimal_separator := false;
           if _getcheckbutton(toggle_format,macro,3) then format.vector := true else format.vector := false;
           if _getcheckbutton(toggle_exponent,macro,4) then format.scientific_notation := true else format.scientific_notation := false;
           if finput^.name <> '' then
           begin
                finput^.save;
                updating;
                tmacro(macro^).writeredo ('save','"'+finput^.name+'"'+' '+getstring(format.decimal_separator)+' '+getstring(format.vector)+' '+getstring(format.scientific_notation));
           end;
           format.pop;
           _cursor_arrow;
     end
     else tmacro(macro^).min_parametererror(1);
end;

procedure proc_save_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save (macro);
end;

procedure proc_save (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-file','',@save,macro);
end;

{ **************************** New all *************************************** }

procedure proc_newall (p1,macro : gtk_pointer); cdecl;
begin
     _cursor_watch;

     if state[1] then red.clear;
     if state[2] then green.clear;
     if state[3] then blue.clear;
     if state[4] then yellow.clear;
     if state[5] then cyan.clear;
     if state[6] then purple.clear;

     state[1] := true;
     ref_state[1] := true;
     finput := @red;
     input := 1;
     finputedit := @red;
     inputedit := 1;

     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('new.all');
     _cursor_arrow;
end;

{ ******************************* Reload all ********************************* }

procedure proc_reloadall (p1,macro : gtk_pointer); cdecl;
begin
     if red.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.red');
          finput := @red; input := 1; reload (macro);
     end;
     if green.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.green');
          finput := @green; input := 2; reload (macro);
     end;
     if blue.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.blue');
          finput := @blue; input := 3; reload (macro);
     end;
     if yellow.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.yellow');
          finput := @yellow; input := 4; reload (macro);
     end;
     if cyan.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.cyan');
          finput := @cyan; input := 5; reload (macro);
     end;
     if purple.name <> '' then
     begin
          tmacro(macro^).writeredo ('set.purple');
          finput := @purple; input := 6; reload (macro);
     end;
     tmacro(macro^).writeredo ('// reload.all',getstring(_getcheckbutton(toggle_punctuation))+' '+getstring(limit(_getreal(load_ignore),0,100)));
end;

{ ********************************* Load all ********************************* }

procedure load_purple (macro : pointer);
begin finput := @purple; input := 6; load (macro); end;

procedure load_cyan (macro : pointer);
begin finput := @cyan; input := 5; load (macro); if state[6] then _openfile (purple.name,@load_purple,macro); end;

procedure load_yellow (macro : pointer);
begin finput := @yellow; input := 4; load (macro); if state[5] then _openfile (cyan.name,@load_cyan,macro) else load_purple (macro); end;

procedure load_blue (macro : pointer);
begin finput := @blue; input := 3; load (macro); if state[4] then _openfile (yellow.name,@load_yellow,macro) else load_cyan (macro); end;

procedure load_green (macro : pointer);
begin finput := @green; input := 2; load (macro); if state[3] then _openfile (blue.name,@load_blue,macro) else load_yellow (macro); end;

procedure load_red (macro : pointer);
begin finput := @red; input := 1; load (macro); if state[2] then _openfile (green.name,@load_green,macro) else load_blue (macro); end;

procedure proc_loadall (p1,macro : gtk_pointer); cdecl;
begin if state[1] then _openfile (red.name,@load_red,macro) else load_green (macro); end;

{ ****************************** Save all ************************************ }

procedure save_purple (macro : pointer);
begin finput := @purple; input := 6; save (macro); end;

procedure save_cyan (macro : pointer);
begin finput := @cyan; input := 5; save (macro); if state[6] then _savefile (purple.name,'new-purple','',@save_purple,macro); end;

procedure save_yellow (macro : pointer);
begin finput := @yellow; input := 4; save (macro); if state[5] then _savefile (cyan.name,'new-cyan','',@save_cyan,macro) else save_purple (macro); end;

procedure save_blue (macro : pointer);
begin finput := @blue; input := 3; save (macro); if state[4] then _savefile (yellow.name,'new-yellow','',@save_yellow,macro) else save_cyan (macro); end;

procedure save_green (macro : pointer);
begin finput := @green; input := 2; save (macro); if state[3] then _savefile (blue.name,'new-blue','',@save_blue,macro) else save_yellow (macro); end;

procedure save_red (macro : pointer);
begin finput := @red; input := 1; save (macro); if state[2] then _savefile (green.name,'new-green','',@save_green,macro) else save_blue (macro); end;

procedure proc_saveall (p1,macro : gtk_pointer); cdecl;
begin
     if state[1] then _savefile (red.name,'new-red','',@save_red,macro) else save_green (macro);
end;

{ ******************************* Rows & Columns ***************************** }

procedure rows (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rows;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rows','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rows_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rows (macro);
end;

procedure proc_rows (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@rows,macro);
end;

procedure columns (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.columns;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.columns','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_columns_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     columns (macro);
end;

procedure proc_columns (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@columns,macro);
end;

{ **************************************************************************** }

procedure line_rows (macro : pointer);
var header,index : integer;
begin
     _cursor_watch;
     header := _getnat (import_header,macro,2);
     index := _getnat (import_index,macro,3);
     if finput^.name <> '' then
     begin
           finput^.lines_rows (header,index);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.line.rows','"'+finput^.name+'"'+' '+getstring(header)+' '+getstring(index));
     end;
     _cursor_arrow;
end;

procedure proc_line_rows_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     line_rows (macro);
end;

procedure proc_line_rows (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@line_rows,macro);
end;

procedure line_columns (macro : pointer);
var header,index : integer;
begin
     _cursor_watch;
     header := _getnat (import_header,macro,2);
     index := _getnat (import_index,macro,3);
     if finput^.name <> '' then
     begin
           finput^.lines_columns (header,index);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.line.columns','"'+finput^.name+'"'+' '+getstring(header)+' '+getstring(index));
     end;
     _cursor_arrow;
end;

procedure proc_line_columns_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     line_columns (macro);
end;

procedure proc_line_columns (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@line_columns,macro);
end;

{ **************************************************************************** }

procedure field (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.field;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.field','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_field_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     field (macro);
end;

procedure proc_field (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@field,macro);
end;

{ ***** }

procedure gray (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.gray;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.gray','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_gray_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     gray (macro);
end;

procedure proc_gray (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@gray,macro);
end;

{ ***** }

procedure rgb_gray (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rgb_gray;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rgb.gray','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rgb_gray_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rgb_gray (macro);
end;

procedure proc_rgb_gray (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@rgb_gray,macro);
end;

{ ***** }

procedure rgb (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rgb;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rgb','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rgb_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rgb (macro);
end;

procedure proc_rgb (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@rgb,macro);
end;

{ ***** }

procedure rgb_point (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rgb_point;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rgb.point','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rgb_point_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rgb_point (macro);
end;

procedure proc_rgb_point (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@rgb_point,macro);
end;

{ ***** }

procedure rgb_count (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rgb_count;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rgb.count','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rgb_count_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rgb_count (macro);
end;

procedure proc_rgb_count (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@rgb_count,macro);
end;

{ ***** }

procedure rgb_halfcount (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.rgb_halfcount;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('load.rgb.halfcount','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_rgb_halfcount_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     rgb_halfcount (macro);
end;

procedure proc_rgb_halfcount (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'All images:*.pnm;*.ppm;*.pgm;*.pbm;*.bmp|All files:*.*',@rgb_halfcount,macro);
end;

{ ********************** Recurrence plots ************************************ }

procedure recurrence (macro : pointer);
var gray : tgray;
    x,y : integer;
    size : real;
begin
     gray := Default (tgray);

     _cursor_watch;
     if (finput^.name <> '') and (finput^.getpointlength > 0) then
     begin
           gray.init (finput^.getpointlength,finput^.getpointlength);
           size := 2*getlength(finput^.max-finput^.min);

           for y := 1 to finput^.getpointlength do
               for x := 1 to finput^.getpointlength do
               begin
                    gray.put (x,y,roundb((0.5+((getlength(finput^.getpoint(x))-getlength(finput^.getpoint(y)))/size))*255));
               end;

           gray.save (finput^.name);
           gray.done;
           updating;
           tmacro(macro^).writeredo ('export.recurrence','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_export_recurrence_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     recurrence (macro);
end;

procedure proc_export_recurrence (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'gray_plot','pgm',@recurrence,macro);
end;

{ ******* }

procedure recurrence_gaps (macro : pointer);
var gray : tgray;
    x,y,xl,xp,yl,yp : integer;
    size : real;
begin
     _cursor_watch;
     if (finput^.name <> '') and (finput^.getpointlength > 0) then
     begin
           gray.init (finput^.getpointlength+finput^.getlinelength-1,finput^.getpointlength+finput^.getlinelength-1);
           size := 2*getlength(finput^.max-finput^.min);

           y := 0;
           for yl := 1 to finput^.getlinelength do
           begin
                for yp := 1 to finput^.getalllinepointlength(yl) do
                begin
                     inc (y);

                     x := 0;
                     for xl := 1 to finput^.getlinelength do
                     begin
                          for xp := 1 to finput^.getalllinepointlength(xl) do
                          begin
                               inc (x);

                               gray.put (x,y,roundb((0.5+((getlength(finput^.getline(xl,xp))-getlength(finput^.getline(yl,yp)))/size))*255));
                          end;
                          inc (x);
                     end;
                end;
                inc(y);
           end;

           gray.save (finput^.name);
           gray.done;
           updating;
           tmacro(macro^).writeredo ('export.recurrence.gaps','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_export_recurrence_gaps_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     recurrence_gaps (macro);
end;

procedure proc_export_recurrence_gaps (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'gray_plot','pgm',@recurrence_gaps,macro);
end;

{ **************************************************************************** }

procedure recurrence_rgb (macro : pointer);
var rgb : trgb;
    x,y : integer;
    size,value : hyper;
begin
     _cursor_watch;
     if (finput^.name <> '') and (finput^.getpointlength > 0) then
     begin
           rgb.init (finput^.getpointlength,finput^.getpointlength);
           size := 2*(finput^.max-finput^.min);

           for y := 1 to finput^.getpointlength do
               for x := 1 to finput^.getpointlength do
               begin
                    value := (0.5+((finput^.getpoint(x)-finput^.getpoint(y))/size))*255;
                    rgb.put (x,y,gvn(roundb(value.x),roundb(value.y),roundb(value.z)));
               end;

           rgb.save (finput^.name);
           rgb.done;
           updating;
           tmacro(macro^).writeredo ('export.recurrence.rgb','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_export_recurrence_rgb_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     recurrence_rgb (macro);
end;

procedure proc_export_recurrence_rgb (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'rgb_plot','ppm',@recurrence_rgb,macro);
end;

{ ******* }

procedure recurrence_rgb_gaps (macro : pointer);
var rgb : trgb;
    x,y,xl,xp,yl,yp : integer;
    size,value : hyper;
begin
     _cursor_watch;
     if (finput^.name <> '') and (finput^.getpointlength > 0) then
     begin
           rgb.init (finput^.getpointlength+finput^.getlinelength-1,finput^.getpointlength+finput^.getlinelength-1);
           size := 2*(finput^.max-finput^.min);

           y := 0;
           for yl := 1 to finput^.getlinelength do
           begin
                for yp := 1 to finput^.getalllinepointlength(yl) do
                begin
                     inc (y);

                     x := 0;
                     for xl := 1 to finput^.getlinelength do
                     begin
                          for xp := 1 to finput^.getalllinepointlength(xl) do
                          begin
                               inc (x);

                               value := (0.5+((finput^.getline(xl,xp)-finput^.getline(yl,yp))/size))*255;
                               rgb.put (x,y,gvn(roundb(value.x),roundb(value.y),roundb(value.z)));
                          end;
                          inc (x);
                     end;
                end;
                inc(y);
           end;

           rgb.save (finput^.name);
           rgb.done;
           updating;
           tmacro(macro^).writeredo ('export.recurrence.rgb.gaps','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_export_recurrence_rgb_gaps_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     recurrence_rgb_gaps (macro);
end;

procedure proc_export_recurrence_rgb_gaps (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'rgb_plot','ppm',@recurrence_rgb_gaps,macro);
end;

{ *************************** Save ******************************************* }

procedure save_rows (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
          finput^.save_rows;
          updating;
          tmacro(macro^).writeredo ('save.rows','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_save_rows_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save_rows (macro);
end;

procedure proc_save_rows (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-rows','',@save_rows,macro);
end;

procedure save_columns (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
          finput^.save_columns;
          updating;
          tmacro(macro^).writeredo ('save.columns','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_save_columns_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save_columns (macro);
end;

procedure proc_save_columns (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-columns','',@save_columns,macro);
end;

{ **************************************************************************** }
{ ****************************** Clipboard *********************************** }
{ **************************************************************************** }

procedure proc_clipboard_clear (p1,macro : gtk_pointer); cdecl;
var s : utf16;
begin
     _cursor_watch;
     s := '';
     _setedittext (clipboard,s);
     _cursor_arrow;
end;

procedure proc_clipboard_point (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    v : hyper;
    d : integer;
begin
     _cursor_watch;
     d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
     s := '';
     v := finput^.getpoint (finput^.pointcounter);
     if _getcheckbutton(toggle_format) then
     begin
          if v.t = 0 then
          begin
               if v.z = 0 then
               begin
                    if v.y = 0 then s := getstring(v.x,d)
                               else s := getstring(gc(v.x,v.y),d);
               end
               else s := getstring(gv(v.x,v.y,v.z),d);
          end
          else s := getstring(v,d);
     end
     else
     begin
          if v.t = 0 then
          begin
               if v.z = 0 then
               begin
                    if v.y = 0 then s := getstring(v.x,d)
                               else s := getstring(v.x,d)+#9+getstring(v.y,d);
               end
               else s := getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
          end
          else s := getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
     end;
     _setedittext (clipboard,s);
     _cursor_arrow;
end;

procedure proc_clipboard_line (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    p : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getalllinepointlength (finput^.linecounter) < 1000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getalllinepointlength (finput^.linecounter))+' points!','Really show?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getalllinepointlength (finput^.linecounter) > 0 then
          begin
               for p := 1 to finput^.getalllinepointlength (finput^.linecounter) do
               begin
                    v := finput^.getline (finput^.linecounter,p);
                    if _getcheckbutton(toggle_format) then
                    begin
                         if v.t = 0 then
                         begin
                              if v.z = 0 then
                              begin
                                   if v.y = 0 then s := s + getstring(v.x,d)
                                              else s := s + getstring(gc(v.x,v.y),d);
                              end
                              else s := s + getstring(gv(v.x,v.y,v.z),d);
                         end
                         else s := s + getstring(v,d);
                    end
                    else
                    begin
                         if v.t = 0 then
                         begin
                              if v.z = 0 then
                              begin
                                   if v.y = 0 then s := s + getstring(v.x,d)
                                              else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                              end
                              else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                         end
                         else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                    end;
                    s := s + #10;
               end;
          end;
          _setedittext (clipboard,s);
          _cursor_arrow;
     end;
end;

procedure proc_clipboard_object (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    l,p : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getobjectlinelength(finput^.objectcounter) < 100) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getobjectlinelength(finput^.objectcounter))+' lines!','Really show?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getobjectlinelength(finput^.objectcounter) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength(finput^.objectcounter) do
               begin
                    if finput^.getlinepointlength(finput^.objectcounter,l) > 0 then
                    begin
                         for p := 1 to finput^.getlinepointlength(finput^.objectcounter,l) do
                         begin
                              v := finput^.getobject (finput^.objectcounter,l,p);
                              if _getcheckbutton(toggle_format) then
                              begin
                                   if v.t = 0 then
                                   begin
                                        if v.z = 0 then
                                        begin
                                             if v.y = 0 then s := s + getstring(v.x,d)
                                                        else s := s + getstring(gc(v.x,v.y),d);
                                        end
                                        else s := s + getstring(gv(v.x,v.y,v.z),d);
                                   end
                                   else s := s + getstring(v,d);
                              end
                              else
                              begin
                                   if v.t = 0 then
                                   begin
                                        if v.z = 0 then
                                        begin
                                             if v.y = 0 then s := s + getstring(v.x,d)
                                                        else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                                        end
                                        else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                                   end
                                   else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                              end;
                              s := s + #10; { every point }
                         end;
                         if l <> finput^.getobjectlinelength(finput^.objectcounter) then s := s + #10; { line_rows space between lines, if len > 0 }
                    end;
               end;
               s := s + 'object:' + finput^.getname(finput^.objectcounter) + #10;
          end;
          _setedittext (clipboard,s);
          _cursor_arrow;
     end;
end;

procedure proc_clipboard_layer (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    o,l,p : integer;
    v : hyper;
    d : integer;
begin
     if ((finput^.getpointlength < 1000) and (finput^.getlinelength < 100)) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points inside '+getstring(finput^.getlinelength)+' lines!','Really show?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getobjectlength > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength(o) do
                         begin
                              if finput^.getlinepointlength(o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength(o,l) do
                                   begin
                                        v := finput^.getobject (o,l,p);
                                        if _getcheckbutton(toggle_format) then
                                        begin
                                             if v.t = 0 then
                                             begin
                                                  if v.z = 0 then
                                                  begin
                                                       if v.y = 0 then s := s + getstring(v.x,d)
                                                                  else s := s + getstring(gc(v.x,v.y),d);
                                                  end
                                                  else s := s + getstring(gv(v.x,v.y,v.z),d);
                                             end
                                             else s := s + getstring(v,d);
                                        end
                                        else
                                        begin
                                             if v.t = 0 then
                                             begin
                                                  if v.z = 0 then
                                                  begin
                                                       if v.y = 0 then s := s + getstring(v.x,d)
                                                                  else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                                                  end
                                                  else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                                             end
                                             else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                                        end;
                                        s := s + #10;
                                   end;
                                   if l <> finput^.getobjectlinelength(o) then s := s + #10; { line_rows space between lines, if len > 0 }
                              end;
                         end;
                    end;
                    s := s + 'object:' + finput^.getname(o) + #10;
               end;
          end;
          _setedittext (clipboard,s);
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }

procedure proc_system_clipboard_point (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    v : hyper;
    d : integer;
begin
     _cursor_watch;
     d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
     s := '';
     v := finput^.getpoint (finput^.pointcounter);
     if _getcheckbutton(toggle_format) then
     begin
          if v.t = 0 then
          begin
               if v.z = 0 then
               begin
                    if v.y = 0 then s := getstring(v.x,d)
                               else s := getstring(gc(v.x,v.y),d);
               end
               else s := getstring(gv(v.x,v.y,v.z),d);
          end
          else s := getstring(v,d);
     end
     else
     begin
          if v.t = 0 then
          begin
               if v.z = 0 then
               begin
                    if v.y = 0 then s := getstring(v.x,d)
                               else s := getstring(v.x,d)+#9+getstring(v.y,d);
               end
               else s := getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
          end
          else s := getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
     end;
     _clipboard_set_text (s);
     tmacro(macro^).command_result := s;
     _cursor_arrow;
end;

procedure proc_system_clipboard_line (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    p : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getalllinepointlength (finput^.linecounter) < 1000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getalllinepointlength (finput^.linecounter))+' points!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getalllinepointlength (finput^.linecounter) > 0 then
          begin
               for p := 1 to finput^.getalllinepointlength (finput^.linecounter) do
               begin
                    v := finput^.getline (finput^.linecounter,p);
                    if _getcheckbutton(toggle_format) then
                    begin
                         if v.t = 0 then
                         begin
                              if v.z = 0 then
                              begin
                                   if v.y = 0 then s := s + getstring(v.x,d)
                                              else s := s + getstring(gc(v.x,v.y),d);
                              end
                              else s := s + getstring(gv(v.x,v.y,v.z),d);
                         end
                         else s := s + getstring(v,d);
                    end
                    else
                    begin
                         if v.t = 0 then
                         begin
                              if v.z = 0 then
                              begin
                                   if v.y = 0 then s := s + getstring(v.x,d)
                                              else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                              end
                              else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                         end
                         else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                    end;
                    s := s + #10;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

procedure proc_system_clipboard_object (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    l,p : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getobjectlinelength(finput^.objectcounter) < 100) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getobjectlinelength(finput^.objectcounter))+' lines!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getobjectlinelength(finput^.objectcounter) > 0 then
          begin
               for l := 1 to finput^.getobjectlinelength(finput^.objectcounter) do
               begin
                    if finput^.getlinepointlength(finput^.objectcounter,l) > 0 then
                    begin
                         for p := 1 to finput^.getlinepointlength(finput^.objectcounter,l) do
                         begin
                              v := finput^.getobject (finput^.objectcounter,l,p);
                              if _getcheckbutton(toggle_format) then
                              begin
                                   if v.t = 0 then
                                   begin
                                        if v.z = 0 then
                                        begin
                                             if v.y = 0 then s := s + getstring(v.x,d)
                                                        else s := s + getstring(gc(v.x,v.y),d);
                                        end
                                        else s := s + getstring(gv(v.x,v.y,v.z),d);
                                   end
                                   else s := s + getstring(v,d);
                              end
                              else
                              begin
                                   if v.t = 0 then
                                   begin
                                        if v.z = 0 then
                                        begin
                                             if v.y = 0 then s := s + getstring(v.x,d)
                                                        else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                                        end
                                        else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                                   end
                                   else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                              end;
                              s := s + #10;
                         end;
                         s := s + #10;
                    end;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

procedure proc_system_clipboard_layer (p1,macro : gtk_pointer); cdecl;
var s : utf16;
    o,l,p : integer;
    v : hyper;
    d : integer;
begin
     if ((finput^.getpointlength < 1000) and (finput^.getlinelength < 100)) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points inside '+getstring(finput^.getlinelength)+' lines!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getobjectlength > 0 then
          begin
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength(o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength(o) do
                         begin
                              if finput^.getlinepointlength(o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength(o,l) do
                                   begin
                                        v := finput^.getobject (o,l,p);
                                        if _getcheckbutton(toggle_format) then
                                        begin
                                             if v.t = 0 then
                                             begin
                                                  if v.z = 0 then
                                                  begin
                                                       if v.y = 0 then s := s + getstring(v.x,d)
                                                                  else s := s + getstring(gc(v.x,v.y),d);
                                                  end
                                                  else s := s + getstring(gv(v.x,v.y,v.z),d);
                                             end
                                             else s := s + getstring(v,d);
                                        end
                                        else
                                        begin
                                             if v.t = 0 then
                                             begin
                                                  if v.z = 0 then
                                                  begin
                                                       if v.y = 0 then s := s + getstring(v.x,d)
                                                                  else s := s + getstring(v.x,d)+#9+getstring(v.y,d);
                                                  end
                                                  else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d);
                                             end
                                             else s := s + getstring(v.x,d)+#9+getstring(v.y,d)+#9+getstring(v.z,d)+#9+getstring(v.t,d);
                                        end;
                                        s := s + #10;
                                   end;
                                   s := s + #10;
                              end;
                         end;
                    end;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

{ ********* }

procedure proc_system_clipboard_hline (p1,macro : gtk_pointer); cdecl;
var s,sx,sy,sz,st : utf16;
    l,p : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getpointlength < 10000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getlinelength > 0 then
          begin
               for l := 1 to finput^.getlinelength do
               begin
                    if finput^.getalllinepointlength (l) > 0 then
                    begin
                         sx := '';
                         sy := '';
                         sz := '';
                         st := '';
                         for p := 1 to finput^.getalllinepointlength (l) do
                         begin
                              v := finput^.getline (l,p);
                              if sx <> '' then sx := sx + #9 + getstring(v.x,d)
                                          else sx := getstring(v.x,d);
                              if sy <> '' then sy := sy + #9 + getstring(v.y,d)
                                          else sy := getstring(v.y,d);
                              if sz <> '' then sz := sz + #9 + getstring(v.z,d)
                                          else sz := getstring(v.z,d);
                              if st <> '' then st := st + #9 + getstring(v.t,d)
                                          else st := getstring(v.t,d);
                         end;
                         sx := sx + #10;
                         sy := sy + #10;
                         sz := sz + #10;
                         st := st + #10;
                    end
                    else
                    begin
                         sx := '';
                         sy := '';
                         sz := '';
                         st := '';
                    end;
                    s := s + sx + sy + sz + st;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

procedure proc_system_clipboard_vline (p1,macro : gtk_pointer); cdecl;
var s,sl : utf16;
    l,p,max : integer;
    v : hyper;
    d : integer;
begin
     if (finput^.getpointlength < 10000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getlinelength > 0 then
          begin
               max := 0;
               for l := 1 to finput^.getlinelength do
               begin
                    if max < finput^.getalllinepointlength (l) then max := finput^.getalllinepointlength (l);
               end;
               if max > 0 then
               for p := 1 to max do
               begin
                    sl := '';
                    for l := 1 to finput^.getlinelength do
                    begin
                         if finput^.getalllinepointlength (l) >= p then
                         begin
                              v := finput^.getline (l,p);
                              if sl <> '' then sl := sl + #9 + getstring(v.x,d) + #9 + getstring(v.y,d) + #9 + getstring(v.z,d) + #9 + getstring(v.t,d)
                                          else sl := getstring(v.x,d) + #9 + getstring(v.y,d) + #9 + getstring(v.z,d) + #9 + getstring(v.t,d);
                         end
                         else
                         begin
                              if sl <> '' then sl := sl + #9 + #9 + #9 + #9
                                          else sl := #9 + #9 + #9;
                         end;
                    end;
                    s := s + sl + #10;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

{ ****** }

procedure proc_system_clipboard_hline_zero (p1,macro : gtk_pointer); cdecl;
var s,sx,sy,sz,st : utf16;
    l,p : integer;
    v,w : hyper;
    d : integer;
    x,y,z,t : boolean;
begin
     if (finput^.getpointlength < 10000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getlinelength > 0 then
          begin
               { check dimension }
               v := finput^.min;
               w := finput^.max;
               if (v.x = 0.0) and (w.x = 0.0) then x := false else x := true;
               if (v.y = 0.0) and (w.y = 0.0) then y := false else y := true;
               if (v.z = 0.0) and (w.z = 0.0) then z := false else z := true;
               if (v.t = 0.0) and (w.t = 0.0) then t := false else t := true;
               for l := 1 to finput^.getlinelength do
               begin
                    if finput^.getalllinepointlength (l) > 0 then
                    begin
                         sx := '';
                         sy := '';
                         sz := '';
                         st := '';
                         for p := 1 to finput^.getalllinepointlength (l) do
                         begin
                              v := finput^.getline (l,p);
                              if x then
                              begin
                                   if sx <> '' then sx := sx + #9 + getstring(v.x,d)
                                               else sx := getstring(v.x,d);
                              end;
                              if y then
                              begin
                                   if sy <> '' then sy := sy + #9 + getstring(v.y,d)
                                               else sy := getstring(v.y,d);
                              end;
                              if z then
                              begin
                                   if sz <> '' then sz := sz + #9 + getstring(v.z,d)
                                               else sz := getstring(v.z,d);
                              end;
                              if t then
                              begin
                                   if st <> '' then st := st + #9 + getstring(v.t,d)
                                               else st := getstring(v.t,d);
                              end;
                         end;
                         if x then sx := sx + #10;
                         if y then sy := sy + #10;
                         if z then sz := sz + #10;
                         if t then st := st + #10;
                    end
                    else
                    begin
                         sx := '';
                         sy := '';
                         sz := '';
                         st := '';
                    end;
                    s := s + sx + sy + sz + st;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

procedure proc_system_clipboard_vline_zero (p1,macro : gtk_pointer); cdecl;
var s,sl : utf16;
    l,p,max : integer;
    v,w : hyper;
    d : integer;
    x,y,z,t : boolean;
    b : byte;
begin
     if (finput^.getpointlength < 10000) or (_dialog_yes_no ('Huge data!','You have selected '+getstring(finput^.getpointlength)+' points!','Really store?')) then
     begin
          _cursor_watch;
          d := limit (_getnat(data_clipboard_digits),0,50); { TODO: see format }
          s := '';
          if finput^.getlinelength > 0 then
          begin
               { check dimension }
               v := finput^.min;
               w := finput^.max;
               b := 0;
               if (v.x = 0.0) and (w.x = 0.0) then x := false else begin x := true; inc(b); end;
               if (v.y = 0.0) and (w.y = 0.0) then y := false else begin y := true; inc(b); end;
               if (v.z = 0.0) and (w.z = 0.0) then z := false else begin z := true; inc(b); end;
               if (v.t = 0.0) and (w.t = 0.0) then t := false else begin t := true; inc(b); end;
               max := 0;
               for l := 1 to finput^.getlinelength do
               begin
                    if max < finput^.getalllinepointlength (l) then max := finput^.getalllinepointlength (l);
               end;
               if (max > 0) and (b > 0) then
               for p := 1 to max do
               begin
                    sl := '';
                    for l := 1 to finput^.getlinelength do
                    begin
                         if finput^.getalllinepointlength (l) >= p then
                         begin
                              v := finput^.getline (l,p);
                              if sl <> '' then
                              begin
                                   if x then sl := sl + #9 + getstring(v.x,d);
                                   if y then sl := sl + #9 + getstring(v.y,d);
                                   if z then sl := sl + #9 + getstring(v.z,d);
                                   if t then sl := sl + #9 + getstring(v.t,d);
                              end
                              else
                              begin
                                   if x then sl := getstring(v.x,d);
                                   if y then
                                   begin
                                        if sl <> '' then sl := sl + #9 + getstring(v.y,d)
                                                    else sl := getstring(v.y,d);
                                   end;
                                   if z then
                                   begin
                                        if sl <> '' then sl := sl + #9 + getstring(v.z,d)
                                                    else sl := getstring(v.z,d);
                                   end;
                                   if t then
                                   begin
                                        if sl <> '' then sl := sl + #9 + getstring(v.t,d)
                                                    else sl := getstring(v.t,d);
                                   end;
                              end;
                         end
                         else
                         begin
                              if (sl <> '') or (l > 1) then
                              begin
                                   case b of
                                        0 :;
                                        1 : sl := sl + #9;
                                        2 : sl := sl + #9 + #9;
                                        3 : sl := sl + #9 + #9 + #9;
                                        4 : sl := sl + #9 + #9 + #9 + #9;
                                   end;
                              end
                              else { only for first line }
                              begin
                                   case b of
                                        0 :;
                                        1 :; { possible error }
                                        2 : sl := sl + #9;
                                        3 : sl := sl + #9 + #9;
                                        4 : sl := sl + #9 + #9 + #9;
                                   end;
                              end;
                         end;
                    end;
                    s := s + sl + #10;
               end;
          end;
          _clipboard_set_text (s);
          _cursor_arrow;
     end;
end;

{ **************************************************************************** }
{ **************************************************************************** }
{ **************************************************************************** }

procedure proc_insert_line (p1,macro : gtk_pointer); cdecl;
var x : integer;
    s : utf16;
begin
     if tmacro(macro^).parameterlength > 0 then
     begin
          for x := 1 to tmacro(macro^).parameterlength do
          begin
               finput^.newpoint(gethyper(tmacro(macro^).getparameter(x)));
          end;
          finput^.newline(0);
          finput^.newobject('new_line');
          s := '';
          for x := 1 to tmacro(macro^).parameterlength do s := s + getstring(gethyper(tmacro(macro^).getparameter(x)));
          tmacro(macro^).writeredo ('insert.line',s);
     end;
end;

procedure proc_clipboard_insert (p1,macro : gtk_pointer); cdecl;
var t : text;
begin
     _cursor_watch;
     if assignwrite (t,'clipboard') then
     begin
          write (t,_getedittext(clipboard));
          close (t);
          finput^.name := 'clipboard';
          load (macro);
     end;
     _cursor_arrow;
end;

procedure proc_clipboard_insert_gaps (p1,macro : gtk_pointer); cdecl;
var t : text;
begin
     _cursor_watch;
     if assignwrite (t,'clipboard') then
     begin
          write (t,_getedittext(clipboard));
          close (t);
          finput^.name := 'clipboard';
          loadgaps (macro);
     end;
     _cursor_arrow;
end;

procedure proc_clipboard_insert_rows (p1,macro : gtk_pointer); cdecl;
var t : text;
begin
     _cursor_watch;
     if assignwrite (t,'clipboard') then
     begin
          write (t,_getedittext(clipboard));
          close (t);
          finput^.name := 'clipboard';
          rows (macro);
     end;
     _cursor_arrow;
end;

procedure proc_clipboard_insert_columns (p1,macro : gtk_pointer); cdecl;
var t : text;
begin
     _cursor_watch;
     if assignwrite (t,'clipboard') then
     begin
          write (t,_getedittext(clipboard));
          close (t);
          finput^.name := 'clipboard';
          columns (macro);
     end;
     _cursor_arrow;
end;

procedure proc_clipboard_insert_field (p1,macro : gtk_pointer); cdecl;
var t : text;
begin
     _cursor_watch;
     if assignwrite (t,'clipboard') then
     begin
          write (t,_getedittext(clipboard));
          close (t);
          finput^.name := 'clipboard';
          field (macro);
     end;
     _cursor_arrow;
end;

{ **************************************************************************** }
{ ************************************ Import ******************************** }
{ **************************************************************************** }

procedure p_import_date (macro : pointer);
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           finput^.loadage (finput^.name);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.date','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_import_date_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_date (macro);
end;

procedure proc_import_date (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_date,macro);
end;

procedure p_import_split (macro : pointer);
var b,e : utf16;
begin
     _cursor_watch;
     if finput^.name <> '' then
     begin
           dummy.clear;
           b := _getedit (import_begin,macro,2);
           e := _getedit (import_end,macro,3);
           finput^.loadsplit (finput^.name,b,e,dummy);
           finputedit^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.split','"'+finput^.name+'" "'+b+'" "'+e+'"');
     end;
     _cursor_arrow;
end;

procedure proc_import_split_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_split (macro);
end;

procedure proc_import_split (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_split,macro);
end;

{ **************************************************************************** }

procedure columns_trigger (macro : pointer);
var v : real;
    c : integer;
begin
     _cursor_watch;
     v := _getreal (export_trigger_value,macro,2);
     c := limit(_getnat (export_trigger_centre,macro,3),0,100);
     if finput^.name <> '' then
     begin
           finput^.trigger (v,c);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.trigger','"'+finput^.name+'"');
     end;
     _cursor_arrow;
end;

procedure proc_columns_trigger_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     columns_trigger (macro);
end;

procedure proc_columns_trigger (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@columns_trigger,macro);
end;

{ **************************************************************************** }
{ ******************************* mesh - points ******************************* }
{ **************************************************************************** }

procedure p_import_mesh_points (macro : pointer);
var f : tfiletext;
    count : integer;
    o,s : utf16;
    h : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           o := '';
           f.load (finput^.name);
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                     if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          else  { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;
                     end
                     else { Faces };
                end;
           end;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.mesh.points','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_mesh_points_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_mesh_points (macro);
end;

procedure proc_import_mesh_points (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'mesh-files:*.obj;*.stl;*.dxf;*.iv;*.vrml;*.wrl;*.anysurf;*.asc|All files:*.*',@p_import_mesh_points,macro);
end;

{ mesh - normals }

procedure p_import_mesh_normals (macro : pointer);
var f : tfiletext;
    count,p : integer;
    o,s : utf16;
    h : hyper;
    points : tpolyhyper;
begin
     f := Default(tfiletext);
     points := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           o := '';
           f.load (finput^.name);
           points.init;
           p := 0;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                     if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    inc (p);
                                    dummy.newpoint (points.get (p));
                                    dummy.newpoint (points.get (p)+h);
                                    dummy.newline (0);
                               end;
                          end
                          else { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    points.put (points.length+1,h);
                               end;
                          end;
                     end
                     else { Faces };
                end;
           end;
           points.done;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.mesh.normals','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_mesh_normals_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_mesh_normals (macro);
end;

procedure proc_import_mesh_normals (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'mesh-files:*.obj;*.stl;*.dxf;*.iv;*.vrml;*.wrl;*.anysurf;*.asc|All files:*.*',@p_import_mesh_normals,macro);
end;

{ mesh - faces }

procedure p_import_mesh_faces (macro : pointer);
var f : tfiletext;
    count,v,v1 : integer;
    o,s : utf16;
    h : hyper;
    points : tpolyhyper;
begin
     f := Default(tfiletext);
     points := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           o := '';
           f.load (finput^.name);
           points.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                      if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          else { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    points.put (points.length+1,h);
                               end;
                          end;
                     end
                     else if (getchar(s,1) = 'p') then { Points }
                     begin
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then
                               begin
                                    dummy.newpoint (points.get(v));
                                    dummy.newline (0);
                               end;
                          end;
                     end
                     else if (getchar(s,1) = 'l') then { Lines }
                     begin
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then dummy.newpoint (points.get(v));
                          end;
                          dummy.newline (0);
                     end
                     else if (getchar(s,1) = 'f') then { Faces }
                     begin
                          v1 := 0;
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then
                               begin
                                    dummy.newpoint (points.get(v));
                                    v1 := v;
                               end;
                          end;
                          if v1 <> 0 then dummy.newpoint (points.get(v1));
                          dummy.newline (0);
                     end;
                end;
           end;
           points.done;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.mesh.faces','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_mesh_faces_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_mesh_faces (macro);
end;

procedure proc_import_mesh_faces (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'mesh-Files:*.obj;*.stl;*.dxf;*.iv;*.vrml;*.wrl;*.anysurf;*.asc|All files:*.*',@p_import_mesh_faces,macro);
end;

{ **************************************************************************** }
{ ******************************* obj - points ******************************* }
{ **************************************************************************** }

procedure p_import_obj_points (macro : pointer);
var f : tfiletext;
    count : integer;
    o,s : utf16;
    h : hyper;
begin
     f := Default(tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;

           o := '';
           f.load (finput^.name);
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                     if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          else  { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;
                     end
                     else { Faces };
                end;
           end;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.obj.points','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_obj_points_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_obj_points (macro);
end;

procedure proc_import_obj_points (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'OBJ-files:*.obj|All files:*.*',@p_import_obj_points,macro);
end;

{ obj - normals }

procedure p_import_obj_normals (macro : pointer);
var f : tfiletext;
    count,p : integer;
    o,s : utf16;
    h : hyper;
    points : tpolyhyper;
begin
     f := Default(tfiletext);
     points := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           o := '';
           f.load (finput^.name);
           points.init;
           p := 0;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                     if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    inc (p);
                                    dummy.newpoint (points.get (p));
                                    dummy.newpoint (points.get (p)+h);
                                    dummy.newline (0);
                               end;
                          end
                          else { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    points.put (points.length+1,h);
                               end;
                          end;
                     end
                     else { Faces };
                end;
           end;
           points.done;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.obj.normals','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_obj_normals_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_obj_normals (macro);
end;

procedure proc_import_obj_normals (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'OBJ-files:*.obj|All files:*.*',@p_import_obj_normals,macro);
end;

{ obj - faces }

procedure p_import_obj_faces (macro : pointer);
var f : tfiletext;
    count,v,v1 : integer;
    o,s : utf16;
    h : hyper;
    points : tpolyhyper;
begin
     f := Default(tfiletext);
     points := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           o := '';
           f.load (finput^.name);
           points.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 1 then
                begin
                      if (getchar(s,1) = 'o') then
                     begin
                          if o <> '' then dummy.newobject (o);
                          o := copy (s,3,length(s));
                          if o = '' then getfile(finput^.name);
                     end
                     else if (getchar(s,1) = 'v') then
                     begin
                          if (getchar(s,2) = 'n') then { Normals }
                          else { Vectors }
                          begin
                               h := gethyper (s);
                               if h <> Hzero then
                               begin
                                    points.put (points.length+1,h);
                               end;
                          end;
                     end
                     else if (getchar(s,1) = 'p') then { Points }
                     begin
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then
                               begin
                                    dummy.newpoint (points.get(v));
                                    dummy.newline (0);
                               end;
                          end;
                     end
                     else if (getchar(s,1) = 'l') then { Lines }
                     begin
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then dummy.newpoint (points.get(v));
                          end;
                          dummy.newline (0);
                     end
                     else if (getchar(s,1) = 'f') then { Faces }
                     begin
                          v1 := 0;
                          while s <> '' do
                          begin
                               v := cutnat (s);
                               if v <> 0 then
                               begin
                                    dummy.newpoint (points.get(v));
                                    v1 := v;
                               end;
                          end;
                          if v1 <> 0 then dummy.newpoint (points.get(v1));
                          dummy.newline (0);
                     end;
                end;
           end;
           points.done;
           if o <> '' then dummy.newobject (o)
                      else dummy.newobject (getfile(finput^.name));
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.obj.faces','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_obj_faces_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_obj_faces (macro);
end;

procedure proc_import_obj_faces (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'OBJ-Files:*.obj|All files:*.*',@p_import_obj_faces,macro);
end;

{ **************************************************************************** }
{ *********************************** DXF ************************************ }
{ **************************************************************************** }

procedure p_import_dxf_splines (macro : pointer);
var f : treaddxf;
    count,o : integer;
    p : tpolyvector;
begin
     f := Default(treaddxf);
     p := Default(tpolyvector);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           if f.load (finput^.name) then
           begin
                dummy.clear;
                o := 0;
                p.init;
                repeat
                      f.spline (p);
                      if p.length > 0 then
                      begin
                           for count := 1 to p.length do
                           begin
                                dummy.newpoint (gh(p.get(count),0));
                           end;
                           dummy.newline (0);
                           inc (o);
                      end;
                until p.length = 0;
                p.done;
                if o > 0 then dummy.newobject (getfile(finput^.name));
                f.done;
                finput^.append (dummy);
                dummy.clear;
                state[input] := true;
                ref_state[input] := true;
                calculating;
                updating;
                drawing;
           end;
           progress;
           tmacro(macro^).writeredo ('import.dxf.splines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_dxf_splines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_dxf_splines (macro);
end;

procedure proc_import_dxf_splines (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'DXF-files:*.dxf|All files:*.*',@p_import_dxf_splines,macro);
end;

{ ******* }

procedure p_import_dxf_lines (macro : pointer);
var f : treaddxf;
    count,o : integer;
    p : tpolyhyper;
begin
     f := Default(treaddxf);
     p := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           if f.load (finput^.name) then
           begin
                dummy.clear;
                o := 0;
                p.init;
                repeat
                      f.polyline (p);
                      if p.length > 0 then
                      begin
                           for count := 1 to p.length do
                           begin
                                dummy.newpoint (p.get(count));
                                writeln (p.get(count));
                           end;
                           writeln;
                           dummy.newline (0);
                           inc (o);
                      end;
                until p.length = 0;
                p.done;
                if o > 0 then dummy.newobject (getfile(finput^.name));
                f.done;
                finput^.append (dummy);
                dummy.clear;
                state[input] := true;
                ref_state[input] := true;
                calculating;
                updating;
                drawing;
           end;
           progress;
           tmacro(macro^).writeredo ('import.dxf.lines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_dxf_lines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_dxf_lines (macro);
end;

procedure proc_import_dxf_lines (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'DXF-files:*.dxf|All files:*.*',@p_import_dxf_lines,macro);
end;

{ **************************************************************************** }
{ ************************************** VTK ********************************* }
{ **************************************************************************** }

procedure p_import_vtk (macro : pointer);
var f : tfiletext;
    v : vector;
    count,n,n1,l,m : integer;
    s : utf8;
    ch : utf8char;
    points : tpolyvector;
    _vtk,_format,_dataset : utf8;
begin
     f := Default(tfiletext);
     points := Default(tpolyvector);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;

           f.load (finput^.name);
           points.init;
           if f.length > 0 then
           begin
                count := 1;
                _vtk := '';
                _format := '';
                _dataset := '';

                { Header }
                repeat
                      s := lowercase(f.get (count));
                      if (getchar(s,1) = '#') then
                      else if (pos ('vtk',s) = 1) then _vtk := copy (s,5,length(s))
                      else if (pos ('ascii',s) = 1) then _format := 'ascii'
                      else if (pos ('binary',s) = 1) then _format := 'binary'
                      else if (pos ('dataset',s) = 1) then _dataset := copy (s,9,length(s));
                      inc (count);
                until (_dataset <> '') or (count > f.length);

                { Data }
                if (_format = 'ascii') and (_dataset = 'polydata') then
                begin
                     s := '';
                     repeat
                           ch := lowercase(f.getfirst (count));
                           if ch = 'p' then s := lowercase(f.get (count));
                           inc (count);
                     until (pos ('points',s) > 0) or (count > f.length);
                     if (pos ('points',s) > 0) then
                     begin
                          repeat
                                ch := f.getfirst (count);
                                if ch in ['-','0'..'9'] then
                                begin
                                     s := f.get (count);
                                     while (killfirst(s,' ') <> '') do
                                     begin
                                          v.x := cutreal (s);
                                          v.y := cutreal (s);
                                          v.z := cutreal (s);
                                          points.push (v);
                                     end;
                                end
                                else break;
                                inc (count);
                          until (count > f.length);

                          s := '';
                          repeat
                                ch := lowercase(f.getfirst (count));
                                if (ch = 'v') or (ch = 'l') or (ch = 'p') or (ch = 't') then s := lowercase(f.get (count));
                                inc (count);
                          until (pos ('vertices',s) > 0) or (pos ('lines',s) > 0) or
                                (pos ('polygons',s) > 0) or (pos ('triangle_strips',s) > 0) or (count > f.length);
                          if (pos ('vertices',s) > 0) then
                          begin
                               repeat
                                     ch := f.getfirst (count);
                                     if ch in ['-','0'..'9'] then
                                     begin
                                          s := lowercase(f.get (count));
                                          m := cutnat (s); { number }
                                          if m > 0 then
                                          for l := 1 to m do
                                          begin
                                               n := cutnat (s);
                                               if into (n+1,1,points.length) then
                                               begin
                                                    dummy.newpoint (gh(points.get(n+1),0));
                                                    dummy.newline (0);
                                               end;
                                          end;
                                     end
                                     else break;
                                     inc (count);
                               until (count > f.length);
                               dummy.newobject (getfile(finput^.name));
                          end
                          else if (pos ('lines',s) > 0) then
                          begin
                               repeat
                                     ch := f.getfirst (count);
                                     if ch in ['-','0'..'9'] then
                                     begin
                                          s := lowercase(f.get (count));
                                          m := cutnat (s); { number }
                                          if m > 0 then
                                          for l := 1 to m do
                                          begin
                                               n := cutnat (s);
                                               if into (n+1,1,points.length) then dummy.newpoint (gh(points.get(n+1),0));
                                          end;
                                          dummy.newline (0);
                                     end
                                     else break;
                                     inc (count);
                               until (count > f.length);
                               dummy.newobject (getfile(finput^.name));
                          end
                          else if (pos ('polygons',s) > 0) or (pos ('triangle_strips',s) > 0) then
                          begin
                               repeat
                                     ch := f.getfirst (count);
                                     if ch in ['-','0'..'9'] then
                                     begin
                                          s := lowercase(f.get (count));
                                          m := cutnat (s); { number }
                                          n1 := -1;
                                          if m > 0 then
                                          for l := 1 to m do
                                          begin
                                               n := cutnat (s);
                                               if l = 1 then n1 := n;
                                               if into (n+1,1,points.length) then dummy.newpoint (gh(points.get(n+1),0));
                                          end;
                                          if into (n1+1,1,points.length) then dummy.newpoint (gh(points.get(n1+1),0));
                                          dummy.newline (0);
                                     end
                                     else break;
                                     inc (count);
                               until (count > f.length);
                               dummy.newobject (getfile(finput^.name));
                          end
                          else writeln ('  Data missmatch (no vertices, lines, polygons or triangle_strips).');
                     end
                     else writeln ('  Data missmatch (no points).');
                end
                else writeln ('  Wrong data type ('+_dataset+' '+_format+')!');
           end;
           points.done;
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.vtk.poly','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_vtk_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_vtk (macro);
end;

procedure proc_import_vtk (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'VTK-Files:*.vtk|All files:*.*',@p_import_vtk,macro);
end;

{ ***** Unstructed vectors ***** }

procedure p_import_vtk_vectors (macro : pointer);
var f : tfilereadtext;
    v : vector;
    count,n,ni,p,old : integer;
    s : utf8;
    ch : utf8char;
    points : tpolyvector;
    cells : tpolyvector;
    _vtk,_format,_dataset : utf8;
begin
     f := Default(tfilereadtext);
     points := Default(tpolyvector);
     cells := Default(tpolyvector);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;

           f.load (finput^.name);
           points.init;
           cells.init;
           if f.length > 0 then
           begin
                count := 1;
                _vtk := '';
                _format := '';
                _dataset := '';

                {# vtk DataFile Version 2.0

                ASCII
                DATASET UNSTRUCTURED_GRID
                POINTS 1482042 float
                537.328 133.178 0.452165
                381 0.728424 262.68
                ...
                CELLS 9116185 45580925 { start at 0 }
                4 31393 383187 31352 31301
                4 1200725 1200705 1201208 1201196
                ...
                CELL_TYPES 9116185
                10 10 10 10 ...  { 10 = VTK_Tetra }
                }

                { Header }
                repeat
                      s := lowercase(f.get (count));
                      if (getchar(s,1) = '#') then
                      else if (pos ('vtk',s) = 1) then _vtk := copy (s,5,length(s))
                      else if (pos ('ascii',s) = 1) then _format := 'ascii'
                      else if (pos ('binary',s) = 1) then _format := 'binary'
                      else if (pos ('dataset',s) = 1) then _dataset := copy (s,9,length(s));
                      inc (count);
                until (_dataset <> '') or (count > f.length);

                {writeln (_format);
                writeln (_dataset);}

                { Data }
                if (_format = 'ascii') and (_dataset = 'unstructured_grid') then
                begin
                     progress ('  Analyze',0.5+count/f.length/2);
                     s := '';
                     repeat
                           ch := lowercase(f.getfirst (count));
                           if ch = 'p' then s := lowercase(f.get (count));
                           inc (count);
                           progress ('  Analyze',count/f.length);
                     until (pos ('points',s) > 0) or (count > f.length);
                     if (pos ('points',s) > 0) then
                     begin
                          repeat
                                ch := f.getfirst (count);
                                if ch in ['-','0'..'9'] then
                                begin
                                     s := f.get (count);
                                     while (killfirst(s,' ') <> '') do
                                     begin
                                          v.x := cutreal (s);
                                          v.y := cutreal (s);
                                          v.z := cutreal (s);
                                          points.push (v);
                                     end;
                                end
                                else break;
                                inc (count);
                                progress ('  Analyze',0.5+count/f.length/2);
                          until (count > f.length);

                          progress ('  Analyze',0.5+count/f.length/2);
                          s := '';
                          repeat
                                ch := lowercase(f.getfirst (count));
                                if ch = 'c' then s := lowercase(f.get (count));
                                inc (count);
                                progress ('  Analyze',count/f.length);
                          until (pos ('cells',s) > 0) or (count > f.length);
                          if (pos ('cells',s) > 0) then
                          begin
                               repeat
                                     ch := f.getfirst (count);
                                     if ch in ['-','0'..'9'] then
                                     begin
                                          s := f.get (count);
                                          n := cutnat (s);
                                          v := Vzero;
                                          for ni := 1 to n do
                                          begin
                                               p := cutnat (s);
                                               v := v + points.get (p+1);
                                          end;
                                          cells.push (v/n);
                                     end
                                     else break;
                                     inc (count);
                                     progress ('  Analyze',0.5+count/f.length/2);
                               until (count > f.length);

                               {CELL_DATA 9116185
                               SCALARS grayscale float 1
                               LOOKUP_TABLE default
                               0.818289 0.434086 0.544904 0.405026 0.544922 ...

                               VECTORS cell_displacements float
                               3.55869 -0.505236 -1.94358 1.15389 2.53026 ...}
                               progress ('  Analyze',0.5+count/f.length/2);
                               s := '';
                               repeat
                                     ch := lowercase(f.getfirst (count));
                                     if ch = 'v' then s := lowercase(f.get (count));
                                     inc (count);
                                     progress ('  Analyze',0.5+count/f.length/2);
                               until (pos ('vectors',s) > 0) or (count > f.length);
                               if (pos ('vectors',s) > 0) then
                               begin
                                    n := 1;
                                    repeat
                                          ch := f.getfirst (count);
                                          {writeln (ch);}
                                          if ch in ['-','0'..'9'] then
                                          begin
                                               p := 1;
                                               {writeln (f.getchunk(count,1,64));}
                                               s := f.getto (count,p,' ',3); { first chunk }
                                               {writeln (s);}
                                               while (killfirst(s,' ') <> '') do
                                               begin
                                                    old := length (s);
                                                    v.x := cutreal (s);
                                                    v.y := cutreal (s);
                                                    v.z := cutreal (s);
                                                    dummy.newpoint (gh(cells.get(n),0));
                                                    dummy.newpoint (gh(cells.get(n)+v,0));
                                                    dummy.newline (0);
                                                    inc (n);
                                                    p := p + (old-length(s)+1);
                                                    {writeln (f.getchunk(count,p,64));}
                                                    s := f.getto (count,p,' ',3); { next chunk }
                                                    {writeln (s);}
                                                    if (n > cells.length) and (s <> '') then
                                                    begin
                                                         writeln ('Data missmatch (points='+getstring(points.length)+'; cells='+getstring(cells.length)+'; vectors='+getstring(n-1)+'; rest='+getstring(f.getlength(count)-p+1)+')');
                                                         writeln ('>>'+f.getto (count,p,' ',64)+'<<');
                                                         break;
                                                    end;
                                               end;
                                          end
                                          else break;
                                          inc (count);
                                          progress ('  Analyze',0.5+count/f.length/2);
                                          if n > cells.length then break;
                                    until (count > f.length);
                                    if n > 1 then dummy.newobject (getfile(finput^.name));
                               end
                               else writeln ('  Data missmatch (no vectors).');
                          end
                          else writeln ('  Data missmatch (no cells).');
                     end
                     else writeln ('  Data missmatch (no points).');
                end
                else writeln ('  Wrong data type ('+_dataset+' '+_format+')!');
           end;
           cells.done;
           points.done;
           progress;
           f.done;

           finput^.append (dummy);
           dummy.clear;
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.vtk.grid','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_vtk_vectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_vtk_vectors (macro);
end;

procedure proc_import_vtk_vectors (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'VTK-Files:*.vtk|All files:*.*',@p_import_vtk_vectors,macro);
end;

{ **************************************************************************** }
{ ************************************ Export ******************************** }
{ **************************************************************************** }

{ *********************************** Write DXF ****************************** }

procedure p_export_dxf (macro : pointer);
var dxf : twritedxf;
    line : tpolyhyper;
procedure run (f : pcloud);
var z,bl,l : integer;
begin
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 0 then
               begin
                    line.init (l);
                    for bl := 1 to l do
                    begin
                         line.put (bl,f^.getline (z,bl));
                    end;
                    line.done;
               end;
               dxf.polyline(line);
          end;
     end;
end;
begin
     {dxf := Default(twritedxf);}
     line := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           if dxf.save (finput^.name) then
           begin
                run (finput);
                dxf.done;
           end;
           updating;
           tmacro(macro^).writeredo ('export.dxf','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_dxf_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_dxf (macro);
end;

procedure proc_export_dxf (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := '';
     _savefile (finput^.name,'new-curves','dxf','DXF-files:*.dxf|All files:*.*',@p_export_dxf,macro);
end;

{ ******************************* Export OBJ ********************************* }

procedure p_export_obj (macro : pointer);
var o : text;
procedure run (f : pcloud);
var z,count,l : integer;
    h : hyper;
begin
     for z := 1 to f^.getpointlength do
     begin
          h := f^.getpoint (z);
          writeln (o,'v '+getstring(h.x)+' '+getstring(h.y)+' '+getstring(h.z));
     end;
     writeln (o,'s 1');
     for z := 1 to f^.getlinelength do
     begin
          l := f^.getalllinepointlength (z);
          if l > 0 then
          begin
                if l = 1 then
                begin
                     write (o,'p ');
                     writeln (o,getstring(f^.getpline (z,1)));
                end
                else if f^.getline (z,1) = f^.getline (z,l) then
                begin
                     write (o,'f ');
                     for count := 1 to l-1 do
                     begin
                          if count < l-1 then write (o,getstring(f^.getpline (z,count))+' ')
                                         else write (o,getstring(f^.getpline (z,count)));
                     end;
                     writeln (o);
                end
                else
                begin
                     write (o,'l ');
                     for count := 1 to l do
                     begin
                          if count < l then write (o,getstring(f^.getpline (z,count))+' ')
                                       else write (o,getstring(f^.getpline (z,count)));
                     end;
                     writeln (o);
                end;
          end;
     end;
end;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          if finput^.getpointlength > 0 then
          begin
               if assignwrite (o,finput^.name) then
               begin
                    run (finput);
                    close (o);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('export.obj','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_obj_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_obj (macro);
end;

procedure proc_export_obj (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-raw','obj','OBJ-files:*.obj|All files:*.*',@p_export_obj,macro);
end;

{ ******************************** Reference OBJ ***************************** }

procedure p_export_ref_obj (macro : pointer);
var o : text;
procedure run (f : pcloud);
var z,l,count : integer;
    h : hyper;
    plist : tpolyhyper;
begin
     plist := Default(tpolyhyper);
     plist.init;
     for z := 1 to f^.getpointlength do
     begin
          h := f^.getpoint (z);
          if plist.search (h) = 0 then plist.put (plist.length+1,h);
     end;
     writeln (o,'# OBJ-File - '+f^.name);
     writeln (o,'# Version 1.0');
     for z := 1 to plist.length do
     begin
          h := plist.get (z);
          writeln (o,'v '+getstring(h.x)+' '+getstring(h.y)+' '+getstring(h.z));
     end;
     writeln (o,'s 1');
     for z := 1 to f^.getlinelength do
     begin
          l := f^.getalllinepointlength (z);
          if l > 0 then
          begin
                if l = 1 then
                begin
                     write (o,'p ');
                     h := f^.getline (z,1);
                     writeln (o,getstring(plist.search(h)));
                end
                else if f^.getline (z,1) = f^.getline (z,l) then
                begin
                     write (o,'f ');
                     for count := 1 to l-1 do
                     begin
                          h := f^.getline (z,count);
                          if count < l-1 then write (o,getstring(plist.search(h))+' ')
                                         else write (o,getstring(plist.search(h)));
                     end;
                     writeln (o);
                end
                else
                begin
                     write (o,'l ');
                     for count := 1 to l do
                     begin
                          h := f^.getline (z,count);
                          if count < l then write (o,getstring(plist.search(h))+' ')
                                       else write (o,getstring(plist.search(h)));
                     end;
                     writeln (o);
                end;
          end;
     end;
     plist.done;
end;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          if finput^.getpointlength > 0 then
          begin
               if assignwrite (o,finput^.name) then
               begin
                    run (finput);
                    close (o);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('export.ref.obj','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_ref_obj_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_ref_obj (macro);
end;

procedure proc_export_ref_obj (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-obj','obj','OBJ-files:*.obj|All files:*.*',@p_export_ref_obj,macro);
end;

{ ********************************* Mesh OBJ ********************************* }

procedure p_export_mesh_obj (macro : pointer);
var o : text;
procedure run (f : pcloud);
var z,l,count : integer;
    h,h1,h2,h3,h4,h5,h6,h7,h8 : hyper;
    plist : tpolyhyper;
begin
     plist := Default(tpolyhyper);
     plist.init;
     for z := 1 to f^.getpointlength do
     begin
          h := f^.getpoint (z);
          if plist.search (h) = 0 then plist.put (plist.length+1,h);
     end;
     writeln (o,'# OBJ-File - '+f^.name);
     writeln (o,'# Version 1.0');
     for z := 1 to plist.length do
     begin
          h := plist.get (z);
          writeln (o,'v '+getstring(h.x)+' '+getstring(h.y)+' '+getstring(h.z));
     end;
     writeln (o,'s 1');
     for z := 1 to f^.getlinelength do
     begin
          l := f^.getalllinepointlength (z);
          if l > 3 then  { for FEM }
          begin
                if f^.getline (z,1) = f^.getline (z,l) then
                begin
                     write (o,'f ');
                     for count := 1 to l-1 do
                     begin
                          h := f^.getline (z,count);
                          if count < l-1 then write (o,getstring(plist.search(h))+' ')
                                         else write (o,getstring(plist.search(h)));
                     end;
                     writeln (o);
                end
                else if l = 8 then
                begin
                     h1 := f^.getline (z,1);
                     h2 := f^.getline (z,2);
                     h3 := f^.getline (z,3);
                     h4 := f^.getline (z,4);
                     h5 := f^.getline (z,5);
                     h6 := f^.getline (z,6);
                     h7 := f^.getline (z,7);
                     h8 := f^.getline (z,8);
                     writeln (o,'f '+getstring(plist.search(h1))+' '+getstring(plist.search(h2))+' '+getstring(plist.search(h6))+' '+getstring(plist.search(h5)));
                     writeln (o,'f '+getstring(plist.search(h2))+' '+getstring(plist.search(h3))+' '+getstring(plist.search(h7))+' '+getstring(plist.search(h6)));
                     writeln (o,'f '+getstring(plist.search(h3))+' '+getstring(plist.search(h4))+' '+getstring(plist.search(h8))+' '+getstring(plist.search(h7)));
                     writeln (o,'f '+getstring(plist.search(h4))+' '+getstring(plist.search(h1))+' '+getstring(plist.search(h5))+' '+getstring(plist.search(h8)));
                     writeln (o,'f '+getstring(plist.search(h1))+' '+getstring(plist.search(h2))+' '+getstring(plist.search(h3))+' '+getstring(plist.search(h4)));
                     writeln (o,'f '+getstring(plist.search(h5))+' '+getstring(plist.search(h6))+' '+getstring(plist.search(h7))+' '+getstring(plist.search(h8)));
                end
                else if l = 6 then
                begin
                     h1 := f^.getline (z,1);
                     h2 := f^.getline (z,2);
                     h3 := f^.getline (z,3);
                     h4 := f^.getline (z,4);
                     h5 := f^.getline (z,5);
                     h6 := f^.getline (z,6);
                     writeln (o,'f '+getstring(plist.search(h1))+' '+getstring(plist.search(h2))+' '+getstring(plist.search(h5))+' '+getstring(plist.search(h4)));
                     writeln (o,'f '+getstring(plist.search(h2))+' '+getstring(plist.search(h3))+' '+getstring(plist.search(h6))+' '+getstring(plist.search(h5)));
                     writeln (o,'f '+getstring(plist.search(h3))+' '+getstring(plist.search(h1))+' '+getstring(plist.search(h4))+' '+getstring(plist.search(h6)));
                     writeln (o,'f '+getstring(plist.search(h1))+' '+getstring(plist.search(h2))+' '+getstring(plist.search(h3)));
                     writeln (o,'f '+getstring(plist.search(h4))+' '+getstring(plist.search(h5))+' '+getstring(plist.search(h6)));
                end
                else if l = 4 then
                begin
                     h1 := f^.getline (z,1);
                     h2 := f^.getline (z,2);
                     h3 := f^.getline (z,3);
                     h4 := f^.getline (z,4);
                     writeln (o,'f '+getstring(plist.search(h1))+' '+getstring(plist.search(h2))+' '+getstring(plist.search(h3)));
                     writeln (o,'f '+getstring(plist.search(h2))+' '+getstring(plist.search(h3))+' '+getstring(plist.search(h4)));
                     writeln (o,'f '+getstring(plist.search(h3))+' '+getstring(plist.search(h1))+' '+getstring(plist.search(h4)));
                     writeln (o,'f '+getstring(plist.search(h4))+' '+getstring(plist.search(h1))+' '+getstring(plist.search(h2)));
                end;
          end;
     end;
     plist.done;
end;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          if finput^.getpointlength > 0 then
          begin
               if assignwrite (o,finput^.name) then
               begin
                    run (finput);
                    close (o);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('export.mesh.obj','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_mesh_obj_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_mesh_obj (macro);
end;

procedure proc_export_mesh_obj (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-mesh','obj','OBJ-files:*.obj|All files:*.*',@p_export_mesh_obj,macro);
end;

{ ******************************** Tube OBJ ********************************** }

procedure p_export_tube_obj (macro : pointer);
var o : text;
    size : real;
procedure run (f : pcloud;r : real);
var z,l,count : integer;
    g,h : hyper;
    n : vector;
    i : array[1..8] of integer;
    plist,nlist : tpolyhyper;
    procedure putlist (a : hyper;b : vector);
    begin
         if plist.search (a+gh(b,0)) = 0 then
         begin
              plist.push (a+gh(b,0));
              nlist.push (norm(gh(b,0)));
         end;
    end;
begin
     plist := Default(tpolyhyper);
     nlist := Default(tpolyhyper);
     if f^.getlinelength > 0 then
     begin
          plist.init; { pointer list }
          nlist.init; { normal list }
          for z := 1 to f^.getlinelength do { write faces }
          begin
               progress ('  Write OBJ-file',1/4*z/f^.getlinelength);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    n := Vzero;
                    g := f^.getline (z,1);
                    for count := 2 to l do
                    begin
                         h := f^.getline (z,count);
                         n := n + (gv(h.x,h.y,h.z)-gv(g.x,g.y,g.z));
                         g := h;
                    end;
                    n := norm (n);
                    if (n.x > n.y) and (n.x > n.z) then
                    begin
                         for count := 1 to l do
                         begin
                              h := f^.getline (z,count);
                              putlist (h,gv (0,r,r));
                              putlist (h,gv (0,r,-r));
                              putlist (h,gv (0,-r,-r));
                              putlist (h,gv (0,-r,r));
                         end;
                    end
                    else if (n.y > n.x) and (n.y > n.z) then
                    begin
                         for count := 1 to l do
                         begin
                              h := f^.getline (z,count);
                              putlist (h,gv (r,0,r));
                              putlist (h,gv (r,0,-r));
                              putlist (h,gv (-r,0,-r));
                              putlist (h,gv (-r,0,r));
                         end;
                    end
                    else
                    begin
                         for count := 1 to l do
                         begin
                              h := f^.getline (z,count);
                              putlist (h,gv (r,r,0));
                              putlist (h,gv (r,-r,0));
                              putlist (h,gv (-r,-r,0));
                              putlist (h,gv (-r,r,0));
                         end;
                    end
               end;
          end;
          writeln (o,'# OBJ-File - '+f^.name);
          writeln (o,'# Version 1.0');
          for z := 1 to plist.length do { write pointer list }
          begin
               progress ('  Write OBJ-file',1/4*z/plist.length+1/4);
               h := plist.get (z);
               writeln (o,'v '+getstring(h.x)+' '+getstring(h.y)+' '+getstring(h.z));
          end;
          for z := 1 to plist.length do { write normal list }
          begin
               progress ('  Write OBJ-file',1/4*z/plist.length+2/4);
               h := nlist.get (z);
               writeln (o,'vn '+getstring(0)+' '+getstring(r)+' '+getstring(r));
          end;
          writeln (o,'s 1');
          for z := 1 to f^.getlinelength do { write faces }
          begin
               progress ('  Write OBJ-file',1/4*z/plist.length+3/4);
               l := f^.getalllinepointlength (z);
               if l > 1 then
               begin
                    n := Vzero;
                    g := f^.getline (z,1);
                    for count := 2 to l do
                    begin
                         h := f^.getline (z,count);
                         n := n + (gv(h.x,h.y,h.z)-gv(g.x,g.y,g.z));
                         g := h;
                    end;
                    n := norm (n);
                    if (n.x > n.y) and (n.x > n.z) then
                    begin
                         g := f^.getline (z,1);
                         i[1] := plist.search(gh(gv(g.x,g.y,g.z)+gv(0,r,r),0));
                         i[2] := plist.search(gh(gv(g.x,g.y,g.z)+gv(0,r,-r),0));
                         i[3] := plist.search(gh(gv(g.x,g.y,g.z)+gv(0,-r,-r),0));
                         i[4] := plist.search(gh(gv(g.x,g.y,g.z)+gv(0,-r,r),0));
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[3]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[4]));
                         for count := 1 to l-1 do { midline }
                         begin
                              h := f^.getline (z,count+1);
                              i[5] := plist.search(gh(gv(h.x,h.y,h.z)+gv(0,r,r),0));
                              i[6] := plist.search(gh(gv(h.x,h.y,h.z)+gv(0,r,-r),0));
                              i[7] := plist.search(gh(gv(h.x,h.y,h.z)+gv(0,-r,-r),0));
                              i[8] := plist.search(gh(gv(h.x,h.y,h.z)+gv(0,-r,r),0));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[6])+' '+getstring(i[5]));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[7])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[3])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[8])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[4])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[5])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[1])+' '+getstring(i[5]));
                              i[1] := i[5];
                              i[2] := i[6];
                              i[3] := i[7];
                              i[4] := i[8];
                         end;
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[2]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[4])+' '+getstring(i[3]));
                    end
                    else if (n.y > n.x) and (n.y > n.z) then
                    begin
                         g := f^.getline (z,1);
                         i[1] := plist.search(gh(gv(g.x,g.y,g.z)+gv(r,0,r),0));
                         i[2] := plist.search(gh(gv(g.x,g.y,g.z)+gv(r,0,-r),0));
                         i[3] := plist.search(gh(gv(g.x,g.y,g.z)+gv(-r,0,-r),0));
                         i[4] := plist.search(gh(gv(g.x,g.y,g.z)+gv(-r,0,r),0));
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[3]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[4]));
                         for count := 1 to l-1 do { midline }
                         begin
                              h := f^.getline (z,count+1);
                              i[5] := plist.search(gh(gv(h.x,h.y,h.z)+gv(r,0,r),0));
                              i[6] := plist.search(gh(gv(h.x,h.y,h.z)+gv(r,0,-r),0));
                              i[7] := plist.search(gh(gv(h.x,h.y,h.z)+gv(-r,0,-r),0));
                              i[8] := plist.search(gh(gv(h.x,h.y,h.z)+gv(-r,0,r),0));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[6])+' '+getstring(i[5]));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[7])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[3])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[8])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[4])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[5])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[1])+' '+getstring(i[5]));
                              i[1] := i[5];
                              i[2] := i[6];
                              i[3] := i[7];
                              i[4] := i[8];
                         end;
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[2]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[4])+' '+getstring(i[3]));
                    end
                    else
                    begin
                         g := f^.getline (z,1);
                         i[1] := plist.search(gh(gv(g.x,g.y,g.z)+gv(r,r,0),0));
                         i[2] := plist.search(gh(gv(g.x,g.y,g.z)+gv(r,-r,0),0));
                         i[3] := plist.search(gh(gv(g.x,g.y,g.z)+gv(-r,-r,0),0));
                         i[4] := plist.search(gh(gv(g.x,g.y,g.z)+gv(-r,r,0),0));
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[3]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[4]));
                         for count := 1 to l-1 do { midline }
                         begin
                              h := f^.getline (z,count+1);
                              i[5] := plist.search(gh(gv(h.x,h.y,h.z)+gv(r,r,0),0));
                              i[6] := plist.search(gh(gv(h.x,h.y,h.z)+gv(r,-r,0),0));
                              i[7] := plist.search(gh(gv(h.x,h.y,h.z)+gv(-r,-r,0),0));
                              i[8] := plist.search(gh(gv(h.x,h.y,h.z)+gv(-r,r,0),0));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[6])+' '+getstring(i[5]));
                              writeln (o,'f '+getstring(i[1])+' '+getstring(i[2])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[7])+' '+getstring(i[6]));
                              writeln (o,'f '+getstring(i[2])+' '+getstring(i[3])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[8])+' '+getstring(i[7]));
                              writeln (o,'f '+getstring(i[3])+' '+getstring(i[4])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[5])+' '+getstring(i[8]));
                              writeln (o,'f '+getstring(i[4])+' '+getstring(i[1])+' '+getstring(i[5]));
                              i[1] := i[5];
                              i[2] := i[6];
                              i[3] := i[7];
                              i[4] := i[8];
                         end;
                         { cup }
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[3])+' '+getstring(i[2]));
                         writeln (o,'f '+getstring(i[1])+' '+getstring(i[4])+' '+getstring(i[3]));
                    end;
               end;
          end;
          nlist.done;
          plist.done;
          progress;
     end;
end;

begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          size := _getreal (export_obj_tube_size,macro,2);
          if finput^.getpointlength > 0 then
          begin
               if assignwrite (o,finput^.name) then
               begin
                    run (finput,size);
                    close (o);
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('export.tube.obj','"'+finput^.name+'"'+' '+getstring(size));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_tube_obj_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_tube_obj (macro);
end;

procedure proc_export_tube_obj (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-tube','obj','OBJ-files:*.obj|All files:*.*',@p_export_tube_obj,macro);
end;

{ ******************************** TrackVis ********************************** }

type TTrackvisHeader = record
            idstring : array [1..6] of system.char;
            dim : array[1..3] of system.smallint;
            voxel_size, origin  : array[1..3] of system.single;
            n_scalars : system.smallint;
            scalar_name  : array [1..10,1..20] of system.char;
            n_properties : system.smallint;
            property_name : array [1..10,1..20] of system.char;
            vox_to_ras : array [1..4,1..4] of system.single;
            reserved : array [1..444] of system.char;
            voxel_order, pad2 : array [1..4] of system.char;
            image_orientation_patient : array [1..6] of system.single;
            pad1 : array [1..2] of system.char;
            invert_x, invert_y, invert_z, swap_xy, swap_yz, swap_zx : system.char;
            n_count, version, hdr_size : system.longint;
     end;

procedure p_import_trackvis (macro : pointer);
var f : file;
    header : TTrackvisHeader;
    track : system.longint;
    point : array[1..6] of system.single;
    count,count2 : integer;
    _trackvis : real;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     _trackvis := _getreal (export_trackvis,macro,2);
     if finput^.name <> '' then
     begin
           dummy.clear;
           if assignread (f,finput^.name) then
           begin
                if not (system.filesize (f) > 1000) then writeln ('Empty file!')
                else
                begin
                     blockread (f,header,sizeof(header));

                     finput^.dim := gh(header.dim[1],header.dim[2],header.dim[3],0);
                     finput^.scale := gh(header.voxel_size[1],header.voxel_size[2],header.voxel_size[3],1);
                     finput^.move := gh(header.origin[1],header.origin[2],header.origin[3],0);

                    { writeln (header.idstring);
                     writeln (getstring(header.dim[1])+' '+getstring(header.dim[2])+' '+getstring(header.dim[3]));
                     writeln (getstring(header.voxel_size[1])+' '+getstring(header.voxel_size[2])+' '+getstring(header.voxel_size[3]));
                     writeln (getstring(header.origin[1])+' '+getstring(header.origin[2])+' '+getstring(header.origin[3]));
                     writeln (getstring(header.n_scalars));
                     for count := 1 to 10 do writeln (header.scalar_name[count]);
                     writeln (getstring(header.n_properties));
                     for count := 1 to 10 do writeln (header.property_name[count]);
                     writeln ('................');
                     for count := 1 to 10 do
                         for count2 := 1 to 10 do writeln (header.vox_to_ras[count,count2]);
                     writeln ('................');
                     writeln (header.voxel_order);
                     writeln (header.pad2);
                     for count := 1 to 6 do writeln (getstring(header.image_orientation_patient[count]));
                     writeln (getstring(ord(header.pad1[1]))+' '+getstring(ord(header.pad1[2])));
                     writeln (getstring(ord(header.invert_x)));
                     writeln (getstring(ord(header.invert_y)));
                     writeln (getstring(ord(header.invert_z)));
                     writeln (getstring(ord(header.swap_xy)));
                     writeln (getstring(ord(header.swap_yz)));
                     writeln (getstring(ord(header.swap_zx)));
                     writeln (getstring(header.n_count));
                     writeln (getstring(header.version));
                     writeln (getstring(header.hdr_size)); }

                     if header.n_count > 0 then
                     begin
                          seek (f,header.hdr_size);
                          for count := 1 to header.n_count do
                          begin
                               progress ('  Analyze Tracks-file',count/header.n_count);
                               blockread (f,track,sizeof (track));
                               if track > 0 then
                               begin
                                    for count2 := 1 to track do
                                    begin
                                         blockread (f,point,(3+header.n_scalars)*4);
                                         if track > _trackvis then
                                         begin
                                              v := gh(point[1],point[2],point[3],0);
                                              dummy.newpoint (v);
                                         end;
                                    end;
                                    blockread (f,point,(header.n_properties*4));
                                    if track > _trackvis then dummy.newline (0);
                               end;
                          end;
                          progress;
                          dummy.newobject (getfile (finput^.name));
                     end
                     else writeln ('Empty file!');
                     finput^.append (dummy);
                     dummy.clear;
                     state[input] := true;
                     ref_state[input] := true;
                     calculating;
                     updating;
                     drawing;
                end;
                close (f);
           end;
           tmacro(macro^).writeredo ('import.trackvis','"'+finput^.name+'"'+' '+getstring(_trackvis));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_trackvis_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_trackvis (macro);
end;

procedure proc_import_trackvis (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'Track-files:*.trk|All files:*.*',@p_import_trackvis,macro);
end;

{ ****** }

procedure p_export_trackvis (macro : pointer);
var f : file;
    header : TTrackvisHeader;
    track : system.longint;
    point : array[1..6] of system.single;
    count,count2 : integer;
    v : hyper;
    olddim : boolean;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
          olddim := _getcheckbutton (export_trackvis_toggle_olddim,macro,2);
          if assignwrite (f,finput^.name) then
          begin
               header.idstring := 'TRACK'+#0;
               if olddim then
               begin
                    header.dim[1] := round(finput^.dim.x); header.dim[2] := round(finput^.dim.y); header.dim[3] := round(finput^.dim.z);
                    header.voxel_size[1] :=  finput^.scale.x; header.voxel_size[2] :=  finput^.scale.y; header.voxel_size[3] :=  finput^.scale.z;
                    header.origin[1] := finput^.move.x; header.origin[2] :=  finput^.move.y; header.origin[3] :=  finput^.move.z;
               end
               else
               begin
                    v := finput^.max-finput^.min; if v.x*v.y*v.z = 0  then v := gh (10,10,10,10);
                    header.dim[1] := round(v.x); header.dim[2] := round(v.y); header.dim[3] := round(v.z);
                    header.voxel_size[1] := 1; header.voxel_size[2] := 1; header.voxel_size[3] := 1;
                    header.origin[1] := 0; header.origin[2] := 0; header.origin[3] := 0;
               end;
               header.n_scalars := 0;
               for count := 1 to 10 do header.scalar_name[count] := #0+#0+#0+#0+#0 + #0+#0+#0+#0+#0;
               header.n_properties := 0;
               for count := 1 to 10 do header.property_name[count] := #0+#0+#0+#0+#0 + #0+#0+#0+#0+#0;
               for count := 1 to 4 do
                   for count2 := 1 to 4 do header.vox_to_ras[count,count2] := 0;
               for count := 1 to 444 do header.reserved[count] := #0;
               header.voxel_order := 'LPS'#0;
               header.pad2 := 'LPS'+#0;
               header.image_orientation_patient[1] := 1; header.image_orientation_patient[2] := 0; header.image_orientation_patient[3] := 0;
               header.image_orientation_patient[4] := 0; header.image_orientation_patient[5] := 1; header.image_orientation_patient[6] := 0;
               header.pad1 := #0+#0;
               header.invert_x := #0;
               header.invert_y := #0;
               header.invert_z := #0;
               header.swap_xy := #0;
               header.swap_yz := #0;
               header.swap_zx := #0;
               header.n_count := finput^.getlinelength;
               header.version := 2;
               header.hdr_size := 1000;

               blockwrite (f,header,sizeof(header));

               for count := 1 to finput^.getlinelength do
               begin
                    progress ('  Write Track-file',count/finput^.getlinelength);
                    track := finput^.getalllinepointlength(count);
                    blockwrite (f,track,sizeof (track));
                    for count2 := 1 to track do
                    begin
                         v := finput^.getline(count,count2);
                         point[1] := v.x;
                         point[2] := v.y;
                         point[3] := v.z;
                         point[4] := v.t;
                         blockwrite (f,point,(3+header.n_scalars)*4);
                    end;
                    point[1] := 0; point[2] := 0; point[3] := 0; point[4] := 0;
                    blockwrite (f,point,(header.n_properties*4));
               end;
               progress;
               close (f);
          end;
          updating;
          tmacro(macro^).writeredo ('export.trackvis','"'+finput^.name+'"'+' '+getstring(olddim));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_trackvis_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_trackvis (macro);
end;

procedure proc_export_trackvis (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-trackvis','trk','Track-files:*.trk|All files:*.*',@p_export_trackvis,macro);
end;

{ ************************************* SWC ********************************** }
{ http://www.neuronland.org/NLMorphologyConverter/MorphologyFormats/SWC/Spec.html }

procedure p_import_swc (macro : pointer);
var f : Tfiletext;
    count,count2 : integer;
    s : utf16;
    id,typ,mat,parent : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           if f.load(finput^.name) then
           begin
                if f.length > 0 then
                begin
                     mat := 0;
                     count2 := 0;
                     for count := 1 to f.length do
                     begin
                          s := killfirst (f.get(count),' ');
                          id := getnat(split (s,' '));
                          typ := getnat(split (s,' '));
                          v.x := getreal(split (s,' '));
                          v.y := getreal(split (s,' '));
                          v.z := getreal(split (s,' '));
                          v.t := getreal(split (s,' '));
                          parent := getnat (s);

                          if id > 0 then
                          begin
                               if parent > 0 then
                               begin
                                    dummy.newpoint (v);
                                    inc (count2);
                               end
                               else
                               begin
                                    dummy.newline (mat);
                                    count2 := 0;
                                    dummy.newpoint (v);
                                    inc (count2);
                               end;
                               mat := typ;
                          end;
                     end;
                     if count2 > 0 then
                     begin
                          dummy.newline (mat);
                          dummy.newobject ('swc');
                     end;
                     finput^.append (dummy);
                     dummy.clear;
                     state[input] := true;
                     ref_state[input] := true;
                     calculating;
                     updating;
                     drawing;
                end
                else  writeln ('Empty file!');
           end;
           f.done;
           tmacro(macro^).writeredo ('import.swc','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_swc_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_swc (macro);
end;

procedure proc_import_swc (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'SWC-files:*.swc|All files:*.*',@p_import_swc,macro);
end;

{ ****** }

procedure p_export_swc (macro : pointer);
var t : text;
    file_len,line,line_len,point,mat : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
          if assignwrite (t,finput^.name) then
          begin
               file_len := 1;
               for line := 1 to finput^.getlinelength do
               begin
                    mat := finput^.getallmaterial(line);
                    progress ('  Write SWC-file',line/finput^.getlinelength);
                    line_len := finput^.getalllinepointlength(line);
                    if line_len > 0 then
                    begin
                         for point := 1 to line_len do
                         begin
                              v := finput^.getline(line,point);
                              { 0 - undefined
                                1 - soma
                                2 - axon
                                3 - (basal) dendrite
                                4 - apical dendrite
                                5+ - custom }
                              if point = 1 then writeln (t,getstring(file_len)+' '+getstring(mat)+' '+getstring(v.x)+' '+getstring(v.y)+' '+getstring(v.z)+' '+getstring(v.t)+' -1')
                                           else writeln (t,getstring(file_len)+' '+getstring(mat)+' '+getstring(v.x)+' '+getstring(v.y)+' '+getstring(v.z)+' '+getstring(v.t)+' '+getstring(file_len-1));
                              inc (file_len);
                         end;
                    end;
               end;
               progress;
               close (t);
          end;
          updating;
          tmacro(macro^).writeredo ('export.swc','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_swc_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_swc (macro);
end;

procedure proc_export_swc (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-swc','swc','SWC-files:*.swc|All files:*.*',@p_export_swc,macro);
end;

{ ******************************* Sphere-Tree ******************************** }

procedure p_import_sphere_tree (macro : pointer);
var f : Tfiletext;
    c : complexnat;
    v : hyper;
    m,n,count : integer;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           dummy.clear;
           if f.load(finput^.name) then
           begin
                if f.length > 1 then
                begin
                     count := 1;
                     c := getcomplexnat (f.get(count));
                     inc (count);
                     if (c.x > 0) and (c.y > 0) then
                     begin
                          { Root }
                          v := gethyper(f.get(count));
                          inc (count);
                          dummy.newpoint (v);
                          dummy.newline (0);
                          dummy.newobject ('level_1');
                          { All other branches }
                          if c.x > 1 then
                          begin
                               for m := 2 to c.x do
                               begin
                                    for n := 1 to c.y**(m-1) do
                                    begin
                                         v := gethyper(f.get(count));
                                         inc (count);
                                         if v.t > 0 then { not empty }
                                         begin
                                              dummy.newpoint (v);
                                              dummy.newline (1+((n-1) div c.y));
                                         end;
                                    end;
                                    dummy.newobject ('level_'+getstring(m));
                               end;
                          end;
                     end
                     else writeln ('Empty file!');
                     finput^.append (dummy);
                     dummy.clear;
                     state[input] := true;
                     ref_state[input] := true;
                     calculating;
                     updating;
                     drawing;
                end
                else  writeln ('Empty file!');
           end;
           f.done;
           tmacro(macro^).writeredo ('import.sphere-tree','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_sphere_tree_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_sphere_tree (macro);
end;

procedure proc_import_sphere_tree (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'Sphere-files:*.sph|All files:*.*',@p_import_sphere_tree,macro);
end;

{ **************************************************************************** }
{ ******************************* Import Matlab ****************************** }
{ **************************************************************************** }

procedure p_import_matlab_2dpoints (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v : hyper;
    s,t : utf16;
begin
     ft := Default(tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := killfirst(killfirst(ft.get(l),' '),#9);
                              if length(t) > 0 then
                                 if isdigit (t) then
                                 begin
                                      v.x := cutreal(t);
                                      v.y := cutreal(t);
                                      v.z := 0;
                                      v.t := 0;
                                      dummy.newpoint (v);
                                      dummy.newline (0);
                                      inc (p);
                                 end;
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               dummy.clear;
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.2dpoints','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_2dpoints_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_2dpoints (macro);
end;

procedure proc_import_matlab_2dpoints (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_2dpoints,macro);
end;

{ **************************************************************************** }

procedure p_import_matlab_2dvectors (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v,u : hyper;
    s,t : utf16;
begin
     ft := Default(tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := killfirst(killfirst(ft.get(l),' '),#9);
                              if length(t) > 0 then
                                 if isdigit (t) then
                                 begin
                                      v.x := cutreal(t);
                                      v.y := cutreal(t);
                                      v.z := 0;
                                      v.t := 0;
                                      dummy.newpoint (v);
                                      u.x := v.x+cutreal(t);
                                      u.y := v.y+cutreal(t);
                                      u.z := 0;
                                      u.t := 0;
                                      dummy.newpoint (u);
                                      dummy.newline (0);
                                      inc (p);
                                 end;
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.2dvectors','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_2dvectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_2dvectors (macro);
end;

procedure proc_import_matlab_2dvectors (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_2dvectors,macro);
end;

{ **************************************************************************** }

procedure p_import_matlab_2dlines (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v : hyper;
    s,t : utf16;
begin
     ft := Default(Tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := ft.get(l);
                              while (length(t) > 0) do
                              begin
                                   t := killfirst(killfirst(t,' '),#9);
                                   if isdigit (t) then
                                   begin
                                        v.x := cutreal(t);
                                        v.y := cutreal(t);
                                        v.z := 0;
                                        v.t := 0;
                                        dummy.newpoint (v);
                                   end
                                   else t := '';
                              end;
                              dummy.newline (0);
                              inc (p);
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         writeln (p);
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.2dlines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_2dlines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_2dlines (macro);
end;

procedure proc_import_matlab_2dlines (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_2dlines,macro);
end;

{ **************************************************************************** }
{ **************************************************************************** }
{ **************************************************************************** }

procedure p_import_matlab_points (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v : hyper;
    s,t : utf16;
begin
     ft := Default(tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := killfirst(killfirst(ft.get(l),' '),#9);
                              if length(t) > 0 then
                                 if isdigit (t) then
                                 begin
                                      v.x := cutreal(t);
                                      v.y := cutreal(t);
                                      v.z := cutreal(t);
                                      v.t := 0;
                                      dummy.newpoint (v);
                                      dummy.newline (0);
                                      inc (p);
                                 end;
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.points','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_points_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_points (macro);
end;

procedure proc_import_matlab_points (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_points,macro);
end;

{ **************************************************************************** }

procedure p_import_matlab_vectors (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v,u : hyper;
    s,t : utf16;
begin
     ft := Default(tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := killfirst(killfirst(ft.get(l),' '),#9);
                              if length(t) > 0 then
                                 if isdigit (t) then
                                 begin
                                      v.x := cutreal(t);
                                      v.y := cutreal(t);
                                      v.z := cutreal(t);
                                      v.t := 0;
                                      dummy.newpoint (v);
                                      u.x := v.x+cutreal(t);
                                      u.y := v.y+cutreal(t);
                                      u.z := v.z+cutreal(t);
                                      u.t := 0;
                                      dummy.newpoint (u);
                                      dummy.newline (0);
                                      inc (p);
                                 end;
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.vectors','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_vectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_vectors (macro);
end;

procedure proc_import_matlab_vectors (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_vectors,macro);
end;

{ **************************************************************************** }

procedure p_import_matlab_lines (macro : pointer);
var ft : Tfiletext;
    list : tfilelist;
    l,p,count : integer;
    v : hyper;
    s,t : utf16;
begin
     ft := Default(tfiletext);
     list := Default(tfilelist);

     _cursor_watch;
     format.push;
     format := format_txt;
     p := 0;
     dummy.clear;
     if finput^.name <> '' then
     begin
          s := getdir (finput^.name);
          list.init (finput^.name);
          if list.length > 0 then
          begin
               for count := 1 to list.length do
               begin
                    if s <> '' then
                    begin
                    {$ifdef LINUX}
                         ft.load (s+'/'+list.get(count));
                    {$else}
                         ft.load (s+'\'+list.get(count));
                    {$endif}
                    end
                    else ft.load (list.get(count));
                    if ft.length > 0 then
                    begin
                         for l := 1 to ft.length do
                         begin
{                              progress ('  Read Matlab-file',l/ft.length);}
                              t := ft.get(l);
                              while (length(t) > 0) do
                              begin
                                   t := killfirst(killfirst(t,' '),#9);
                                   if isdigit (t) then
                                   begin
                                        v.x := cutreal(t);
                                        v.y := cutreal(t);
                                        v.z := cutreal(t);
                                        v.t := 0;
                                        dummy.newpoint (v);
                                   end
                                   else t := '';
                              end;
                              dummy.newline (0);
                              inc (p);
                         end;
                    end;
                    ft.done;
                    if p > 0 then
                    begin
                         writeln (p);
                         dummy.newobject (getfile(list.get(count)));
                         p := 0;
                    end;
{                    progress;}
               end;
               finput^.append (dummy);
               state[input] := true;
               ref_state[input] := true;
               calculating;
               updating;
               drawing;
          end;
          list.done;
          tmacro(macro^).writeredo ('import.matlab.lines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_matlab_lines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_matlab_lines (macro);
end;

procedure proc_import_matlab_lines (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_matlab_lines,macro);
end;

{ **************************************************************************** }
{ ******************************* Export Matlab ****************************** }
{ **************************************************************************** }

procedure p_export_matlab_2dpoints (macro : pointer);
var f : text;
    count,track : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
 {                    progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track = 1 then
                     begin
                          v := finput^.getline(count,1);
                          writeln (f,getstring(v.x)+#9+getstring(v.y));
                     end;
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.2dpoints','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_2dpoints_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_2dpoints (macro);
end;

procedure proc_export_matlab_2dpoints (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-points','txt',@p_export_matlab_2dpoints,macro);
end;

{ **************************************************************************** }

procedure p_export_matlab_2dvectors (macro : pointer);
var f : text;
    count,track : integer;
    v,u : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
{                     progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track = 2 then
                     begin
                          v := finput^.getline(count,1);
                          u := norm(finput^.getline(count,2)-v);
                          writeln (f,getstring(v.x)+#9+getstring(v.y)+#9+getstring(u.x)+#9+getstring(u.y));
                     end;
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.2dvectors','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_2dvectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_2dvectors (macro);
end;

procedure proc_export_matlab_2dvectors (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-vectors','txt',@p_export_matlab_2dvectors,macro);
end;

{ **************************************************************************** }

procedure p_export_matlab_2dlines (macro : pointer);
var f : text;
    count,track,p : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
{                     progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track > 0 then
                        for p := 1 to track do
                        begin
                             v := finput^.getline(count,p);
                             if p <> track then write (f,getstring(v.x)+#9+getstring(v.y)+#9)
                                           else write (f,getstring(v.x)+#9+getstring(v.y));
                        end;
                     writeln (f);
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.2dlines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_2dlines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_2dlines (macro);
end;

procedure proc_export_matlab_2dlines (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-lines','txt',@p_export_matlab_2dlines,macro);
end;

{ **************************************************************************** }
{ **************************************************************************** }
{ **************************************************************************** }

procedure p_export_matlab_points (macro : pointer);
var f : text;
    count,track : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
 {                    progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track = 1 then
                     begin
                          v := finput^.getline(count,1);
                          writeln (f,getstring(v.x)+#9+getstring(v.y)+#9+getstring(v.z));
                     end;
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.points','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_points_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_points (macro);
end;

procedure proc_export_matlab_points (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-points','txt',@p_export_matlab_points,macro);
end;

{ **************************************************************************** }

procedure p_export_matlab_vectors (macro : pointer);
var f : text;
    count,track : integer;
    v,u : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
{                     progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track = 2 then
                     begin
                          v := finput^.getline(count,1);
                          u := norm(finput^.getline(count,2)-v);
                          writeln (f,getstring(v.x)+#9+getstring(v.y)+#9+getstring(v.z)+#9+getstring(u.x)+#9+getstring(u.y)+#9+getstring(u.z));
                     end;
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.vectors','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_vectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_vectors (macro);
end;

procedure proc_export_matlab_vectors (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-vectors','txt',@p_export_matlab_vectors,macro);
end;

{ **************************************************************************** }

procedure p_export_matlab_lines (macro : pointer);
var f : text;
    count,track,p : integer;
    v : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
           if assignwrite (f,finput^.name) then
           begin
                for count := 1 to finput^.getlinelength do
                begin
{                     progress ('  Write Matlab-file',count/finput^.getlinelength);}
                     track := finput^.getalllinepointlength(count);
                     if track > 0 then
                        for p := 1 to track do
                        begin
                             v := finput^.getline(count,p);
                             if p <> track then write (f,getstring(v.x)+#9+getstring(v.y)+#9+getstring(v.z)+#9)
                                           else write (f,getstring(v.x)+#9+getstring(v.y)+#9+getstring(v.z));
                        end;
                     writeln (f);
                end;
{                progress;}
                close (f);
           end;
           updating;
           tmacro(macro^).writeredo ('export.matlab.lines','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_matlab_lines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_matlab_lines (macro);
end;

procedure proc_export_matlab_lines (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-lines','txt',@p_export_matlab_lines,macro);
end;

{ **************************************************************************** }
{ **************************************************************************** }
{ **************************************************************************** }

procedure p_export_amira_vectors (macro : pointer);
var f : text;
    count,track,x,y,z : integer;
    v,w : hyper;
    p,min,max : vector;
    l : vectornat;
    field : tspacevector;
    fieldcount : tspacenat;
    step : real;
    b8 : natural;
begin
     field := Default(tspacevector);
     fieldcount := Default(tspacenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if (finput^.name <> '') and (finput^.getlinelength > 0) then
     begin
          { Min & Max only for the first Vector-Point }
          min := Vmax;
          max := Vmin;
          for count := 1 to finput^.getlinelength do
          begin
               if finput^.getalllinepointlength(count) = 2 then
               begin
                    v := finput^.getline(count,1);
                    if v.x < min.x then min.x := v.x;
                    if v.y < min.y then min.y := v.y;
                    if v.z < min.x then min.z := v.z;
                    if v.x > max.x then max.x := v.x;
                    if v.y > max.y then max.y := v.y;
                    if v.z > max.x then max.z := v.z;
               end;
          end;
          step := _getnat (export_amira_step,macro,2);
          if (into(step,1,1000000)) and (min <> Vmax) and (max <> Vmin) and (min <> max) then
          begin
               l := gvn(1+round((max.x-min.x)/step),1+round((max.y-min.y)/step),1+round((max.z-min.z)/step));
               b8 := (l.x*l.y*l.z*((3+1)*8));
               if (b8 <= (2*1073741824-1)) or _dialog_yes_no ('Limit check','Your calculation is bigger then 2GiB (~'+liball.getprefix(b8,3)+'iB)!','Do you want to try anyway?') then
               begin
                    field.init (l.x,l.y,l.z);
                    fieldcount.init (l.x,l.y,l.z);
                    if fieldcount.length > 0 then
                    if assignwrite (f,finput^.name) then
                    begin
                         writelnln (f,'# AmiraMesh 3D ASCII 2.0');
                         writelnln (f,'define Lattice '+getstring(l.x)+' '+getstring(l.y)+' '+getstring(l.z));
                         writeln (f,'Parameters {');
                         writeln (f,'            BoundingBox '+getstring(round(min.x))+' '+getstring(round(max.x))+' '+getstring(round(min.y))+' '+getstring(round(max.y))+' '+getstring(round(min.z))+' '+getstring(round(max.z))+',');
                         writeln (f,'            CoordType "uniform",');
                         writeln (f,'            Content "'+getstring(l.x)+'x'+getstring(l.y)+'x'+getstring(l.z)+' float[3], uniform coordinates"');
                         writelnln (f,'           }');
                         writelnln (f,'Lattice { float[3] Data } @1');
                         writeln (f,'# Data section follows');
                         writeln (f,'@1');
                         for count := 1 to finput^.getlinelength do
                         begin
                              track := finput^.getalllinepointlength(count);
                              if track = 2 then
                              begin
                                   v := finput^.getline(count,1);
                                   w := finput^.getline(count,2)-v;
                                   l := gvn(round((v.x-min.x)/step),round((v.y-min.y)/step),round((v.z-min.z)/step));
                                   x := fieldcount.get (l.x,l.y,l.z);
                                   if x = 0 then
                                   begin
                                        field.put (l.x,l.y,l.z,gv(w.x,w.y,w.z));
                                        fieldcount.put (l.x,l.y,l.z,1);
                                   end
                                   else
                                   begin
                                        field.put (l.x,l.y,l.z,field.get (l.x,l.y,l.z)+gv(w.x,w.y,w.z));
                                        fieldcount.put (l.x,l.y,l.z,x+1);
                                   end;
                              end;
                         end;
                         for z := 1 to field.lengthz do
                             for y := 1 to field.lengthy do
                                 for x := 1 to field.lengthx do
                                 begin
                                      count := fieldcount.get (x,y,z);
                                      if count > 0 then
                                      begin
                                           if count > 1 then p := field.get (x,y,z)/count
                                                        else p := field.get (x,y,z);
                                           writeln (f,getstring(p.x)+' '+getstring(p.y)+' '+getstring(p.z));
                                      end
                                      else writeln (f,'0 0 0');
                                 end;
                         close (f);
                    end;
                    fieldcount.done;
                    field.done;
               end;
          end;
          updating;
          tmacro(macro^).writeredo ('export.amira.vectors','"'+finput^.name+'" '+getstring(step));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_amira_vectors_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_amira_vectors (macro);
end;

procedure proc_export_amira_vectors (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-amira','am','Amira-files:*.am|All files:*.*',@p_export_amira_vectors,macro);
end;

{ **************************************************************************** }

procedure save_mel (macro : pointer);
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          finput^.save_mel (finput^.name);
          updating;
          tmacro(macro^).writeredo ('export.maya','"'+finput^.name+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_mel_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save_mel (macro);
end;

procedure proc_export_mel (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-maya','mel','Maya-files:*.mel|All files:*.*',@save_mel,macro);
end;

{ **************************************************************************** }

procedure save_py (macro : pointer);
var t : text;
    o,l,p,item : integer;
    h : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          if assignwrite(t,finput^.name) then
          begin
               item := _getitem (export_blender,macro,2);
               writeln (t,'import bpy');
               writeln (t);
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) > 0 then
                              begin
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        h := finput^.getobject (o,l,p);
                                        case item of
                                  {Metaball} 1 : writeln (t,'bpy.ops.object.metaball_add(type=''BALL'', location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                           {low res UV-Mesh} 2 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                          {high res UV-Mesh} 3 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=64, ring_count=32, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                              {low Ico-Mesh} 4 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=2, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                            {high Ico-Mesh}  5 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=4, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                    {Nurbs} else writeln (t,'bpy.ops.surface.primitive_nurbs_surface_sphere_add(location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                        end;
                                   end;

                              end;
                         end;
                    end;
               end;
               close (t);
               updating;
               tmacro(macro^).writeredo ('export.blender.points','"'+finput^.name+'"');
          end;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_py_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save_py (macro);
end;

procedure proc_export_py (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-blender','py','Blender-files:*.py|All files:*.*',@save_py,macro);
end;

{ **************************************************************************** }

procedure save_py_lines (macro : pointer);
var t : text;
    o,l,p,item : integer;
    h : hyper;
begin
     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          if assignwrite(t,finput^.name) then
          begin
               item := _getitem (export_blender,macro,2);
               writeln (t,'import bpy');
               for o := 1 to finput^.getobjectlength do
               begin
                    if finput^.getobjectlinelength (o) > 0 then
                    begin
                         for l := 1 to finput^.getobjectlinelength (o) do
                         begin
                              if finput^.getlinepointlength (o,l) = 1 then { point }
                              begin
                                   writeln (t);
                                   h := finput^.getobject (o,l,1);
                                   case item of
                             {Metaball} 1 : writeln (t,'bpy.ops.object.metaball_add(type=''BALL'', location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                      {low res UV-Mesh} 2 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                     {high res UV-Mesh} 3 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=64, ring_count=32, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                         {low Ico-Mesh} 4 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=2, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                       {high Ico-Mesh}  5 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=4, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                               {Nurbs} else writeln (t,'bpy.ops.surface.primitive_nurbs_surface_sphere_add(location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                   end;
                              end
                              else if finput^.getlinepointlength (o,l) > 1 then { line_rows }
                              begin
                                   writeln (t);
                                   for p := 1 to finput^.getlinepointlength (o,l) do
                                   begin
                                        h := finput^.getobject (o,l,p);
                                        if (p = 1) then
                                        begin
                                             case item of
                                       {Metaball} 1 : writeln (t,'bpy.ops.object.metaball_add(type=''BALL'', location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                {low res UV-Mesh} 2 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                               {high res UV-Mesh} 3 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=64, ring_count=32, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                   {low Ico-Mesh} 4 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=2, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                 {high Ico-Mesh}  5 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=4, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                         {Nurbs} else writeln (t,'bpy.ops.surface.primitive_nurbs_surface_sphere_add(location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                             end;
                                             writeln (t,'bpy.ops.curve.primitive_nurbs_path_add()');
                                             writeln (t,'a = bpy.context.object');
                                             writeln (t,'a.data.resolution_u = 6');
                                             writeln (t,'a.data.fill_mode = ''FULL''');
                                             writeln (t,'a.data.bevel_depth = 1');
                                             writeln (t,'a.data.bevel_resolution = 16');
                                             writeln (t,'bpy.ops.object.editmode_toggle()');
                                             writeln (t,'bpy.ops.curve.delete(type=''VERT'')');
                                        end;

                                        writeln (t,'bpy.ops.curve.vertex_add(location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'))');
                                        writeln (t,'bpy.ops.curve.radius_set(radius='+getstring(h.t)+')');

                                        if p = finput^.getlinepointlength (o,l) then
                                        begin
                                             writeln (t,'bpy.ops.object.editmode_toggle()');
                                             case item of
                                       {Metaball} 1 : writeln (t,'bpy.ops.object.metaball_add(type=''BALL'', location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                {low res UV-Mesh} 2 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                               {high res UV-Mesh} 3 : writeln (t,'bpy.ops.mesh.primitive_uv_sphere_add(segments=64, ring_count=32, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                   {low Ico-Mesh} 4 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=2, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                 {high Ico-Mesh}  5 : writeln (t,'bpy.ops.mesh.primitive_ico_sphere_add(subdivisions=4, location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), size='+getstring(abs(h.t)/2)+')');
                                         {Nurbs} else writeln (t,'bpy.ops.surface.primitive_nurbs_surface_sphere_add(location=('+getstring(h.x)+', '+getstring(h.y)+', '+getstring(h.z)+'), radius='+getstring(abs(h.t))+')');
                                             end;
                                        end;
                                   end;

                              end;
                         end;
                    end;
               end;
               close (t);
               updating;
               tmacro(macro^).writeredo ('export.blender.lines','"'+finput^.name+'"');
          end;
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_export_py_lines_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     save_py_lines (macro);
end;

procedure proc_export_py_lines (p1,macro : gtk_pointer); cdecl;
begin
     _savefile (finput^.name,'new-blender','py','Blender-files:*.py|All files:*.*',@save_py_lines,macro);
end;

{ **************************************************************************** }
{ ******************************** Mol *************************************** }
{ **************************************************************************** }

{ http://crystalmaker.com/support/tutorials/atomic-radii/index.html
Atomic Number
Element Symbol
Atomic Radius [Å]
Ionic Radius [Å]
Covalent Radius [Å]
Van-der-Waals Radius [Å]
"Crystal" Radius [Å]
}

type Tatom_entry = record
            element : string;
            atomic_r,ionic_r,vanderwaals_r : real;
            end;

const Tatom : array[1..96] of Tatom_entry = (
(element : 'H';atomic_r : 0.53;ionic_r : 0.25;vanderwaals_r : 1.2),
(element : 'He';atomic_r : 0.31;ionic_r : 0.31;vanderwaals_r : 1.4),
(element : 'Li';atomic_r : 1.67;ionic_r : 1.45;vanderwaals_r : 1.82),
(element : 'Be';atomic_r : 1.12;ionic_r : 1.05;vanderwaals_r : 0),
(element : 'B';atomic_r : 0.87;ionic_r : 0.85;vanderwaals_r : 0),
(element : 'C';atomic_r : 0.67;ionic_r : 0.70;vanderwaals_r : 1.7),
(element : 'N';atomic_r : 0.56;ionic_r : 0.65;vanderwaals_r : 1.55),
(element : 'O';atomic_r : 0.48;ionic_r : 0.60;vanderwaals_r : 1.52),
(element : 'F';atomic_r : 0.42;ionic_r : 0.50;vanderwaals_r : 1.47),
{10}
(element : 'Ne';atomic_r : 0.38;ionic_r : 0.38;vanderwaals_r : 1.54),
(element : 'Na';atomic_r : 1.90;ionic_r : 1.80;vanderwaals_r : 2.27),
(element : 'Mg';atomic_r : 1.45;ionic_r : 1.50;vanderwaals_r : 1.73),
(element : 'Al';atomic_r : 1.18;ionic_r : 1.25;vanderwaals_r : 0),
(element : 'Si';atomic_r : 1.11;ionic_r : 1.10;vanderwaals_r : 2.1),
(element : 'P';atomic_r : 0.98;ionic_r : 1.00;vanderwaals_r : 1.8),
(element : 'S';atomic_r : 0.88;ionic_r : 1.00;vanderwaals_r : 1.8),
(element : 'Cl';atomic_r : 0.79;ionic_r : 1.00;vanderwaals_r : 1.75),
(element : 'Ar';atomic_r : 0.71;ionic_r : 0.71;vanderwaals_r : 1.88),
(element : 'K';atomic_r : 2.43;ionic_r : 2.20;vanderwaals_r : 2.75),
{20}
(element : 'Ca';atomic_r : 1.94;ionic_r : 1.80;vanderwaals_r : 0),
(element : 'Sc';atomic_r : 1.84;ionic_r : 1.60;vanderwaals_r : 0),
(element : 'Ti';atomic_r : 1.76;ionic_r : 1.40;vanderwaals_r : 0),
(element : 'V';atomic_r : 1.71;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Cr';atomic_r : 1.66;ionic_r : 1.40;vanderwaals_r : 0),
(element : 'Mn';atomic_r : 1.61;ionic_r : 1.40;vanderwaals_r : 0),
(element : 'Fe';atomic_r : 1.56;ionic_r : 1.40;vanderwaals_r : 0),
(element : 'Co';atomic_r : 1.52;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Ni';atomic_r : 1.49;ionic_r : 1.35;vanderwaals_r : 1.63),
(element : 'Cu';atomic_r : 1.45;ionic_r : 1.35;vanderwaals_r : 1.4),
{30}
(element : 'Zn';atomic_r : 1.42;ionic_r : 1.35;vanderwaals_r : 1.39),
(element : 'Ga';atomic_r : 1.36;ionic_r : 1.30;vanderwaals_r : 1.87),
(element : 'Ge';atomic_r : 1.25;ionic_r : 1.25;vanderwaals_r : 0),
(element : 'As';atomic_r : 1.14;ionic_r : 1.15;vanderwaals_r : 1.85),
(element : 'Se';atomic_r : 1.03;ionic_r : 1.15;vanderwaals_r : 1.9),
(element : 'Br';atomic_r : 0.94;ionic_r : 1.15;vanderwaals_r : 1.85),
(element : 'Kr';atomic_r : 0.88;ionic_r : 0.88;vanderwaals_r : 2.02),
(element : 'Rb';atomic_r : 2.65;ionic_r : 2.35;vanderwaals_r : 0),
(element : 'Sr';atomic_r : 2.19;ionic_r : 2.00;vanderwaals_r : 0),
(element : 'Y';atomic_r : 2.12;ionic_r : 1.85;vanderwaals_r : 0),
{40}
(element : 'Zr';atomic_r : 2.06;ionic_r : 1.55;vanderwaals_r : 0),
(element : 'Nb';atomic_r : 1.98;ionic_r : 1.45;vanderwaals_r : 0),
(element : 'Mo';atomic_r : 1.90;ionic_r : 1.45;vanderwaals_r : 0),
(element : 'Tc';atomic_r : 1.83;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Ru';atomic_r : 1.78;ionic_r : 1.30;vanderwaals_r : 0),
(element : 'Rh';atomic_r : 1.73;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Pd';atomic_r : 1.69;ionic_r : 1.40;vanderwaals_r : 1.63),
(element : 'Ag';atomic_r : 1.65;ionic_r : 1.60;vanderwaals_r : 1.72),
(element : 'Cd';atomic_r : 1.61;ionic_r : 1.55;vanderwaals_r : 1.58),
(element : 'In';atomic_r : 1.56;ionic_r : 1.55;vanderwaals_r : 1.93),
{50}
(element : 'Sn';atomic_r : 1.45;ionic_r : 1.45;vanderwaals_r : 2.17),
(element : 'Sb';atomic_r : 1.33;ionic_r : 1.45;vanderwaals_r : 0),
(element : 'Te';atomic_r : 1.23;ionic_r : 1.40;vanderwaals_r : 2.06),
(element : 'I';atomic_r : 1.15;ionic_r : 1.40;vanderwaals_r : 1.98),
(element : 'Xe';atomic_r : 1.08;ionic_r : 1.08;vanderwaals_r : 2.16),
(element : 'Cs';atomic_r : 2.98;ionic_r : 2.60;vanderwaals_r : 0),
(element : 'Ba';atomic_r : 2.53;ionic_r : 2.15;vanderwaals_r : 0),
(element : 'La';atomic_r : 1.95;ionic_r : 1.95;vanderwaals_r : 0),
(element : 'Ce';atomic_r : 1.85;ionic_r : 1.85;vanderwaals_r : 0),
(element : 'Pr';atomic_r : 2.47;ionic_r : 1.85;vanderwaals_r : 0),
{60}
(element : 'Nd';atomic_r : 2.06;ionic_r : 1.85;vanderwaals_r : 0),
(element : 'Pm';atomic_r : 2.05;ionic_r : 1.85;vanderwaals_r : 0),
(element : 'Sm';atomic_r : 2.38;ionic_r : 1.85;vanderwaals_r : 0),
(element : 'Eu';atomic_r : 2.31;ionic_r : 1.85;vanderwaals_r : 0),
(element : 'Gd';atomic_r : 2.33;ionic_r : 1.80;vanderwaals_r : 0),
(element : 'Tb';atomic_r : 2.25;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Dy';atomic_r : 2.28;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Ho';atomic_r : 2.26;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Er';atomic_r : 2.26;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Tm';atomic_r : 2.22;ionic_r : 1.75;vanderwaals_r : 0),
{70}
(element : 'Yb';atomic_r : 2.22;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Lu';atomic_r : 2.17;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Hf';atomic_r : 2.08;ionic_r : 1.55;vanderwaals_r : 0),
(element : 'Ta';atomic_r : 2.00;ionic_r : 1.45;vanderwaals_r : 0),
(element : 'W';atomic_r : 1.93;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Re';atomic_r : 1.88;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Os';atomic_r : 1.85;ionic_r : 1.30;vanderwaals_r : 0),
(element : 'Ir';atomic_r : 1.80;ionic_r : 1.35;vanderwaals_r : 0),
(element : 'Pt';atomic_r : 1.77;ionic_r : 1.35;vanderwaals_r : 1.75),
(element : 'Au';atomic_r : 1.74;ionic_r : 1.35;vanderwaals_r : 1.66),
{80}
(element : 'Hg';atomic_r : 1.71;ionic_r : 1.50;vanderwaals_r : 1.55),
(element : 'Tl';atomic_r : 1.56;ionic_r : 1.90;vanderwaals_r : 1.96),
(element : 'Pb';atomic_r : 1.54;ionic_r : 1.80;vanderwaals_r : 2.02),
(element : 'Bi';atomic_r : 1.43;ionic_r : 1.60;vanderwaals_r : 0),
(element : 'Po';atomic_r : 1.35;ionic_r : 1.90;vanderwaals_r : 0),
(element : 'At';atomic_r : 1.27;ionic_r : 1.27;vanderwaals_r : 0),
(element : 'Rn';atomic_r : 1.20;ionic_r : 1.20;vanderwaals_r : 0),
(element : 'Fr';atomic_r : 0;ionic_r : 0;vanderwaals_r : 0),
(element : 'Ra';atomic_r : 0;ionic_r : 2.15;vanderwaals_r : 0),
(element : 'Ac';atomic_r : 1.95;ionic_r : 1.95;vanderwaals_r : 0),
{90}
(element : 'Th';atomic_r : 1.80;ionic_r : 1.80;vanderwaals_r : 0),
(element : 'Pa';atomic_r : 1.80;ionic_r : 1.80;vanderwaals_r : 0),
(element : 'U';atomic_r : 1.75;ionic_r : 1.75;vanderwaals_r : 1.86),
(element : 'Np';atomic_r : 1.75;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Pu';atomic_r : 1.75;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Am';atomic_r : 1.75;ionic_r : 1.75;vanderwaals_r : 0),
(element : 'Cm';atomic_r : 0;ionic_r : 0;vanderwaals_r : 0));

procedure p_import_pdb_info (macro : pointer);
var f : tfiletext;
    count,model : integer;
    s,t,u : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
begin
     f := Default (tfiletext);

     format.push;
     format := format_txt;

     pdbid := '';
     classi := '';
     model := 1;
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           f.load (finput^.name);
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 4 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'model') then
                     begin
                          model := getnat(killlast(copy(s,11,70),' '));
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           f.done;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.models',getstring(model));
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.info','"'+finput^.name+'"');
     format.pop;
end;

procedure proc_import_pdb_info_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdb_info (macro);
end;

{ **************************************************************************** }

procedure p_import_pdb_data (macro : pointer);
var f : tfiletext;
    count,v,w,id,oldid,acount,model,radius : integer;
    s,t,u,acid,oldacid,atom : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
    h : hyper;
    found : boolean;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     radius := _getitem_0 (import_pdb,macro,2);

     pdbid := '';
     classi := '';
     model := 1;
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     acid := '';
     oldacid := '';
     atom := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           dummy.clear;
           f.load (finput^.name);
           v := 0; { aminoacid }
           w := 0; { atom }
           oldid := 1;
           oldacid := '';
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 4 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'atom') then
                     begin
                          acid := killspace(copy(s,18,3)); { aminoacid name }
                          id := getnat(copy(s,23,4)); { aminoacid number }

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          if oldid <> id then dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));

                          if liball.length (atom) = 1 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;

                          oldid := id;
                          oldacid := acid;
                          inc (v);
                     end
                     else if (t = 'hetatm') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                          end;

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          if liball.length (atom) > 0 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;
                          inc (w);
                     end
                     else if (t = 'model') then
                     begin
                          model := getnat(killlast(copy(s,11,70),' '));
                     end
                     else if (t = 'endmdl') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                          end;
                          if w > 0 then
                          begin
                               dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
                               w := 0;
                          end;
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           if v > 0 then
           begin
                dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           if w > 0 then
           begin
                dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.models',getstring(model));
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.atom','"'+finput^.name+'" '+getstring(radius));
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_pdb_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdb_data (macro);
end;

procedure proc_import_pdb_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'PDB:*.pdb;*.ent;*.pdb.gz;*.ent.gz|All files:*.*',@p_import_pdb_data,macro);
end;

{ **************************************************************************** }

procedure p_import_pdbbb_data (macro : pointer);
var f : tfiletext;
    count,v,w,x,id,oldid,acount,model,radius : integer;
    s,t,u,acid,oldacid,atom : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
    h : hyper;
    found : boolean;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     radius := _getitem_0 (import_pdb,macro,2);

     pdbid := '';
     classi := '';
     model := 1;
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     acid := '';
     oldacid := '';
     atom := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           dummy.clear;
           f.load (finput^.name);
           v := 0; { aminoacid }
           w := 0; { atom }
           x := 0; { atom count per AA }
           oldid := 1;
           oldacid := '';
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 4 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'atom') then
                     begin
                          acid := killspace(copy(s,18,3)); { aminoacid name or HOH }
                          id := getnat(copy(s,23,4)); { aminoacid number }

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          if oldid <> id then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               x := 0;
                          end;

                          if liball.length (atom) = 1 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               inc (x);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    if x < 5 then dummy.newline (-acount)
                                             else dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;

                          oldid := id;
                          oldacid := acid;
                          inc (v);
                     end
                     else if (t = 'hetatm') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                               x := 0;
                          end;

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          if liball.length (atom) > 0 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               inc (x);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    if x < 5 then dummy.newline (-acount)
                                             else dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;
                          inc (w);
                     end
                     else if (t = 'model') then
                     begin
                          model := getnat(killlast(copy(s,11,70),' '));
                     end
                     else if (t = 'endmdl') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                               x := 0;
                          end;
                          if w > 0 then
                          begin
                               dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
                               w := 0;
                               x := 0;
                          end;
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           if v > 0 then
           begin
                dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           if w > 0 then
           begin
                dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.models',getstring(model));
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.backbone','"'+finput^.name+'" '+getstring(radius));
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_pdbbb_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdbbb_data (macro);
end;

procedure proc_import_pdbbb_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'PDB:*.pdb;*.ent;*.pdb.gz;*.ent.gz|All files:*.*',@p_import_pdbbb_data,macro);
end;

{ **************************************************************************** }

procedure p_import_pdblink_data (macro : pointer);
var f : tfiletext;
    count,v,w,id,oldid,acount,serial,n1,n2,n3,n4,model,radius : integer;
    s,t,u,acid,oldacid,atom : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
    h : hyper;
    found : boolean;
    helper : tpolyhyper;
begin
     f := Default(tfiletext);
     helper := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     radius := _getitem_0 (import_pdb,macro,2);

     pdbid := '';
     classi := '';
     model := 1;
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     acid := '';
     oldacid := '';
     atom := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           dummy.clear;
           f.load (finput^.name);
           helper.init;
           v := 0; { aminoacid }
           w := 0; { atom }
           oldid := 1;
           oldacid := '';
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 4 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'atom') then
                     begin
                          serial := getnat(copy(s,7,5));
                          acid := killspace(copy(s,18,3)); { aminoacid name }
                          id := getnat(copy(s,23,4)); { aminoacid number }

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          helper.put (serial,h);

                          if oldid <> id then dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));

                          if liball.length (atom) = 1 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;

                          oldid := id;
                          oldacid := acid;
                          inc (v);
                     end
                     else if (t = 'hetatm') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                          end;

                          serial := getnat(copy(s,7,5));

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          atom := killspace(copy(s,77,2)); { atom name }

                          helper.put (serial,h);

                          if liball.length (atom) > 0 then
                          begin
                               if liball.length (atom) = 1 then atom := uppercase(getchar(atom,1))
                                                           else atom := uppercase(getchar(atom,1))+lowercase(getchar(atom,2));
                               found := false;
                               acount := 1;
                               repeat
                                     if tatom[acount].element = atom then found := true
                                                                     else inc (acount);
                               until (found) or (acount > 96);
                               if found then
                               begin
                                    case radius of
                                         1 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].ionic_r));
                                         2 : dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].vanderwaals_r));
                                         else {0} dummy.newpoint (gh(h.x,h.y,h.z,tatom[acount].atomic_r));
                                    end;
                                    dummy.newline (acount);
                               end
                               else { what that? }
                               begin
                                    dummy.newpoint (h);
                                    dummy.newline (0);
                               end;
                          end;
                          inc (w);
                     end
                     else if (t = 'conect') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                          end;
                          if w > 0 then
                          begin
                               dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
                               w := 0;
                          end;

                          { do connection }
                          {TODO: !!! Attention 'ter' counts !!! }

                           id := getnat(copy(s,7,5));
                           n1 := getnat(copy(s,12,5));
                           n2 := getnat(copy(s,17,5));
                           n3 := getnat(copy(s,22,5));
                           n4 := getnat(copy(s,27,5));
                           if n1 > 0 then
                           begin
                                dummy.newpoint (helper.get(n1));
                                dummy.newpoint (helper.get(id));
                                dummy.newline (0);
                           end;
                           if n2 > 0 then
                           begin
                                dummy.newpoint (helper.get(n2));
                                dummy.newpoint (helper.get(id));
                                dummy.newline (0);
                           end;
                           if n3 > 0 then
                           begin
                                dummy.newpoint (helper.get(n3));
                                dummy.newpoint (helper.get(id));
                                dummy.newline (0);

                           end;
                           if n4 > 0 then
                           begin
                                dummy.newpoint (helper.get(n4));
                                dummy.newpoint (helper.get(id));
                                dummy.newline (0);
                           end;
                           if (n1 > 0) or (n2 > 0) or (n3 > 0) or (n4 > 0) then dummy.newobject ('HET_'+getstring(id)+'_model:'+fillbefore(getstring(model),3,'0'));
                     end
                     else if (t = 'model') then
                     begin
                          model := getnat(killlast(copy(s,11,70),' '));
                     end
                     else if (t = 'endmdl') then
                     begin
                          if v > 0 then
                          begin
                               dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
                               v := 0;
                          end;
                          if w > 0 then
                          begin
                               dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
                               w := 0;
                          end;
                          helper.newlength(0);
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           if v > 0 then
           begin
                dummy.newobject (oldacid+'_'+fillbefore(getstring(oldid),3,'0')+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           if w > 0 then
           begin
                dummy.newobject ('HET'+'_model:'+fillbefore(getstring(model),3,'0'));
           end;
           helper.done;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.models',getstring(model));
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.atom.link','"'+finput^.name+'" '+getstring(radius));
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_pdblink_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdb_data (macro);
end;

procedure proc_import_pdblink_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'PDB:*.pdb;*.ent;*.pdb.gz;*.ent.gz|All files:*.*',@p_import_pdblink_data,macro);
end;

{ **************************************************************************** }

procedure p_import_pdbpaa_data (macro : pointer);
var f : tfiletext;
    count,v,w,id,oldid,radius : integer;
    s,t,u,acid : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
    h,k : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     radius := _getitem_0 (import_pdb,macro,2);

     pdbid := '';
     classi := '';
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           dummy.clear;
           f.load (finput^.name);
           v := 0;

           k := Hzero;
           w := 0;

           oldid := 1;

           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 3 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'atom') then
                     begin
                          acid := killspace(copy(s,18,3)); { aminoacid name }
                          id := getnat(copy(s,23,4)); { aminoacid number }

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          if oldid <> id then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                                    dummy.newline (oldid);
                               end;
                               k := Hzero;
                               w := 0;
                          end
                          else
                          begin
                               k := k + h;
                               inc(w);
                          end;

                          oldid := id;
                          inc (v);
                     end
                     else if (t = 'ter') then { end line_rows }
                     begin
                          if v > 0 then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                                    dummy.newline (oldid);
                                    w := 0;
                               end;
                               dummy.newobject (getfilename(finput^.name));
                               v := 0;
                          end;
                     end
                     else if (t = 'endmdl') then { end model }
                     begin
                          if v > 0 then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                                    dummy.newline (oldid);
                                    w := 0;
                               end;
                               dummy.newobject (getfilename(finput^.name));
                               v := 0;
                          end;
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           if v > 0 then
           begin
                if w > 0 then
                begin
                     dummy.newpoint (k/w);
                     dummy.newline (oldid);
                end;
                dummy.newobject (getfilename(finput^.name));
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.paa','"'+finput^.name+'" '+getstring(radius));
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_pdbpaa_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdbpaa_data (macro);
end;

procedure proc_import_pdbpaa_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'PDB:*.pdb;*.ent;*.pdb.gz;*.ent.gz|All files:*.*',@p_import_pdbpaa_data,macro);
end;

{ **************************************************************************** }

procedure p_import_pdblaa_data (macro : pointer);
var f : tfiletext;
    count,v,w,id,oldid,radius : integer;
    s,t,u,acid : utf16;
    pdbid,classi,title,compound_molecule,compound_ec,source_organism,source_gene,keywords,expdata : utf16;
    h,k : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     radius := _getitem_0 (import_pdb,macro,2);

     pdbid := '';
     classi := '';
     title := '';
     compound_molecule := '';
     compound_ec := '';
     source_organism := '';
     source_gene := '';
     keywords := '';
     expdata := '';
     if finput^.name <> '' then
     begin
           dummy.clear;
           f.load (finput^.name);
           v := 0;

           k := Hzero;
           w := 0;

           oldid := 1;

           if f.length > 0 then
           for count := 1 to f.length do
           begin
                s := f.get (count);
                if length (s) > 3 then
                begin
                     t := killspace(lowercase(copy(s,1,6)));
                     if (t = 'atom') then
                     begin
                          acid := killspace(copy(s,18,3)); { aminoacid name }
                          id := getnat(copy(s,23,4)); { aminoacid number }

                          h.x := getreal (copy(s,31,8)); { x }
                          h.y := getreal (copy(s,39,8)); { y }
                          h.z := getreal (copy(s,47,8)); { z }
                          h.t := getreal (copy(s,55,8)); { size - use atom name for size }

                          if oldid <> id then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                               end;
                               k := Hzero;
                               w := 0;
                          end
                          else
                          begin
                               k := k + h;
                               inc(w);
                          end;

                          oldid := id;
                          inc (v);
                     end
                     else if (t = 'ter') then { end line_rows }
                     begin
                          if v > 0 then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                                    w := 0;
                               end;
                               dummy.newline (0);
                               dummy.newobject (getfilename(finput^.name));
                               v := 0;
                          end;
                     end
                     else if (t = 'endmdl') then { end model }
                     begin
                          if v > 0 then
                          begin
                               if w > 0 then
                               begin
                                    dummy.newpoint (k/w);
                                    w := 0;
                               end;
                               dummy.newline (0);
                               dummy.newobject (getfilename(finput^.name));
                               v := 0;
                          end;
                     end
                     else if (t = 'header') then
                     begin
                          classi := killlast(killfirst(copy(s,11,40),' '),' '); { HEADER    OXIDOREDUCTASE                          13-JUL-04   1W35 }
                          pdbid := killlast(killfirst(copy(s,63,4),' '),' ');
                     end
                     else if (t = 'title') then
                     begin
                          title := title + killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'compnd') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('MOLECULE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,21,35),' '),' ');
                               compound_molecule := killlast (u,';');
                          end
                          else if pos ('EC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,15,35),' '),' ');
                               compound_ec := killlast (u,';');
                          end;
                     end
                     else if (t = 'source') then
                     begin
                          u := killlast(killfirst(copy(s,11,40),' '),' ');
                          if pos ('ORGANISM_SCIENTIFIC:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,32,35),' '),' ');
                               source_organism := killlast (u,';');
                          end
                          else if pos ('GENE:',u) > 0 then
                          begin
                               u := killlast(killfirst(copy(s,17,35),' '),' ');
                               source_gene := killlast (u,';');
                          end
                     end
                     else if (t = 'keywds') then
                     begin
                          keywords := killlast(copy(s,11,70),' ');
                     end
                     else if (t = 'expdta') then
                     begin
                          expdata := killlast(copy(s,11,70),' ');
                     end;
                end;
           end;
           if v > 0 then
           begin
                if w > 0 then
                begin
                     dummy.newpoint (k/w);
                end;
                dummy.newline (0);
                dummy.newobject (getfilename(finput^.name));
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
     end;
     if tmacro(macro^).running then
     begin
          tmacro(macro^).putconstant('pdb.title',title);
          tmacro(macro^).putconstant('pdb.id',pdbid);
          tmacro(macro^).putconstant('pdb.class',classi);
          tmacro(macro^).putconstant('pdb.molecule',compound_molecule);
          tmacro(macro^).putconstant('pdb.ec',compound_ec);
          tmacro(macro^).putconstant('pdb.organism',source_organism);
          tmacro(macro^).putconstant('pdb.gene',source_gene);
          tmacro(macro^).putconstant('pdb.keywords',keywords);
          tmacro(macro^).putconstant('pdb.expdata',expdata);
     end;
     tmacro(macro^).writeredo ('import.pdb.laa','"'+finput^.name+'" '+getstring(radius));
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_pdblaa_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_pdblaa_data (macro);
end;

procedure proc_import_pdblaa_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'PDB:*.pdb;*.ent;*.pdb.gz;*.ent.gz|All files:*.*',@p_import_pdblaa_data,macro);
end;

{ **************************************************************************** }

var save_filename : utf16;

procedure p_export_triplets (macro : pointer);
var f : text;
    count : integer;
    aa : utf16;
    empty : boolean;
begin
     empty := _getcheckbutton (toggle_seq_empty,macro,2);
     if (finput^.getobjectlength > 0) or empty then
     begin
          _cursor_watch;
          format.push;
          format := format_txt;
          if (finput^.name <> '') then
          begin
               if assignwrite (f,finput^.name) then
               begin
                    writeln (f,'>'+getfilename(save_filename)+#9+'length:'+getstring(finput^.getobjectlength*3)+#9+#9);
                    aa := '';
                    if (finput^.getobjectlength > 0) then
                    for count := 1 to finput^.getobjectlength do
                    begin
                         aa := aa + one_to_triplet (three_to_one (finput^.getname(count)));
                    end;
                    writeln (f,aa);
                    close (f);
               end;
               updating;
               tmacro(macro^).writeredo ('export.triplets','"'+finput^.name+'"'+' '+getstring(empty));
          end;
          format.pop;
          _cursor_arrow;
     end;
end;

procedure proc_export_triplets_1 (p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_triplets (macro);
end;

procedure proc_export_triplets(p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     _savefile (finput^.name,'new-rna','txt','All files:*.*',@p_export_triplets,macro);
end;

procedure p_append_triplets (macro : pointer);
var f : text;
    count : integer;
    aa : utf16;
    empty : boolean;
begin
     empty := _getcheckbutton (toggle_seq_empty,macro,2);
     if (finput^.getobjectlength > 0) or empty then
     begin
          _cursor_watch;
          format.push;
          format := format_txt;
          if (finput^.name <> '') then
          begin
               if assignappend (f,finput^.name) then
               begin
                    writeln (f,'>'+getfilename(save_filename)+#9+'length:'+getstring(finput^.getobjectlength*3)+#9+#9);
                    aa := '';
                    if (finput^.getobjectlength > 0) then
                    for count := 1 to finput^.getobjectlength do
                    begin
                         aa := aa + one_to_triplet (three_to_one (finput^.getname(count)));
                    end;
                    writeln (f,aa);
                    close (f);
               end;
               updating;
               tmacro(macro^).writeredo ('append.triplets','"'+finput^.name+'"'+' '+getstring(empty));
          end;
          format.pop;
          _cursor_arrow;
     end;
end;

procedure proc_append_triplets_1 (p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     finput^.name := tmacro(macro^).getparameter(1);
     p_append_triplets (macro);
end;

procedure proc_append_triplets(p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     _appendfile (finput^.name,'new-rna','txt','All files:*.*',@p_append_triplets,macro);
end;

{ ***** }

procedure p_export_aminoacids (macro : pointer);
var f : text;
    count : integer;
    aa : utf16;
    empty : boolean;
begin
     empty := _getcheckbutton (toggle_seq_empty,macro,2);
     if (finput^.getobjectlength > 0) or empty then
     begin
          _cursor_watch;
          format.push;
          format := format_txt;
          if (finput^.name <> '') then
          begin
               if assignwrite (f,finput^.name) then
               begin
                    writeln (f,'>'+getfilename(save_filename)+#9+'length:'+getstring(finput^.getobjectlength)+#9+#9);
                    aa := '';
                    if (finput^.getobjectlength > 0) then
                    for count := 1 to finput^.getobjectlength do
                    begin
                         aa := aa + three_to_one (finput^.getname(count));
                    end;
                    writeln (f,aa);
                    close (f);
               end;
               updating;
               tmacro(macro^).writeredo ('export.amminoacids','"'+finput^.name+'"'+' '+getstring(empty));
          end;
          format.pop;
          _cursor_arrow;
     end;
end;

procedure proc_export_aminoacids_1 (p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     finput^.name := tmacro(macro^).getparameter(1);
     p_export_aminoacids (macro);
end;

procedure proc_export_aminoacids(p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     _savefile (finput^.name,'new-aa','max','MAX:*.max|All files:*.*',@p_export_aminoacids,macro);
end;

procedure p_append_aminoacids (macro : pointer);
var f : text;
    count : integer;
    aa : utf16;
    empty : boolean;
begin
     empty := _getcheckbutton (toggle_seq_empty,macro,2);
     if (finput^.getobjectlength > 0) or empty then
     begin
          _cursor_watch;
          format.push;
          format := format_txt;
          if (finput^.name <> '') then
          begin
               if assignappend (f,finput^.name) then
               begin
                    writeln (f,'>'+getfilename(save_filename)+#9+'length:'+getstring(finput^.getobjectlength)+#9+#9);
                    aa := '';
                    if (finput^.getobjectlength > 0) then
                    for count := 1 to finput^.getobjectlength do
                    begin
                         aa := aa + three_to_one (finput^.getname(count));
                    end;
                    writeln (f,aa);
                    close (f);
               end;
               updating;
               tmacro(macro^).writeredo ('export.amminoacids','"'+finput^.name+'"'+' '+getstring(empty));
          end;
          format.pop;
          _cursor_arrow;
     end;
end;

procedure proc_append_aminoacids_1 (p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     finput^.name := tmacro(macro^).getparameter(1);
     p_append_aminoacids (macro);
end;

procedure proc_append_aminoacids(p1,macro : gtk_pointer); cdecl;
begin
     save_filename := finput^.name;
     _appendfile (finput^.name,'new-aa','max','MAX:*.max|All files:*.*',@p_append_aminoacids,macro);
end;

{ **************************************************************************** }
{ ******************************** FEBio - Plot ****************************** }
{ **************************************************************************** }

const febio_listmax = 256;
var febio_list : array[1..febio_listmax] of real;

procedure getlist (const s,r : utf16);
var dummy : array[1..febio_listmax] of real;
    x,len : integer;
    ch : utf16char;
    t : utf16;
begin
{ clean }
     fillbyte (dummy,sizeof(dummy),0);
     fillbyte (febio_list,sizeof(febio_list),0);
{     for x := 1 to febio_listmax do begin dummy[x] := 0; febio_list[x] := 0; end;}
{ fill }
     x := 0;
     t := s;
     while (t <> '') and (x < febio_listmax) do
     begin
          inc (x);
          dummy[x] := cutreal (t);
     end;
{ resort }
     len := length(r);
     if len > 0 then
     begin
          if len > febio_listmax then len := febio_listmax;
          for x := 1 to len do
          begin
               ch := getchar(r,x);
               if ch.high = #0 then
               begin
                    case ch.low of
                         '1'..'9' : febio_list[x] := dummy[ord(ch.low)-48];
                         'A'..'Z' : febio_list[x] := dummy[9+ord(ch.low)-64];
                         'a'..'z' : febio_list[x] := dummy[9+ord(ch.low)-96];
                         { else febio_list[x] := 0; }
                    end;
               end;
          end;
     end;
end;

{ *** }

procedure p_import_febio_info (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    check : boolean;
    h : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then dummy.newobject (step+'_'+time);
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := true;
                     end
                     else if check then
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          dummy.newline (getnat(step));
                          check := false;
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.info','"'+finput^.name+'"'+' "'+fmask+'"');
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_info_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_info (macro);
end;

procedure proc_import_febio_info (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_info,macro);
end;

{ ****** }

procedure p_import_febio_point (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then dummy.newobject (step+'_'+time);
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if check then
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          dummy.newline (getnat(step));
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.point','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_point_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_point (macro);
end;

procedure proc_import_febio_point (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_point,macro);
end;

{ ****** }

procedure p_import_febio_vector (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h,i : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then dummy.newobject (step+'_'+time);
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if check then
                     begin
                          getlist (f.get (count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          i.x := febio_list[5];
                          i.y := febio_list[6];
                          i.z := febio_list[7];
                          i.t := febio_list[8];
                          dummy.newpoint (h+i);
                          dummy.newline (getnat(step));
                    end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.vector','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_vector_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_vector (macro);
end;

procedure proc_import_febio_vector (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_vector,macro);
end;

{ ****** }

procedure p_import_febio_line (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               v := 0;
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if check then
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          inc (v);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then
           begin
                dummy.newline (getnat(step));
                dummy.newobject (step+'_'+time);
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.line','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_line_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_line (macro);
end;

procedure proc_import_febio_line (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_line,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_dpoint (macro : pointer);
var f : tfiletext;
    count,v,p : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h,i : hyper;
    points : tpolyhyper;
    first : boolean;
begin
     f := Default(tfiletext);
     points := Default(tpolyhyper);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0; p := 0;
           check := false;
           first := true;
           points.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if first then first := false
                               else
                               begin
                                    if v > 0 then dummy.newobject (step+'_'+time);
                                    inc (v);
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               p := 0;
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if not first then
                     begin
                          if check then
                          begin
                               inc (p);
                               getlist (f.get(count),fmask);
                               i := points.get(p);
                               h.x := febio_list[1];
                               h.y := febio_list[2];
                               h.z := febio_list[3];
                               h.t := febio_list[4]-i.t;
                               dummy.newpoint (h);
                               dummy.newline (getnat(step));
                          end;
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          points.push (h);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           points.done;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dpoint','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dpoint_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dpoint (macro);
end;

procedure proc_import_febio_dpoint (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dpoint,macro);
end;

{ ****** }

procedure p_import_febio_dvector (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h,i : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then dummy.newobject (step+'_'+time);
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if check then
                     begin
                          getlist (f.get (count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          i.x := febio_list[5];
                          i.y := febio_list[6];
                          i.z := febio_list[7];
                          i.t := febio_list[8];
                          dummy.newpoint (h+i);
                          dummy.newline (getnat(step));
                    end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dvector','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dvector_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dvector (macro);
end;

procedure proc_import_febio_dvector (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dvector,macro);
end;

{ ****** }

procedure p_import_febio_dline (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    ffromtime,ftotime,ffromstep,ftostep : real;
    check : boolean;
    h : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           ffromtime := _getreal (import_febio_from_time,macro,3);
           ftotime := _getreal (import_febio_to_time,macro,4);
           ffromstep := _getreal (import_febio_from_step,macro,5);
           ftostep := _getreal (import_febio_to_step,macro,6);
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           check := false;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               v := 0;
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                          check := into(getreal(time),ffromtime,ftotime) and into(getreal(step),ffromstep,ftostep);
                     end
                     else if check then
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          dummy.newpoint (h);
                          inc (v);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then
           begin
                dummy.newline (getnat(step));
                dummy.newobject (step+'_'+time);
           end;
           f.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dline','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(ffromtime)+' '+getstring(ftotime)+' '+getstring(ffromstep)+' '+getstring(ftostep));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dline_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dline (macro);
end;

procedure proc_import_febio_dline (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dline,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_line_sum (macro : pointer);
var f : tfiletext;
    count,count2,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    new : integer;
    sides : tline;
    csides : tlinenat;
begin
     f := Default(tfiletext);
     sides := Default(tline);
     csides := Default(tlinenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           sides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    if sides.neg_length > 0 then
                                       for count2 := (-1*sides.neg_length) to sides.pos_length do
                                           if csides.get(count2) > 0 then dummy.newpoint (gh(count2*fraster,sides.get(count2),0,0));
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          {h.y := febio_list[2];}
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new := round(h.x/fraster);
                          sides.put (new,sides.get(new)+h.t);
                          csides.put (new,csides.get(new)+1);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           sides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.line.sum','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_line_sum_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_line_sum (macro);
end;

procedure proc_import_febio_line_sum (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_line_sum,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_dline_sum (macro : pointer);
var f : tfiletext;
    count,count2,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    new : integer;
    nsides,sides : tline;
    cnsides,csides : tlinenat;
begin
     f := Default(tfiletext);
     nsides := Default(tline);
     sides := Default(tline);
     cnsides := Default(tlinenat);
     csides := Default(tlinenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           nsides.init;
           sides.init;
           cnsides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    if nsides.neg_length > 0 then
                                       for count2 := (-1*nsides.neg_length) to nsides.pos_length do
                                           if cnsides.get (count2) > 0 then dummy.newpoint (gh(count2*fraster,nsides.get(count2),0,0));
                                    dummy.newline (getnat(step));

                                    if sides.neg_length > 0 then
                                       for count2 := (-1*sides.neg_length) to sides.pos_length do
                                           if csides.get (count2) > 0 then dummy.newpoint (gh(count2*fraster,sides.get(count2),0,0));
                                    dummy.newline (getnat(step));

                                    dummy.newobject (step+'_'+time);
                                    nsides.clear;
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new := round(h.x/fraster);
                          if h.y < 0 then
                          begin
                               nsides.put (new,nsides.get(new)+h.t);
                               cnsides.put (new,cnsides.get(new)+1);
                          end
                          else
                          begin
                               sides.put (new,sides.get(new)+h.t);
                               csides.put (new,csides.get(new)+1);
                          end;
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           cnsides.done;
           sides.done;
           nsides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dline.sum','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dline_sum_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dline_sum (macro);
end;

procedure proc_import_febio_dline_sum (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dline_sum,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_line_mean (macro : pointer);
var f : tfiletext;
    count,count2,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    new : integer;
    sides : tline;
    csides : tlinenat;
begin
     f := Default(tfiletext);
     sides := Default(tline);
     csides := Default(tlinenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           sides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    if sides.neg_length > 0 then
                                       for count2 := (-1*sides.neg_length) to sides.pos_length do
                                           if csides.get(count2) > 0 then dummy.newpoint (gh(count2*fraster,sides.get(count2)/csides.get(count2),0,0));
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          {h.y := febio_list[2];}
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new := round(h.x/fraster);
                          sides.put (new,sides.get(new)+h.t);
                          csides.put (new,csides.get(new)+1);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           sides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.line.mean','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_line_mean_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_line_mean (macro);
end;

procedure proc_import_febio_line_mean (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_line_mean,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_dline_mean (macro : pointer);
var f : tfiletext;
    count,count2,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    new : integer;
    nsides,sides : tline;
    cnsides,csides : tlinenat;
begin
     f := Default(tfiletext);
     nsides := Default(tline);
     sides := Default(tline);
     cnsides := Default(tlinenat);
     csides := Default(tlinenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           nsides.init;
           sides.init;
           cnsides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    if nsides.neg_length > 0 then
                                       for count2 := (-1*nsides.neg_length) to nsides.pos_length do
                                           if cnsides.get (count2) > 0 then dummy.newpoint (gh(count2*fraster,nsides.get(count2)/cnsides.get(count2),0,0));
                                    dummy.newline (getnat(step));

                                    if sides.neg_length > 0 then
                                       for count2 := (-1*sides.neg_length) to sides.pos_length do
                                           if csides.get (count2) > 0 then dummy.newpoint (gh(count2*fraster,sides.get(count2)/csides.get(count2),0,0));
                                    dummy.newline (getnat(step));

                                    dummy.newobject (step+'_'+time);
                                    nsides.clear;
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new := round(h.x/fraster);
                          if h.y < 0 then
                          begin
                               nsides.put (new,nsides.get(new)+h.t);
                               cnsides.put (new,cnsides.get(new)+1);
                          end
                          else
                          begin
                               sides.put (new,sides.get(new)+h.t);
                               csides.put (new,csides.get(new)+1);
                          end;
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           cnsides.done;
           sides.done;
           nsides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dline.mean','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dline_mean_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dline_mean (macro);
end;

procedure proc_import_febio_dline_mean (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dline_mean,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_plane_sum (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    rx,ry,new : complexnat;
    x,y : integer;
    sides : tplane;
    csides : tplanenat;
begin
     f := Default(tfiletext);
     sides := Default(tplane);
     csides := Default(tplanenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           sides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    rx := sides.rangex;
                                    ry := sides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if csides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,sides.get(x,y)));
                                                dummy.newline (getnat(step));
                                           end;
                                    dummy.newobject (step+'_'+time);
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new.x := round(h.x/fraster);
                          new.y := round(h.y/fraster);
                          sides.put (new.x,new.y,sides.get(new.x,new.y)+h.t);
                          csides.put (new.x,new.y,csides.get(new.x,new.y)+1);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           sides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.plane.sum','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_plane_sum_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_plane_sum (macro);
end;

procedure proc_import_febio_plane_sum (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_plane_sum,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_dplane_sum (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    rx,ry,new : complexnat;
    x,y : integer;
    nsides,sides : tplane;
    cnsides,csides : tplanenat;
begin
     f := Default(tfiletext);
     nsides := Default(tplane);
     sides := Default(tplane);
     cnsides := Default(tplanenat);
     csides := Default(tplanenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           nsides.init;
           sides.init;
           cnsides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    rx := nsides.rangex;
                                    ry := nsides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if cnsides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,nsides.get(x,y)));
                                           end;
                                    dummy.newline (getnat(step));
                                    rx := sides.rangex;
                                    ry := sides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if csides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,sides.get(x,y)));
                                           end;
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                                    nsides.clear;
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          new.x := round(h.x/fraster);
                          new.y := round(h.y/fraster);
                          if h.z < 0 then
                          begin
                               nsides.put (new.x,new.y,nsides.get(new.x,new.y)+h.t);
                               cnsides.put (new.x,new.y,cnsides.get(new.x,new.y)+1);
                          end
                          else
                          begin
                               sides.put (new.x,new.y,sides.get(new.x,new.y)+h.t);
                               csides.put (new.x,new.y,csides.get(new.x,new.y)+1);
                          end;
                     end;
                end;
           end;
           if data <> '' then progress;
           {if v > 0 then dummy.newobject (step+'_'+time);}
           f.done;
           csides.done;
           cnsides.done;
           sides.done;
           nsides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dplane.sum','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dplane_sum_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dplane_sum (macro);
end;

procedure proc_import_febio_dplane_sum (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dplane_sum,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_plane_mean (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    rx,ry,new : complexnat;
    x,y : integer;
    sides : tplane;
    csides : tplanenat;
begin
     f := Default(tfiletext);
     sides := Default(tplane);
     csides := Default(tplanenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           sides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    rx := sides.rangex;
                                    ry := sides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if csides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,sides.get(x,y)/csides.get(x,y)));
                                                dummy.newline (getnat(step));
                                           end;
                                    dummy.newobject (step+'_'+time);
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          {h.z := febio_list[3];}
                          h.t := febio_list[4];
                          new.x := round(h.x/fraster);
                          new.y := round(h.y/fraster);
                          sides.put (new.x,new.y,sides.get(new.x,new.y)+h.t);
                          csides.put (new.x,new.y,csides.get(new.x,new.y)+1);
                     end;
                end;
           end;
           if data <> '' then progress;
           if v > 0 then dummy.newobject (step+'_'+time);
           f.done;
           csides.done;
           sides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.plane.mean','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_plane_mean_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_plane_mean (macro);
end;

procedure proc_import_febio_plane_mean (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_plane_mean,macro);
end;

{ **************************************************************************** }

procedure p_import_febio_dplane_mean (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s,fmask,step,time,data : utf16;
    fraster : real;
    h : hyper;
    rx,ry,new : complexnat;
    x,y : integer;
    nsides,sides : tplane;
    cnsides,csides : tplanenat;
begin
     f := Default(tfiletext);
     nsides := Default(tplane);
     sides := Default(tplane);
     cnsides := Default(tplanenat);
     csides := Default(tplanenat);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
           fmask := _getedit (import_febio_mask,macro,2);
           fraster := _getreal (import_febio_raster,macro,3);
           if fraster = 0 then fraster := 1;
           dummy.clear;
           f.load (finput^.name);
           step := '';
           time := '';
           data := '';
           v := 0;
           nsides.init;
           sides.init;
           cnsides.init;
           csides.init;
           if f.length > 0 then
           for count := 1 to f.length do
           begin
                if data <> '' then progress ('  Analyze Febio-file ('+data+')',count/f.length);
                if f.getlength (count) > 1 then
                begin
                     if f.getfirst (count) = '*' then
                     begin
                          s := lowercase(f.get (count));
                          if (pos('*step',s) > 0) then
                          begin
                               if v > 0 then
                               begin
                                    rx := nsides.rangex;
                                    ry := nsides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if cnsides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,nsides.get(x,y)/cnsides.get(x,y)));
                                           end;
                                    dummy.newline (getnat(step));
                                    rx := sides.rangex;
                                    ry := sides.rangey;
                                    for x := rx.x to rx.y do
                                        for y := ry.x to ry.y do
                                           if csides.get(x,y) > 0 then
                                           begin
                                                dummy.newpoint (gh(x*fraster,y*fraster,0,sides.get(x,y)/csides.get(x,y)));
                                           end;
                                    dummy.newline (getnat(step));
                                    dummy.newobject (step+'_'+time);
                                    nsides.clear;
                                    sides.clear;
                               end;
                               step := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                               time := '';
                               data := '';
                               inc (v);
                          end
                          else if (pos('*time',s) > 0) then time := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ')
                          else if (pos('*data',s) > 0) then data := killlast(killfirst (copy (s,pos('=',s)+1,length(s)),' '),' ');
                     end
                     else
                     begin
                          getlist (f.get(count),fmask);
                          h.x := febio_list[1];
                          h.y := febio_list[2];
                          h.z := febio_list[3];
                          h.t := febio_list[4];
                          new.x := round(h.x/fraster);
                          new.y := round(h.y/fraster);
                          if h.z < 0 then
                          begin
                               nsides.put (new.x,new.y,nsides.get(new.x,new.y)+h.t);
                               cnsides.put (new.x,new.y,cnsides.get(new.x,new.y)+1);
                          end
                          else
                          begin
                               sides.put (new.x,new.y,sides.get(new.x,new.y)+h.t);
                               csides.put (new.x,new.y,csides.get(new.x,new.y)+1);
                          end;
                     end;
                end;
           end;
           if data <> '' then progress;
           {if v > 0 then dummy.newobject (step+'_'+time);}
           f.done;
           csides.done;
           cnsides.done;
           sides.done;
           nsides.done;

           finput^.append (dummy);
           state[input] := true;
           ref_state[input] := true;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('import.febio.dplane.mean','"'+finput^.name+'"'+' "'+fmask+'" '+getstring(fraster));
     end;
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_febio_dplane_mean_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_febio_dplane_mean (macro);
end;

procedure proc_import_febio_dplane_mean (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,@p_import_febio_dplane_mean,macro);
end;

{ **************************************************************************** }

procedure p_import_gps_data (macro : pointer);
var f : tfiletext;
    count,v : integer;
    s : utf16;
    h : hyper;
begin
     f := Default (tfiletext);

     _cursor_watch;
     format.push;
     format := format_txt;
     if finput^.name <> '' then
     begin
          dummy.clear;
          f.load (finput^.name);
          v := 0;
          if f.length > 0 then
          for count := 1 to f.length do
          begin
               s := f.get (count);
               if length (s) > 9 then
               if split(s,',') = '$PMGNTRK' then
               begin
                    h.y := getreal (split (s,',')); { index number }
                    split (s,',');
                    h.x := getreal (split (s,','));
                    split (s,',');
                    h.z := getreal (split (s,','))/1000;
                    split (s,',');
                    h.t := getreal (split (s,','));
                    if h <> Hzero then
                    begin
                         dummy.newpoint (h);
                         inc (v);
                    end;
               end;
          end;
          if v > 0 then
          begin
               dummy.newline (0);
               dummy.newobject (getfile(finput^.name));
          end;
          f.done;

          finput^.append (dummy);
          state[input] := true;
          ref_state[input] := true;
          calculating;
          updating;
          drawing;
     end;
     tmacro(macro^).writeredo ('import.gps.data','"'+finput^.name+'"');
     format.pop;
     _cursor_arrow;
end;

procedure proc_import_gps_data_1 (p1,macro : gtk_pointer); cdecl;
begin
     finput^.name := tmacro(macro^).getparameter(1);
     p_import_gps_data (macro);
end;

procedure proc_import_gps_data (p1,macro : gtk_pointer); cdecl;
begin
     _openfile (finput^.name,'Track:*.trk|All files:*.*',@p_import_gps_data,macro);
end;

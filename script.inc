{//////////////////////////////////////////////////////////////////////////////}

procedure clear_macro (p1,macro : gtk_pointer); cdecl;
var i : integer;
    s : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          tmacro(macro^).clear;
          s := '';
          _setedittext (macro_text[i],s);
          macro_save[i] := false;
          _setpagelabel (subnote_macro,i,'Macro '+getstring(i+1)+' ');
          macro_filename[i] := 'Macro'+getstring(i+1);
          _cursor_arrow;
     end;
end;

procedure log_macro (p1,macro : gtk_pointer); cdecl;
var x,i : integer;
    s : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
           _cursor_watch;
           s := '';
           if tmacro(macro^).redolength > 0 then
              for x := 1 to tmacro(macro^).redolength do s := s + tmacro(macro^).getredo (x) + #10;
           _setedittext (macro_text[i],s);
           macro_save[i] := true;
           _setpagelabel (subnote_macro,i,'*Log ');
           macro_filename[i] := 'Log';
           _cursor_arrow;
     end;
end;

procedure proc_load_macro (macro : pointer);
var x,i : integer;
    s : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          tmacro(macro^).load (macro_filename[i]);
          s := '';
          if tmacro(macro^).length > 0 then
             for x := 1 to tmacro(macro^).length do s := s + tmacro(macro^).get (x) + #10;
          _setedittext (macro_text[i],s);
          macro_save[i] := false;
          s := getfile (macro_filename[i]);
     {$ifdef cloud}
          if length (s) > 8 then _setpagelabel (subnote_macro,i,copy(s,1,8)+'... ')  { 12 chars }
                            else _setpagelabel (subnote_macro,i,s+' ');
     {$else}
          if length (s) > 28 then _setpagelabel (subnote_macro,i,copy(s,1,28)+'... ')  { 32 chars }
                             else _setpagelabel (subnote_macro,i,s+' ');
     {$endif}
          _cursor_arrow;
     end;
end;

procedure load_macro_1 (p1,macro : gtk_pointer); cdecl;
var i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          macro_filename[i] := '';
          _openfile (macro_filename[i],'All files:*.*|Script:*.run;*.macro;*.script',@proc_load_macro,macro);
     end;
end;

procedure load_macro (const filename : utf16;macro : pointer);
var x{,y},i : integer;
    s,t : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          tmacro(macro^).load (filename);
          s := '';
          if tmacro(macro^).length > 0 then
          for x := 1 to tmacro(macro^).length do
          begin
               t := tmacro(macro^).get (x);
               s := s + t + #10;
          end;
          _setedittext (macro_text[i],s);
          macro_save[i] := false;
          macro_filename[i] := filename;
          s := getfile (filename);
{$ifdef cloud}
          if length (s) > 8 then _setpagelabel (subnote_macro,i,copy(s,1,8)+'... ')  { 12 chars }
                            else _setpagelabel (subnote_macro,i,s+' ');
{$else}
          if length (s) > 28 then _setpagelabel (subnote_macro,i,copy(s,1,28)+'... ')  { 32 chars }
                             else _setpagelabel (subnote_macro,i,s+' ');
{$endif}
          _cursor_arrow;
     end;
end;

procedure proc_save_macro (macro : pointer);
var t : text;
    i : integer;
    buffer : gtk_textbuffer;
    u,s : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          buffer := macro_text[i];
          macro_save[i] := false;
          if (_getedittextlength (buffer) > 0) then
          begin
               if assignwrite (t,macro_filename[i]) then
               begin
                    u := _getedittext(buffer);
                    {LineEnding = #10    Linux, Amiga, ...
                     LineEnding = #13    MacOS
                     LineEnding = #13#10 Windows, Dos, ...}
                    if (getchar (u,length(u)) = #10) or (getchar (u,length(u)) = #13) then write (t,u)
                                                                                      else writeln (t,u);
                    writeln (t,'// saved on date '+getstring(getdate)+' | time '+getstring(gettime));
                    close (t);
               end;
          end;
          s := getfile (macro_filename[i]);
     {$ifdef cloud}
          if length (s) > 8 then _setpagelabel (subnote_macro,i,copy(s,1,8)+'... ')  { 12 chars }
                            else _setpagelabel (subnote_macro,i,s+' ');
     {$else}
          if length (s) > 28 then _setpagelabel (subnote_macro,i,copy(s,1,28)+'... ')  { 32 chars }
                             else _setpagelabel (subnote_macro,i,s+' ');
     {$endif}
          _cursor_arrow;
     end;
end;

procedure save_macro_1 (p1,macro : gtk_pointer); cdecl;
var i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then _savefile (macro_filename[i],'Macro'+getstring(i+1),'macro','All files:*.*|Script:*.run;*.macro;*.script',@proc_save_macro,macro);
end;

procedure save_macro (const filename : utf16;macro : pointer);
var t : text;
    i : integer;
    buffer : gtk_textbuffer;
    u,s : utf16;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          buffer := macro_text[i];
          if _getedittextlength (buffer) > 0 then
          begin
               if assignwrite (t,filename) then
               begin
                    u := _getedittext(buffer);
                    if getchar (u,length(u)) = #10 then write (t,u)
                                                   else writeln (t,u);
                    writeln (t,'// saved on date '+getstring(getdate)+' | time '+getstring(gettime));
                    close (t);
               end;
          end;
          macro_filename[i] := filename;
          s := getfile (filename);
{$ifdef cloud}
          if length (s) > 8 then _setpagelabel (subnote_macro,i,copy(s,1,8)+'... ')  { 12 chars }
                            else _setpagelabel (subnote_macro,i,s+' ');
{$else}
          if length (s) > 28 then _setpagelabel (subnote_macro,i,copy(s,1,28)+'... ')  { 32 chars }
                             else _setpagelabel (subnote_macro,i,s+' ');
{$endif}
          _cursor_arrow;
     end;
end;

procedure my_refresh_constants;
begin
{$ifdef cloud}
     macro_self.putconstant ('point.length',getstring(finput^.getpointlength));
     macro_self.putconstant ('point.count',getstring(finput^.pointcounter));
     macro_self.putconstant ('line.length',getstring(finput^.getlinelength));
     macro_self.putconstant ('line.count',getstring(finput^.linecounter));
     macro_self.putconstant ('line.material',getstring(finput^.getallmaterial(finput^.linecounter)));
     macro_self.putconstant ('object.length',getstring(finput^.getobjectlength));
     macro_self.putconstant ('object.count',getstring(finput^.objectcounter));
     macro_self.putconstant ('object.name',finput^.getname(finput^.objectcounter));
{$endif}
     _update; { for core functions with no update }
end;

procedure run_macro (p1,macro : gtk_pointer); cdecl;
var s,oldfilename,oldlabelname : utf16;
    i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          oldlabelname := _getpagelabel (subnote_macro,i);
          oldfilename := macro_filename[i];
          s := 'script.macro.run';
          save_macro (s,macro); { ??? override old files ??? }
          tmacro(macro^).load (s);
          macro_filename[i] := oldfilename;
          _setpagelabel (subnote_macro,i,oldlabelname);
          _cursor_arrow;

          tmacro(macro^).refresh_constants := @my_refresh_constants;
          tmacro(macro^).run;

          if tmacro(macro^).status <> '' then _dialog_message ('Script error!',#10+' '+tmacro(macro^).status+' '+#10);
     end;
end;

procedure run_hide_macro (p1,macro : gtk_pointer); cdecl;
var s,oldfilename,oldlabelname : utf16;
    i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          ifdraw := false;
          oldlabelname := _getpagelabel (subnote_macro,i);
          oldfilename := macro_filename[i];
          s := 'script.macro.run';
          save_macro (s,macro); { ??? override old files ??? }
          tmacro(macro^).load (s);
          macro_filename[i] := oldfilename;
          _setpagelabel (subnote_macro,i,oldlabelname);
          _cursor_arrow;

          tmacro(macro^).refresh_constants := @my_refresh_constants;
          tmacro(macro^).run;

          _cursor_watch;
          ifdraw := true;
{$ifdef cloud}
          calculating;
          updating;
          drawing;
{$endif}
          _cursor_arrow;
          if tmacro(macro^).status <> '' then _dialog_message ('Script error!',#10+' '+tmacro(macro^).status+' '+#10);
    end;
end;

procedure run_hidehide_macro (p1,macro : gtk_pointer); cdecl;
var s,oldfilename,oldlabelname : utf16;
    i : integer;
begin
     i := _getpage (subnote_macro);
     if into (i,0,macro_length) then
     begin
          _cursor_watch;
          ifdraw := false;
          oldlabelname := _getpagelabel (subnote_macro,i);
          oldfilename := macro_filename[i];
          s := 'script.tmacro(macro^).run';
          save_macro (s,macro); { ??? override old files ??? }
          tmacro(macro^).load (s);
          macro_filename[i] := oldfilename;
          _setpagelabel (subnote_macro,i,oldlabelname);
          _cursor_arrow;

          tmacro(macro^).refresh_constants := @my_refresh_constants;
          tmacro(macro^).run;

          _cursor_watch;
          ifdraw := true;
          _cursor_arrow;
          if tmacro(macro^).status <> '' then _dialog_message ('Script error!',#10+' '+tmacro(macro^).status+' '+#10);
    end;
end;

procedure kill_macro (p1,macro : gtk_pointer); cdecl;
begin
     if into (_getpage (subnote_macro),0,macro_length) then
     begin
          if tmacro(macro^).running then
          begin
               tmacro(macro^).kill;
          end;
     end;
end;

{ **************************************************************************** }
{ ********************************* Events *********************************** }
{ **************************************************************************** }

var tagupdate : integer;

function set_tags (macro : gtk_pointer): gtk_boolean; cdecl;
var count : integer;
    start,ende,marke1,marke2 : tgtk_iteration;
    s,t,u,v : utf16;
    x,linelen,i : integer;
    vars : tpolychars;
    buffer : gtk_textbuffer;
  procedure command (first,second : integer;const s : utf16);
  var ch,oldch : utf16char;
      t : utf16;
      x,oldx,k1,k2,k3,k4,a1,a2 : integer;
      ccount : integer;
    procedure test;
    begin
         if oldx = 0 then
         begin
              oldx := x;
              oldch := ch;
         end;
    end;
  begin
       if liball.length (s) > 0 then
       begin
            a1 := 0; a2 := 0;
            k1 := 0; k2 := 0; k3 := 0; k4 := 0;
            oldx := 0;
            ccount := 0;
            oldch.high := #0;
            oldch.low := #0;
            for x := 1 to liball.length (s) do
            begin
                 ch := getchar(s,x);
                 if (ch.high = #0) then
                 begin
                      if (ch.low = '''') then
                      begin
                           if a2 = 0 then { " has priority, first serves }
                           begin
                                if a1 = 0 then inc (a1)
                                          else dec (a1);
                           end;
                           test;
                      end
                      else if (ch.low = '"') then
                      begin
                           if a1 = 0 then { ' has priority, first serves }
                           begin
                                if a2 = 0 then inc (a2)
                                          else dec (a2);
                           end;
                           test;
                      end
                      else if (a1 <> 0) or (a2 <> 0) then { do nothing inside of '' or "" }
                      else
                      begin
                           case ch.low of
                              '(' : begin inc (k1); test; end;
                              ')' : begin dec (k1); test; end;
                              '{' : begin inc (k2); test; end;
                              '}' : begin dec (k2); test; end;
                              '[' : begin inc (k3); test; end;
                              ']' : begin dec (k3); test; end;
                              '<' : begin inc (k4); test; end;
                              '>' : begin dec (k4); test; end;
                              else
                              begin
                                   if (a1 = 0) and (a2 = 0) then
                                      if (k1 = 0) and (k2 = 0) and (k3 = 0) and (k4 = 0) then
                                      begin
                                           case ch.low of
                                              ' ',#9  :
                                                        if oldx <> 0 then
                                                        begin
                                                             marke1 := _getbufferpos (buffer, count, oldx-1);
                                                             marke2 := _getbufferpos (buffer, count, x-1);
                                                             inc (ccount);
                                                             if (first = 1) and (first = ccount) then { command }
                                                             begin
                                                                  _applybuffertag (buffer, 'command', marke1, marke2);
                                                             end
                                                             else if (first > 1) and (first = ccount) then { *command command }
                                                             begin
                                                                  _applybuffertag (buffer, 'execute', marke1, marke2);
                                                             end
                                                             else if (first > 1) and (first-1 = ccount) then { command *command }
                                                             begin
                                                                  _applybuffertag (buffer, 'command', marke1, marke2);
                                                             end
                                                             else if second <= ccount then
                                                             begin
                                                                  if ((oldch.high = #0) and (oldch.low in ['"','''','#']))
                                                                  then _applybuffertag (buffer, 'string', marke1, marke2)
                                                                  else
                                                                  begin
                                                                       if ((oldch.high = #0) and (oldch.low in ['-','0'..'9','(','[','{','<','%','$']))
                                                                          then _applybuffertag (buffer, 'value', marke1, marke2)
                                                                          else
                                                                          begin
                                                                               t := copy (s,oldx,x-oldx);
                                                                               if t <> '' then
                                                                               begin
                                                                                    if (t.high[1] = #0) and (t.low[1] = '@') then
                                                                                    begin
                                                                                         if vars.search (copy(t,2,length(t))) > 0 then _applybuffertag (buffer, 'variable2', marke1, marke2)
                                                                                    end
                                                                                    else if vars.search (t) > 0 then _applybuffertag (buffer, 'variable2', marke1, marke2);
                                                                               end;
                                                                          end;
                                                                  end;
                                                             end;
                                                             oldx := 0;
                                                        end;
                                              else
                                              begin
                                                   if oldx = 0 then
                                                   begin
                                                        oldx := x;
                                                        oldch := ch;
                                                   end;
                                              end;
                                           end;
                                      end;
                              end;
                          end;
                      end;
                 end
                 else
                 begin
                      if oldx = 0 then
                      begin
                           oldx := x;
                           oldch := ch;
                      end;
                 end;
            end;
            if oldx <> 0 then
            begin
                 marke1 := _getbufferpos (buffer, count, oldx-1);
                 marke2 := _getbufferpos (buffer, count, liball.length(s));
                 inc (ccount);
                 if (first = 1) and (first = ccount) then { command }
                 begin
                      _applybuffertag (buffer, 'command', marke1, marke2);
                 end
                 else if (first > 1) and (first = ccount) then { *command command }
                 begin
                      _applybuffertag (buffer, 'execute', marke1, marke2);
                 end
                 else if (first > 1) and (first-1 = ccount) then { command *command }
                 begin
                      _applybuffertag (buffer, 'command', marke1, marke2);
                 end
                 else if second <= ccount then
                 begin
                      if ((oldch.high = #0) and (oldch.low in ['"','''','#']))
                         then _applybuffertag (buffer, 'string', marke1, marke2)
                         else
                         begin
                              if ((oldch.high = #0) and (oldch.low in ['-','0'..'9','(','[','{','<','%','$']))
                                 then _applybuffertag (buffer, 'value', marke1, marke2)
                                 else
                                 begin
                                      t := copy (s,oldx,liball.length(s));
                                      if t <> '' then
                                      begin
                                           if (t.high[1] = #0) and (t.low[1] = '@') then
                                           begin
                                                if vars.search (copy(t,2,length(t))) > 0 then _applybuffertag (buffer, 'variable2', marke1, marke2)
                                           end
                                           else if vars.search (t) > 0 then _applybuffertag (buffer, 'variable2', marke1, marke2);
                                      end;
                                 end;
                         end;
                 end;
            end;
       end;
  end;

begin
     vars := Default(tpolychars);

     if (_mainwindow <> nil) then
     begin
          i := _getpage (subnote_macro);
          if into (i,0,macro_length) then
          begin
               buffer := macro_text[i];
               linelen := _getedittextlinelength (buffer);
               if  linelen > 0 then
               begin
          { line_rows numbers }
 {                  if linelen <> gtk_text_buffer_get_line_count (macro_text_count[i]) then
                    begin
                         s := '';
                         if linelen > 1 then
                            for count := 1 to linelen-1 do s := s + getstring(count,true)+#10;
                         s := s + getstring(linelen,true);
                         _settext (macro_text_count[i],s);
                    end;}
          { Init }
                    if _tagtablesize (buffer) < 9 then
                    begin
                         _createtag (buffer, 'command','',true,false);
                         _createtag (buffer, 'assignment','#F00',true,false);
                         _createtag (buffer, 'execute','#808',true,false);
                         _createtag (buffer, 'comment','#00F',true,false);
                         _createtag (buffer, 'lightcomment','#AA0',true,false);
                         _createtag (buffer, 'string','#F00',false,false);
                         _createtag (buffer, 'variable','#080',false,true);
                         _createtag (buffer, 'variable2','#080',false,false);
                         _createtag (buffer, 'value','#00F',false,false);
                    end;
                    vars.init;
                    vars.push ('io.workdir');
                    vars.push ('options');
                    vars.push ('point.length');
                    vars.push ('point.count');
                    vars.push ('line.length');
                    vars.push ('line.count');
                    vars.push ('line.material');
                    vars.push ('object.length');
                    vars.push ('object.count');
                    vars.push ('object.name');
                    vars.push ('io.files.get'); { with dir and file }
                    vars.push ('io.files.getfile');
                    vars.push ('io.files.getdir');
                    vars.push ('io.files.getname');
                    vars.push ('io.files.getextension');
                    vars.push ('io.files.length');
                    vars.push ('io.dirs.get');
                    vars.push ('io.dirs.length');
                    vars.push ('for.length');
                    vars.push ('for.count');
                    vars.push ('condition');
                    vars.sort;
               { Read Buffer }
                    {linelen := gtk_text_buffer_get_line_count (buffer)-1;}
                    for count := 0 to linelen do
                    begin
                         tagupdate := 1;
                         _update;
                         if (_mainwindow = nil) or (tagupdate = 0) then
                         begin
                              vars.done;
                              exit (false); { leave is outdated }
                         end;
                         s := _getbufferline (buffer,count);
                         _getbufferline (buffer,count,start,ende);
                         _clearbufferlinetags (buffer,count);
               { Check Buffer line_rows }
                         if s <> '' then
                         begin
               { Comments }
                               replace (s,#9,' ');

                               if (pos ('//',s) = 1) then x := 1 else x := pos (' //',s);
                               if (pos ('@@ ',s) = 1) then x := 1; { for store or append block }
                               if x > 0 then
                               begin
                                    marke1 := _getbufferpos (buffer, count, x-1);
                                    _applybuffertag (buffer, 'comment', marke1, ende);
                                    if x > 1 then s := copy (s,1,x-1)
                                             else s := '';
                               end;
                               if (pos ('**',s) = 1) then x := 1 else x := pos (' **',s);
                               if x > 0 then { highlighted comment }
                               begin
                                    marke1 := _getbufferpos (buffer, count, x-1);
                                    _applybuffertag (buffer, 'lightcomment', marke1, ende);
                                    if x > 1 then s := copy (s,1,x-1)
                                             else s := '';
                               end;

                               t := s;
                               t := killfirst(killlast(t,' '),' ');
                               if (t <> '') and (x <> 1) then
                               begin
                                    u := lowercase(split (t,' ')); { get command in t }
                                    v := getsplit (t,' '); { get second command in t }
                                    if liball.length (u) > 0 then
                                    if (v = ':=') or (v = '~=') or (v = '|=') or (v = '+=') or
                                       (v = '-=') or (v = '*=') or (v = '/=') or (v = 'x=') or
                                       (v = '#=') then
                                    begin
                                         x := pos (v,s);
                                         if x > 0 then
                                         begin
                                              if x > 1 then
                                              begin
                                                   if vars.search (u) = 0 then
                                                   begin
                                                        marke1 := _getbufferpos (buffer, count, x-1-1);
                                                        _applybuffertag (buffer, 'variable', start, marke1);
                                                        vars.push (u);
                                                   end
                                                   else
                                                   begin
                                                        marke1 := _getbufferpos (buffer, count, x-1-1);
                                                        _applybuffertag (buffer, 'variable2', start, marke1);
                                                   end;
                                              end;
                                              marke1 := _getbufferpos (buffer, count, x-1);
                                              marke2 := _getbufferpos (buffer, count, x+2-1);
                                              _applybuffertag (buffer, 'assignment', marke1, marke2);
                                         end;
                                         v := split (t,' '); { get third command in t }
                                         if tmacro(macro^).search_function_command(v) > 0 then
                                         begin
                                              x := pos (v,s);
                                              marke1 := _getbufferpos (buffer, count, x-1);
                                              marke2 := _getbufferpos (buffer, count, x+length(v)-1);
                                              _applybuffertag (buffer, 'command', marke1, marke2);
                                              command (0,4,s);
                                         end
                                         else command (0,3,s);
                                    end
                                    else
                                    begin
                                         if u.high[1] = #0 then
                                         begin
                                              case u.low[1] of
                                                   '@' : begin
                                                              x := pos ('@',s);
                                                              if x > 0 then command (1,2,s);
                                                         end;
               { ************************************* }
                                                   'a' : if  (u = 'append') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'b' : if (u = 'begin') or (u = 'break') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'e' : if (u = 'execute') then command (2,3,s)
                                                         else if (u = 'end') then command (1,2,s)
                                                         else if (u = 'else') then command (2,3,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'f' : if (u = 'for') or (u = 'for.part') or (u = 'function') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'g' : if (u = 'global') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'h' : if (u = 'halt') then command (1,2,s)
                                                       else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'i' : if pos ('if',u) = 1 then
                                                         begin
                                                              if (u = 'if') or (u = 'ifall') or
                                                                 (u = 'ifnot') or (u = 'ifnotall') or
                                                                 (u = 'ifone') or (u = 'ifnotone') or
                                                                 (u = 'ifsmaller') or (u = 'ifequal') or (u = 'ifbigger') or
                                                                 (u = 'ifempty') or
                                                                 (u = 'ifsame') or (u = 'ifnotsame') or
                                                                 (u = 'ifcontain') or (u = 'ifnotcontain') or
                                                                 (u = 'ifallcontain') or (u = 'ifnotallcontain') or
                                                                 (u = 'ifonecontain') or (u = 'ifnotonecontain') or
                                                                 (u = 'ifexists') or (u = 'ifnotexists') or (u = 'iffilesize')
                                                              then command (1,2,s)
                                                              else if (u = 'if.then') or (u = 'if.else') or
                                                                      (u = 'if.true') or (u = 'if.false')
                                                              then command (2,3,s);
                                                         end
                                                         else if (u = 'ignore') then command (1,2,s)
                                                         else if (u = 'include') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'l' : if (u = 'local') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'm' : if (u = 'module') or (u = 'maximize') or (u = 'minimize') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'o' : if (u = 'output.store') or (u = 'output.append') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'p' : if (u = 'procedure') or (u = 'process') or (u = 'parallel') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'r' : if (u = 'run') or (u = 'repeat') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   's' : if (u = 'sub') or (u = 'store') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   't' : if (u = 'then') then command (2,3,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'u' : if (u = 'until') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'v' : if (u = 'var') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                   'w' : if (u = 'while') or (u = 'with') then command (1,2,s)
                                                         else if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                         else command (0,2,s);
               { ************************************* }
                                                    else
                                                    begin
                                                         if tmacro(macro^).search_block_procedure_command (u) > 0 then command (1,2,s)
                                                                                                                  else command (0,2,s);
                                                    end;

                                               end;
                                         end;
                                    end;
                               end;
                         end;
                    end;
                    vars.done;
               end;
          end;
          tagupdate := 0;
     end;
     set_tags := gtk_false; { to remove from idle list }
end;

procedure set_changed (buffer,macro : gtk_pointer); cdecl;
var i : integer;
    s : utf16;
begin
     if (_mainwindow <> nil) then
     begin
          i := _getpage (subnote_macro);
          if into (i,0,macro_length) then
          begin
               if not stop_change then
               begin
                    {writeln ('o:'+pre_buf+'|'+new_buf+'|'+post_buf);}
                    pre_buf := new_buf;
                    new_buf := _getedittext(macro_text[i]);
                    post_buf := new_buf;
                    {writeln ('c:'+pre_buf+'|'+new_buf+'|'+post_buf);}
               end;
               macro_save[i] := false; { false }
               s := liball.getfile (macro_filename[i]);
               {$ifdef cloud}
                if liball.length (s) > 8 then _setpagelabel (subnote_macro,i,'*'+copy(s,1,8)+'... ')  { 12 chars }
                                         else _setpagelabel (subnote_macro,i,'*'+s+' ');
               {$else}
               if liball.length (s) > 28 then _setpagelabel (subnote_macro,i,'*'+copy(s,1,28)+'... ')  { 32 chars }
                                         else _setpagelabel (subnote_macro,i,'*'+s+' ');
               {$endif}
               _idle (@set_tags,macro);
          end;
     end;
end;

procedure set_switched (notebook,page : gtk_pointer;page_num : gtk_int;macro : gtk_pointer); cdecl;
begin
     if (_mainwindow <> nil) then
     begin
          if notebook = subnote_macro then
             if into (page_num,0,macro_length) then
             begin
                  if not stop_change then
                  begin
                       pre_buf := _getedittext(macro_text[page_num]);
                       new_buf := pre_buf;
                       post_buf := pre_buf;
                       {writeln (pre_buf+'|'+new_buf+'|'+post_buf);}
                  end;
                  _idle (@set_tags,macro);
             end;
     end;
end;

function set_focused : gtk_boolean; cdecl;
begin
     set_focused := gtk_true;
end;

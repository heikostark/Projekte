{ **************************************************************************** }
{ ***************************** Mircoscibe Inputmethod *********************** }
{ **************************************************************************** }

var minput : utf16;

{ **************************************************************************** }

procedure proc_input (p1,macro : gtk_pointer); cdecl;
begin
     inc (inputmethod);
     if inputmethod > 4 then inputmethod := 1;
     if finput^.getlinelength > 0 then
        if  (inputmethod = 4) and ((finput^.getpointlength/finput^.getlinelength) > 1000) then inputmethod := 1;
     updating;
end;

{ ****************************** Newline ************************************* }

procedure proc_mic_newpoint (p1,macro : gtk_pointer); cdecl;
var v : hyper;
begin
     _setlabel (m3dlabel,minput);
     v := gethyper (minput);
     if v <> Hzero then
     begin
          finput^.newpoint (v);
     end;
     minput := '';
     calculating;
     updating;
     drawing;
end;

procedure proc_mic_newline (p1,macro : gtk_pointer); cdecl;
var v : hyper;
begin
     _setlabel (m3dlabel,minput);
     v := gethyper (minput);
     if v <> Hzero then
     begin
          finput^.newpoint (v);
     end;
     minput := '';
     if finput^.getpointlength > 0 then
     begin
          finput^.newline (0); { newline }
          calculating;
          updating;
          drawing;
     end;
end;

procedure proc_mic_newobject (p1,macro : gtk_pointer); cdecl;
var v : hyper;
begin
     _setlabel (m3dlabel,minput);
     v := gethyper (minput);
     if v <> Hzero then
     begin
          finput^.newpoint (v);
          finput^.newline (0);
     end;
     minput := '';
     if finput^.getpointlength > 0 then
     begin
          finput^.newobject ('');
          calculating;
          updating;
          drawing;
     end;
end;

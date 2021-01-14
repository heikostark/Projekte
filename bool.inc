{ **************************************************************************** }
{ ******************************* Erase / Move / Copy ************************ }
{ **************************************************************************** }

{ ***************************** Point erasing ******************************** }

procedure proc_erase_point (p1,macro : gtk_pointer); cdecl;
begin
      if finput^.getpointlength > 0 then
      begin
           _cursor_watch;
           finput^.markallpoint (finput^.pointcounter);
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.erase.point');
           _cursor_arrow;
      end;
end;

procedure proc_erase_point_list (p1,macro : gtk_pointer); cdecl; { only command }
var x,p : integer;
begin
      if finput^.getpointlength > 0 then
      begin
           if tmacro(macro^).parameterlength > 0 then
           begin
                _cursor_watch;
                for x := 1 to tmacro(macro^).parameterlength do
                begin
                     p := getnat(tmacro(macro^).getparameter (x));
                     finput^.markallpoint (p);
                end;
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.point.list');
                _cursor_arrow;
           end;
      end;
end;

{ ***************************** Point masking ******************************** }

procedure proc_mask_points (p1,macro : gtk_pointer); cdecl;
var i1,i2 : integer;
    check : boolean;
begin
      if (finput^.getpointlength > 0) and (finputedit^.getpointlength > 0) then
      begin
           _cursor_watch;
           for i1 := 1 to finput^.getpointlength do
           begin
                case brush of
                     1,2 : check := true; { inside }
                     11,12 : check := false; { outside }
                     else check := false; { always outside }
                end;
                for i2 := 1 to finputedit^.getpointlength do
                begin
                     case brush of
                          1,2 : if finput^.getpoint(i1) = finputedit^.getpoint(i2) then
                          begin
                               check := false;
                               break;
                          end;
                          else if finput^.getpoint(i1) = finputedit^.getpoint(i2) then
                          begin
                               check := true;
                               break;
                          end;
                     end;
                end;
                if check then finput^.markallpoint (i1);
           end;
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.mask.points');
           _cursor_arrow;
      end;
end;

{ ***************************** Point moving ********************************* }

procedure proc_move_point (p1,macro : gtk_pointer); cdecl;
var z : integer;
begin
      if finput^.getpointlength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           z := finput^.pointcounter;
           dummy.newpoint(finput^.getpoint(z));
           dummy.newline (finput^.getallmaterial(z));
           dummy.newobject ('');
           finput^.markallpoint (z);
           finput^.erasemarked;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.move.point');
           _cursor_arrow;
      end;
end;

{ ***************************** Point kopieren ******************************* }

procedure proc_copy_point (p1,macro : gtk_pointer); cdecl;
begin
      if finput^.getpointlength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           dummy.newpoint(finput^.getpoint(finput^.pointcounter));
           dummy.newline (finput^.getallmaterial(finput^.pointcounter));
           dummy.newobject ('');
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.copy.point');
           _cursor_arrow;
      end;
end;

{ ****************************** Line löschen ******************************** }

procedure proc_erase_line (p1,macro : gtk_pointer); cdecl;
begin
      if finput^.getlinelength > 0 then
      begin
           _cursor_watch;
           finput^.markallline (finput^.linecounter);
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.erase.line');
           _cursor_arrow;
      end;
end;

procedure proc_erase_line_list (p1,macro : gtk_pointer); cdecl; { only command }
var x,l : integer;
    s : utf16;
begin
      if finput^.getlinelength > 0 then
      begin
           if tmacro(macro^).parameterlength > 0 then
           begin
                _cursor_watch;
                s := '';
                for x := 1 to tmacro(macro^).parameterlength do
                begin
                     l := getnat(tmacro(macro^).getparameter (x));
                     finput^.markallline (l);
                     s := s + getstring(l) + ' ';
                end;
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.line.list',s);
                _cursor_arrow;
           end;
      end;
end;

procedure proc_erase_material_list (p1,macro : gtk_pointer); cdecl; { only command }
var x,m,l : integer;
    s : utf16;
begin
      if finput^.getlinelength > 0 then
      begin
           if tmacro(macro^).parameterlength > 0 then
           begin
                _cursor_watch;
                s := '';
                for x := 1 to tmacro(macro^).parameterlength do
                begin
                     m := getnat(tmacro(macro^).getparameter (x));
                     for l := 1 to finput^.getlinelength do
                     begin
                          if finput^.getallmaterial (l) = m then finput^.markallline (l);
                     end;
                     s := s + getstring(m) + ' ';
                end;
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.material.list',s);
                _cursor_arrow;
           end;
      end;
end;

procedure proc_erase_line_lengths (p1,macro : gtk_pointer); cdecl;
var l : integer;
    mi,ma : real;
    function getlen (l : integer) : real;
    var x : integer;
    begin
         getlen := 0;
         if finput^.getalllinepointlength(l) > 1 then
         begin
              for x := 1 to finput^.getalllinepointlength(l)-1 do
              begin
                   getlen := getlen + getlength(finput^.getline(l,x+1)-finput^.getline(l,x));
              end;
         end;
    end;
begin
      if finput^.getlinelength > 0 then
      begin
          _cursor_watch;
          mi := _getreal (bool_line_materials_left,macro,1);
          ma := _getreal (bool_line_materials_right,macro,2);
          for l := 1 to finput^.getlinelength do
          begin
               if into (getlen(l),mi,ma) then finput^.markallline (l);
          end;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.erase.line.lengths',getstring(mi)+' '+getstring(ma));
          _cursor_arrow;
      end;
end;

procedure proc_erase_line_materials (p1,macro : gtk_pointer); cdecl;
var l : integer;
    mi,ma : integer;
begin
      if finput^.getlinelength > 0 then
      begin
          _cursor_watch;
          mi := _getnat (bool_line_materials_left,macro,1);
          ma := _getnat (bool_line_materials_right,macro,2);
          for l := 1 to finput^.getlinelength do
          begin
               if into (finput^.getallmaterial (l),mi,ma) then finput^.markallline (l);
          end;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.erase.line.materials',getstring(mi)+' '+getstring(ma));
          _cursor_arrow;
      end;
end;

{ ***************************** Line masking ********************************* }

procedure proc_mask_lines (p1,macro : gtk_pointer); cdecl;
var i1,i2 : integer;
    check : boolean;
begin
      if (finput^.getlinelength > 0) and (finputedit^.getlinelength > 0) then
      begin
           _cursor_watch;
           for i1 := 1 to finput^.getlinelength do
           begin
                case brush of
                     1,2 : check := true; { inside }
                     11,12 : check := false; { outside }
                     else check := false; { always outside }
                end;
                for i2 := 1 to finputedit^.getlinelength do
                begin
                     case brush of
                          1,2 : if finput^.getallmaterial(i1) = finputedit^.getallmaterial(i2) then
                          begin
                               check := false;
                               break;
                          end;
                          else if finput^.getallmaterial(i1) = finputedit^.getallmaterial(i2) then
                          begin
                               check := true;
                               break;
                          end;
                     end;
                end;
                if check then finput^.markallline(i1);
           end;
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.mask.lines');
           _cursor_arrow;
      end;
end;

{ ****************************** Line bewegen ******************************** }

procedure proc_move_line (p1,macro : gtk_pointer); cdecl;
var z,p : integer;
begin
      if finput^.getlinelength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           z := finput^.linecounter;
           if finput^.getalllinepointlength(z) > 0 then
           begin
                for p := 1 to finput^.getalllinepointlength(z) do
                begin
                     dummy.newpoint(finput^.getline(z,p));
                end;
                dummy.newline (finput^.getallmaterial(z));
                dummy.newobject ('');
           end;
           finput^.markallline (z);
           finput^.erasemarked;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.move.line');
           _cursor_arrow;
      end;
end;

procedure proc_move_line_lengths (p1,macro : gtk_pointer); cdecl;
var o,l,p,io : integer;
    mi,ma : real;
    function getlen (o,l : integer) : real;
    var x : integer;
    begin
         getlen := 0;
         if finput^.getlinepointlength(o,l) > 1 then
         begin
              for x := 1 to finput^.getlinepointlength(o,l)-1 do
              begin
                   getlen := getlen + getlength(finput^.getobject(o,l,x+1)-finput^.getobject(o,l,x));
              end;
         end;
    end;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          mi := _getreal (bool_line_materials_left,macro,1);
          ma := _getreal (bool_line_materials_right,macro,2);
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    io := 0;
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if into (getlen (o,l),mi,ma) then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                              inc (io);
                              finput^.markline (o,l);
                         end;
                    end;
                    if io > 0 then dummy.newobject (finput^.getname(o));
               end;
           end;
           finput^.erasemarked;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.move.line.lengths',getstring(mi)+' '+getstring(ma));
           _cursor_arrow;
      end;
end;

procedure proc_move_line_materials (p1,macro : gtk_pointer); cdecl;
var o,l,p,io : integer;
    mi,ma : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          mi := _getnat (bool_line_materials_left,macro,1);
          ma := _getnat (bool_line_materials_right,macro,2);
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    io := 0;
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if into (finput^.getmaterial (o,l),mi,ma) then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                              inc (io);
                              finput^.markline (o,l);
                         end;
                    end;
                    if io > 0 then dummy.newobject (finput^.getname(o));
               end;
           end;
           finput^.erasemarked;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.move.line.materials',getstring(mi)+' '+getstring(ma));
           _cursor_arrow;
      end;
end;

{ ****************************** Line kopieren ******************************* }

procedure proc_copy_line (p1,macro : gtk_pointer); cdecl;
var z,p : integer;
begin
      if finput^.getlinelength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           if finput^.getalllinepointlength(finput^.linecounter) > 0 then
           begin
                z := finput^.linecounter;
                for p := 1 to finput^.getalllinepointlength(z) do
                begin
                     dummy.newpoint(finput^.getline(z,p));
                end;
                dummy.newline (finput^.getallmaterial(z));
                dummy.newobject ('');
           end;
           finputedit^.append (dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.copy.line');
           _cursor_arrow;
      end;
end;

procedure proc_copy_line_lengths (p1,macro : gtk_pointer); cdecl;
var o,l,p,io : integer;
    mi,ma : real;
    function getlen (o,l : integer) : real;
    var x : integer;
    begin
         getlen := 0;
         if finput^.getlinepointlength(o,l) > 1 then
         begin
              for x := 1 to finput^.getlinepointlength(o,l)-1 do
              begin
                   getlen := getlen + getlength(finput^.getobject(o,l,x+1)-finput^.getobject(o,l,x));
              end;
         end;
    end;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          mi := _getreal (bool_line_materials_left,macro,1);
          ma := _getreal (bool_line_materials_right,macro,2);
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    io := 0;
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if into (getlen (o,l),mi,ma) then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                              inc (io);
                         end;
                    end;
                    if io > 0 then dummy.newobject (finput^.getname(o));
               end;
           end;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.copy.line.lengths',getstring(mi)+' '+getstring(ma));
           _cursor_arrow;
      end;
end;

procedure proc_copy_line_materials (p1,macro : gtk_pointer); cdecl;
var o,l,p,io : integer;
    mi,ma : integer;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          mi := _getnat (bool_line_materials_left,macro,1);
          ma := _getnat (bool_line_materials_right,macro,2);
          dummy.clear;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    io := 0;
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         if into (finput^.getmaterial (o,l),mi,ma) then
                         begin
                              for p := 1 to finput^.getlinepointlength(o,l) do
                              begin
                                   dummy.newpoint(finput^.getobject(o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                              inc (io);
                         end;
                    end;
                    if io > 0 then dummy.newobject (finput^.getname(o));
               end;
           end;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.copy.line.materials',getstring(mi)+' '+getstring(ma));
           _cursor_arrow;
      end;
end;

{ ******************************** Mesh löschen ****************************** }

procedure proc_erase_mesh (p1,macro : gtk_pointer); cdecl;
var o,l : integer;
begin
     if finput^.getobjectlength > 0 then
      begin
           _cursor_watch;
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength (o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          if finput^.getlinepointlength (o,l) > 0 then
                          begin
                               if finput^.ifinsideline (o,l,finputedit^) then finput^.markline (o,l);
                          end;
                     end;
                end;
           end;
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.erase.mesh');
           _cursor_arrow;
      end;
end;

{ ************************* Make object in mesh ****************************** }

procedure proc_make_mesh (p1,macro : gtk_pointer); cdecl;
var l,p : integer;
begin
      _cursor_watch;
      dummy.clear;
      if finput^.getlinelength > 0 then
      begin
           for l := 1 to finput^.getlinelength do
           begin
                if finput^.getalllinepointlength (l) > 0 then
                begin
                     if finput^.ifinsideallline (l,finputedit^) then
                     begin
                          for p := 1 to finput^.getalllinepointlength (l) do
                          begin
                               dummy.newpoint (finput^.getline (l,p));
                          end;
                          dummy.newline (finput^.getallmaterial(l));
                          finput^.markallline (l);
                     end;
                end;
                progress ('Make own mesh',l/finput^.getlinelength);
           end;
           progress;
      end;
      if dummy.getpointlength > 0 then dummy.newobject ('new_mesh');

      finput^.erasemarked;
      finput^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.make.mesh');
      _cursor_arrow;
end;

procedure proc_make2_mesh (p1,macro : gtk_pointer); cdecl;
var l,p : integer;
begin
      _cursor_watch;
      dummy.clear;
      if finput^.getlinelength > 0 then
      begin
           for l := 1 to finput^.getlinelength do
           begin
                if finput^.getalllinepointlength (l) > 0 then
                begin
                     if finput^.ifinsideallsphere (l,finputedit^) then
                     begin
                          for p := 1 to finput^.getalllinepointlength (l) do
                          begin
                               dummy.newpoint (finput^.getline (l,p));
                          end;
                          dummy.newline (finput^.getallmaterial(l));
                          finput^.markallline (l);
                     end;
                end;
                progress ('Make own mesh',l/finput^.getlinelength);
           end;
           progress;
      end;
      if dummy.getpointlength > 0 then dummy.newobject ('new_mesh');

      finput^.erasemarked;
      finput^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.make2.mesh');
      _cursor_arrow;
end;

{ ****************************** Split mesh ********************************** }

procedure proc_split_mesh (p1,macro : gtk_pointer); cdecl;  { Error }
var o,oc,l,p : integer;
    b : tpolynat;
    listh : tpolyhyper;
    listp : tpolynat;
procedure replacewith (i,o : integer);
var lc : integer;
begin
     if i <> o then
        for lc := 1 to b.length do
            if b.get (lc) = i then b.put (lc,o);
end;
procedure markifsame (v,o : integer);
var l,p : integer;
begin
     for l := 1 to finput^.getlinelength do
     begin
          if b.get (l) = 0 then
          begin
               if finput^.getalllinepointlength (l) > 0 then
               begin
                    for p := 1 to finput^.getalllinepointlength (l) do
                    begin
                         if listp.get (v) = listp.get (finput^.getpline (l,p)) then b.put (l,o);
                    end;
               end;
          end
          else
          begin { loops }
               if finput^.getalllinepointlength (l) > 0 then
               begin
                    for p := 1 to finput^.getalllinepointlength (l) do
                    begin
                         if listp.get (v) = listp.get (finput^.getpline (l,p)) then replacewith (b.get(l),o);
                    end;
               end;
          end;
     end;
end;
begin
     b := Default(tpolynat);
     listh := Default(tpolyhyper);
     listp := Default(tpolynat);

     _cursor_watch;
     if finput^.getlinelength > 0 then
     begin
{ search same points }
          finput^.reference (listh,listp); { init of listh and listp }
{ mark same lines }
          o := 0;
          b.init (finput^.getlinelength);
          if finput^.getlinelength > 0 then
          begin
               for l := 1 to finput^.getlinelength do
               begin
                    if b.get (l) = 0 then
                    begin
                         inc (o);
                         b.put (l,o);
                         if finput^.getalllinepointlength (l) > 0 then
                         begin
                              for p := 1 to finput^.getalllinepointlength (l) do
                              begin
                                   markifsame (finput^.getpline(l,p),o);
                              end;
                         end;
                    end;
                    progress ('Search splitable meshs',l/finput^.getlinelength);
               end;
               progress;
          end;
          listh.done;
          listp.done;
{ split mesh }
          if o > 0 then
          for oc := 1 to o do
          begin
               dummy.clear;
               for l := 1 to finput^.getlinelength do
               begin
                    if b.get(l) = oc then
                       if finput^.getalllinepointlength (l) > 0 then
                       begin
                            for p := 1 to finput^.getalllinepointlength (l) do
                            begin
                                 dummy.newpoint (finput^.getline (l,p));
                            end;
                            dummy.newline (finput^.getallmaterial(l));
                            finput^.markallline (l);
                       end;
               end;
               if dummy.getpointlength > 0 then
               begin
                    dummy.newobject ('split_'+getstring(oc));
                    finput^.append(dummy);
               end;
               progress ('Split mesh',oc/o);
          end;
          dummy.clear;
          progress;
          b.done;
     end;
     finput^.erasemarked;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('bool.split.mesh');
     _cursor_arrow;
end;

{ ****************************** Erase duplicates **************************** }

procedure proc_erase_duplicates_between (p1,macro : gtk_pointer); cdecl;
var l,lp,p : integer;
    line : tpolyhyper;
begin
     line := Default(tpolyhyper);

     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          if finput^.getlinelength > 0 then
          begin
               for l := 1 to finput^.getlinelength do
               begin
                    if finput^.getalllinepointlength (l) > 0 then
                    begin
                         lp := finput^.getalllinepointlength (l);
                         if lp > 0 then
                         begin
                              line.init (lp);
                              for p := 1 to lp do line.put (p,finput^.getline (l,p));
                              if finputedit^.searchline (line) then finput^.markallline (l);
                              line.done;
                         end;
                         progress ('Erase duplicates',finput^.getpline(l,lp)/finput^.getpointlength);
                    end;
               end;
            end;
          progress;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          _cursor_arrow;
          tmacro(macro^).writeredo ('bool.erase.duplicates');
     end;
end;

{ ****************************** Object löschen ****************************** }

procedure proc_erase_object (p1,macro : gtk_pointer); cdecl;
begin
      if finput^.getobjectlength > 0 then
      begin
           _cursor_watch;
           finput^.markobject (finput^.objectcounter);
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.erase.object');
           _cursor_arrow;
      end;
end;

procedure proc_erase_object_list (p1,macro : gtk_pointer); cdecl; { only command }
var x,o : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           if tmacro(macro^).parameterlength > 0 then
           begin
                _cursor_watch;
                for x := 1 to tmacro(macro^).parameterlength do
                begin
                     o := getnat(tmacro(macro^).getparameter (x));
                     finput^.markobject (o);
                end;
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.object.list');
                _cursor_arrow;
           end;
      end;
end;

procedure proc_erase_name_list (p1,macro : gtk_pointer); cdecl; { only command }
var x,o : integer;
    n : utf16;
begin
      if finput^.getobjectlength > 0 then
      begin
           if tmacro(macro^).parameterlength > 0 then
           begin
                _cursor_watch;
                for x := 1 to tmacro(macro^).parameterlength do
                begin
                     n := tmacro(macro^).getparameter (x);
                     for o := 1 to finput^.getobjectlength do
                     begin
                          if finput^.getname(o) = n then finput^.markobject (o);
                     end;
                end;
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.name.list');
                _cursor_arrow;
           end;
      end;
end;

procedure proc_erase_object_named (p1,macro : gtk_pointer); cdecl;
var o : integer;
    olds,s,n : utf16;
begin
      if finput^.getobjectlength > 0 then
      begin
           olds := _getedit (bool_object_named,macro,1);
           s := lowercase(olds);
           if s <> '' then
           begin
                _cursor_watch;
                repeat
                     n := split (s,' ');
                     for o := 1 to finput^.getobjectlength do
                     begin
                          if pos (n,lowercase(finput^.getname(o))) > 0 then finput^.markobject (o);
                     end;
                until s = '';
                finput^.erasemarked;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.erase.object.named',olds);
                _cursor_arrow;
           end;
      end;
end;

{ ***************************** Object masking ******************************* }

procedure proc_mask_objects (p1,macro : gtk_pointer); cdecl;
var i1,i2 : integer;
    check : boolean;
begin
      if (finput^.getobjectlength > 0) and (finputedit^.getobjectlength > 0) then
      begin
           _cursor_watch;
           for i1 := 1 to finput^.getobjectlength do
           begin
                case brush of
                     1,2 : check := true; { inside }
                     11,12 : check := false; { outside }
                     else check := false; { always outside }
                end;
                for i2 := 1 to finputedit^.getobjectlength do
                begin
                     case brush of
                          1,2 : if finput^.getname(i1) = finputedit^.getname(i2) then
                          begin
                               check := false;
                               break;
                          end;
                          else if finput^.getname(i1) = finputedit^.getname(i2) then
                          begin
                               check := true;
                               break;
                          end;
                     end;
                end;
                if check then finput^.markobject(i1);
           end;
           finput^.erasemarked;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.mask.objects');
           _cursor_arrow;
      end;
end;

{ ****************************** Object bewegen ****************************** }

procedure proc_move_object (p1,macro : gtk_pointer); cdecl;
var z,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           z := finput^.objectcounter;
           if finput^.getobjectlinelength (z) > 0 then
           begin
                for l := 1 to finput^.getobjectlinelength (z) do
                begin
                     if finput^.getlinepointlength (z,l) > 0 then
                     begin
                          for p := 1 to finput^.getlinepointlength (z,l) do
                          begin
                               dummy.newpoint(finput^.getobject (z,l,p));
                          end;
                          dummy.newline (finput^.getmaterial (z,l));
                     end;
                end;
               dummy.newobject (finput^.getname (z));
           end;
           finput^.markobject (z);
           finput^.erasemarked;
           finputedit^.append(dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.move.object');
           _cursor_arrow;
      end;
end;

procedure proc_move_object_named (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    olds,s,n : utf16;
begin
      if finput^.getobjectlength > 0 then
      begin
           olds := _getedit (bool_object_named,macro,1);
           s := lowercase(olds);
           if s <> '' then
           begin
                _cursor_watch;
                dummy.clear;
                repeat
                     n := split (s,' ');
                     for o := 1 to finput^.getobjectlength do
                     begin
                          if pos (n,lowercase(finput^.getname(o))) > 0 then
                          begin
                               if finput^.getobjectlinelength (o) > 0 then
                               begin
                                    for l := 1 to finput^.getobjectlinelength (o) do
                                    begin
                                         if finput^.getlinepointlength (o,l) > 0 then
                                         begin
                                              for p := 1 to finput^.getlinepointlength (o,l) do
                                              begin
                                                   dummy.newpoint(finput^.getobject (o,l,p));
                                              end;
                                              dummy.newline (finput^.getmaterial (o,l));
                                         end;
                                    end;
                                   dummy.newobject (finput^.getname (o));
                               end;
                               finput^.markobject (o);
                          end;
                     end;
                until s = '';
                finput^.erasemarked;
                finputedit^.append(dummy);
                dummy.clear;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.move.object.named',olds);
                _cursor_arrow;
           end;
      end;
end;

{ ****************************** Object kopieren ***************************** }

procedure proc_copy_object (p1,macro : gtk_pointer); cdecl;
var z,l,p : integer;
begin
      if finput^.getobjectlength > 0 then
      begin
           _cursor_watch;
           dummy.clear;
           z := finput^.objectcounter;
           if finput^.getobjectlinelength (z) > 0 then
           begin
                for l := 1 to finput^.getobjectlinelength (z) do
                begin
                     if finput^.getlinepointlength (z,l) > 0 then
                     begin
                          for p := 1 to finput^.getlinepointlength (z,l) do
                          begin
                               dummy.newpoint(finput^.getobject (z,l,p));
                          end;
                          dummy.newline (finput^.getmaterial (z,l));
                     end;
                end;
                dummy.newobject (finput^.getname (z));
           end;
           finputedit^.append (dummy);
           dummy.clear;
           calculating;
           updating;
           drawing;
           tmacro(macro^).writeredo ('bool.copy.object');
           _cursor_arrow;
      end;
end;

procedure proc_copy_object_named (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    olds,s,n : utf16;
begin
      if finput^.getobjectlength > 0 then
      begin
           olds := _getedit (bool_object_named,macro,1);
           s := lowercase(olds);
           if s <> '' then
           begin
                _cursor_watch;
                dummy.clear;
                repeat
                     n := split (s,' ');
                     for o := 1 to finput^.getobjectlength do
                     begin
                          if pos (n,lowercase(finput^.getname(o))) > 0 then
                          begin
                               if finput^.getobjectlinelength (o) > 0 then
                               begin
                                    for l := 1 to finput^.getobjectlinelength (o) do
                                    begin
                                         if finput^.getlinepointlength (o,l) > 0 then
                                         begin
                                              for p := 1 to finput^.getlinepointlength (o,l) do
                                              begin
                                                   dummy.newpoint(finput^.getobject (o,l,p));
                                              end;
                                              dummy.newline (finput^.getmaterial (o,l));
                                         end;
                                    end;
                                   dummy.newobject (finput^.getname (o));
                               end;
                          end;
                     end;
                until s = '';
                finputedit^.append(dummy);
                dummy.clear;
                calculating;
                updating;
                drawing;
                tmacro(macro^).writeredo ('bool.copy.object.named',olds);
                _cursor_arrow;
           end;
      end;
end;

{ **************************************************************************** }
{ ************************* Loeschen mit Radius ****************************** }
{ **************************************************************************** }

function ifbool3 (a,b : hyper;r,z : real) : boolean;
var bin : byte;
begin
     if random <= z then
     begin
           if a.x = 0.0 then bin := %0 else bin := %1;
           if a.y = 0.0 then bin := (bin shl 1) + %0 else bin := (bin shl 1) + %1;
           if a.z = 0.0 then bin := (bin shl 1) + %0 else bin := (bin shl 1) + %1;
           if a.t = 0.0 then bin := (bin shl 1) + %0 else bin := (bin shl 1) + %1;
           { %xyzt }
           case bin of
               %1100 : { Screen 1 - ignore z and t }
               begin
                     case brush of
                          1 : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)) <= r then ifbool3 := true else ifbool3 := false;
                          2 : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %1010 : { Screen 2 - ignore y and t }
               begin
                     case brush of
                          1 : if sqrt(sqr(b.x-a.x)+sqr(b.z-a.z)) <= r then ifbool3 := true else ifbool3 := false;
                          2 : if (abs(b.x-a.x) < r) and (abs(b.z-a.z) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.x-a.x)+sqr(b.z-a.z)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.x-a.x) < r) and (abs(b.z-a.z) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %1001 : { Screen 4 - ignore y and z }
               begin
                     case brush of
                          1 : if sqrt(sqr(b.x-a.x)+sqr(b.t-a.t)) <= r then ifbool3 := true else ifbool3 := false;
                          2 : if (abs(b.x-a.x) < r) and (abs(b.t-a.t) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.x-a.x)+sqr(b.t-a.t)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.x-a.x) < r) and (abs(b.t-a.t) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %0110 : { Screen 3 - ignore x and t }
               begin
                     case brush of
                          1 : if sqrt(sqr(b.y-a.y)+sqr(b.z-a.z)) <= r then ifbool3 := true else ifbool3 := false;
                          2 : if (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.y-a.y)+sqr(b.z-a.z)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %0011 : { Screen 5 - ignore x and y }
               begin
                     case brush of
                          1 : if sqrt(sqr(b.z-a.z)+sqr(b.t-a.t)) <= r then ifbool3 := true else ifbool3 := false;
                          2 : if (abs(b.z-a.z) < r) and (abs(b.t-a.t) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.z-a.z)+sqr(b.t-a.t)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.z-a.z) < r) and (abs(b.t-a.t) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %1110 : { ??? Additional : true body in 3d - ignore t }
               begin
                     case brush of
                          1  : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)+sqr(b.z-a.z)) <= r then ifbool3 := true else ifbool3 := false;
                          2  : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)+sqr(b.z-a.z)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               %1111 : { ??? Additional : true body in 4d }
               begin
                     case brush of
                          1  : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)+sqr(b.z-a.z)+sqr(b.t-a.t)) <= r then ifbool3 := true else ifbool3 := false;
                          2  : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) and (abs(b.t-a.t) <= r) then ifbool3 := true else ifbool3 := false;
                          11 : if sqrt(sqr(b.x-a.x)+sqr(b.y-a.y)+sqr(b.z-a.z)+sqr(b.t-a.t)) <= r then ifbool3 := false else ifbool3 := true;
                          12 : if (abs(b.x-a.x) < r) and (abs(b.y-a.y) < r) and (abs(b.z-a.z) <= r) and (abs(b.t-a.t) <= r) then ifbool3 := false else ifbool3 := true;
                          else ifbool3 := false;
                     end;
               end;
               else ifbool3 := false;
           end;
     end
     else ifbool3 := false;
end;

{ ******************************* Point ************************************** }
{ +EDIT }

procedure edit_cursor_erase_p (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point : hyper;
    radius,randome : real;
    z : integer;
begin
      _cursor_watch;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getpointlength > 0 then
         for z := 1 to finput^.getpointlength do
         begin
              if ifbool3 (point,finput^.getpoint (z),radius,randome) then finput^.markallpoint (z);
         end;

      finput^.erasemarked;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.erase.cursor.point',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_erase_point (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_erase_p (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_move_p (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point : hyper;
    radius,randome : real;
    z : integer;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getpointlength > 0 then
        for z := 1 to finput^.getpointlength do
        begin
             if ifbool3 (point,finput^.getpoint (z),radius,randome) then
             begin
                  dummy.newpoint (finput^.getpoint (z));
                  dummy.newline (0);
                  finput^.markallpoint (z);
             end;
        end;
      if dummy.getpointlength > 0 then dummy.newobject ('');

      finput^.erasemarked;
      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.move.cursor.point',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_move_point (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_move_p (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_copy_p (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point : hyper;
    radius,randome : real;
    z : integer;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

       if finput^.getpointlength > 0 then
        for z := 1 to finput^.getpointlength do
        begin
             if ifbool3 (point,finput^.getpoint (z),radius,randome) then
             begin
                  dummy.newpoint (finput^.getpoint (z));
                  dummy.newline (0);
             end;
        end;
      if dummy.getpointlength > 0 then dummy.newobject ('');

      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.copy.cursor.point',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_copy_point (p1,macro : gtk_pointer); cdecl;
begin
     edit_cursor_copy_p (nil,M4zero,0,0,macro); { only command }
end;

{ ******************************** Segment *********************************** }

procedure edit_cursor_erase_s (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getobjectlength > 0 then
      begin
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength(o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          p := finput^.getlinepointlength (o,l);
                          if p > 1 then
                          begin
                               u := Hzero;
                               v := Hzero;
                               for bl := 1 to p-1 do { for segments on lines (short and dirty) }
                               begin
                                    v := finput^.getobject (o,l,bl);
                                    u := finput^.getobject (o,l,bl+1);
                                    w := (v+u)/2; { for one point on segments (better intersection between line_rows and circle) }
                                    if ifbool3 (point,v,radius,randome)
                                       then dummy.newline(finput^.getmaterial(o,l))
                                       else dummy.newpoint (finput^.getobject (o,l,bl));
                                    if ifbool3 (point,w,radius,randome) then dummy.newline(finput^.getmaterial(o,l));
                               end;
                               if not ifbool3 (point,u,radius,randome) then dummy.newpoint (finput^.getobject (o,l,p));
                               dummy.newline(finput^.getmaterial(o,l));
                          end
                          else if p = 1 then
                          begin
                               if not ifbool3 (point,finput^.getobject (o,l,1),radius,randome) then
                               begin
                                    dummy.newpoint (finput^.getobject (o,l,1));
                                    dummy.newline (finput^.getmaterial(o,l));
                               end;
                          end;
                     end;
                     dummy.newobject (finput^.getname(o));
                end;
           end;
      end;

      finput^.replace (dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.erase.cursor.segment',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_erase_segment (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_erase_s (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_move_s (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
    dummy2 : tcloud;
begin
     dummy2 := Default (tcloud);

     _cursor_watch;
     dummy2.init;
     dummy.clear;

     if widget <> nil then
     begin
          if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                               else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
          point := getpoint2coord (ex,ey);
          radius := _getreal (bool_radius);
          randome := abs(_getreal (bool_random)/100);
     end
     else
     begin
          point := gethyper (tmacro(macro^).getparameter (1));
          radius := _getreal (bool_radius,macro,2);
          randome := abs(_getreal (bool_random,macro,3)/100);
     end;

     if finput^.getobjectlength > 0 then
     begin
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength (o) do
                    begin
                         p := finput^.getlinepointlength (o,l);
                         if p > 1 then
                         begin
                              u := Hzero;
                              v := Hzero;
                              for bl := 1 to p-1 do { for segments on lines (short and dirty) }
                              begin
                                   v := finput^.getobject (o,l,bl);
                                   u := finput^.getobject (o,l,bl+1);
                                   w := (v+u)/2; { for one point on segments (better intersection between line_rows and circle) }
                                   if ifbool3 (point,v,radius,randome) then
                                   begin
                                        dummy.newline(finput^.getmaterial(o,l));
                                        dummy2.newpoint (finput^.getobject (o,l,bl));
                                   end
                                   else
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,bl));
                                        dummy2.newline(finput^.getmaterial(o,l));
                                   end;
                                   if ifbool3 (point,w,radius,randome) then dummy.newline(finput^.getmaterial(o,l))
                                                               else dummy2.newline(finput^.getmaterial(o,l));
                              end;
                              if ifbool3 (point,u,radius,randome) then dummy2.newpoint (finput^.getobject (o,l,p))
                                                          else dummy.newpoint (finput^.getobject (o,l,p));
                              dummy.newline(finput^.getmaterial(o,l));
                              dummy2.newline(finput^.getmaterial(o,l));
                         end
                         else if p = 1 then
                         begin
                              if ifbool3 (point,finput^.getobject (o,l,1),radius,randome) then
                              begin
                                   dummy2.newpoint (finput^.getobject (o,l,1));
                                   dummy2.newline (finput^.getmaterial(o,l));
                              end
                              else
                              begin
                                   dummy.newpoint (finput^.getobject (o,l,1));
                                   dummy.newline (finput^.getmaterial(o,l));
                              end;
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
                    if dummy2.getpointlength > 0 then
                    begin
                         dummy2.newobject (finput^.getname(o));
                         finputedit^.append (dummy2);
                         dummy2.clear;
                    end;
               end;
          end;
     end;

     finput^.replace (dummy);
     dummy.clear;
     dummy2.done;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('bool.move.cursor.segment',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
     _cursor_arrow;
end;

procedure proc_cursor_move_segment (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_move_s (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_copy_s (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getobjectlength > 0 then
      begin
           for o := 1 to finput^.getobjectlength do
           begin
                if finput^.getobjectlinelength(o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          p := finput^.getlinepointlength (o,l);
                          if p > 1 then
                          begin
                               u := Hzero;
                               v := Hzero;
                               for bl := 1 to p-1 do { for segments on lines (short and dirty) }
                               begin
                                    v := finput^.getobject (o,l,bl);
                                    u := finput^.getobject (o,l,bl+1);
                                    w := (v+u)/2; { for one point on segments (better intersection between line_rows and circle) }
                                    if ifbool3 (point,v,radius,randome) then dummy.newpoint (finput^.getobject (o,l,bl))
                                                                else dummy.newline(finput^.getmaterial(o,l));
                                    if not ifbool3 (point,w,radius,randome) then dummy.newline(finput^.getmaterial(o,l));
                               end;
                               if ifbool3 (point,u,radius,randome) then dummy.newpoint (finput^.getobject (o,l,p));
                               dummy.newline(finput^.getmaterial(o,l));
                          end
                          else if p = 1 then
                          begin
                               if ifbool3 (point,finput^.getobject (o,l,1),radius,randome) then
                               begin
                                    dummy.newpoint (finput^.getobject (o,l,1));
                                    dummy.newline (finput^.getmaterial(o,l));
                               end;
                          end;
                     end;
                     if dummy.getpointlength > 0 then
                     begin
                          dummy.newobject (finput^.getname(o));
                          finputedit^.append (dummy);
                          dummy.clear;
                     end;
                end;
           end;
      end;

      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.copy.cursor.segment',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_copy_segment (p1,macro : gtk_pointer); cdecl; { only comannd }
begin
     edit_cursor_copy_s (nil,M4zero,0,0,macro);
end;

{  *********************************** Line ********************************** }

procedure edit_cursor_erase_l (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    z,l,bl : integer;
    found : boolean;
begin
      _cursor_watch;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getlinelength > 0 then
      begin
           for z := 1 to finput^.getlinelength do
           begin
                l := finput^.getalllinepointlength (z);
                if l > 0 then
                begin
                     found := false;
                     for bl := 1 to l do
                     begin
                          v := finput^.getline (z,bl);
                          if ifbool3 (point,v,radius,randome) then found := true;
                     end;
                     if l > 1 then
                     begin
                          for bl := 1 to l-1 do { for links on lines (short and dirty) }
                          begin
                               v := finput^.getline (z,bl);
                               u := finput^.getline (z,bl+1);
                               w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                               if ifbool3 (point,w,radius,randome) then found := true;
                               v := (v+w)/2;
                               if ifbool3 (point,v,radius,randome) then found := true;
                               u := (w+u)/2;
                               if ifbool3 (point,u,radius,randome) then found := true;
                          end;
                     end;
                     if found then finput^.markallline (z);
                end;
           end;
      end;

      finput^.erasemarked;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.erase.cursor.line',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_erase_line (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_erase_l (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_move_l (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    z,l,bl : integer;
    found : boolean;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getlinelength > 0 then
      begin
           for z := 1 to finput^.getlinelength do
           begin
                l := finput^.getalllinepointlength (z);
                if l > 0 then
                begin
                     found := false;
                     for bl := 1 to l do
                     begin
                          v := finput^.getline (z,bl);
                          if ifbool3 (point,v,radius,randome) then found := true;
                     end;
                     if l > 1 then
                     begin
                          for bl := 1 to l-1 do { for links on lines (short and dirty) }
                          begin
                               v := finput^.getline (z,bl);
                               u := finput^.getline (z,bl+1);
                               w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                               if ifbool3 (point,w,radius,randome) then found := true;
                               v := (v+w)/2;
                               if ifbool3 (point,v,radius,randome) then found := true;
                               u := (w+u)/2;
                               if ifbool3 (point,u,radius,randome) then found := true;
                          end;
                     end;
                     if found then
                     begin
                          for bl := 1 to l do
                          begin
                               dummy.newpoint (finput^.getline (z,bl));
                          end;
                          dummy.newline (finput^.getallmaterial(z));
                          finput^.markallline (z);
                     end;
                end;
           end;
      end;
      if dummy.getpointlength > 0 then dummy.newobject ('');

      finput^.erasemarked;
      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.move.cursor.line',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_move_line (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_move_l (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_copy_l (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    z,l,bl : integer;
    found : boolean;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getlinelength > 0 then
      begin
           for z := 1 to finput^.getlinelength do
           begin
                l := finput^.getalllinepointlength (z);
                if l > 0 then
                begin
                     found := false;
                     for bl := 1 to l do
                     begin
                          v := finput^.getline (z,bl);
                          if ifbool3 (point,v,radius,randome) then found := true;
                     end;
                     if l > 1 then
                     begin
                          for bl := 1 to l-1 do { for links on lines (short and dirty) }
                          begin
                               v := finput^.getline (z,bl);
                               u := finput^.getline (z,bl+1);
                               w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                               if ifbool3 (point,w,radius,randome) then found := true;
                               v := (v+w)/2;
                               if ifbool3 (point,v,radius,randome) then found := true;
                               u := (w+u)/2;
                               if ifbool3 (point,u,radius,randome) then found := true;
                          end;
                     end;
                     if found then
                     begin
                          for bl := 1 to l do
                          begin
                               dummy.newpoint (finput^.getline (z,bl));
                          end;
                          dummy.newline (finput^.getallmaterial(z));
                     end;
                end;
           end;
      end;
      if dummy.getpointlength > 0 then dummy.newobject ('');

      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.copy.cursor.line',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_copy_line (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_copy_l (nil,M4zero,0,0,macro);
end;

{ *********************************** Object ********************************* }

procedure edit_cursor_erase_o (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
    found : boolean;
begin
      _cursor_watch;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getobjectlength > 0 then
      begin
           for o := 1 to finput^.getobjectlength do
           begin
                found := false;
                if finput^.getobjectlinelength(o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          p := finput^.getlinepointlength (o,l);
                          if p > 0 then
                          begin
                               for bl := 1 to p do
                               begin
                                    v := finput^.getobject (o,l,bl);
                                    if ifbool3 (point,v,radius,randome) then found := true;
                               end;
                               if p > 1 then
                               begin
                                    for bl := 1 to p-1 do { for vectors on links (short and dirty) }
                                    begin
                                         v := finput^.getobject (o,l,bl);
                                         u := finput^.getobject (o,l,bl+1);
                                         w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                                         if ifbool3 (point,w,radius,randome) then found := true;
                                         v := (v+w)/2;
                                         if ifbool3 (point,v,radius,randome) then found := true;
                                         u := (w+u)/2;
                                         if ifbool3 (point,u,radius,randome) then found := true;
                                    end;
                               end;
                          end;
                     end;
                end;
                if found then finput^.markobject (o);
           end;
      end;

      finput^.erasemarked;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.erase.cursor.object',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_erase_object (p1,macro : gtk_pointer); cdecl; { only command }
begin
     edit_cursor_erase_o (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_move_o (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
    found : boolean;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getobjectlength > 0 then
      begin
           for o := 1 to finput^.getobjectlength do
           begin
                found := false;
                if finput^.getobjectlinelength(o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          p := finput^.getlinepointlength (o,l);
                          if p > 0 then
                          begin
                               for bl := 1 to p do
                               begin
                                    v := finput^.getobject (o,l,bl);
                                    if ifbool3 (point,v,radius,randome) then found := true;
                               end;
                               if p > 1 then
                               begin
                                    for bl := 1 to p-1 do { for vectors on links (short and dirty) }
                                    begin
                                         v := finput^.getobject (o,l,bl);
                                         u := finput^.getobject (o,l,bl+1);
                                         w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                                         if ifbool3 (point,w,radius,randome) then found := true;
                                         v := (v+w)/2;
                                         if ifbool3 (point,v,radius,randome) then found := true;
                                         u := (w+u)/2;
                                         if ifbool3 (point,u,radius,randome) then found := true;
                                    end;
                               end;
                          end;
                     end;
                end;
                if found then
                begin
                     if finput^.getobjectlinelength(o) > 0 then
                     begin
                          for l := 1 to finput^.getobjectlinelength (o) do
                          begin
                               p := finput^.getlinepointlength (o,l);
                               if p > 0 then
                               begin
                                    for bl := 1 to p do
                                    begin
                                         dummy.newpoint (finput^.getobject (o,l,bl));
                                    end;
                                    dummy.newline (finput^.getmaterial(o,l));
                               end;
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                     finput^.markobject (o);
                end;
           end;
      end;

      finput^.erasemarked;
      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.move.cursor.object',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_move_object (p1,macro : gtk_pointer); cdecl; { onyl command }
begin
     edit_cursor_move_o (nil,M4zero,0,0,macro);
end;

procedure edit_cursor_copy_o (widget : gtk_widget;m : matrix4;ex,ey : integer;macro : pointer);
var point,u,v,w : hyper;
    radius,randome : real;
    o,l,p,bl : integer;
    found : boolean;
begin
      _cursor_watch;
      dummy.clear;

      if widget <> nil then
      begin
           if _getcheckbutton (toggle_realsize) then initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,true)
                                                else initcoord (gcn(widget^.allocation.width,widget^.allocation.height),m,false);
           point := getpoint2coord (ex,ey);
           radius := _getreal (bool_radius);
           randome := abs(_getreal (bool_random)/100);
      end
      else
      begin
           point := gethyper (tmacro(macro^).getparameter (1));
           radius := _getreal (bool_radius,macro,2);
           randome := abs(_getreal (bool_random,macro,3)/100);
      end;

      if finput^.getobjectlength > 0 then
      begin
           for o := 1 to finput^.getobjectlength do
           begin
                found := false;
                if finput^.getobjectlinelength(o) > 0 then
                begin
                     for l := 1 to finput^.getobjectlinelength (o) do
                     begin
                          p := finput^.getlinepointlength (o,l);
                          if p > 0 then
                          begin
                              for bl := 1 to p do
                               begin
                                    v := finput^.getobject (o,l,bl);
                                    if ifbool3 (point,v,radius,randome) then found := true;
                               end;
                               if p > 1 then
                               begin
                                    for bl := 1 to p-1 do { for vectors on links (short and dirty) }
                                    begin
                                         v := finput^.getobject (o,l,bl);
                                         u := finput^.getobject (o,l,bl+1);
                                         w := (v+u)/2; { for three points on link (better: intersection between line_rows and circle) }
                                         if ifbool3 (point,w,radius,randome) then found := true;
                                         v := (v+w)/2;
                                         if ifbool3 (point,v,radius,randome) then found := true;
                                         u := (w+u)/2;
                                         if ifbool3 (point,u,radius,randome) then found := true;
                                    end;
                               end;
                          end;
                     end;
                end;
                if found then
                begin
                     if finput^.getobjectlinelength(o) > 0 then
                     begin
                          for l := 1 to finput^.getobjectlinelength (o) do
                          begin
                               p := finput^.getlinepointlength (o,l);
                               if p > 0 then
                               begin
                                    for bl := 1 to p do
                                    begin
                                         dummy.newpoint (finput^.getobject (o,l,bl));
                                    end;
                                    dummy.newline (finput^.getmaterial(o,l));
                               end;
                          end;
                          dummy.newobject (finput^.getname(o));
                     end;
                end;
           end;
      end;

      finputedit^.append(dummy);
      dummy.clear;
      calculating;
      updating;
      drawing;
      tmacro(macro^).writeredo ('bool.copy.cursor.object',getstring(point)+' '+getstring(radius)+' '+getstring(randome*100));
      _cursor_arrow;
end;

procedure proc_cursor_copy_object (p1,macro : gtk_pointer); cdecl; { onyl command }
begin
     edit_cursor_copy_o (nil,M4zero,0,0,macro);
end;

{ **************************************************************************** }
{ ****************************** Raster ************************************** }
{ **************************************************************************** }

function ifbool (v,min,max : hyper;z : real) : boolean;
var center,r,u : hyper;
begin
     if random <= z then
     begin
          case brush of
               1 :
               begin
                    center := (min+max)/2;
                    r := (max-min)/2;
                    u := v - center;
                    if sum(sqr(u)/sqr(r)) <= 1 then ifbool := true else ifbool := false;
               end;
               2 : if into (v,min,max) then ifbool := true else ifbool := false;
               11 :
               begin
                    center := (min+max)/2;
                    r := (max-min)/2;
                    u := v - center;
                    if sum(sqr(u)/sqr(r)) <= 1 then ifbool := false else ifbool := true;
               end;
               12 : if into (v,min,max) then ifbool := false else ifbool := true;
               else ifbool := false;
          end;
     end
     else ifbool := false;
end;

{ **************************************************************************** }

procedure proc_bool_points_set_dimension_min (p1,macro : gtk_pointer); cdecl;
var min : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          tmacro(macro^).writereundo ('bool.points.set.min','auto','bool.points.set.min',_getedit (bool_points_dimension_min));
          _setedit (bool_points_dimension_min,getstring(floor(1000*min)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_points_dimension_min,macro,1);
          tmacro(macro^).writereundo ('bool.points.set.min',getstring(min),'bool.points.set.min',_getedit (bool_points_dimension_min));
          _setedit (bool_points_dimension_min,getstring(floor(1000*min)/1000,3));
     end;
end;

procedure proc_bool_points_set_dimension_max (p1,macro : gtk_pointer); cdecl;
var max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.points.set.max','auto','bool.points.set.max',_getedit (bool_points_dimension_max));
          _setedit (bool_points_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          max := _gethyper (bool_points_dimension_max,macro,1);
          tmacro(macro^).writereundo ('bool.points.set.max',getstring(max),'bool.points.set.max',_getedit (bool_points_dimension_max));
          _setedit (bool_points_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_bool_points_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
var min,max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          _setedit (bool_points_dimension_min,getstring(floor(1000*min)/1000,3));
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.points.set.minmax','auto','bool.points.set.minmax',_getedit (bool_points_dimension_min)+' '+_getedit (bool_points_dimension_max));
          _setedit (bool_points_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_points_dimension_min,macro,1);
          max := _gethyper (bool_points_dimension_max,macro,2);
          tmacro(macro^).writereundo ('bool.points.set.minmax',getstring(min)+' '+getstring(max),'bool.points.set.minmax',_getedit (bool_points_dimension_min)+' '+_getedit (bool_points_dimension_max));
          _setedit (bool_points_dimension_min,getstring(floor(1000*min)/1000,3));
          _setedit (bool_points_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_erase_minmax_points (p1,macro : gtk_pointer); cdecl;
var z : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          min := _gethyper (bool_points_dimension_min);
          max := _gethyper (bool_points_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          for z := 1 to finput^.getpointlength do
          begin
               v := finput^.getpoint (z);
               if ifbool (v,min,max,randome) then finput^.markallpoint (z);
          end;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.points.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.points.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.erase.minmax.points',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_move_minmax_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_points_dimension_min);
          max := _gethyper (bool_points_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
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
                                   if ifbool (v,min,max,randome) then
                                   begin
                                        dummy.newpoint(v);
                                        finput^.markpoint (o,l,p);
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finput^.erasemarked;
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.points.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.points.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.move.minmax.points',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_copy_minmax_points (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getpointlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_points_dimension_min);
          max := _gethyper (bool_points_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
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
                                   if ifbool (v,min,max,randome) then
                                   begin
                                        dummy.newpoint(v);
                                        dummy.newline(0);
                                   end;
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.points.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.points.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.copy.minmax.points',getstring(randome*100));
          _cursor_arrow;
     end;
end;

{ ***************************** Raster Segments ****************************** }

procedure proc_bool_segments_set_dimension_min (p1,macro : gtk_pointer); cdecl;
var min : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          tmacro(macro^).writereundo ('bool.segments.set.min','auto','bool.segments.set.min',_getedit (bool_segments_dimension_min));
          _setedit (bool_segments_dimension_min,getstring(floor(1000*min)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_segments_dimension_min,macro,1);
          tmacro(macro^).writereundo ('bool.segments.set.min',getstring(min),'bool.segments.set.min',_getedit (bool_segments_dimension_min));
          _setedit (bool_segments_dimension_min,getstring(floor(1000*min)/1000,3));
     end;
end;

procedure proc_bool_segments_set_dimension_max (p1,macro : gtk_pointer); cdecl;
var max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.segments.set.max','auto','bool.segments.set.max',_getedit (bool_segments_dimension_max));
          _setedit (bool_segments_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          max := _gethyper (bool_segments_dimension_max,macro,1);
          tmacro(macro^).writereundo ('bool.segments.set.max',getstring(max),'bool.segments.set.max',_getedit (bool_segments_dimension_max));
          _setedit (bool_segments_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_bool_segments_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
var min,max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          _setedit (bool_segments_dimension_min,getstring(floor(1000*min)/1000,3));
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.segments.set.minmax','auto','bool.segments.set.minmax',_getedit (bool_segments_dimension_min)+' '+_getedit (bool_segments_dimension_max));
          _setedit (bool_segments_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_segments_dimension_min,macro,1);
          max := _gethyper (bool_segments_dimension_max,macro,2);
          tmacro(macro^).writereundo ('bool.segments.set.minmax',getstring(min)+' '+getstring(max),'bool.segments.set.minmax',_getedit (bool_segments_dimension_min)+' '+_getedit (bool_segments_dimension_max));
          _setedit (bool_segments_dimension_min,getstring(floor(1000*min)/1000,3));
          _setedit (bool_segments_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_erase_minmax_segments (p1,macro : gtk_pointer); cdecl;
var o,l,p,len,old_p,old_l : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_segments_dimension_min);
          max := _gethyper (bool_segments_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          old_p := 0;
          old_l := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then { found }
                                   begin
                                        if old_p > 0 then
                                        begin
                                             dummy.newline (finput^.getmaterial(o,l));
                                             inc(old_l);
                                             old_p := 0;
                                        end;
                                   end
                                   else
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                        inc (old_p);
                                   end;
                              end;
                         end;
                         if old_p > 0 then
                         begin
                              dummy.newline (finput^.getmaterial(o,l));
                              inc(old_l);
                              old_p := 0;
                         end;
                    end;
               end;
               if old_l > 0 then
               begin
                    dummy.newobject(finput^.getname(o));
                    old_p := 0;
                    old_l := 0;
               end;
          end;
          finput^.replace (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.segments.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.segments.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.erase.minmax.segments',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_move_minmax_segments (p1,macro : gtk_pointer); cdecl;
var o,l,p,len,old_p,old_l,new_p,new_l : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_segments_dimension_min);
          max := _gethyper (bool_segments_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          old_p := 0;
          old_l := 0;
          new_p := 0;
          new_l := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then { found }
                                   begin
                                        if old_p > 0 then
                                        begin
                                             dummy.newline (finput^.getmaterial(o,l));
                                             inc (old_l);
                                             old_p := 0;
                                        end;
                                        finputedit^.newpoint (finput^.getobject (o,l,p));
                                        inc (new_p);
                                   end
                                   else
                                   begin
                                        if new_p > 0 then
                                        begin
                                             finputedit^.newline (finput^.getmaterial(o,l));
                                             inc (new_l);
                                             new_p := 0;
                                        end;
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                        inc (old_p);
                                   end;
                              end;
                         end;
                         if old_p > 0 then
                         begin
                              dummy.newline (finput^.getmaterial(o,l));
                              inc(old_l);
                              old_p := 0;
                         end;
                         if new_p > 0 then
                         begin
                              finputedit^.newline(finput^.getmaterial(o,l));
                              inc(new_l);
                              new_p := 0;
                         end;
                    end;
               end;
               if old_l > 0 then
               begin
                    dummy.newobject(finput^.getname(o));
                    old_p := 0;
                    old_l := 0;
               end;
               if new_l > 0 then
               begin
                    finputedit^.newobject(finput^.getname(o));
                    new_p := 0;
                    new_l := 0;
               end;
          end;
          finput^.replace (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.segments.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.segments.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.move.minmax.segments',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_copy_minmax_segments (p1,macro : gtk_pointer); cdecl;
var o,l,p,len,new_p,new_l : integer;
    min,max : hyper;
    v : hyper;
    randome : real;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          min := _gethyper (bool_segments_dimension_min);
          max := _gethyper (bool_segments_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          new_p := 0;
          new_l := 0;
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then { found }
                                   begin
                                        finputedit^.newpoint (finput^.getobject (o,l,p));
                                        inc (new_p);
                                   end
                                   else
                                   begin
                                        if new_p > 0 then
                                        begin
                                             finputedit^.newline (finput^.getmaterial(o,l));
                                             inc(new_l);
                                             new_p := 0;
                                        end;
                                   end;
                              end;
                         end;
                         if new_p > 0 then
                         begin
                              finputedit^.newline(finput^.getmaterial(o,l));
                              inc(new_l);
                              new_p := 0;
                         end;
                    end;
               end;
               if new_l > 0 then
               begin
                    finputedit^.newobject(finput^.getname(o));
                    new_p := 0;
                    new_l := 0;
               end;
          end;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.segments.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.segments.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.copy.minmax.segments',getstring(randome*100));
          _cursor_arrow;
     end;
end;

{ ****************************** Raster Lines ******************************** }

procedure proc_bool_lines_set_dimension_min (p1,macro : gtk_pointer); cdecl;
var min : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          tmacro(macro^).writereundo ('bool.lines.set.min','auto','bool.lines.set.min',_getedit (bool_lines_dimension_min));
          _setedit (bool_lines_dimension_min,getstring(floor(1000*min)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_lines_dimension_min,macro,1);
          tmacro(macro^).writereundo ('bool.lines.set.min',getstring(min),'bool.lines.set.min',_getedit (bool_lines_dimension_min));
          _setedit (bool_lines_dimension_min,getstring(floor(1000*min)/1000,3));
     end;
end;

procedure proc_bool_lines_set_dimension_max (p1,macro : gtk_pointer); cdecl;
var max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.lines.set.max','auto','bool.lines.set.max',_getedit (bool_lines_dimension_max));
          _setedit (bool_lines_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          max := _gethyper (bool_lines_dimension_max,macro,1);
          tmacro(macro^).writereundo ('bool.lines.set.max',getstring(max),'bool.lines.set.max',_getedit (bool_lines_dimension_max));
          _setedit (bool_lines_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_bool_lines_set_dimension_minmax (p1,macro : gtk_pointer); cdecl;
var min,max : hyper;
begin
     if (tmacro(macro^).parameterlength <= 0) or (tmacro(macro^).getparameter(1) = 'auto') then
     begin
          case input of
               1 : begin min := red.min; end;
               2 : begin min := green.min; end;
               3 : begin min := blue.min; end;
               4 : begin min := yellow.min; end;
               5 : begin min := cyan.min; end;
               else begin min := purple.min; end;
          end;
          if min = Hmax then min := Hzero;
          _setedit (bool_lines_dimension_min,getstring(floor(1000*min)/1000,3));
          case input of
               1 : begin max := red.max; end;
               2 : begin max := green.max; end;
               3 : begin max := blue.max; end;
               4 : begin max := yellow.max; end;
               5 : begin max := cyan.max; end;
               else begin max := purple.max; end;
          end;
          if max = Hmin then max := Hzero;
          tmacro(macro^).writereundo ('bool.lines.set.minmax','auto','bool.lines.set.minmax',_getedit (bool_lines_dimension_min)+' '+_getedit (bool_lines_dimension_max));
          _setedit (bool_lines_dimension_max,getstring(ceil(1000*max)/1000,3));
     end
     else { only command }
     begin
          min := _gethyper (bool_lines_dimension_min,macro,1);
          max := _gethyper (bool_lines_dimension_max,macro,2);
          tmacro(macro^).writereundo ('bool.lines.set.minmax',getstring(min)+' '+getstring(max),'bool.lines.set.minmax',_getedit (bool_lines_dimension_min)+' '+_getedit (bool_lines_dimension_max));
          _setedit (bool_lines_dimension_min,getstring(floor(1000*min)/1000,3));
          _setedit (bool_lines_dimension_max,getstring(ceil(1000*max)/1000,3));
     end;
end;

procedure proc_erase_minmax_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,len : integer;
    min,max : hyper;
    v,v1 : hyper;
    randome : real;
    found : boolean;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_lines_dimension_min);
          max := _gethyper (bool_lines_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              found := false;
                              v1 := finput^.getobject(o,l,1);
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then found := true;
                                   if ifbool ((v+v1)/2,min,max,randome) then found := true;
                                   v1 := v;
                              end;
                              if found then finput^.markline(o,l);
                         end;
                    end;
               end;
          end;
          finput^.erasemarked;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.lines.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.lines.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.erase.minmax.lines',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_move_minmax_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,len : integer;
    min,max : hyper;
    v,v1 : hyper;
    randome : real;
    found : boolean;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_lines_dimension_min);
          max := _gethyper (bool_lines_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              found := false;
                              v1 := finput^.getobject(o,l,1);
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then found := true;
                                   if ifbool ((v+v1)/2,min,max,randome) then found := true;
                                   v1 := v;
                              end;
                              if found then
                              begin
                                   for p := 1 to len do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial(o,l));
                                   finput^.markline(o,l);
                              end;
                         end;
                    end;
               end;
               dummy.newobject(finput^.getname(o));
          end;
          finput^.erasemarked;
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.lines.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.lines.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.move.minmax.lines',getstring(randome*100));
          _cursor_arrow;
     end;
end;

procedure proc_copy_minmax_lines (p1,macro : gtk_pointer); cdecl;
var o,l,p,len : integer;
    min,max : hyper;
    v,v1 : hyper;
    randome : real;
    found : boolean;
begin
     if finput^.getobjectlength > 0 then
     begin
          _cursor_watch;
          dummy.clear;
          min := _gethyper (bool_lines_dimension_min);
          max := _gethyper (bool_lines_dimension_max);
          randome := abs(_getreal (bool_random,macro,1)/100);
          for o := 1 to finput^.getobjectlength do
          begin
               if finput^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to finput^.getobjectlinelength(o) do
                    begin
                         len := finput^.getlinepointlength(o,l);
                         if len > 0 then
                         begin
                              found := false;
                              v1 := finput^.getobject(o,l,1);
                              for p := 1 to len do
                              begin
                                   v := finput^.getobject(o,l,p);
                                   if ifbool (v,min,max,randome) then found := true;
                                   if ifbool ((v+v1)/2,min,max,randome) then found := true;
                                   v1 := v;
                              end;
                              if found then
                              begin
                                   for p := 1 to len do
                                   begin
                                        dummy.newpoint (finput^.getobject (o,l,p));
                                   end;
                                   dummy.newline (finput^.getmaterial(o,l));
                              end;
                         end;
                    end;
               end;
               dummy.newobject(finput^.getname(o));
          end;
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.lines.set.min',getstring (min));
          tmacro(macro^).writeredo ('bool.lines.set.max',getstring (max));
          tmacro(macro^).writeredo ('bool.copy.minmax.lines',getstring(randome*100));
          _cursor_arrow;
     end;
end;

{ ***************************** Layer löschen ******************************** }

procedure proc_erase_layer (p1,macro : gtk_pointer); cdecl;
begin
     _cursor_watch;
     finput^.clear;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('bool.erase.layer');
     _cursor_arrow;
end;

{ ***************************** Layer bewegen ******************************** }

procedure proc_move_layer (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          dummy.clear;
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
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          if (finputedit^.name = '') then finputedit^.name := finput^.name; { always store name }
          finput^.clear;
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.move.layer');
     end;
     _cursor_arrow;
end;

{ ***************************** Layer kopieren ******************************* }

procedure proc_copy_layer (p1,macro : gtk_pointer); cdecl;
var o,l,p : integer;
begin
     _cursor_watch;
     if finput^.getobjectlength > 0 then
     begin
          dummy.clear;
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
                                   dummy.newpoint (finput^.getobject (o,l,p));
                              end;
                              dummy.newline (finput^.getmaterial(o,l));
                         end;
                    end;
                    dummy.newobject (finput^.getname(o));
               end;
          end;
          if (finputedit^.name = '') and (finputedit^.getpointlength = 0) then finputedit^.name := finput^.name; { store name only if empty }
          finputedit^.append (dummy);
          dummy.clear;
          calculating;
          updating;
          drawing;
          tmacro(macro^).writeredo ('bool.copy.layer');
     end;
     _cursor_arrow;
end;

{ ***************************** Layer tauschen ******************************* }

procedure proc_swap_layer (p1,macro : gtk_pointer); cdecl;
var mydummy : tcloud;
begin
     mydummy := Default(tcloud);

     _cursor_watch;

     mydummy := finput^;
     finput^ := finputedit^;
     finputedit^ := mydummy;
     calculating;
     updating;
     drawing;
     tmacro(macro^).writeredo ('bool.swap.layer');

     _cursor_arrow;
end;


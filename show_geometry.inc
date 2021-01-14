{ **************************************************************************** }
{ ******************************* Geometry *********************************** }
{ **************************************************************************** }

function getstat (const layer,name : utf16;var my : tpolyreal) : utf16;
var n : integer;
    q : vector;
    m : hyper;
    jbs,jbk,jb : real;
    {vs,ek,vk,jbu : real;}
begin
     getstat := '';
     if my.length > 0 then
     begin
          getstat := getstat + layer + ' '+name+' ->' + '   ';
          getstat := getstat + 'N: '+getstring(my.length)+#10;

          m := my.stat;
          getstat := getstat + 'Mean: '+getstring(m.x,10,5)+'  ';
          getstat := getstat + 'Var: '+getstring(m.y,10,5)+'  ';
          getstat := getstat + 'SD: '+getstring(m.z,10,5)+#10;

          getstat := getstat + 'Sum: '+getstring(my.sum,10,5)+'  ';
          getstat := getstat + 'Residues: '+getstring(m.t,10,5)+#10;

          q := my.quantile;
          getstat := getstat + 'Min: '+getstring(my.min,10,5)+'  ';
          getstat := getstat + 'Q.25: '+getstring(q.x,10,5)+'  ';
          getstat := getstat + 'Median: '+getstring(q.y,10,5)+'  ';
          getstat := getstat + 'Q.75: '+getstring(q.z,10,5)+'  ';
          getstat := getstat + 'Max: '+getstring(my.max,10,5)+#10;

{ Jarque-Bera test - normal distribution }
          if m.y {variance} <> 0 then
          begin
               n := my.length;
               jbs := my.variance3/power(m.y,3/2);
               jbk := (my.variance4/sqr(m.y));
               jb := (n/6)*(sqr(jbs)+sqr(jbk-3)/4);
{              vs := (6*(n-2)) / ((n+1)+(n+3));
               ek := (3*(n-1)) / (n+1);
               vk := (24*n*(n-2)*(n-3)) / (sqr(n+1)*(n+3)*(n+5));
               jbu := (sqr(jbs)/vs)+(sqr(jbk-ek)/vk); }
               getstat := getstat + 'Skewness: '+getstring(jbs,10,5)+' | (Kurtosis-3): '+getstring(jbk-3,10,5)+#10;
               getstat := getstat + 'Jarque-Bera-Test: '+getstring(jb,10,5)+' | JB < X²(1-α,2) | α: 0.10->4.6 0.05->5.99 0.02->7.8 0.01->9.21'+#10;
{ too big      getstat := getstat + 'Jarque-Bera-Urzúa-Test: '+getstring(jbu,10,5)+' | JBU < X²(1-α,2) | α: 0.05->5.99 0.01->9.21'+#10+'--  --  --'+#10; }
          end
          else getstat := getstat + '--  --  --'+#10;
          getstat := getstat + #10;
     end;
end;


procedure _make_visible (const name,objects : utf16);
var s : utf16;
begin
{ Report }
     statname := name;
     statobjects := objects;
     stattype := 1;
     s := '';
     if state[1] then s := s + getstat ('Red',name,stat[1]);
     _update;
     if state[2] then s := s + getstat ('Green',name,stat[2]);
     _update;
     if state[3] then s := s + getstat ('Blue',name,stat[3]);
     _update;
     if state[4] then s := s + getstat ('Yellow',name,stat[4]);
     _update;
     if state[5] then s := s + getstat ('Cyan',name,stat[5]);
     _update;
     if state[6] then s := s + getstat ('Purple',name,stat[6]);
     _update;
     if s = '' then _settext (text_report,'No data!')
               else _settext (text_report,s);
     _update;
{ Graph }
     if _getcheckbutton (togglegrouped) then
     begin
          screen_histo.done;
          screen_histo.init (area_shot^.allocation.width,area_shot^.allocation.height);
          screen_histo.left ('grouped '+objects);
          if _getcheckbutton (togglelog) then screen_histo.bottom ('log '+name+' [units]')
                                         else screen_histo.bottom (name+' [units]');
          screen_histo.setstyle (2); { steps }
          if _getcheckbutton (togglelog) then screen_histo.logscale := 10;
          if _getnat (geometry_groups) > 1 then
          screen_histo.grouped (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred,_getnat(geometry_groups));
          screen_histo.render;
     end
     else
     begin
          screen_histo.done;
          screen_histo.init (area_shot^.allocation.width,area_shot^.allocation.height);
          if _getcheckbutton (togglelog) then screen_histo.left ('log '+name+' [units]')
                                         else screen_histo.left (name+' [units]');
          screen_histo.bottom ('sorted '+objects);
          screen_histo.setstyle (5); { vvline }
          if _getcheckbutton (togglelog) then screen_histo.logscale := 10;
          screen_histo.histogram (stat[6],stat[5],stat[4],stat[3],stat[2],stat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
          screen_histo.render;
     end;
     _setpage (subnote_show,2);
     _update;
end;

procedure proc_show_pzerodistance (p1,macro : gtk_pointer); cdecl; { zero distance }
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
    d : real;
begin
     if f^.getpointlength > 1 then
     begin
          my.newlength (f^.getpointlength);
          my.clear;
          for z := 1 to f^.getpointlength do
          begin
               d := getlength(f^.getpoint (z));
               my.put (z,d);
               progress ('Calculate distance (points-zero)',z/f^.getpointlength);
          end;
          progress;
          my.sort;
     end
     else my.newlength (0);
end;
begin
     _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('point zero distances','points');

     _cursor_arrow;
end;

procedure proc_show_pmindistance (p1,macro : gtk_pointer); cdecl; { min distance }
procedure run (f : pcloud;var my : tpolyreal);
var z,c,l : integer;
    d,n : real;
begin
     if f^.getpointlength > 1 then
     begin
          my.newlength (f^.getpointlength);
          my.clear;
          l := 1;
          for z := 1 to f^.getpointlength do
          begin
               if my.get (z) = 0 then { too avoid double calculations }
               begin
                    d := infinity;
                    for c := 1 to f^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((f^.getpoint (z)-f^.getpoint(c)));
                              if d > n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my.put (z,d);
                    my.put (l,d); { double calculation }
               end;
               progress ('Calculate neighbors (points)',z/f^.getpointlength);
          end;
          progress;
          my.sort;
     end
     else my.newlength (0);
end;
begin
     _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('point min distances','points');

     _cursor_arrow;
end;

procedure proc_show_pmaxdistance (p1,macro : gtk_pointer); cdecl; { max distance }
procedure run (f : pcloud;var my : tpolyreal);
var z,c,l : integer;
    d,n : real;
begin
     if f^.getpointlength > 1 then
     begin
          my.newlength (f^.getpointlength);
          my.clear;
          l := 1;
          for z := 1 to f^.getpointlength do
          begin
               if my.get (z) = 0 then { too avoid double calculations }
               begin
                    d := 0;
                    for c := 1 to f^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((f^.getpoint (z)-f^.getpoint(c)));
                              if d < n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my.put (z,d);
                    my.put (l,d); { double calculation }
               end;
               progress ('Calculate neighbors (points)',z/f^.getpointlength);
          end;
          progress;
          my.sort;
     end
     else my.newlength (0);
end;
begin
     _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('point max distances','points');

     _cursor_arrow;
end;

{ *********************** Show sub length 3D ********************************* }

procedure proc_show_ltortuosity_3d (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,l,bl : integer;
    rc,rl : real;
    h1,h2 : hyper;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 2 then { lines }
               begin
                    rc := 0;
                    for bl := 1 to l-1 do
                    begin
                         h1 := f^.getline (z,bl);
                         h2 := f^.getline (z,bl+1);
                         rc := rc + getlength(gv(h1.x,h1.y,h1.z)-gv(h2.x,h2.y,h2.z));
                    end;
                    h1 := f^.getline (z,1);
                    h2 := f^.getline (z,l);
                    rl := getlength(gv(h1.x,h1.y,h1.z)-gv(h2.x,h2.y,h2.z));
                    if rl <> 0.0 then my.push (rc/rl)
                                 else my.push (0);
               end
               else if l = 2 then  { vectors }
               begin
                    my.push (1);
               end
               else my.push (0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('tortuosity','lines');

     _cursor_arrow;
end;

{ *********************** Show sub length 3D ********************************* }

procedure proc_show_lsublength_3d (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,l,bl : integer;
    h1,h2 : hyper;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 1 then { lines }
               begin
                    for bl := 1 to l-1 do
                    begin
                         h1 := f^.getline (z,bl);
                         h2 := f^.getline (z,bl+1);
                         my.push (getlength(gv(h1.x,h1.y,h1.z)-gv(h2.x,h2.y,h2.z)));
                    end;
               end
               else my.push (0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line sub lengths','lines');

     _cursor_arrow;
end;

{ *********************** Show length 3D ************************************* }

procedure proc_show_llength_3d (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,l,bl : integer;
    rl : real;
    h1,h2 : hyper;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 2 then { lines }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         h1 := f^.getline (z,bl);
                         h2 := f^.getline (z,bl+1);
                         rl := rl + getlength(gv(h1.x,h1.y,h1.z)-gv(h2.x,h2.y,h2.z));
                    end;
                    my.push (rl);
               end
               else if l = 2 then  { vectors }
               begin
                    h1 := f^.getline (z,1);
                    h2 := f^.getline (z,2);
                    rl := getlength(gv(h1.x,h1.y,h1.z)-gv(h2.x,h2.y,h2.z));
                    my.push (rl);
               end
               else my.push (0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line lengths','lines');

     _cursor_arrow;
end;

{ *************************** Neighbor distances (lines) ********************* }

procedure proc_show_lmindistance (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,c,l,bl : integer;
    d,n : real;
    my1 : tpolyreal;
begin
     my1 := Default(tpolyreal);

     if f^.getlinelength > 1 then
     begin
          my1.init (f^.getpointlength);
          l := 1;
          for z := 1 to f^.getpointlength do
          begin
               if my1.get (z) = 0 then
               begin
                    d := infinity;
                    for c := 1 to f^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((f^.getpoint (z)-f^.getpoint(c)));
                              if d > n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my1.put (z,d);
                    my1.put (l,d);
               end;
               progress ('Calculate neighbors (lines)',z/f^.getpointlength);
          end;
          progress;
          my.newlength (f^.getlinelength);
          my.clear;
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength(z);
               if l > 0 then
               begin
                    for bl := 1 to l do
                    begin
                         my.put (z,my.get(z)+my1.get(f^.getpline(z,bl)));
                    end;
               end;
          end;
          my1.done;
          my.sort;
     end
     else my.newlength (0);
end;
begin
     _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line distances','lines');

     _cursor_arrow;
end;

procedure proc_show_lmaxdistance (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,c,l,bl : integer;
    d,n : real;
    my1 : tpolyreal;
begin
     my1 := Default(tpolyreal);

     if f^.getlinelength > 1 then
     begin
          my1.init (f^.getpointlength);
          l := 1;
          for z := 1 to f^.getpointlength do
          begin
               if my1.get (z) = 0 then
               begin
                    d := 0;
                    for c := 1 to f^.getpointlength do
                    begin
                         if z <> c then
                         begin
                              n := getlength((f^.getpoint (z)-f^.getpoint(c)));
                              if d < n then
                              begin
                                   d := n;
                                   l := c;
                              end;
                         end;
                    end;
                    my1.put (z,d);
                    my1.put (l,d);
               end;
               progress ('Calculate neighbors (lines)',z/f^.getpointlength);
          end;
          progress;
          my.newlength (f^.getlinelength);
          my.clear;
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength(z);
               if l > 0 then
               begin
                    for bl := 1 to l do
                    begin
                         my.put (z,my.get(z)+my1.get(f^.getpline(z,bl)));
                    end;
               end;
          end;
          my1.done;
          my.sort;
     end
     else my.newlength (0);
end;
begin
     _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line max distances','lines');

     _cursor_arrow;
end;

{ *********************** Show points **************************************** }

procedure proc_show_lpoints (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
    rl : real;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin

          for z := 1 to f^.getlinelength do
          begin
               rl := f^.getalllinepointlength (z);
               my.push (rl);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line points','lines');

     _cursor_arrow;
end;

{ *********************** Show sub length ************************************ }

procedure proc_show_lsublength (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,l,bl : integer;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 1 then { lines }
               begin
                    for bl := 1 to l-1 do
                    begin
                         my.push (getlength(f^.getline (z,bl)-f^.getline (z,bl+1)));
                    end;
               end
               else my.push (0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line sub lengths','lines');

     _cursor_arrow;
end;

{ *********************** Show length **************************************** }

procedure proc_show_llength (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z,l,bl : integer;
    rl : real;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               if l > 2 then { lines }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         rl := rl + getlength(f^.getline (z,bl)-f^.getline (z,bl+1));
                    end;
                    my.push (rl);
               end
               else if l = 2 then  { vectors }
               begin
                    rl := getlength(f^.getline (z,1)-f^.getline (z,2));
                    my.push (rl);
               end
               else my.push (0);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('line lengths','lines');

     _cursor_arrow;
end;

{ ********************************* Axis values ****************************** }

procedure proc_show_x_values (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getpointlength do
          begin
               my.push (f^.getpoint(z).x);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('values','points');

     _cursor_arrow;
end;

procedure proc_show_y_values (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getpointlength do
          begin
               my.push (f^.getpoint(z).y);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('values','points');

     _cursor_arrow;
end;

procedure proc_show_z_values (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getpointlength do
          begin
               my.push (f^.getpoint(z).z);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('values','points');

     _cursor_arrow;
end;

procedure proc_show_t_values (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getpointlength do
          begin
               my.push (f^.getpoint(z).t);
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('values','points');

     _cursor_arrow;
end;

{ ***** }

procedure proc_show_material_values (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolyreal);
var z : integer;
begin
     my.newlength (0);
     if f^.getlinelength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               my.push (f^.getallmaterial(z));
          end;
          my.sort;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,stat[1])
                 else stat[1].newlength(0);
     _update;
     if state[2] then run (@green,stat[2])
                 else stat[2].newlength(0);
     _update;
     if state[3] then run (@blue,stat[3])
                 else stat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,stat[4])
                 else stat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,stat[5])
                 else stat[5].newlength(0);
     _update;
     if state[6] then run (@purple,stat[6])
                 else stat[6].newlength(0);
     _update;
     _make_visible ('values','lines');

     _cursor_arrow;
end;

{ **************************************************************************** }
{ ******************************* Geometry 2 ********************************* }
{ **************************************************************************** }

procedure _make_visible2 (const name,objects : utf16);
var s : utf16;
procedure run (const layer : utf16;var my : tpolycomplex);
var w : integer;
    l : tpolyreal;
begin
     l := Default (tpolyreal);

     if my.length > 0 then
     begin
          l.init;
          for w := 1 to my.length do l.push (my.get(w).y);
          s := s + getstat (layer,name,l);
          l.done;
     end;
end;
begin
     { Report }
     statname := name;
     statobjects := objects;
     stattype := 2;
     s := '';
     if state[1] then run ('Red',cstat[1]);
     _update;
     if state[2] then run ('Green',cstat[2]);
     _update;
     if state[3] then run ('Blue',cstat[3]);
     _update;
     if state[4] then run ('Yellow',cstat[4]);
     _update;
     if state[5] then run ('Cyan',cstat[5]);
     _update;
     if s = '' then _settext (text_report,'No data!')
               else _settext (text_report,s);
     _update;
{ Graph }
     screen_histo.done;
     screen_histo.init (area_shot^.allocation.width,area_shot^.allocation.height);
     screen_histo.left (name+' [units]');
     screen_histo.bottom (objects);
     screen_histo.setstyle (5);
     screen_histo.histogram (cstat[6],cstat[5],cstat[4],cstat[3],cstat[2],cstat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
     screen_histo.render;
     _setpage (subnote_show,2);
end;

{ ********************************* Show area ******************************** }

procedure proc_show_areax (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.x = v.x then rl := rl + (v.z+u.z)*(u.y-v.y);
                    end;
                    if abs(rl) > 0.0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.x,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible2 ('area','areas along x-axis');

     _cursor_arrow;
end;

procedure proc_show_areay (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getlinelength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.y = v.y then rl := rl + (v.x+u.x)*(u.z-v.z);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.y,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible2 ('area','areas along y-axis');

     _cursor_arrow;
end;

procedure proc_show_areaz (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getlinelength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.z = v.z then rl := rl + (v.x+u.x)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.z,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible2 ('area','areas along z-axis');

     _cursor_arrow;
end;

{ **************************************************************************** }

procedure _make_visible3 (const name,objects : utf16);
var s : utf16;
procedure run (const layer : utf16;var my : tpolycomplex);
var o : real;
    w : integer;
    u,v : complex;
    l : tpolyreal;
begin
     l := Default (tpolyreal);

     if my.length > 0 then
     begin
          { calculation of volume from areas }
          if my.length > 1 then
          begin
               u := my.get (1);
               for w := 2 to my.length do
               begin
                    v := my.get(w);
                    o := (v.x-u.x)*((v.y+u.y)/2); { Mittelwert zwischen zwei Werten }
                    my.put (w-1,gc(((v.x+u.x)/2),o));
                    u := v;
               end;
               my.newlength (my.length-1);
          end;
          l.init;
          for w := 1 to my.length do l.push (my.get(w).y);
          s := s + getstat (layer,name,l);
          l.done;
     end;
end;
begin
     { Report }
     statname := name;
     statobjects := objects;
     stattype := 3;
     s := '';
     if state[1] then run ('Red',cstat[1]);
     _update;
     if state[2] then run ('Green',cstat[2]);
     _update;
     if state[3] then run ('Blue',cstat[3]);
     _update;
     if state[4] then run ('Yellow',cstat[4]);
     _update;
     if state[5] then run ('Cyan',cstat[5]);
     _update;
     if state[6] then run ('Purple',cstat[6]);
     _update;
     if s = '' then _settext (text_report,'No data!')
               else _settext (text_report,s);
     _update;
{ Graph }
     screen_histo.done;
     screen_histo.init (area_shot^.allocation.width,area_shot^.allocation.height);
     screen_histo.left (name+' [units]');
     screen_histo.bottom (objects);
     screen_histo.setstyle (5);
     screen_histo.histogram (cstat[6],cstat[5],cstat[4],cstat[3],cstat[2],cstat[1],Hpurple,Hcyan,Hyellow,Hblue,Hgreen,Hred);
     screen_histo.render;
     _setpage (subnote_show,2);
end;

{ *********************** Show volume **************************************** }

procedure proc_show_volumex (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getlinelength > 1 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.x = v.x then rl := rl + (v.z+u.z)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.x,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible3 ('volume','volumes along x-axis');

     _cursor_arrow;
end;

procedure proc_show_volumey (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getlinelength > 1 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.y = v.y then rl := rl + (v.x+u.x)*(u.z-v.z);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.y,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible3 ('volume','volumes along y-axis');

     _cursor_arrow;
end;

procedure proc_show_volumez (p1,macro : gtk_pointer); cdecl;
procedure run (f : pcloud;var my : tpolycomplex);
var z,l,bl : integer;
    rl : real;
    u,v : hyper;
begin
     my.newlength (0);
     if f^.getpointlength > 0 then
     begin
          for z := 1 to f^.getlinelength do
          begin
               l := f^.getalllinepointlength (z);
               v := Hzero;
               if l > 2 then { lines }
               if  finput^.getline (z,1) = finput^.getline (z,l) then { closed }
               begin
                    rl := 0;
                    for bl := 1 to l-1 do
                    begin
                         u := f^.getline (z,bl);
                         v := f^.getline (z,bl+1);
                         if u.z = v.z then rl := rl + (v.x+u.x)*(u.y-v.y);
                    end;
                    if abs(rl) > 0 then
                    begin
                         rl := abs(rl / 2);
                         my.push (gc(v.z,rl));
                    end;
               end;
          end;
          my.sortx;
     end;
end;
begin
{ Neighbors }
    _cursor_watch;

     if state[1] then run (@red,cstat[1])
                 else cstat[1].newlength(0);
     _update;
     if state[2] then run (@green,cstat[2])
                 else cstat[2].newlength(0);
     _update;
     if state[3] then run (@blue,cstat[3])
                 else cstat[3].newlength(0);
     _update;
     if state[4] then run (@yellow,cstat[4])
                 else cstat[4].newlength(0);
     _update;
     if state[5] then run (@cyan,cstat[5])
                 else cstat[5].newlength(0);
     _update;
     if state[6] then run (@purple,cstat[6])
                 else cstat[6].newlength(0);
     _update;
     _make_visible3 ('volume','volumes along z-axis');

     _cursor_arrow;
end;

{ **************************************************************************** }

procedure proc_clipboard_red (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[1].length > 0 then
               begin
                    for x := 1 to stat[1].length do
                    begin
                         message := message + getstring(stat[1].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[1].length > 0 then
               begin
                    for x := 1 to cstat[1].length do
                    begin
                         message := message + getstring(cstat[1].get(x).x) + #9 + getstring(cstat[1].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_green (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[2].length > 0 then
               begin
                    for x := 1 to stat[2].length do
                    begin
                         message := message + getstring(stat[2].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[2].length > 0 then
               begin
                    for x := 1 to cstat[2].length do
                    begin
                         message := message + getstring(cstat[2].get(x).x) + #9 + getstring(cstat[2].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_blue (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[3].length > 0 then
               begin
                    for x := 1 to stat[3].length do
                    begin
                         message := message + getstring(stat[3].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[3].length > 0 then
               begin
                    for x := 1 to cstat[3].length do
                    begin
                         message := message + getstring(cstat[3].get(x).x) + #9 + getstring(cstat[3].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_yellow (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[4].length > 0 then
               begin
                    for x := 1 to stat[4].length do
                    begin
                         message := message + getstring(stat[4].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[4].length > 0 then
               begin
                    for x := 1 to cstat[4].length do
                    begin
                         message := message + getstring(cstat[4].get(x).x) + #9 + getstring(cstat[4].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_cyan (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[5].length > 0 then
               begin
                    for x := 1 to stat[5].length do
                    begin
                         message := message + getstring(stat[5].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[5].length > 0 then
               begin
                    for x := 1 to cstat[5].length do
                    begin
                         message := message + getstring(cstat[5].get(x).x) + #9 + getstring(cstat[5].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_purple (p1,macro : gtk_pointer); cdecl;
var message : utf16;
    x : integer;
begin
     message := '';
     case stattype of
          1 :
          begin
               if stat[6].length > 0 then
               begin
                    for x := 1 to stat[6].length do
                    begin
                         message := message + getstring(stat[6].get(x)) + #10;
                    end;
               end;
          end;
          2,3 :
          begin
               if cstat[6].length > 0 then
               begin
                    for x := 1 to cstat[6].length do
                    begin
                         message := message + getstring(cstat[6].get(x).x) + #9 + getstring(cstat[6].get(x).y) + #10;
                    end;
               end;
          end;
     end;
     _clipboard_set_text (message);
end;

procedure proc_clipboard_image (p1,macro : gtk_pointer); cdecl;
begin
{     gdk_pixbuf_new
     gtk_clipboard_set_image (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), );
     gtk_clipboard_store(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));}
end;

procedure proc_clipboard_report (p1,macro : gtk_pointer); cdecl;
var message : utf16;
begin
     message := _gettext (text_report);
     _clipboard_set_text (message);
end;

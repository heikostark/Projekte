{ **************************************************************************** }
{ ******************************** Transform********************************** }
{ **************************************************************************** }

{ **************************************************************************** }

procedure proc_transform_object; cdecl;
begin inc (input); if input > 6 then input := 1; updating; end;

procedure proc_transform_objectedit; cdecl;
begin inc (inputedit); if inputedit > 6 then inputedit := 1; updating; end;

procedure proc_screen; cdecl;
begin inc (screen); if screen > 5 then screen := 1; updating; drawing; end;

procedure proc_screen1; cdecl;
begin screen := 1; updating; drawing; end;

procedure proc_screen2; cdecl;
begin screen := 2; updating; drawing; end;

procedure proc_screen4; cdecl;
begin screen := 4; updating; drawing; end;

procedure proc_screen3; cdecl;
begin screen := 3; updating; drawing; end;

procedure proc_screen5; cdecl;
begin screen := 5; updating; drawing; end;

{ ****************************** Spiegeln ************************************ }

procedure fmx; cdecl;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(-1,1,1,1)*my^.getpoint(z));
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure fmy; cdecl;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,-1,1,1)*my^.getpoint(z));
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;

     calculating;
     updating;
     drawing;
end;

procedure fmz; cdecl;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,1,-1,1)*my^.getpoint(z));
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure fmt; cdecl;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,gethyper(1,1,1,-1)*my^.getpoint(z));
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

{ ****************************** Skalieren *********************************** }

procedure proc_scale; cdecl;
var v : hyper;
    s : string;
procedure run (my : ptline);
var z : integer;
    u : hyper;
begin
     if my^.getpointlength > 0 then
     begin
          u := v*centerall+centerall;
          for z := 1 to my^.getpointlength do my^.putpoint (z,v*my^.getpoint(z)-u);
     end;
end;
begin
     v := _gethyper (transform_scale);
     s := getstring (v);
     _setedit (transform_scale,s);
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_scale_objects; cdecl;
var v : hyper;
    s : string;
procedure run (my : ptline);
var z,o,l,p : integer;
    list : tpolyhyper;
    u : hyper;
begin
     if my^.getobjectlength > 0 then
     begin
          list.init;
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    u := list.get(o)-v*list.get(o);
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              my^.putobject (o,l,p,v*my^.getobject(o,l,p)+u);
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     v := _gethyper (transform_scale2);
     s := getstring (v);
     _setedit (transform_scale2,s);
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

{ ****************************** Bewegen ************************************* }

procedure move (x,y : real);
var v : hyper;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do my^.putpoint (z,v+my^.getpoint(z));
end;
begin
     case screen of
          1 : v := gh (x,y,0,0);
          2 : v := gh (x,0,y,0);
          4 : v := gh (0,x,0,y);
          3 : v := gh (0,x,y,0);
          5 : v := gh (0,0,x,y);
          else v := Vzero;
     end;
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure movel; cdecl;
begin step := _getreal (edit2); move (-step,0); end;

procedure mover; cdecl;
begin step := _getreal (edit2); move (step,0); end;

procedure moveu; cdecl;
begin step := _getreal (edit2); move (0,step); end;

procedure moved; cdecl;
begin step := _getreal (edit2); move (0,-step); end;

{ ****************************** Rotieren ************************************ }

procedure rotation (center : hyper;rot : real);
procedure run (my : ptline);
var z : integer;
    u,v,winkel: hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             u := v-center;
             case screen of
                  1 : begin
                           winkel := rotatezt (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  2 : begin
                           winkel := rotateyt (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  4 : begin
                           winkel := rotateyz (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  3 : begin
                           winkel := rotatext (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
                  5 : begin
                           winkel := rotatexy (u,rot);
                           my^.putpoint (z,center+winkel);
                      end;
             end;
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
end;

procedure rotl; cdecl;
begin
     grad := _getreal (edit_rotation);
     rotation (Hzero,grad*rad);
     calculating;
     updating;
     drawing;
end;

procedure rotr; cdecl;
begin
     grad := _getreal (edit_rotation);
     rotation (Hzero,-1*grad*rad);
     calculating;
     updating;
     drawing;
end;

procedure rotol; cdecl;
begin
     grad := _getreal (edit_rotation);
     rotation (centerall,grad*rad);
     calculating;
     updating;
     drawing;
end;

procedure rotor; cdecl;
begin
     grad := _getreal (edit_rotation);
     rotation (centerall,-1*grad*rad);
     calculating;
     updating;
     drawing;
end;

{ **************************************************************************** }
{ **************************** Transform + *********************************** }
{ **************************************************************************** }


{ ****************************** Swap Axis *********************************** }

procedure proc_swap_xy; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.y,v.x,v.z,v.t));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_swap_xz; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.z,v.y,v.x,v.t));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_swap_yz; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.x,v.z,v.y,v.t));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_swap_xt; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.t,v.y,v.z,v.x));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_swap_yt; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.x,v.t,v.z,v.y));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

procedure proc_swap_zt; cdecl;
procedure run (my : ptline);
var z : integer;
    v : hyper;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             v := my^.getpoint(z);
             my^.putpoint (z,gh(v.x,v.y,v.t,v.z));
        end;
end;
begin
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
end;

{ ********************************** Center ********************************** }

procedure proc_transform_center; cdecl;
procedure run (my : ptline);
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-centerall);
        end;
end;
begin
     _cursor_watch;
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     _cursor_arrow;
end;

procedure proc_transform_center_objects; cdecl;
procedure run (my : ptline);
var z,o,l,p : integer;
    list : tpolyhyper;
begin
     if my^.getobjectlength > 0 then
     begin
          list.init;
          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    z := 0;
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              list.put (o,my^.getobject(o,l,p)+list.get(o));
                              inc (z);
                         end;
                    end;
                    if z <> 0 then list.put (o,list.get(o)/z);
               end;
          end;

          for o := 1 to my^.getobjectlength do
          begin
               if my^.getobjectlinelength(o) > 0 then
               begin
                    for l := 1 to my^.getobjectlinelength(o) do
                    begin
                         if my^.getlinepointlength(o,l) > 0 then
                         for p := 1 to my^.getlinepointlength(o,l) do
                         begin
                              my^.putobject (o,l,p,my^.getobject(o,l,p)-list.get(o));
                         end;
                    end;
               end;
          end;
          list.done;
     end;
end;
begin
     _cursor_watch;
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
     calculating;
     updating;
     drawing;
     _cursor_arrow;
end;

{ ******************************** Balance *********************************** }

procedure proc_transform_balance; cdecl;
var l,mybalance : real;
    c : complex;
procedure run (my : ptline);
var u,v : hyper;
    p : complex;
    x,y : integer;
begin
     if my^.getpointlength > 0 then
     begin
        for x := 1 to my^.getpointlength do
            for y := 1 to my^.getpointlength do
            begin
                 case screen of
                      1 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.y-v.y);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                          end;
                      2 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.z-v.z);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                          end;
                      4 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.t-v.t);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                      3 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.y-v.y,u.z-v.z);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                      5 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.z-v.z,u.t-v.t);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                 end;
             end;
        end;
end;
begin
     _cursor_watch;
{ Balance }
     l := 0;
     if red_state then run (@red);
     _update;
     if green_state then run (@green);
     _update;
     if blue_state then run (@blue);
     _update;
     if yellow_state then run (@yellow);
     _update;
     if cyan_state then run (@cyan);
     _update;
     if purple_state then run (@purple);
     _update;
{ Rotation }
     mybalance := fullangle(c,Cright,Cup)+pi/2;
     _setedit (edit_rotation,getstring(mybalance*deg));
     rotation (centerall,mybalance);
     _update;
     calculating;
     updating;
     drawing;
     _cursor_arrow;
end;

{ *************************** Center + Balance ******************************* }

procedure proc_transform_adjust; cdecl;
var l,mybalance : real;
    b : integer;
    c : complex;
procedure runc (my : ptline); { Center }
var z : integer;
begin
     if my^.getpointlength > 0 then
        for z := 1 to my^.getpointlength do
        begin
             my^.putpoint (z,my^.getpoint(z)-centerall);
        end;
end;
procedure runb (my : ptline); { Balance }
var u,v : hyper;
    p : complex;
    x,y : integer;
begin
     if my^.getpointlength > 0 then
     begin
        for x := 1 to my^.getpointlength do
            for y := 1 to my^.getpointlength do
            begin
                 case screen of
                      1 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.y-v.y);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                          end;
                      2 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.z-v.z);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                          end;
                      4 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.x-v.x,u.t-v.t);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                      3 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.y-v.y,u.z-v.z);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                      5 : begin
                               u := my^.getpoint (x);
                               v := my^.getpoint (y);
                               p := gc(u.z-v.z,u.t-v.t);
                               if l < getlength(p) then
                               begin
                                    l := getlength(p);
                                    c := p;
                               end;
                           end;
                 end;
             end;
        end;

end;
begin
     _cursor_watch;
     for b := 1 to 6 do
     begin
{ Center }
          if red_state then runc (@red);
          _update;
          if green_state then runc (@green);
          _update;
          if blue_state then runc (@blue);
          _update;
          if yellow_state then runc (@yellow);
          _update;
          if cyan_state then runc (@cyan);
          _update;
          if purple_state then runc (@purple);
          _update;
          calculating;
          _update;
{ Balance }
          l := 0;
          if red_state then runb (@red);
          _update;
          if green_state then runb (@green);
          _update;
          if blue_state then runb (@blue);
          _update;
          if yellow_state then runb (@yellow);
          _update;
          if cyan_state then runb (@cyan);
          _update;
          if purple_state then runb (@purple);
          _update;
{ Rotation }
          mybalance := fullangle(c,Cright,Cup)+pi/2;
          _setedit (edit_rotation,getstring(mybalance*deg));
          rotation (centerall,mybalance);
          _update;
          calculating;
          _update;
          inc (screen);
          if screen > 5 then screen := 1;
     end;
     calculating;
     updating;
     drawing;
     _cursor_arrow;
end;

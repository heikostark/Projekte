{ ******************************** Script ************************************ }

_vbox;
_shrink;
        _hbox;
        _expand;
                bclear := command (@xpm_white_page,' Clear','','','','Clear all',@clear_macro);
                blog := command ('Log','','','','Load log',@log_macro);
                bopen := command (@xpm_open,' Load','','','','Load macro',@load_macro_1);
                bcog := command (@xpm_cog,' Run','','','','Run macro',@run_macro);
                brun := command (@xpm_cog,' (Run)','','','','Run macro without output',@run_hide_macro);
                bkill := command (@xpm_cancel,' Kill','','','','Kill macro',@kill_macro);
                command (@xpm_save,' Save','','','','Save macro',@save_macro_1);
        _endbox;
_fill;
        subnote_macro := _notebook;
        for x := 0 to 5 do
        begin
             _page ('Macro '+getstring(x+1)+' ');
             _shrink;
                    _hbox;
                    _shrink;
                          viewport := _hiddenscrollbox;
                              macro_widget_count[x] := _text (macro_text_count[x]);
                              _justification (2);
                          _endbox;
                          _fill;
                          viewport1 := _showscrollbox;
                              macro_widget[x] := _edittext (macro_text[x]);
                          _endbox;
                    _endbox;
           { line_rows numbers }
                    _syncron (viewport,viewport1);
                    _size (viewport,32,200);
                    s := '';
                    for count := 1 to 998 do s := s + getstring(count,true)+#10;
                    s := s + getstring(999,true);
                    _settext (macro_text_count[x],s);
          { line_rows numbers }
             _endpage;
        end;
        _page ('Syntax ');
              _scrollbox;
{              _eventbox;
              _backcolor ($FFFF,$FFFF,$BFFF);}
                            _vbox;
                            _fill;
                                  _text (syntax);
                                  s := '***** Core commands *****' + #10;
                                  s := s + 'break // terminate' + #10;
                                  s := s + 'ignore // for blocks' + #10;
                                  s := s + 'include file' + #10;
                                  s := s + 'write | writeln | print | echo' + #10;
                                  s := s + 'if | ifall' + #10;
                                  s := s + 'ifnot | ifnotall' + #10;
                                  s := s + 'ifone' + #10;
                                  s := s + 'ifsmaller' + #10;
                                  s := s + 'ifequal' + #10;
                                  s := s + 'ifbigger' + #10;
                                  s := s + 'ifempty' + #10;
                                  s := s + 'ifsame' + #10;
                                  s := s + 'ifnotsame' + #10;
                                  s := s + 'ifnotone' + #10;
                                  s := s + 'ifcontain | ifallcontain' + #10;
                                  s := s + 'ifnotcontain | ifnotallcontain' + #10;
                                  s := s + 'ifonecontain' + #10;
                                  s := s + 'ifnotonecontain' + #10;
                                  s := s + 'if.then | then' + #10;
                                  s := s + 'if.else | else' + #10;
                                  s := s + 'for' + #10;
                                  s := s + 'repeat' + #10;
                                  s := s + 'while' + #10;
                                  s := s + 'store' + #10;
                                  s := s + 'append' + #10;
                                  s := s + 'run' + #10;
                                  s := s + 'execute' + #10;
                                  s := s + 'dump.vars | _.progs | _.stack' + #10;
                                  s := s + #10;

                                  s := s + '***** Operators *****' + #10;
                                  s := s + ':=' + #10;
                                  s := s + '|=' + #10;
                                  s := s + '+=' + #10;
                                  s := s + '-=' + #10;
                                  s := s + '*=' + #10;
                                  s := s + '/=' + #10;
                                  s := s + 'x=' + #10;
                                  s := s + #10;

                                  s := s + '***** Commands *****' + #10;
                                  if macro_self.commandlength > 0 then
                                  begin
                                       list.init;
                                       macro_self.getsortedcommand (list);
                                       if list.length > 0 then
                                       for count := 1 to list.length do
                                       begin
                                            count2 := list.get(count);
                                            t := macro_self.getcommandhelp (count2);
                                            replace (t,'<i>','');
                                            replace (t,'</i>','');
                                            replace (t,#10,#10+#9);
                                            case macro_self.getcommandid (count2) of
                                                 program_block :
                                                 begin
                                                      if macro_self.getcommandinput (count2) <> '' then
                                                      begin
                                                           if t <> '' then s := s + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + ' ... end' + ' // ' + t + #10
                                                                      else s := s + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + ' ... end' + #10;
                                                      end
                                                      else
                                                      begin
                                                           if t <> '' then s := s + macro_self.getcommand (count2) + ' ... end' + ' // ' + t + #10
                                                                      else s := s + macro_self.getcommand (count2) + ' ... end' + #10;
                                                      end;
                                                 end;
                                                 program_procedure :
                                                 begin
                                                      if macro_self.getcommandinput (count2) <> '' then
                                                      begin
                                                           if t <> '' then s := s + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + ' // ' + t + #10
                                                                      else s := s + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + #10;
                                                      end
                                                      else
                                                      begin
                                                           if t <> '' then s := s + macro_self.getcommand (count2) + ' // ' + t + #10
                                                                      else s := s + macro_self.getcommand (count2) + #10;
                                                      end;
                                                 end;
                                                 program_function :
                                                 begin
                                                      if macro_self.getcommandinput (count2) <> '' then
                                                      begin
                                                           if macro_self.getcommandoutput (count2) <> '' then
                                                           begin
                                                                if t <> '' then s := s + macro_self.getcommandoutput (count2) + ' := ' + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + ' // ' + t + #10
                                                                           else s := s + macro_self.getcommandoutput (count2) + ' := ' + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + #10;
                                                           end
                                                           else
                                                           begin
                                                                if t <> '' then s := s + 'var := ' + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + ' // ' + t + #10
                                                                           else s := s + 'var := ' + macro_self.getcommand (count2) + ' ' + macro_self.getcommandinput (count2) + #10;
                                                           end;
                                                      end
                                                      else
                                                      begin
                                                           if macro_self.getcommandoutput (count2) <> '' then
                                                           begin
                                                                if t <> '' then s := s + macro_self.getcommandoutput (count2) + ' := ' + macro_self.getcommand (count2) + ' // ' + t + #10
                                                                           else s := s + macro_self.getcommandoutput (count2) + ' := ' + macro_self.getcommand (count2) + #10;
                                                           end
                                                           else
                                                           begin
                                                                if t <> '' then s := s + 'var := ' + macro_self.getcommand (count2) + ' // ' + t + #10
                                                                           else s := s + 'var := ' + macro_self.getcommand (count2) + #10;
                                                           end;
                                                      end;
                                                 end;
                                                 program_operation : { see above } ;
                                                 program_module : { not used } ;
                                            end;
                                       end;
                                       list.done;
                                  end;
                                  s := s + #10;

                                  s := s + '***** Variables *****' + #10;
                                  if macro_self.constantlength > 0 then
                                  begin
                                       list.init;
                                       macro_self.getsortedconstant(list);
                                       if list.length > 0 then
                                       for count := 1 to list.length do
                                       begin
                                            s := s + macro_self.getconstant(list.get(count)) + ' := ' + macro_self.getconstantvalue(macro_self.getconstant(list.get(count))) + #10;
                                       end;
                                       list.done;
                                  end;

                                  _settext (syntax,s);
                                  _createtag (syntax, 'heading','',true,false);
                                  _createtag (syntax, 'comment','#00F',true,false);
                                  _createtag (syntax, 'weakcomment','#00F',false,false);
                                  _createtag (syntax, 'var','#090',false,false);
                                  _createtag (syntax, 'assignment','#B00',false,false);
                                  _createtag (syntax, 'block','',true,false);
                                  if _gettextlinelength (syntax) > 0 then
                                  begin
                                       for count := 0 to _getedittextlinelength (syntax) do
                                       begin
                                            s := _getbufferline (syntax,count);
                                            _getbufferline (syntax,count,start,ende);
                                            if (pos('*****',s) = 1) then { Heading }
                                            begin
                                                 _applybuffertag (syntax, 'heading', start, ende);
                                            end
                                            else
                                            begin
                                                 if (pos ('//',s) > 0) then { Comment }
                                                 begin
                                                      marke1 := _getbufferpos (syntax, count, pos ('//',s)-1);
                                                      _applybuffertag (syntax, 'comment', marke1, ende);
                                                 end
                                                 else if (pos ('Note: ',s) > 0) then { or Note }
                                                 begin
                                                      _applybuffertag (syntax, 'weakcomment', start, ende);
                                                 end;

                                                 if (pos (' := ',s) > 0) then { Assignment }
                                                 begin
                                                      marke1 := _getbufferpos (syntax, count, pos (' := ',s)-1);
                                                      marke2 := _getbufferpos (syntax, count, pos (' := ',s)-1+4);
                                                      _applybuffertag (syntax, 'var', start, marke1);
                                                      _applybuffertag (syntax, 'assignment', marke1,marke2);
                                                 end
                                                 else if (pos (' ... end',s) > 0) then { Block }
                                                 begin
                                                      marke1 := _getbufferpos (syntax, count, pos (' ... ',s)-1);
                                                      marke2 := _getbufferpos (syntax, count, pos (' ... ',s)-1+5);
                                                      _applybuffertag (syntax, 'block', start, marke1);
                                                      _applybuffertag (syntax, 'block', marke2,ende);
                                                 end;
                                            end;
                                       end;
                                  end;
                            _endbox;
{              _endbox;}
              _endbox;
        _endpage;
        _endnotebook;
_endbox;
